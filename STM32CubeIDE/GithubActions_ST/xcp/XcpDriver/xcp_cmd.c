/**
*
* \file
*
* \brief General XCP commands.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmd.c 18434 2010-03-31 10:02:00Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#ifdef XCP_ENABLE

/**
 * This function is called if the command requested by the XCP master is not implemented. It transmits the
 * response ERR_CMD_UNKNOWN.
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
uint XCP_FN_TYPE Xcp_CmdUnknown(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    pTxPacket->pid      = XCP_PID_ERROR;
    pTxPacket->data[0]  = XCP_ERR_CMD_UNKNOWN;

    *pTxPacketSize = 2;

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command GET_STATUS as described in the XCP specification.
 *
 * \param [in] sessionId    The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdGetStatus(
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
        uint8  sessionStatus;
        uint8  ctResourceProtection;
        uint8  reserved;
        uint16 sessionCfgId;
    } ) RespPacket_t;

    RespPacket_t* const        pRespPacket = (RespPacket_t*)pTxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;
    Xcp_Session_t* const       pSession    = Xcp_Sessions + sessionId;
    uint                       i;

    /* Calculate the DAQ_RUNNING bit of the session status. */
    pSession->sessionStatus &= (uint8)(~XCP_DAQLISTMODE_RUNNING);
    for( i = 0; i < (uint)pSessionCfg->numStatDaqLists + (uint)pSession->numDynDaqLists; ++i )
    {
        if( pSessionCfg->pDaqStates[ i ].daqListMode & XCP_DAQLISTMODE_RUNNING )
        {
            pSession->sessionStatus |= XCP_SESSION_STATE_DAQ_RUNNING;
            break;
        }
    }

    /* Mask out any unused bits. */
    pRespPacket->sessionStatus         = pSession->sessionStatus & ( XCP_SESSION_STATE_STORE_CAL |
                                                                     XCP_SESSION_STATE_STORE_DAQ |
                                                                     XCP_SESSION_STATE_CLEAR_DAQ |
                                                                     XCP_SESSION_STATE_DAQ_RUNNING |
                                                                     XCP_SESSION_STATE_RESUME );
#ifdef XCP_ENABLE_SEEDNKEY
    pRespPacket->ctResourceProtection  = pSession->ctResourceProtection;
#else
    pRespPacket->ctResourceProtection  = 0;
#endif
    pRespPacket->pid                   = XCP_PID_RESPONSE;
#ifdef XCP_ENABLE_RESUME
    pRespPacket->sessionCfgId          = pSession->sessionCfgId;
#else
    pRespPacket->sessionCfgId          = 0;
