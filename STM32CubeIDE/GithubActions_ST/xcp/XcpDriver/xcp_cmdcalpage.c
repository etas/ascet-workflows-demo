/**
*
* \file
*
* \brief XCP calibration commands.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmdcalpage.c 17051 2009-11-24 09:37:39Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#if defined( XCP_ENABLE ) && defined( XCP_ENABLE_CALPAG )

/**
 * This function implements the XCP command SET_CAL_PAGE as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdSetCalPage(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  mode;
        uint8  segment;
        uint8  calPage;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;
    Xcp_CalPageErr             calPageErr  = CALPAGE_OK;
    uint                       i;

    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    if( !( pCmdPacket->mode & 0x03 ) )
    {
        /* The command is not requesting a valid mode. */
        pTxPacket->data[0] = XCP_ERR_MODE_NOT_VALID;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    if( pCmdPacket->mode & 0x01 )
    {
        /* We must set the ECU page. */
        if( pCmdPacket->mode & 0x80 )
        {
            /* We must make the change on all segments. */
            calPageErr = XcpApp_SetEcuCalPageAllSegs  ( pCmdPacket->calPage );
        }
        else
        {
            /* We must make the change on a single segment. */
    		calPageErr = XcpApp_SetEcuCalPage         ( pCmdPacket->segment, pCmdPacket->calPage );
        }
    }
    if( ( CALPAGE_OK == calPageErr ) && ( pCmdPacket->mode & 0x02 ) )
    {
        /* We must set the tool page. */

        if( pCmdPacket->mode & 0x80 )
        {
            /* We must make the change on all segments. */
            calPageErr = XcpApp_SetToolCalPageAllSegs( pCmdPacket->calPage );

            if( CALPAGE_OK == calPageErr )
            {
                for( i = 0; i < pSessionCfg->numSegs; ++i )
                {
                    /* Note that we assume XcpApp_SetToolCalPageAllSegs() will have validated pCmdPacket->calPage. */
                    pSessionCfg->pSegStates[ i ].toolPage = (uint8)( pCmdPacket->calPage );
                }
            }
        }
        else
        {
            /* We must make the change on a single segment. */
            calPageErr = XcpApp_SetToolCalPage( pCmdPacket->segment, pCmdPacket->calPage );

            if( CALPAGE_OK == calPageErr )
            {
                /* Note that we assume XcpApp_SetToolCalPage() will have validated pCmdPacket->segment and pCmdPacket->calPage. */
                pSessionCfg->pSegStates[ pCmdPacket->segment ].toolPage = (uint8)( pCmdPacket->calPage );
            }
        }
    }

    switch( calPageErr )
    {
    case CALPAGE_OK:
        pTxPacket->pid = XCP_PID_RESPONSE;
        *pTxPacketSize = 1;
        break;
    case CALPAGE_PAGEINVALID:
        pTxPacket->data[0]  = XCP_ERR_PAGE_NOT_VALID;
        break;
    case CALPAGE_SEGINVALID:
        pTxPacket->data[0]  = XCP_ERR_SEGMENT_NOT_VALID;
        break;
    case CALPAGE_REQUESTINVALID:
        pTxPacket->data[0]  = XCP_ERR_MODE_NOT_VALID;
    }
    
    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command GET_CAL_PAGE as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdGetCalPage(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  accessMode;
        uint8  segment;
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  reserved1;
        uint8  reserved2;
        uint8  calPage;
    } ) RespPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const        pRespPacket = (RespPacket_t*) pTxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;

    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    if( pCmdPacket->segment >= pSessionCfg->numSegs )
    {
        /* Segment not valid */
        pTxPacket->data[0]   = XCP_ERR_SEGMENT_NOT_VALID;
    }
    else if( pCmdPacket->accessMode == 0x01 )
    {
        /* Get ECU page */
        pRespPacket->calPage = XcpApp_GetEcuCalPage( pCmdPacket->segment );
        pRespPacket->pid     = XCP_PID_RESPONSE;
        *pTxPacketSize       = 4;
    }
    else if( pCmdPacket->accessMode == 0x02 )
    {
        /* Get Tool page */
        pRespPacket->calPage = pSessionCfg->pSegStates[ pCmdPacket->segment ].toolPage;
        pRespPacket->pid     = XCP_PID_RESPONSE;
        *pTxPacketSize       = 4;
    }
    else
    {
        /* Mode not valid */
        pTxPacket->data[0]   = XCP_ERR_MODE_NOT_VALID;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the XCP command GET_PAG_PROCESSOR_INFO as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdGetPagProcInfo(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  numSegs;
        uint8  pageProps;
    } ) RespPacket_t;

    RespPacket_t* const pRespPacket = (RespPacket_t*)pTxPacket;

    pRespPacket->pid       = XCP_PID_RESPONSE;
    pRespPacket->numSegs   = Xcp_SessionConfigs[ sessionId ].numSegs;
    pRespPacket->pageProps = 0x01;                      /* FREEZE_SUPPORTED */
    *pTxPacketSize         = 3;

    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

