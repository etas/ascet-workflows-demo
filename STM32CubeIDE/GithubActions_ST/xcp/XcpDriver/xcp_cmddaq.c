/**
*
* \file
*
* \brief XCP DAQ commands.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmddaq.c 22434 2011-04-28 08:29:05Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#ifdef XCP_ENABLE

#define DAQ_CONFIG_TYPE         0x01
#define PRESCALER_SUPPORTED     0x02
#define RESUME_SUPPORTED        0x04
#define BIT_STIM_SUPPORTED      0x08
#define TIMESTAMP_SUPPORTED     0x10
#define PID_OFF_SUPPORTED       0x20
#define NO_OVERLOAD_INDICATION  0x00

/**
 * This function implements the XCP command CLEAR_DAQ_LIST as described in the XCP specification.
 *
 * The function stops the DAQ list, then resets all state associated with the DAQ list.
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
uint XCP_FN_TYPE Xcp_CmdClearDaqList(
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
        uint16 daqListId;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket      = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg     = Xcp_SessionConfigs + sessionId;
    Xcp_DaqConfig_t* const     pDaqConfig      = pSessionCfg->pDaqConfigs + pCmdPacket->daqListId;
    Xcp_Daq_t* const           pDaqState       = pSessionCfg->pDaqStates + pCmdPacket->daqListId;
    const uint                 totOdtEntries   = pDaqConfig->numOdt * pDaqConfig->numOdtEntries;

    if( pCmdPacket->daqListId < (uint)pSessionCfg->numStatDaqLists + (uint)Xcp_Sessions[ sessionId ].numDynDaqLists )
    {
        /* The Daq List Number is valid. */

        /* Clear the state of the DAQ list. */
        /* TEMPORARY WORKAROUND. At this point we should call Xcp_ResetDaqList(); however, this conflicts with the behaviour which
         * the ES910 XCP master expects from an XCP slave. The ES910 XCP master executes SET_DAQ_LIST_MODE before CLEAR_DAQ_LIST and
         * therefore expects that CLEAR_DAQ_LIST will not reset the mode of the DAQ list.
         * As a temporary workround until the ES910 XCP master is fixed, we replace the call to Xcp_ResetDaqList() with the
         * following two lines. */
        pDaqState->daqListMode &= ~XCP_DAQLISTMODE_RUNNING;
        pDaqState->maxOdtIdUsed = 0;
        /* Xcp_ResetDaqList( sessionId, pCmdPacket->daqListId ); */

        /* Clear all the ODT entries of the daq list. */

        Xcp_MemZero( (Xcp_StatePtr8)( pSessionCfg->pOdtEntryAddrs + pDaqConfig->idxDaqStart ), totOdtEntries * sizeof( Xcp_OdtEntryAddr_t ) );
        Xcp_MemZero( (Xcp_StatePtr8)( pSessionCfg->pOdtEntryCfgs  + pDaqConfig->idxDaqStart ), totOdtEntries * sizeof( uint8 ) );

        /* Send positive response. */
        pTxPacket->pid = XCP_PID_RESPONSE;
        *pTxPacketSize = 1;
    }
    else
    {
        /* Daq List Number is not valid; send a negative response with XCP_ERR_OUT_OF_RANGE */
        pTxPacket->pid     = XCP_PID_ERROR;
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        *pTxPacketSize     = 2;
    }
    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command SET_DAQ_PTR as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdSetDaqPtr(
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
        uint16 daqListId;
        uint8  odtId;
        uint8  odtEntryId;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;
    Xcp_Session_t* const       pSession    = Xcp_Sessions + sessionId;
    const uint                 daqListId   = pCmdPacket->daqListId;
    const uint                 odtId       = pCmdPacket->odtId;
    const uint                 odtEntryId  = pCmdPacket->odtEntryId;

    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    if( daqListId < (uint)pSessionCfg->numStatDaqLists + (uint)pSession->numDynDaqLists )
    {
        /* The DAQ list number is valid. */

        if( !( pSessionCfg->pDaqStates[ daqListId ].daqListMode & XCP_DAQLISTMODE_RUNNING ) )
        {
            /* The DAQ list is not running, so it is safe to modify it. */

            /* Check the IDs of requested ODT and ODT entry. The check varies according to whether the session uses
             * dynamic DAQ lists. */
            if( ( pSessionCfg->maxDynDaqLists == 0 &&
                  odtId < pSessionCfg->pDaqConfigs[ daqListId ].numOdt &&
                  odtEntryId < pSessionCfg->pDaqConfigs[ daqListId ].numOdtEntries )
#ifdef XCP_ENABLE_DYNDAQ
                ||
                ( pSessionCfg->maxDynDaqLists > 0 &&
                  odtId < pSessionCfg->pDaqDynConfigs[ daqListId ].numOdt &&
                  odtEntryId < pSessionCfg->pDaqDynConfigs[ daqListId ].odtEntryNums[ odtId ] )
#endif /* XCP_ENABLE_DYNDAQ */
                )
            {
                /* Store the specified ODT and ODT entry IDs */
                pSession->ctDaqListId  = (uint16)daqListId;
                pSession->ctOdtId      = (uint8)odtId;
                pSession->ctOdtEntryId = (uint8)odtEntryId;

                pTxPacket->pid = XCP_PID_RESPONSE;
                *pTxPacketSize = 1;
            }
            else
            {
                /* Either the ODT ID or the ODT entry ID is invalid. */
                pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;

                /* We no longer know what the current DAQ list is. */
                pSession->ctDaqListId = XCP_DAQLIST_UNDEF;
            }
        }
        else
        {
            /* The DAQ list is running; send a negative response with XCP_ERR_DAQ_ACTIVE. */
            pTxPacket->data[0] = XCP_ERR_DAQ_ACTIVE;
        }
    }
    else
    {
        /* The DAQ list number is invalid; send a negative response. */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;

        /* We no longer know what the current DAQ list is. */
        pSession->ctDaqListId = XCP_DAQLIST_UNDEF;
    }

    return (XCP_RX_READY | XCP_TX_READY);
}

