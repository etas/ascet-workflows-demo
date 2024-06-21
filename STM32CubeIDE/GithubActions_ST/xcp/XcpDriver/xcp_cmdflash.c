/**
*
* \file
*
* \brief Flash programming XCP commands.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmdflash.c 18358 2010-03-25 13:57:40Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#if defined( XCP_ENABLE ) && defined( XCP_ENABLE_PGM )

/**
 * This function writes flash data to the ECU's memory. Note that some portions of this function (e.g. handling
 * block mode) may not be used when it is called in certain circumstances (e.g. from PROGRAM_MAX).
 *
 * \param [in] pSession         The state of the session which received the flash command.
 * \param [in] numBytesToWrite  The number of bytes at pDataToWrite.
 * \param [in] pDataToWrite     The flash data to be written to the ECU's memory.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacket       The response packet.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The flash data has been completely received and written to memory, or an error
 *                                  occurred and the write was aborted.
 *  - XCP_RX_READY                  The first block in the flash block sequence has been received and written
 *                                  to memory. A response will not be sent to the XCP master; instead, it must send
 *                                  a PROGRAM_NEXT command.
 *  - 0                             The user application is processing an asynchronous request to write the flash
 *                                  data to memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_WriteFlashData(
    Xcp_Session_t*  pSession,
    uint            numBytesToWrite,
    Xcp_StatePtr8   pDataToWrite,
    uint            prevCmd,
    Xcp_Packet_t*   pTxPacket,
    uint*           pTxPacketSize
)
{
    Xcp_ProgramState requestResult;
    uint             retVal          = XCP_RX_READY | XCP_TX_READY;

    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    if( !( pSession->sessionStatus & XCP_SESSION_STATE_PGM ) )
    {
        /* PROGRAM_START has not been called yet. */
        pTxPacket->data[0] = XCP_ERR_SEQUENCE;
        return XCP_RX_READY | XCP_TX_READY;
    }

    if( prevCmd != XCP_CMD_CURR_CMD )
    {
        /* This is the first time we have processed this command packet, so we ask the application to program the
         * data to memory. */
        requestResult = XcpApp_Program( pSession->mta, (uint8)numBytesToWrite, pDataToWrite );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * asked the application to write the program data to memory.
         * 
         * Now we check to see what progress the application has made. */
        requestResult = XcpApp_ProgramGetRequestState();
    }

    switch( requestResult )
    {
        case PROGRAM_FINISHED:
            /* The application has finished processing the request. */
            pSession->mta  += numBytesToWrite;

            if( 0 != pSession->downloadRemainBytes )
            {
                /* We are in block mode and we expect the master to send more data, so we do not transmit a response yet. */
                retVal = XCP_RX_READY;
            }

            pTxPacket->pid  = XCP_PID_RESPONSE;
            *pTxPacketSize  = 1;
            break;

        case PROGRAM_BUSY:
            /* The application has not yet finished processing the request.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal          = 0;
            *pTxPacketSize  = 0;
            break;

        case PROGRAM_REJECTED:
            /* The application is temporarily unable to process the request. The master may re-try. */
            pTxPacket->data[0] = XCP_ERR_CMD_BUSY;
            break;

        default:
            /* The application is not in a state which permits this request to be fulfilled. */
            pTxPacket->data[0] = XCP_ERR_ACCESS_DENIED;

            /* Force the master to begin the programming sequence again with PROGRAM_START. */
            pSession->sessionStatus &= ~XCP_SESSION_STATE_PGM;
    }

    return retVal;
}