#endif /* XCP_ENABLE_RESUME */

    *pTxPacketSize = 6;
    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command SYNCH as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdSynch(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    pTxPacket->pid      = XCP_PID_ERROR;
    pTxPacket->data[0]  = XCP_ERR_CMD_SYNCH;

    *pTxPacketSize = 2;

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command SET_MTA as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdSetMta(
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
        uint8  reserved1;
        uint8  reserved2;
        uint8  addrExtension;
        uint32 address;
    } ) CmdPacket_t;

    const CmdPacket_t* const pCmdPacket  = (CmdPacket_t*)pRxPacket;
    const Xcp_Addr_t         newMta      = XcpApp_ConvertAddress( pCmdPacket->address, pCmdPacket->addrExtension );

    if( newMta != 0 )
    {
        Xcp_Sessions[ sessionId ].mta  = newMta;
        pTxPacket->pid = XCP_PID_RESPONSE;
        *pTxPacketSize = 1;
    }
    else
    {
        pTxPacket->pid     = XCP_PID_ERROR;
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        *pTxPacketSize     = 2;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the XCP command GET_ID as described in the XCP specification with the exceptions that:
 *  - only identification type "ASCII text" is supported;
 *  - only response mode 0 (transfer identification via UPLOAD) is supported.
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
uint XCP_FN_TYPE Xcp_CmdGetId(
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
        uint8  requestedType;
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  mode;
        uint16 reserved;
        uint32 length;
    } ) RespPacket_t;

    const CmdPacket_t* const pCmdPacket  = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const      pRespPacket = (RespPacket_t*)pTxPacket;

    if( pCmdPacket->requestedType == 0 )
    {
        /* ID type "ASCII text" is requested. */

        /* Set the MTA so that the master can upload the ID string. */
        Xcp_Sessions[ sessionId ].mta = (Xcp_Addr_t)Xcp_SlaveIdStrings[ sessionId ].idString;

        pRespPacket->length = (uint32)Xcp_SlaveIdStrings[ sessionId ].len;
        pRespPacket->mode = 0;
        pRespPacket->pid = XCP_PID_RESPONSE;
    }
    else
    {
        /* Only ID type 0 is supported. */

        pRespPacket->length = 0;
        pRespPacket->mode = 0;
        pRespPacket->pid = XCP_PID_RESPONSE;
    }

    *pTxPacketSize = 8;
    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command GET_COMM_MODE_INFO as described in the XCP specification with, the exceptions that:
 *  - only identification type "ASCII text" is supported;
 *  - only response mode 0 (transfer identification via UPLOAD) is supported.
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
uint XCP_FN_TYPE Xcp_CmdGetCommModeInfo(
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
        uint8  reserved1;
        uint8  commModeOptional;
        uint8  reserved2;
        uint8  maxBs;
        uint8  minSt;
        uint8  queueSize;
        uint8  driverVer;
    } ) RespPacket_t;

    RespPacket_t* const pRespPacket = (RespPacket_t*) pTxPacket;

    pRespPacket->pid                = XCP_PID_RESPONSE;
    pRespPacket->commModeOptional   = 1; /* MASTER_BLOCK_MODE */
    pRespPacket->maxBs              = 255;
    pRespPacket->driverVer          = ( ( XCP_DRIVER_VERSION_MAJOR & 0x0f ) << 4 ) |
                                      ( XCP_DRIVER_VERSION_MINOR & 0x0f );

    /* MIN_ST must be set so as to prevent the command queue from overflowing in master block mode.
     * Usually it would be sufficient to set MIN_ST to the same time interval as XCP_POLL_INTERVAL;
     * however this does not take account of the fact that a command which involves an asynchronous
     * request to the ECU application (e.g. writing to calibration memory) may require more than one
     * invocation of Xcp_CmdProcessor() to complete. */
    pRespPacket->minSt              = XCP_BLOCK_SEPARATION_TIME * 10; /* We want units of 100us; XCP_BLOCK_SEPARATION_TIME is measured in ms. */

    /* We ignore QUEUE_SIZE since we do not support interleaved mode. */

    *pTxPacketSize = 8;
    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

/**
 * This function implements the XCP command TRANSPORT_LAYER_CMD by delegating to the transport layer.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return Delegated to transport layer.
 */
uint XCP_FN_TYPE Xcp_CmdTransportLayer(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    if( Xcp_SessionConfigs[ sessionId ].pCmdProc )
    {
        return Xcp_SessionConfigs[ sessionId ].pCmdProc( sessionId, pRxPacket, pTxPacket, prevCmd, pTxPacketSize );
    }

    /* The transport layer does not support any XCP commands. */
    return Xcp_CmdUnknown( sessionId, pRxPacket, pTxPacket, prevCmd, pTxPacketSize );
}

#ifdef XCP_ENABLE_PAGEFREEZE