/**
 * This function implements the XCP command COPY_CAL_PAGE as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - 0                             The user application is processing a page copy request asynchronously. The command processor will
 *                                  mark this command as being pending and will process it again on the next tick.
 *                                  No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdCopyCalPage(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  sourceSeg;
        uint8  sourcePage;
        uint8  destSeg;
        uint8  destPage;
    } ) CmdPacket_t;

    const CmdPacket_t* const pCmdPacket  = (CmdPacket_t*)pRxPacket;
    Xcp_CalMemState          copyResult;
    uint                     retVal      = XCP_RX_READY | XCP_TX_READY;

    if( prevCmd != XCP_CMD_CURR_CMD )
    {
        /* This is the first time we have processed this command packet, so we ask the application to copy the page. */
        copyResult = XcpApp_CalPageCopy( pCmdPacket->destSeg, pCmdPacket->destPage, pCmdPacket->sourceSeg, pCmdPacket->sourcePage );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * asked the application to copy the page.
         * 
         * Now we check to see what progress the application has made. */
        copyResult = XcpApp_CalMemGetRequestState();
    }

    *pTxPacketSize = 2;
    pTxPacket->pid = XCP_PID_ERROR;

    switch( copyResult )
    {
        case CALMEM_FINISHED:
            /* The application has finished copying the page. */
            pTxPacket->pid = XCP_PID_RESPONSE;
            *pTxPacketSize = 1;
            break;

        case CALMEM_BUSY:
            /* The application has not yet finished copying the page.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal = 0;
            *pTxPacketSize = 0;
            break;

        case CALMEM_PAGENOTVALID:
            pTxPacket->data[0] = XCP_ERR_PAGE_NOT_VALID;
            break;

        case CALMEM_SEGNOTVALID:
            pTxPacket->data[0] = XCP_ERR_SEGMENT_NOT_VALID;
            break;

        case CALMEM_REJECTED:
            /* The application is temporarily unable to write the data to memory. The master may re-try. */
            pTxPacket->data[0] = XCP_ERR_CMD_BUSY;
            break;

        default:
            pTxPacket->data[0] = XCP_ERR_WRITE_PROTECTED;
    }

    return retVal;
}

#ifdef XCP_ENABLE_PAGEFREEZE

/**
 * This function implements the XCP command SET_SEGMENT_MODE as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdSetSegmentMode(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  mode;
        uint8  segment;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;

    if( pCmdPacket->segment < pSessionCfg->numSegs )
    {
        /* Set the segment mode, masking any unused bits. */
        pSessionCfg->pSegStates[ pCmdPacket->segment ].mode = pCmdPacket->mode & XCP_SEGMODE_FREEZE;

        pTxPacket->pid = XCP_PID_RESPONSE;
        *pTxPacketSize = 1;
    }
    else
    {
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        pTxPacket->pid     = XCP_PID_ERROR;
        *pTxPacketSize     = 2;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command GET_SEGMENT_MODE as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdGetSegmentMode(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  reserved;
        uint8  segment;
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  reserved;
        uint8  mode;
    } ) RespPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const        pRespPacket = (RespPacket_t*) pTxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;

    if( pCmdPacket->segment < pSessionCfg->numSegs )
    {
        /* Get the segment mode, masking any unused bits. */
        pRespPacket->pid    = XCP_PID_RESPONSE;
        pRespPacket->mode   = pSessionCfg->pSegStates[ pCmdPacket->segment ].mode & XCP_SEGMODE_FREEZE;
        *pTxPacketSize      = 3;
    }
    else
    {
        pTxPacket->data[0]  = XCP_ERR_OUT_OF_RANGE;
        pTxPacket->pid      = XCP_PID_ERROR;
        *pTxPacketSize      = 2;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE_PAGEFREEZE */


#endif /* XCP_ENABLE && XCP_ENABLE_CALPAG */