/**
 * This function implements the XCP command PROGRAM_START as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - 0                             The user application is processing this request asynchronously. The command processor
 *                                  will mark this command as pending and will process it again on the next tick. No
 *                                  response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdProgramStart(
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
        uint8  commModePgm;
        uint8  maxCtoPgm;
        uint8  maxBsPgm;
        uint8  minStPgm;
        uint8  queueSizePgm;
    } ) RespPacket_t;

    RespPacket_t* const  pRespPacket     = (RespPacket_t*)pTxPacket;
    Xcp_Session_t* const pSession        = Xcp_Sessions + sessionId;
    Xcp_ProgramState     requestResult;
    uint                 retVal          = XCP_RX_READY | XCP_TX_READY;
    uint                 i;

    for( i = 0; i < XCP_NUM_SESSIONS; ++i )
    {
        if( Xcp_Sessions + i != pSession && ( Xcp_Sessions[i].sessionStatus & XCP_SESSION_STATE_PGM ) )
        {
            /* Another session is already performing flash programming. */
            pTxPacket->pid     = XCP_PID_ERROR;
            pTxPacket->data[0] = XCP_ERR_GENERIC;
            *pTxPacketSize     = 2;
            return XCP_RX_READY | XCP_TX_READY;
        }
    }

    if( prevCmd != XCP_CMD_CURR_CMD)
    {
        /* This is the first time we have processed this command packet, so we submit this request to the application. */
        requestResult = XcpApp_ProgramStart( pSession->mta );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * submitted this request to the application.
         * 
         * Now we check to see what progress the application has made. */
        requestResult = XcpApp_ProgramGetRequestState();
    }

    switch( requestResult )
    {
        case PROGRAM_FINISHED:
            /* The application has finished processing the request. */

            /* See Xcp_CmdGetCommModeInfo() for comments on the values specified for the various communication parameters. */
            pRespPacket->pid            = XCP_PID_RESPONSE;
            pRespPacket->commModePgm    = 0x41;                             /* SLAVE_BLOCK_MODE | MASTER_BLOCK_MODE */
            pRespPacket->maxCtoPgm      = Xcp_SessionConfigs[ sessionId ].maxCtoLen;
            pRespPacket->maxBsPgm       = 255;
            pRespPacket->minStPgm       = XCP_BLOCK_SEPARATION_TIME * 10;   /* We want units of 100us; XCP_BLOCK_SEPARATION_TIME is measured in ms. */

            /* We ignore QUEUE_SIZE_PGM since we do not support interleaved mode. */

            *pTxPacketSize              = 7;
            pSession->sessionStatus    |= XCP_SESSION_STATE_PGM;

            break;

        case PROGRAM_BUSY:
            /* The application has not yet finished processing the request.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal              = 0ul;
            *pTxPacketSize      = 0;
            break;

        case PROGRAM_REJECTED:
            /* The application is temporarily unable to process the request. The master may re-try. */
            pTxPacket->data[0] = XCP_ERR_CMD_BUSY;
            pTxPacket->pid     = XCP_PID_ERROR;
            *pTxPacketSize     = 2;
            break;

        default:
            /* The application is not in a state which permits this request to be fulfilled. */
            pTxPacket->data[0] = XCP_ERR_GENERIC;
            pTxPacket->pid     = XCP_PID_ERROR;
            *pTxPacketSize     = 2;
    }

    return retVal;
}

/**
 * This function implements the XCP command PROGRAM_CLEAR as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - 0                             The user application is processing this request asynchronously. The command processor
 *                                  will mark this command as pending and will process it again on the next tick. No
 *                                  response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdProgramClear(
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
        uint16 reserved;
        uint32 clearRange;
    } ) CmdPacket_t;

    const CmdPacket_t* const pCmdPacket      = (CmdPacket_t*)pRxPacket;
    Xcp_Session_t* const     pSession        = Xcp_Sessions + sessionId;
    Xcp_ProgramState         requestResult;
    uint                     retVal          = XCP_RX_READY | XCP_TX_READY;

    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    if( 1 == pCmdPacket->mode )
    {
        /* We do not support function access mode. */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;

        /* Force the master to begin the programming sequence again with PROGRAM_START. */
        pSession->sessionStatus &= ~XCP_SESSION_STATE_PGM;

        return XCP_RX_READY | XCP_TX_READY;
    }

    if( !( pSession->sessionStatus & XCP_SESSION_STATE_PGM ) )
    {
        /* PROGRAM_START has not been called yet. */
        pTxPacket->data[0] = XCP_ERR_SEQUENCE;
        return XCP_RX_READY | XCP_TX_READY;
    }

    if( prevCmd != XCP_CMD_CURR_CMD)
    {
        /* This is the first time we have processed this command packet, so we submit this request to the application. */
        requestResult = XcpApp_ProgramClear( pSession->mta, pCmdPacket->clearRange );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * submitted this request to the application.
         * 
         * Now we check to see what progress the application has made. */
        requestResult = XcpApp_ProgramGetRequestState();
    }

    switch( requestResult )
    {
        case PROGRAM_FINISHED:
            /* The application has finished processing the request. */
            pTxPacket->pid      = XCP_PID_RESPONSE;
            *pTxPacketSize      = 1;
            break;

        case PROGRAM_BUSY:
            /* The application has not yet finished processing the request.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal              = 0ul;
            *pTxPacketSize      = 0;
            break;

        case PROGRAM_REJECTED:
            /* The application is temporarily unable to process the request. The master may re-try. */
            pTxPacket->data[0]  = XCP_ERR_CMD_BUSY;
            break;

        default:
            /* The application is not in a state which permits this request to be fulfilled. */

            /* Force the master to begin the programming sequence again with PROGRAM_START. */
            pSession->sessionStatus &= ~XCP_SESSION_STATE_PGM;

            pTxPacket->data[0]  = XCP_ERR_ACCESS_DENIED;
    }

    return retVal;
}