/**
 * This function is called during the command SET_REQUEST; it freezes any calibration segments which have been selected
 * for freezing.
 *
 * As required by the XCP specification this function sets a bit in the session status while it is freezing segments.
 * However, since this command blocks the command queue, the XCP master will be unable to read the session status.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - 0                             The user application is processing a freeze request asynchronously. The command processor will
 *                                  mark this command as being pending and will process it again on the next tick.
 *                                  No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_StoreCalReq(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    Xcp_SessionConfig_t* const pSessionCfg     = Xcp_SessionConfigs + sessionId;
    Xcp_CalMemState            freezeResult;
    Xcp_SegState_t*            pSegState       = pSessionCfg->pSegStates;
    Xcp_SegConfig_t*           pSegConfig      = pSessionCfg->pSegConfigs;
    uint                       i;
    Xcp_StatePtr8              pSessionStatus  = &( Xcp_Sessions[ sessionId ].sessionStatus );

    *pTxPacketSize = 2;
    pTxPacket->pid = XCP_PID_ERROR;

    /* This function can terminate in one of three states:
     *  - All segments selected for freezing were successfully frozen.
     *  - An error was encountered while trying to freeze a segment. If this function is called again the freezing process
     *    will start again from the beginning.
     *  - A request to freeze a segment could not be completed immediately and will be processed asynchronously. The command
     *    processor will re-process this command on the next tick, whereupon this function should resume the freezing
     *    process at the segment in question.
     */

    for( i = 0; i < pSessionCfg->numSegs; ++i )
    {
        /* Is the current segment selected for freezing? */
        if( pSegState->mode & XCP_SEGMODE_FREEZE )
        {
            if( pSegState->mode & XCP_SEGMODE_FREEZE_PENDING )
            {
                /* A request to freeze the current segment is already pending; check to see what progress the request has made. */
                freezeResult = XcpApp_CalMemGetRequestState();

                pSegState->mode &= ~XCP_SEGMODE_FREEZE_PENDING;
            }
            else if( prevCmd != XCP_CMD_CURR_CMD )
            {
                /* This command has not been processed previously, so we have not yet asked the application to
                 * freeze the current segment. We do so now. */
                *pSessionStatus |= XCP_SESSION_STATE_STORE_CAL;
                freezeResult = XcpApp_CalSegFreeze( (uint8)i, pSegConfig->pPageConfigs[ pSegState->toolPage ].initSegment );
            }
            else
            {
                /* This command has been processed previously, so a request to freeze a segment is pending, but this is
                 * not the segment in question. Continue to the next segment. */
                ++pSegState;
                ++pSegConfig;
                continue;
            }

            switch( freezeResult )
            {
            case CALMEM_FINISHED:
                /* The application has finished freezing the segment. */

                /* Ensure that prevCmd != XCP_CMD_CURR_CMD, since any subsequent iteration of the loop should treat this
                 * command as being processed afresh. */
                prevCmd = 0;

                break;

            case CALMEM_BUSY:
                /* The application has not yet finished freezing the segment.
                 * The command processor will mark this command as being pending and will process it again on
                 * the next tick. No response will be transmitted to the master. */
                *pTxPacketSize   = 0;
                pSegState->mode |= XCP_SEGMODE_FREEZE_PENDING;
                return 0;

            case CALMEM_SEGNOTVALID:
                pTxPacket->data[0]       = XCP_ERR_SEGMENT_NOT_VALID;
                *pSessionStatus         &= ~XCP_SESSION_STATE_STORE_CAL;
                return XCP_RX_READY | XCP_TX_READY;

            case CALMEM_REJECTED:
                /* The application is temporarily unable to freeze the segment. The master may re-try, though in
                 * this case freezing will start again with the first segment. */
                pTxPacket->data[0]       = XCP_ERR_CMD_BUSY;
                *pSessionStatus         &= ~XCP_SESSION_STATE_STORE_CAL;
                return XCP_RX_READY | XCP_TX_READY;

            default:
                pTxPacket->data[0]       = XCP_ERR_WRITE_PROTECTED;
                *pSessionStatus         &= ~XCP_SESSION_STATE_STORE_CAL;
                return XCP_RX_READY | XCP_TX_READY;
            }
        }

        ++pSegState;
        ++pSegConfig;
    }

    *pSessionStatus         &= ~XCP_SESSION_STATE_STORE_CAL;
    pTxPacket->pid           = XCP_PID_RESPONSE;
    *pTxPacketSize           = 1;

    return XCP_RX_READY | XCP_TX_READY;
}

#endif /* XCP_ENABLE_PAGEFREEZE */

#if defined( XCP_ENABLE_PAGEFREEZE ) || defined( XCP_ENABLE_RESUME )

/**
 * This function implements the XCP command SET_REQUEST as described in the XCP specification with the exception that
 * the events EV_STORE_CAL, EV_STORE_DAQ and EV_CLEAR_DAQ are never transmitted by the slave.
 *
 * Within the command, the STORE_CAL_REQ bit cannot be set at the same time as either the STORE_DAQ_REQ bit or
 * the CLEAR_DAQ_REQ bit.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - Delegated to Xcp_StoreCalReq().
 */
