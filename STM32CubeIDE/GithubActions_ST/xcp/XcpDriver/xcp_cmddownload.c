/**
*
* \file
*
* \brief XCP download commands.
*
* Note that if the CALPAG resource is disabled we still define DOWNLOAD commands since they can have uses other than
* calibration.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmddownload.c 18358 2010-03-25 13:57:40Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#if defined( XCP_ENABLE ) && defined( XCP_ENABLE_CALPAG )

/**
 * This function writes downloaded data to the ECU's memory. Note that some portions of this function (e.g. handling
 * block mode) may not be used when it is called in certain circumstances (e.g. from DOWNLOAD_MAX).
 *
 * \param [in] pSession         The state of the session which received the download command.
 * \param [in] numBytesToWrite  The number of bytes at pDataToWrite.
 * \param [in] pDataToWrite     The download data to be written to the ECU's memory.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacket       The response packet.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The downloaded data has been completely received and written to memory, or an error
 *                                  occurred and the write was aborted.
 *  - XCP_RX_READY                  The first block in the download block sequence has been received and written
 *                                  to memory. A response will not be sent to the XCP master; instead, it must send
 *                                  a DOWNLOAD_NEXT command.
 *  - 0                             The user application is processing an asynchronous request to write the download
 *                                  data to memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_WriteDownloadData(
    Xcp_Session_t*  pSession,
    uint            numBytesToWrite,
    Xcp_StatePtr8   pDataToWrite,
    uint            prevCmd,
    Xcp_Packet_t*   pTxPacket,
    uint*           pTxPacketSize
)
{
    Xcp_CalMemState writeResult;
    uint            retVal      = XCP_RX_READY | XCP_TX_READY;

    if( prevCmd != XCP_CMD_CURR_CMD )
    {
        /* This is the first time we have processed this command packet, so we ask the application to write the
         * downloaded data to memory. */
        writeResult = XcpApp_CalMemWrite( pSession->mta, numBytesToWrite, pDataToWrite );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * asked the application to write the downloaded data to memory.
         * 
         * Now we check to see what progress the application has made. */
        writeResult = XcpApp_CalMemGetRequestState();
    }

    *pTxPacketSize = 2;

    switch( writeResult )
    {
        case CALMEM_FINISHED:
            /* The application has finished writing the data to memory. */
            pSession->mta += numBytesToWrite;

            if( 0 != pSession->downloadRemainBytes )
            {
                /* We are in block mode and we expect the master to send more data, so we do not transmit a response yet. */
                retVal = XCP_RX_READY;
            }

            pTxPacket->pid = XCP_PID_RESPONSE;
            *pTxPacketSize = 1;
            break;

        case CALMEM_BUSY:
            /* The application has not yet finished writing the data to memory.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal = 0;
            *pTxPacketSize = 0;
            break;

        case CALMEM_OUTOFRAM:
            /* The application is out of memory. */
            pTxPacket->pid      = XCP_PID_ERROR;
            pTxPacket->data[0]  = XCP_ERR_MEMORY_OVERFLOW;
            break;

        case CALMEM_REJECTED:
            /* The application is temporarily unable to write the data to memory. The master may re-try. */
            pTxPacket->pid      = XCP_PID_ERROR;
            pTxPacket->data[0]  = XCP_ERR_CMD_BUSY;
            break;

        case CALMEM_REQUESTNOTVALID:
        default:
            pTxPacket->pid      = XCP_PID_ERROR;
            pTxPacket->data[0]  = XCP_ERR_ACCESS_DENIED;
    }

    return retVal;
}

/**
 * This function implements the XCP command DOWNLOAD as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The downloaded data has been completely received and written to memory.
 *  - XCP_RX_READY                  The first block in the download block sequence has been received and written
 *                                  to memory. A response will not be sent to the XCP master; instead, it must send
 *                                  a DOWNLOAD_NEXT command.
 *  - 0                             The user application is processing an asynchronous request to write the download
 *                                  data to memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdDownload(
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

    const CmdPacket_t* const   pCmdPacket      = (CmdPacket_t*)pRxPacket;
    uint                       numBytesToWrite = (uint) pCmdPacket->numBytes;
    const uint                 maxBlockSize    = Xcp_SessionConfigs[ sessionId ].maxCtoLen - 2;
    Xcp_Session_t* const       pSession        = Xcp_Sessions + sessionId;

    if( numBytesToWrite <= maxBlockSize )
    {
        /* The data to be downloaded is contained within this single command packet. */
        pSession->downloadRemainBytes = 0;
    }
    else
    {
        /* The data to be downloaded is larger than this command packet, so we are in block mode. */

        pSession->downloadRemainBytes = (uint8)( numBytesToWrite - maxBlockSize );
        numBytesToWrite = maxBlockSize;
    }

    return Xcp_WriteDownloadData( pSession, numBytesToWrite, pRxPacket->data + 1, prevCmd, pTxPacket, pTxPacketSize );
}