/**
 * This function implements the XCP command PROGRAM as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The program data has been completely received and written to memory.
 *  - XCP_RX_READY                  The first block in the program block sequence has been received and written
 *                                  to memory. A response will not be sent to the XCP master; instead, it must send
 *                                  a PROGRAM_NEXT command.
 *  - 0                             The user application is processing an asynchronous request to write the program
 *                                  data to memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdProgram(
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
        uint8  numBytes;
        uint8  data[1];     /* Strictly speaking, there may be more than 1 data byte. However, we only declare
                             * 1 to encourage the compiler to pack the structure on byte boundaries. This works
                             * because we never declare instances of this type, only pointers to pre-allocated buffers. */
    } ) CmdPacket_t;

    const CmdPacket_t* const pCmdPacket      = (CmdPacket_t*)pRxPacket;
    Xcp_Session_t* const     pSession        = Xcp_Sessions + sessionId;
    const uint               maxBlockSize    = Xcp_SessionConfigs[ sessionId ].maxCtoLen - 2;
    uint                     numBytesToWrite = (uint)pCmdPacket->numBytes;

    if( numBytesToWrite <= maxBlockSize )
    {
        /* The data to be programmed is contained within this single command packet. */
        pSession->downloadRemainBytes = 0;
    }
    else
    {
        /* The data to be programmed is larger than this command packet, so we are in block mode. */

        pSession->downloadRemainBytes = (uint8)( numBytesToWrite - maxBlockSize );
        numBytesToWrite = maxBlockSize;
    }

    return Xcp_WriteFlashData( pSession, numBytesToWrite, pRxPacket->data + 1, prevCmd, pTxPacket, pTxPacketSize );
}