uint XCP_FN_TYPE Xcp_CmdSetRequest(
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
        uint16 sessionConfigId;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;
    Xcp_Session_t*             pSession    = Xcp_Sessions + sessionId;
    uint                       nvIdx;

    pTxPacket->pid     = XCP_PID_ERROR;
    pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
    *pTxPacketSize     = 2;

    if( pCmdPacket->mode & XCP_SESSION_STATE_STORE_CAL )
    {
#ifdef XCP_ENABLE_PAGEFREEZE
        /* We do not allow XCP_SESSION_STATE_STORE_CAL to be set along with either XCP_SESSION_STATE_STORE_DAQ or
         * XCP_SESSION_STATE_CLEAR_DAQ because of the difficulty of reporting the results of each operation separately. */
        if( pCmdPacket->mode & ( XCP_SESSION_STATE_CLEAR_DAQ | XCP_SESSION_STATE_STORE_DAQ ) )
        {
            return( XCP_RX_READY | XCP_TX_READY );
        }

        return Xcp_StoreCalReq( sessionId, pRxPacket, pTxPacket, prevCmd, pTxPacketSize );
#else
        /* We do not support page freezing in this build. */
        return( XCP_RX_READY | XCP_TX_READY );
#endif /* XCP_ENABLE_PAGEFREEZE */
    }

#ifdef XCP_ENABLE_RESUME

    nvIdx = pSessionCfg->nvStartIdx;

    /* If the specified session has no configured non-volatile (NV) memory region then an error has occurred. */
    if( XCP_INVALID_NV_IDX == nvIdx )
    {
        return( XCP_RX_READY | XCP_TX_READY );
    }

    /* If we are requested to, clear our session's data from the NV memory.
     *
     * We do not clear every item of data associated with the session; we just clear the instance of Xcp_NvSession_t,
     * meaning that the rest of the session data can no longer be read from the NV memory. */

    if( pCmdPacket->mode & XCP_SESSION_STATE_CLEAR_DAQ )
    {
        pSession->sessionStatus |= XCP_SESSION_STATE_CLEAR_DAQ;
        XcpApp_NvMemClear( nvIdx, sizeof_Xcp_NvSession_t );
        pSession->sessionStatus &= ~XCP_SESSION_STATE_CLEAR_DAQ;
    }

    if( pCmdPacket->mode & XCP_SESSION_STATE_STORE_DAQ )
    {
        Xcp_NvSession_t        nvSession       = { XCP_NVMEM_MAGIC_NUMBER, 0, 0, 0 };
        Xcp_NvDaqState_t       nvDaqState;
        Xcp_Daq_t*             pDaqState       = pSessionCfg->pDaqStates;
        Xcp_DaqConfig_t*       pDaqConfig      = pSessionCfg->pDaqConfigs;
        uint                   numOdtEntries;
        uint                   i;
#ifdef XCP_ENABLE_DYNDAQ
        Xcp_DaqDynConfig_t*    pDaqDynConfig   = pSessionCfg->pDaqDynConfigs;
#endif
        nvSession.sessionCfgId   = pCmdPacket->sessionConfigId;
        nvSession.numDynDaqLists = pSession->numDynDaqLists;

        /* Notes about storing RESUME data to NV memory:
         *
         *  - The XCP specification requires that we clear the NV region before writing fresh data to it. However
         *    we do not clear the region explicitly because we over-write any data which was there previously.
         *
         *  - As required by the XCP specification we set bit(s) in the session status while we are accessing NV memory.
         *    However, since the NV operations block the command-processing task (i.e. the current task), the XCP master
         *    will be unable to read the session status.
         */

        pSession->sessionStatus |= XCP_SESSION_STATE_STORE_DAQ;
        pSession->sessionCfgId   = pCmdPacket->sessionConfigId;

        /* 
         * Now we write all the relevant data from our session to the NV memory region.
         */

        /* The NV memory region for the session begins with an instance of Xcp_NvSession_t. However, we do not have
         * enough information to write this instance immediately, so we leave a gap and will come back to write it later. */
        nvIdx += sizeof_Xcp_NvSession_t;

        /* Next the NV memory region contains a block of data for each DAQ list which has been selected for RESUME.
         *
         * Note the following optimisations in this code:
         *
         *  - Either numStatDaqLists is zero or numDynDaqLists is zero (recall that static DAQ lists and dynamic DAQ lists
         *    cannot be configured simultaneously).
         *
         *  - pDaqDynConfig is zero if the session uses static DAQ lists.
         *
         *  - It is possible to use complex optimisation to minimize the amount of data stored for a DAQ list, based on
         *    the actual configuration of the DAQ list at runtime; this is particularly the case for dynamic DAQ lists.
         *    However, the NV memory region must be large enough to store *any* possible configuration of the DAQ list, so
         *    such optimisations do not save NV memory. They may save execution time, but it is assumed that the time to
         *    read / write the RESUME data is not critical.
         *    Therefore only the simplest of optimisations are used when storing data for a DAQ list.
         */

        for( i = 0; i < (uint)pSessionCfg->numStatDaqLists + (uint)pSession->numDynDaqLists; ++i )
        {
            /* Skip the current DAQ list unless it is selected for RESUME. */
            if( pDaqState->daqListMode & XCP_DAQLISTMODE_SELECTED )
            {
                pDaqState->daqListMode &= ~XCP_DAQLISTMODE_SELECTED;
                pDaqState->daqListMode |= XCP_DAQLISTMODE_RESUME;
            }
            else
            {
                ++pDaqState;
                ++pDaqConfig;
#ifdef XCP_ENABLE_DYNDAQ
                if( pDaqDynConfig )
                {
                    ++pDaqDynConfig;
                }
#endif
                continue;
            }

            /* Store data which is common to static and dynamic DAQ lists. */

            nvDaqState.daqListId    = (uint16)i;
            nvDaqState.daqListMode  = pDaqState->daqListMode;
            nvDaqState.daqEvent     = pDaqState->daqEvent;
            nvDaqState.maxOdtIdUsed = pDaqState->maxOdtIdUsed;
            XcpApp_NvMemWrite( nvIdx, (Xcp_StatePtr8)&nvDaqState, sizeof_Xcp_NvDaqState_t );
            nvIdx += sizeof_Xcp_NvDaqState_t;

            /* Store data which is required for dynamic DAQ lists. */
#ifdef XCP_ENABLE_DYNDAQ
            if( pDaqDynConfig )
            {
                XcpApp_NvMemWrite( nvIdx, (Xcp_StatePtr8)pDaqDynConfig, sizeof_Xcp_DaqDynConfig_t );
                nvIdx += sizeof_Xcp_DaqDynConfig_t;

                ++pDaqDynConfig;
            }
#endif /* XCP_ENABLE_DYNDAQ */

            /* Store the addresses and lengths assigned to each ODT entry in each currently-used ODT in the DAQ list. */

            numOdtEntries = pDaqConfig->numOdtEntries * ( pDaqState->maxOdtIdUsed + 1 );

            XcpApp_NvMemWrite( nvIdx, (Xcp_StatePtr8)( pSessionCfg->pOdtEntryAddrs + pDaqConfig->idxDaqStart ), numOdtEntries * sizeof( Xcp_OdtEntryAddr_t ) );
            nvIdx += numOdtEntries * sizeof( Xcp_OdtEntryAddr_t );

            XcpApp_NvMemWrite( nvIdx, (Xcp_StatePtr8)( pSessionCfg->pOdtEntryCfgs + pDaqConfig->idxDaqStart ), numOdtEntries );
            nvIdx += numOdtEntries;

            /* Allow the transport layer to store data for this DAQ list. */
            nvIdx += pSessionCfg->pPrepareResume( sessionId, i, nvIdx );

            ++pDaqState;
            ++pDaqConfig;
            ++nvSession.numResumeDaqLists;
        }

        /* Now we have enough information to go back and write an instance of Xcp_NvSession_t at the start of the session's
         * NV memory region. */
        XcpApp_NvMemWrite( pSessionCfg->nvStartIdx, (Xcp_StatePtr8)&nvSession, sizeof_Xcp_NvSession_t );

        pSession->sessionStatus &= ~XCP_SESSION_STATE_STORE_DAQ;
    }

    pTxPacket->pid = XCP_PID_RESPONSE;
    *pTxPacketSize = 1;

#endif /* XCP_ENABLE_RESUME */

    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE_PAGEFREEZE || XCP_ENABLE_RESUME */

#ifdef XCP_ENABLE_USER_CMD

/**
 * This function implements the XCP command USER_CMD as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdUser(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    /* Initialise the response packet to indicate an error. This ensures that a valid XCP response will be returned in the
     * event that XcpApp_UserCmd() does not create one. */
    pTxPacket->pid      = XCP_PID_ERROR;
    pTxPacket->data[0]  = XCP_ERR_CMD_UNKNOWN;
    *pTxPacketSize      = 2;

    XcpApp_UserCmd( sessionId, (Xcp_StatePtr8)pRxPacket, (Xcp_StatePtr8)pTxPacket, pTxPacketSize );

    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE_USER_CMD */

#endif /* XCP_ENABLE */