/**
 * This function implements the XCP command DOWNLOAD_NEXT as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The downloaded block sequence has been completely received and written to memory.
 *  - XCP_RX_READY                  A non-final block in the download block sequence has been received
 *                                  and written to memory. A response will not be sent to the XCP master; instead,
 *                                  it must send another DOWNLOAD_NEXT command.
 *  - 0                             The user application is processing an asynchronous request to write the download
 *                                  data block to memory. The command processor will mark this command as pending
 *                                  and will process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdDownloadNext(
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

    const uint               remainBytes = Xcp_Sessions[ sessionId ].downloadRemainBytes;
    const CmdPacket_t* const pCmdPacket  = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const      pRespPacket = (RespPacket_t*)pTxPacket;

    if( ( pCmdPacket->numBytes != remainBytes ) || ( remainBytes == 0 ) )
    {
        /* A sequence error has occurred. Either the master is not supplying the expected number of
         * download bytes or a block download is not in progress. */
        pRespPacket->pid              = XCP_PID_ERROR;
        pRespPacket->errorCode        = XCP_ERR_SEQUENCE;
        pRespPacket->numExpectedBytes = (uint8)remainBytes;
        *pTxPacketSize                = 3;

        return XCP_RX_READY | XCP_TX_READY;
    }

    return Xcp_CmdDownload( sessionId, pRxPacket, pTxPacket, prevCmd, pTxPacketSize );
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the XCP command DOWNLOAD_MAX as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The downloaded data has been completely received and written to memory.
 *  - 0                             The user application is processing an asynchronous request to write the download
 *                                  data to memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdDownloadMax(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    /* Note that we are never in block mode, so pSession->downloadRemainBytes is always zero at this point. */
    Xcp_Session_t* pSession = Xcp_Sessions + sessionId;

    return Xcp_WriteDownloadData( pSession, Xcp_SessionConfigs[ sessionId ].maxCtoLen - 1, pRxPacket->data, prevCmd, pTxPacket, pTxPacketSize );
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

/**
 * This function implements the XCP command MODIFY_BITS as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - 0                             The user application is processing an asynchronous request to write the modifications
 *                                  to memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdModifyBits(
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
        uint8  numShiftBits;
        uint16 andMask;
        uint16 xorMask;
    } ) CmdPacket_t;

    const CmdPacket_t* const pCmdPacket   = (CmdPacket_t*)pRxPacket;
    Xcp_CalMemState          writeResult;
    uint                     retVal       = XCP_RX_READY | XCP_TX_READY;

    if( prevCmd != XCP_CMD_CURR_CMD )
    {
        /* This is the first time we have processed this command packet, so we ask the application to modify the
         * bits in memory. */
        writeResult = XcpApp_CalMemModifyBits( Xcp_Sessions[ sessionId ].mta, pCmdPacket->numShiftBits, pCmdPacket->andMask, pCmdPacket->xorMask );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * asked the application to modify the bits in memory.
         * 
         * Now we check to see what progress the application has made. */
        writeResult = XcpApp_CalMemGetRequestState();
    }

    *pTxPacketSize = 2;

    switch( writeResult )
    {
        case CALMEM_FINISHED:
            /* The application has finished writing the data to memory. Note that we do *not* modify the MTA. */
            pTxPacket->pid  = XCP_PID_RESPONSE;
            *pTxPacketSize  = 1;
            break;

        case CALMEM_BUSY:
            /* The application has not yet finished modifying the bits.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal          = 0;
            *pTxPacketSize  = 0;
            break;

        case CALMEM_OUTOFRAM:
            /* The application is out of memory. */
            pTxPacket->pid          = XCP_PID_ERROR;
            pTxPacket->data[0]      = XCP_ERR_MEMORY_OVERFLOW;
            break;

        case CALMEM_REJECTED:
            /* The application is temporarily unable to write the data to memory. The master may re-try. */
            pTxPacket->pid          = XCP_PID_ERROR;
            pTxPacket->data[0]      = XCP_ERR_CMD_BUSY;
            break;

        case CALMEM_REQUESTNOTVALID:
        default:
            pTxPacket->pid          = XCP_PID_ERROR;
            pTxPacket->data[0]      = XCP_ERR_ACCESS_DENIED;
    }

    return retVal;
}

#endif /* XCP_ENABLE && XCP_ENABLE_CALPAG */