/**
 * This function implements the XCP command PROGRAM_NEXT as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The program block sequence has been completely received and written to memory.
 *  - XCP_RX_READY                  A non-final block in the program block sequence has been received
 *                                  and written to memory. A response will not be sent to the XCP master; instead,
 *                                  it must send another PROGRAM_NEXT command.
 *  - 0                             The user application is processing an asynchronous request to write the program
 *                                  data block to memory. The command processor will mark this command as pending
 *                                  and will process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdProgramNext(
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
        uint8  numBytes;
        uint8  data[1];     /* Strictly speaking, there may be more than 1 data byte. However, we only declare
                             * 1 to encourage the compiler to pack the structure on byte boundaries. This works
                             * because we never declare instances of this type, only pointers to pre-allocated buffers */
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  errorCode;
        uint8  numExpectedBytes;
    } ) RespPacket_t;

    Xcp_Session_t* const     pSession        = Xcp_Sessions + sessionId;
    uint                     remainBytes     = pSession->downloadRemainBytes;
    const CmdPacket_t* const pCmdPacket      = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const      pRespPacket     = (RespPacket_t*)pTxPacket;

    if( ( pCmdPacket->numBytes != remainBytes ) || ( remainBytes == 0 ) )
    {
        /* A sequence error has occurred. Either the master is not supplying the expected number of
         * program bytes or a program sequence is not in progress. */
        pRespPacket->pid              = XCP_PID_ERROR;
        pRespPacket->errorCode        = XCP_ERR_SEQUENCE;
        pRespPacket->numExpectedBytes = (uint8)remainBytes;
        *pTxPacketSize                = 3;

        /* Force the master to begin the programming sequence again with PROGRAM_START. */
        pSession->sessionStatus &= ~XCP_SESSION_STATE_PGM;

        return XCP_RX_READY | XCP_TX_READY;
    }

    return Xcp_CmdProgram( sessionId, pRxPacket, pTxPacket, prevCmd, pTxPacketSize );
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the XCP command PROGRAM_MAX as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The program data has been completely received and written to memory.
 *  - 0                             The user application is processing an asynchronous request to write the program
 *                                  data to memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdProgramMax(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    /* Note that we are never in block mode, so pSession->downloadRemainBytes is always zero at this point. */
    Xcp_Session_t* pSession = Xcp_Sessions + sessionId;

    return Xcp_WriteFlashData( pSession, Xcp_SessionConfigs[ sessionId ].maxCtoLen - 1, pRxPacket->data, prevCmd, pTxPacket, pTxPacketSize );
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

/**
 * This function implements the XCP command PROGRAM_RESET as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - 0                             The user application is processing this request asynchronously. The command processor
 *                                  will mark this command as pending and will process it again on the next tick. No
 *                                  response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdProgramReset(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    Xcp_Session_t* const pSession        = Xcp_Sessions + sessionId;
    Xcp_ProgramState     requestResult;
    uint                 retVal          = XCP_RX_READY | XCP_TX_READY;

    if( prevCmd != XCP_CMD_CURR_CMD)
    {
        /* This is the first time we have processed this command packet, so we submit this request to the application.
         *
         * Note that this function call may cause a reset of the device. */
        requestResult = XcpApp_ProgramReset();
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * submitted this request to the application.
         * 
         * Now we check to see what progress the application has made. */
        requestResult = XcpApp_ProgramGetRequestState();
    }

    switch( requestResult )
    {
        case PROGRAM_FINISHED:
            /* The application has finished processing the request. */
            Xcp_DoDisconnect( sessionId, pSession );
            pTxPacket->pid           = XCP_PID_RESPONSE;
            *pTxPacketSize           = 1;
            pSession->sessionStatus &= ~XCP_SESSION_STATE_PGM;
            break;

        case PROGRAM_BUSY:
            /* The application has not yet finished processing the request.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal              = 0ul;
            *pTxPacketSize      = 0;
            break;

        case PROGRAM_REJECTED:
            /* The application is temporarily unable to process the request. The master may re-try. */
            pTxPacket->data[0]  = XCP_ERR_CMD_BUSY;
            pTxPacket->pid      = XCP_PID_ERROR;
            *pTxPacketSize      = 2;
            break;

        default:
            /* The application is not in a state which permits this request to be fulfilled. */
            pTxPacket->data[0]  = XCP_ERR_GENERIC;
            pTxPacket->pid      = XCP_PID_ERROR;
            *pTxPacketSize      = 2;

            /* Force the master to begin the programming sequence again with PROGRAM_START. */
            pSession->sessionStatus &= ~XCP_SESSION_STATE_PGM;
    }

    return retVal;
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the XCP command PROGRAM_PREPARE as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - 0                             The user application is processing this request asynchronously. The command processor
 *                                  will mark this command as pending and will process it again on the next tick. No
 *                                  response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdProgramPrepare(
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
        uint16 codeSize;
    } ) CmdPacket_t;

    const CmdPacket_t* const pCmdPacket      = (CmdPacket_t*)pRxPacket;
    Xcp_ProgramState         requestResult;
    uint                     retVal          = XCP_RX_READY | XCP_TX_READY;

    if( prevCmd != XCP_CMD_CURR_CMD)
    {
        /* This is the first time we have processed this command packet, so we submit this request to the application. */
        requestResult = XcpApp_ProgramPrepare( Xcp_Sessions[ sessionId ].mta, pCmdPacket->codeSize );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * submitted this request to the application.
         * 
         * Now we check to see what progress the application has made. */
        requestResult = XcpApp_ProgramGetRequestState();
    }

    switch( requestResult )
    {
        case PROGRAM_FINISHED:
            /* The application has finished processing the request. */
            pTxPacket->pid      = XCP_PID_RESPONSE;
            *pTxPacketSize      = 1;
            break;

        case PROGRAM_BUSY:
            /* The application has not yet finished processing the request.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal              = 0ul;
            *pTxPacketSize      = 0;
            break;

        case PROGRAM_REJECTED:
            /* The application is temporarily unable to process the request. The master may re-try. */
            pTxPacket->data[0]  = XCP_ERR_CMD_BUSY;
            pTxPacket->pid      = XCP_PID_ERROR;
            *pTxPacketSize      = 2;
            break;

        default:
            /* The application is not in a state which permits this request to be fulfilled. */
            pTxPacket->data[0]  = XCP_ERR_GENERIC;
            pTxPacket->pid      = XCP_PID_ERROR;
            *pTxPacketSize      = 2;
    }

    return retVal;
}

/**
 * This function implements the XCP command PROGRAM_FORMAT as described in the XCP specification. Note, however, that
 * only non-compressed, non-encrypted, sequential programming using absolute access mode is supported.
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
uint XCP_FN_TYPE Xcp_CmdProgramFormat(
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
        uint8  compressionMethod;
        uint8  encryptionMethod;
        uint8  programmingMethod;
        uint8  accessMethod;
    } ) CmdPacket_t;

    const CmdPacket_t* const pCmdPacket = (CmdPacket_t*)pRxPacket;

    /* We only support non-compressed, non-encrypted, sequential, absolute mode programming. */
    if( pCmdPacket->compressionMethod == 0 && pCmdPacket->encryptionMethod == 0 &&
        pCmdPacket->programmingMethod == 0 && pCmdPacket->accessMethod == 0 )
    {
        pTxPacket->pid      = XCP_PID_RESPONSE;
        *pTxPacketSize      = 1;
    }
    else
    {
        pTxPacket->data[0]  = XCP_ERR_OUT_OF_RANGE;
        pTxPacket->pid      = XCP_PID_ERROR;
        *pTxPacketSize      = 2;
    }

    return XCP_RX_READY | XCP_TX_READY;
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

#endif /* XCP_ENABLE && XCP_ENABLE_PGM */