/**
 * This function implements the XCP command WRITE_DAQ as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdWriteDaq(
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
        uint8  bitOffset;
        uint8  odtEntryLen;
        uint8  odtEntryAddrExt;
        uint32 odtEntryAddr;
    } ) CmdPacket_t;

    Xcp_SessionConfig_t* const pSessionCfg     = Xcp_SessionConfigs + sessionId;
    Xcp_Session_t* const       pSession        = Xcp_Sessions + sessionId;
    Xcp_DaqConfig_t*           pDaqCfg;
    uint32                     idxCurrOdtEntry;
    CmdPacket_t* const         pCmdPacket      = (CmdPacket_t*)pRxPacket;
    Xcp_StatePtr8              pMaxOdtIdUsed;

    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    /* Do we have a current DAQ list (set via SET_DAQ_PTR)? */
    if( XCP_DAQLIST_UNDEF == pSession->ctDaqListId )
    {
        pTxPacket->data[0] = XCP_ERR_WRITE_PROTECTED;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    pDaqCfg       = pSessionCfg->pDaqConfigs + pSession->ctDaqListId;
    pMaxOdtIdUsed = &( pSessionCfg->pDaqStates[ pSession->ctDaqListId ].maxOdtIdUsed );

    /* Is the specified ODT entry too long, or is the memory region specified by the master unsuitable for measurement/stimulation? */
    if( pCmdPacket->odtEntryLen > pSessionCfg->maxOdtEntryLen ||
        !XcpApp_IsRegionMeasurable( pCmdPacket->odtEntryAddr, pCmdPacket->odtEntryAddrExt, pCmdPacket->odtEntryLen ) )
    {
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    /* Is the DAQ list running, and therefore not able to be modified? */
    if( pSessionCfg->pDaqStates[ pSession->ctDaqListId ].daqListMode & XCP_DAQLISTMODE_RUNNING )
    {
        pTxPacket->data[0] = XCP_ERR_DAQ_ACTIVE;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    /* This is an index into any array which has 1 element per ODT entry for all ODTs in all DAQ lists.
     *
     * In the case of a dynamic DAQ, the array has space for each DAQ list to have its maximum possible number
     * of ODTs and ODT entries. If the dynamic DAQ uses fewer than the maximum, the array will be sparsely
     * populated.
     */
    idxCurrOdtEntry =   pDaqCfg->idxDaqStart                            /*   Index for start of DAQ list                                */
                      + ( pDaqCfg->numOdtEntries * pSession->ctOdtId )  /* + num of array elements in previous ODTs in current DAQ list */
                      + pSession->ctOdtEntryId;                         /* + num of array elements in current ODT in current DAQ list   */

    /* Store the address and length (or bit offset) of the specified ODT entry. */
    if( pCmdPacket->bitOffset > 0x1f )
    {
        /* The ODT entry describes a whole number of bytes. */
        pSessionCfg->pOdtEntryCfgs[ idxCurrOdtEntry ]  = XCP_PACK_ODTENTRYCFG_BYTE ( pCmdPacket->odtEntryAddr, pCmdPacket->odtEntryAddrExt, pCmdPacket->odtEntryLen );
        pSessionCfg->pOdtEntryAddrs[ idxCurrOdtEntry ] = XCP_PACK_ODTENTRYADDR_BYTE( pCmdPacket->odtEntryAddr, pCmdPacket->odtEntryAddrExt, pCmdPacket->odtEntryLen );
    }
    else
    {
        /* The ODT entry describes a single bit. */

        /* According to the specification of WRITE_DAQ, the bit offset can be from 0 to 31. Given that we support a "byte" address
         * granularity, we modify the ODT entry address and the bit offset so that the bit offset is from 0 to 7. We do this for
         * two reasons:
         *  - less space is required to store the bit offset;
         *  - the measurement or stimulation can be performed with a byte access instead of a dword access, thus avoiding the error
         *    which would occur on some targets if the dword access was not dword-aligned. */

#if XCP_TARGET_BYTE_ORDER == XCP_BYTE_ORDER_LITTLE_ENDIAN
        for( ; pCmdPacket->bitOffset > 0x07; pCmdPacket->bitOffset -= 0x08 )
        {
            ++( pCmdPacket->odtEntryAddr );
        }
#else /* XCP_BYTE_ORDER_LITTLE_ENDIAN */
        pCmdPacket->odtEntryAddr += 3;
        for( ; pCmdPacket->bitOffset > 0x07; pCmdPacket->bitOffset -= 0x08 )
        {
            --( pCmdPacket->odtEntryAddr );
        }
#endif
        pSessionCfg->pOdtEntryCfgs[ idxCurrOdtEntry ]  = XCP_PACK_ODTENTRYCFG_BIT  ( pCmdPacket->odtEntryAddr, pCmdPacket->odtEntryAddrExt, pCmdPacket->bitOffset );
        pSessionCfg->pOdtEntryAddrs[ idxCurrOdtEntry ] = XCP_PACK_ODTENTRYADDR_BYTE( pCmdPacket->odtEntryAddr, pCmdPacket->odtEntryAddrExt, 1 );
    }

    /* Record the maximum ODT ID which has been used in the current DAQ list */
    if( pSession->ctOdtId >= *pMaxOdtIdUsed )
    {
        *pMaxOdtIdUsed = pSession->ctOdtId;
    }

    if( ( pSessionCfg->maxDynDaqLists == 0 &&
          pSession->ctOdtEntryId < pDaqCfg->numOdtEntries - 1 )
#ifdef XCP_ENABLE_DYNDAQ
        ||
        ( pSessionCfg->maxDynDaqLists > 0 &&
          pSession->ctOdtEntryId < pSessionCfg->pDaqDynConfigs[ pSession->ctDaqListId ].odtEntryNums[ pSession->ctOdtId ] - 1 )
#endif /* XCP_ENABLE_DYNDAQ */
        )
    {
        /* Increment to the next ODT entry in the current ODT. */
        pSession->ctOdtEntryId++;
    }
    else
    {
        /* We have reached the last ODT entry in the current ODT. The master will need to set a new ODT with SET_DAQ_PTR. */
        pSession->ctDaqListId = XCP_DAQLIST_UNDEF;
    }

    pTxPacket->pid = XCP_PID_RESPONSE;
    *pTxPacketSize = 1;
    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command SET_DAQ_LIST_MODE as described in the XCP specification with the exceptions that:
 *  - DAQ list prioritisation is not supported.
 *  - The transmission rate prescaler is not supported.
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
uint XCP_FN_TYPE Xcp_CmdSetDaqListMode(
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
        uint16 daqListId;
        uint16 eventId;
        uint8  txPrescaler;
        uint8  daqListPrio;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;
    Xcp_DaqConfig_t*           pDaqConfig;
    Xcp_Daq_t*                 pDaqState;

    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    /* Is:
     *  - the DAQ list ID invalid;
     *  - or the specified DAQ list priority unsupported;
     *  - or the specified tx prescaler unsupported;
     *  - or the specified event ID invalid.
     */
    if( pCmdPacket->daqListId >= (uint)pSessionCfg->numStatDaqLists + (uint)Xcp_Sessions[ sessionId ].numDynDaqLists ||
        pCmdPacket->daqListPrio != 0             ||
        pCmdPacket->txPrescaler != 1             ||
        pCmdPacket->eventId >= XCP_NUM_EVENTS )
    {
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        return (XCP_RX_READY | XCP_TX_READY);
    }

    pDaqConfig = pSessionCfg->pDaqConfigs + pCmdPacket->daqListId;
    pDaqState  = pSessionCfg->pDaqStates + pCmdPacket->daqListId;

    if( pDaqState->daqListMode & (uint8)XCP_DAQLISTMODE_RUNNING )
    {
        /* The DAQ list is running; send a negative response with XCP_ERR_DAQ_ACTIVE */
        pTxPacket->data[0] = XCP_ERR_DAQ_ACTIVE;
        return (XCP_RX_READY | XCP_TX_READY);
    }

    if( pCmdPacket->eventId != pDaqState->daqEvent && ( XCP_DAQLISTPROPERTY_EVENTFIXED & pDaqConfig->properties ) )
    {
        /* The DAQ event cannot be modified, yet the command is trying to do so. */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        return (XCP_RX_READY | XCP_TX_READY);
    }

    if( ( ( pCmdPacket->mode ^ pDaqState->daqListMode ) & (uint8)XCP_DAQLISTMODE_DIRECTION ) &&
        ( XCP_DAQLISTPROPERTY_DAQ_STIM & pDaqConfig->properties ) != XCP_DAQLISTPROPERTY_DAQ_STIM )
    {
        /* The DAQ list direction cannot be modified, yet the command is trying to do so. */
        pTxPacket->data[0] = XCP_ERR_MODE_NOT_VALID;
        return (XCP_RX_READY | XCP_TX_READY);
    }

    /* Set or unset the DAQ list's mode bits as requested by the XCP master. Take care only to modify those bits which this
     * command is permitted to modify. */
    pDaqState->daqListMode &= ~0x32;
    pDaqState->daqListMode |= ( pCmdPacket->mode & 0x32 );
#ifdef XCP_ENABLE_PIDOFF
    if( XCP_CAN != pSessionCfg->transportLayerId )
    {
        /* This session does not use XCP-on-CAN, so PID_OFF mode cannot be enabled. */
        pDaqState->daqListMode &= ~PID_OFF_SUPPORTED;
    }
#else
    pDaqState->daqListMode &= ~PID_OFF_SUPPORTED;
#endif

    pDaqState->daqEvent     = (uint8)pCmdPacket->eventId;

    /* Send a positive response */
    pTxPacket->pid = XCP_PID_RESPONSE;
    *pTxPacketSize = 1;
    return (XCP_RX_READY | XCP_TX_READY);
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the XCP command GET_DAQ_LIST_MODE as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdGetDaqListMode(
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
        uint16 daqListId;
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  mode;
        uint16 reserved;
        uint16 eventId;
        uint8  txPrescaler;
        uint8  daqListPrio;
    } ) RespPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*) pRxPacket;
    RespPacket_t* const        pRespPacket = (RespPacket_t*) pTxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;

    if( pCmdPacket->daqListId < (uint)pSessionCfg->numStatDaqLists + (uint)Xcp_Sessions[ sessionId ].numDynDaqLists )
    {
        pRespPacket->pid         = XCP_PID_RESPONSE;
        pRespPacket->mode        = pSessionCfg->pDaqStates[ pCmdPacket->daqListId ].daqListMode;
        pRespPacket->eventId     = pSessionCfg->pDaqStates[ pCmdPacket->daqListId ].daqEvent;
        pRespPacket->txPrescaler = 1;
        pRespPacket->daqListPrio = 0xff;
        *pTxPacketSize           = 8;
    }
    else
    {
        /* The DAQ list ID is invalid; send a negative response with XCP_ERR_OUT_OF_RANGE */
        pTxPacket->pid     = XCP_PID_ERROR;
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        *pTxPacketSize     = 2;
    }

    return (XCP_RX_READY | XCP_TX_READY);
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

/**
 * This function implements the XCP command START_STOP_DAQ_LIST as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdStartStopDaqList(
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
        uint16 daqListId;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;

    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    if( pCmdPacket->daqListId < (uint)pSessionCfg->numStatDaqLists + (uint)Xcp_Sessions[ sessionId ].numDynDaqLists )
    {
        if( pCmdPacket->mode <= XCP_DAQLIST_SELECT )
        {
            switch( pCmdPacket->mode )
            {
            case XCP_DAQLIST_SELECT:
                pSessionCfg->pDaqStates[ pCmdPacket->daqListId ].daqListMode |= XCP_DAQLISTMODE_SELECTED;
                break;

            case XCP_DAQLIST_START:
                pSessionCfg->pDaqStates[ pCmdPacket->daqListId ].daqListMode |= XCP_DAQLISTMODE_RUNNING;
                break;

            case XCP_DAQLIST_STOP:
                pSessionCfg->pDaqStates[ pCmdPacket->daqListId ].daqListMode &= (uint8)(~XCP_DAQLISTMODE_RUNNING);
            }

            /* Send positive response with first pid of DAQ list. */
            pTxPacket->pid     = XCP_PID_RESPONSE;
            pTxPacket->data[0] = pSessionCfg->pDaqConfigs[ pCmdPacket->daqListId ].firstPid;
        }
        else
        {
            /* The mode parameter is invalid; send a negative response with XCP_ERR_MODE_NOT_VALID */
            pTxPacket->data[0] = XCP_ERR_MODE_NOT_VALID;
        }
    }
    else
    {
        /* The DAQ list ID is invalid; send a negative response with XCP_ERR_OUT_OF_RANGE */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command START_STOP_SYNCH as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdStartStopSync(
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
    } ) CmdPacket_t;


    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;
    uint                       i;

    if( pCmdPacket->mode <= XCP_DAQLIST_SYNC_STOPSEL )
    {
        for( i = 0; i < (uint)pSessionCfg->numStatDaqLists + (uint)Xcp_Sessions[ sessionId ].numDynDaqLists; ++i )
        {
            switch( pCmdPacket->mode )
            {
            case XCP_DAQLIST_SYNC_STOPALL:
                pSessionCfg->pDaqStates[ i ].daqListMode &= (uint8)(~XCP_DAQLISTMODE_RUNNING);
                break;

            case XCP_DAQLIST_SYNC_STARTSEL:
                if( pSessionCfg->pDaqStates[ i ].daqListMode & XCP_DAQLISTMODE_SELECTED )
                {
                    pSessionCfg->pDaqStates[ i ].daqListMode |= XCP_DAQLISTMODE_RUNNING;
                }
                break;

            case XCP_DAQLIST_SYNC_STOPSEL:
                if( pSessionCfg->pDaqStates[ i ].daqListMode & XCP_DAQLISTMODE_SELECTED )
                {
                    pSessionCfg->pDaqStates[ i ].daqListMode &= (uint8)(~XCP_DAQLISTMODE_RUNNING);
                }
            }

            /* When this command completes, all DAQ lists must be unselected. */
            pSessionCfg->pDaqStates[ i ].daqListMode &= (uint8)(~XCP_DAQLISTMODE_SELECTED);
        }

        /* sends positive response */
        pTxPacket->pid = XCP_PID_RESPONSE;
        *pTxPacketSize = 1;
    }
    else
    {
        /* The mode parameter is not valid; send a negative response with XCP_ERR_MODE_NOT_VALID */
        pTxPacket->pid      = XCP_PID_ERROR;
        pTxPacket->data[0]  = XCP_ERR_MODE_NOT_VALID;
        *pTxPacketSize      = 2;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command GET_DAQ_CLOCK as described in the XCP specification.
 *
 * The length of the timestamp will be as indicated by GET_DAQ_RESOLUTION_INFO. If the XCP timestamp is configured
 * to have a zero size this command sends the response ERR_GENERIC.
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
uint XCP_FN_TYPE Xcp_CmdGetDaqClock(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    uint numBytesTimestamp = Xcp_SessionConfigs[ sessionId ].numBytesTimestamp;

    if( numBytesTimestamp > 0 )
    {
        pTxPacket->pid = XCP_PID_RESPONSE;
        *pTxPacketSize   = 4 + numBytesTimestamp;

        Xcp_GetTimestamp( pTxPacket->data + 3, numBytesTimestamp );
    }
    else
    {
        /* The timestamp is configured to have zero size; send a negative response with XCP_ERR_GENERIC */
        pTxPacket->pid     = XCP_PID_ERROR;
        pTxPacket->data[0] = XCP_ERR_GENERIC;
        *pTxPacketSize     = 2;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function writes the current DAQ timestamp value to the specified location. The function ensures
 * that the timestamp is written correctly no matter its length nor the target's endianness.
 *
 * \param [out] pTimestamp          The location at which the function will write the timestamp value.
 *                                  NOTE that this address may *not* be word-aligned.
 * \param [in] numBytesTimestamp    The length of the timestamp value in bytes (1, 2 or 4).
 */
void XCP_FN_TYPE Xcp_GetTimestamp( 
    Xcp_StatePtr8 pTimestamp,
    uint          numBytesTimestamp
)
{
    uint32 timestamp = XcpApp_GetTimestamp();

#if XCP_TARGET_BYTE_ORDER == XCP_BYTE_ORDER_LITTLE_ENDIAN

    pTimestamp[0] = (uint8)timestamp;

    switch( numBytesTimestamp )
    {
    case 4:
        pTimestamp[3] = (uint8)( timestamp >> 24 );
        pTimestamp[2] = (uint8)( timestamp >> 16 );
        /* Fall through */
    case 2:
        pTimestamp[1] = (uint8)( timestamp >> 8 );
    }

#else /* XCP_BYTE_ORDER_BIG_ENDIAN */

    pTimestamp[ numBytesTimestamp - 1 ] = (uint8)timestamp;

    switch( numBytesTimestamp )
    {
    case 4:
        pTimestamp[ numBytesTimestamp - 4 ] = (uint8)( timestamp >> 24 );
        pTimestamp[ numBytesTimestamp - 3 ] = (uint8)( timestamp >> 16 );
        /* Fall through */
    case 2:
        pTimestamp[ numBytesTimestamp - 2 ] = (uint8)( timestamp >> 8 );
    }

#endif
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the XCP command GET_DAQ_PROCESSOR_INFO as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdGetDaqProcInfo(
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
        uint8  daqProperties;
        uint16 maxDaq;
        uint16 maxEventChannel;
        uint8  minDaq;
        uint8  daqKeyByte;
    } ) RespPacket_t;

    RespPacket_t* const        pRespPacket = (RespPacket_t*)pTxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;

    pRespPacket->pid             = XCP_PID_RESPONSE;
    pRespPacket->daqProperties   = BIT_STIM_SUPPORTED |
                                   NO_OVERLOAD_INDICATION;
#ifdef XCP_ENABLE_RESUME
    pRespPacket->daqProperties |= RESUME_SUPPORTED;
#endif
#ifdef XCP_ENABLE_PIDOFF
    if( XCP_CAN == pSessionCfg->transportLayerId )
    {
        pRespPacket->daqProperties |= PID_OFF_SUPPORTED;
    }
#endif
#ifdef XCP_ENABLE_DYNDAQ
    if( pSessionCfg->maxDynDaqLists > 0 )
    {
        pRespPacket->daqProperties |= DAQ_CONFIG_TYPE;
    }
#endif /* XCP_ENABLE_DYNDAQ */

    /* One or other of maxDynDaqLists and numStatDaqLists will be zero, but not both. */
    pRespPacket->maxDaq          = pSessionCfg->numStatDaqLists + pSessionCfg->maxDynDaqLists;
    pRespPacket->minDaq          = 0;
    pRespPacket->maxEventChannel = XCP_NUM_EVENTS;

    /* The DAQ key byte encodes:
     * - No DAQ list optimisation.
     * - Address extension is XCP_ADDR_EXTENSION_TYPE.
     * - Identification field is "absolute ODT number". */
    pRespPacket->daqKeyByte      = XCP_ADDR_EXTENSION_TYPE << 4;

    if( pSessionCfg->numBytesTimestamp )
    {
        pRespPacket->daqProperties |= TIMESTAMP_SUPPORTED;
    }

    *pTxPacketSize = 8;
    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command GET_DAQ_RESOLUTION_INFO as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdGetDaqResInfo(
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
        uint8  granOdtEntryDaq;
        uint8  maxOdtEntrySizeDaq;
        uint8  granOdtEntryStim;
        uint8  maxOdtEntrySizeStim;
        uint8  timestampMode;
        uint16 timestampTicks;
    } ) RespPacket_t;

    RespPacket_t* const pRespPacket = (RespPacket_t*)pTxPacket;

    pRespPacket->pid                    = XCP_PID_RESPONSE;
    pRespPacket->granOdtEntryDaq        = 1;
    pRespPacket->granOdtEntryStim       = 1;
    pRespPacket->maxOdtEntrySizeDaq     = 8;
    pRespPacket->maxOdtEntrySizeStim    = 8;
    /* If numBytesTimestamp is zero the following fields should be ignored by the XCP master. */
    pRespPacket->timestampMode          = ( Xcp_SessionConfigs[ sessionId ].numBytesTimestamp & 0x07 ) |
                                          ( XCP_TIMESTAMP_UNIT << 4 );
    pRespPacket->timestampTicks         = XCP_TIMESTAMP_TICKS;

    *pTxPacketSize = 8;
    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command GET_DAQ_LIST_INFO as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdGetDaqListInfo(
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
        uint16 daqListId;
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  daqListProperties;
        uint8  maxOdt;
        uint8  maxOdtEntries;
        uint16 fixedEvent;
    } ) RespPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const        pRespPacket = (RespPacket_t*)pTxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;
    Xcp_DaqConfig_t*           pDaqConfig;

    if( pCmdPacket->daqListId >= (uint)pSessionCfg->numStatDaqLists + (uint)Xcp_Sessions[ sessionId ].numDynDaqLists )
    {
        /* The DAQ list ID is invalid. */
        pTxPacket->pid     = XCP_PID_ERROR;
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        *pTxPacketSize     = 2;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    pDaqConfig = pSessionCfg->pDaqConfigs + pCmdPacket->daqListId;

    pRespPacket->pid                    = XCP_PID_RESPONSE;
    pRespPacket->fixedEvent             = 0;
    pRespPacket->daqListProperties      = 0x00;                     /* !PREDEFINED */

    if( pDaqConfig->properties & XCP_DAQLISTPROPERTY_EVENTFIXED )
    {
        pRespPacket->fixedEvent         = pDaqConfig->defaultEvent;
        pRespPacket->daqListProperties |= 0x02;                     /* EVENT_FIXED permitted. */
    }
    if( pDaqConfig->properties & XCP_DAQLISTPROPERTY_DAQ )
    {
        pRespPacket->daqListProperties |= 0x04;                     /* DAQ permitted. */
    }
    if( pDaqConfig->properties & XCP_DAQLISTPROPERTY_STIM )
    {
        pRespPacket->daqListProperties |= 0x08;                     /* STIM permitted. */
    }

#ifdef XCP_ENABLE_DYNDAQ
    if( pSessionCfg->maxDynDaqLists != 0 )
    {
        /* This session uses dynamic DAQ lists. */
        pRespPacket->maxOdt         = 0;
        pRespPacket->maxOdtEntries  = 0;
    }
    else
#endif /* XCP_ENABLE_DYNDAQ */
    {
        /* This session does not use dynamic DAQ lists. */
        pRespPacket->maxOdt         = pSessionCfg->pDaqConfigs[ pCmdPacket->daqListId ].numOdt;
        pRespPacket->maxOdtEntries  = pSessionCfg->pDaqConfigs[ pCmdPacket->daqListId ].numOdtEntries;
    }

    *pTxPacketSize = 6;
    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

#endif /* XCP_ENABLE */
