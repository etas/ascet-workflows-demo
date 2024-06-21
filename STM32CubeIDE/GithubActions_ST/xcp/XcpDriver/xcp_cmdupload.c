/**
*
* \file
*
* \brief XCP upload commands.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmdupload.c 18358 2010-03-25 13:57:40Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#ifdef XCP_ENABLE

/**
 * This function reads upload data from the ECU's memory. Note that some portions of this function (e.g. handling
 * block mode) may not be used when it is called in certain circumstances (e.g. from SHORT_UPLOAD).
 *
 * \param [in] pSession                 The state of the session which received the download command.
 * \param [in] prevCmd                  The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [in] numBytesToRead           The number of bytes to be read from the MTA.
 * \param [in, out] pTotBytesToRead     The total number of bytes to be read. If we are in block mode this may be greater than numBytesToRead.
 * \param [out] pTxPacket               The response packet.
 * \param [out] pTxPacketSize           The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The upload data has been completely transmitted to the XCP master.
 *  - XCP_TX_READY                  A non-final block in the upload block sequence is ready to be transmitted to the
 *                                  XCP master. This command will not be discarded; instead the command processor will
 *                                  mark it as pending and will re-process it on the next tick, causing a further
 *                                  upload block to be transmitted.
 *  - 0                             The user application is processing an asynchronous request to read the upload
 *                                  data from memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_ReadUploadData(
    Xcp_Session_t*  pSession,
    uint            prevCmd,
    uint            numBytesToRead,
    Xcp_StatePtr8   pTotBytesToRead,
    Xcp_Packet_t*   pTxPacket,
    uint*           pTxPacketSize
)
{
    Xcp_CalMemState readResult;
    uint            retVal      = XCP_RX_READY | XCP_TX_READY;

    if( prevCmd != XCP_CMD_CURR_CMD)
    {
        /* This is the first time we have processed this command packet, so we ask the application to read
         * the upload data from memory. */
        readResult = XcpApp_CalMemRead( pSession->mta, numBytesToRead, pTxPacket->data );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * asked the application to read the upload data from memory.
         * 
         * Now we check to see what progress the application has made. */
        readResult = XcpApp_CalMemGetRequestState();
    }

    *pTxPacketSize = 2;

    switch( readResult )
    {
        case CALMEM_FINISHED:
            /* The application has reading the data from memory. */
            pSession->mta += numBytesToRead;
            *pTotBytesToRead -= (uint8)numBytesToRead;

            if( *pTotBytesToRead > 0 )
            {
                /* We are in block mode and there is still more data to be uploaded. Tell the command processor to
                 * send a response but not to discard the current command. We will process it again and upload more
                 * data on the next tick. */
                retVal = XCP_TX_READY;
            }

            pTxPacket->pid = XCP_PID_RESPONSE;
            *pTxPacketSize = numBytesToRead + 1;
            break;

        case CALMEM_BUSY:
            /* The application has not yet finished reading the data from memory.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal = 0ul;
            *pTxPacketSize = 0;
            break;

        case CALMEM_REJECTED:
            /* The application is temporarily unable to read the data from memory. The master may re-try. */
            pTxPacket->data[0] = XCP_ERR_CMD_BUSY;
            pTxPacket->pid     = XCP_PID_ERROR;
            break;

        case CALMEM_REQUESTNOTVALID:
        default:
            pTxPacket->data[0] = XCP_ERR_ACCESS_DENIED;
            pTxPacket->pid     = XCP_PID_ERROR;
    }

    return retVal;
}

/**
 * This function implements the XCP command UPLOAD as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The upload data has been completely transmitted to the XCP master.
 *  - XCP_TX_READY                  A non-final block in the upload block sequence is ready to be transmitted to the
 *                                  XCP master. This command will not be discarded; instead the command processor will
 *                                  mark it as pending and will re-process it on the next tick, causing a further
 *                                  upload block to be transmitted.
 *  - 0                             The user application is processing an asynchronous request to read the upload
 *                                  data from memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdUpload(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    const uint           maxBlockSize    = Xcp_SessionConfigs[ sessionId ].maxCtoLen - 1;
    Xcp_Session_t* const pSession        = Xcp_Sessions + sessionId;
    uint                 numBytesToRead  = pRxPacket->data[0];

    if( numBytesToRead > maxBlockSize )
    {
        numBytesToRead = maxBlockSize;
    }

    return Xcp_ReadUploadData( pSession, prevCmd, numBytesToRead, pRxPacket->data, pTxPacket, pTxPacketSize );
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the XCP command SHORT_UPLOAD as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   The upload data has been completely transmitted to the XCP master.
 *  - 0                             The user application is processing an asynchronous request to read the upload
 *                                  data from memory. The command processor will mark this command as pending and will
 *                                  process it again on the next tick. No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdShortUpload(
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
        uint8  reserved2;
        uint8  addrExt;
        uint32 addr;
    } ) CmdPacket_t;

    CmdPacket_t* const   pCmdPacket = (CmdPacket_t*) pRxPacket;
    Xcp_Addr_t           newMta;
    Xcp_Session_t* const pSession   = Xcp_Sessions + sessionId;

    *pTxPacketSize = 2;

	newMta = XcpApp_ConvertAddress( pCmdPacket->addr, pCmdPacket->addrExt );

    if( 0 == newMta )
    {
        /* The master is not permitted to read from the specified region. */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        pTxPacket->pid     = XCP_PID_ERROR;

        return XCP_RX_READY | XCP_TX_READY;
    }

    pSession->mta = newMta;

    if( pCmdPacket->numBytes > (uint)( Xcp_SessionConfigs[ sessionId ].maxCtoLen - 1 ) )
    {
        /* The requested number of bytes is too much for a SHORT_UPLOAD */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        pTxPacket->pid     = XCP_PID_ERROR;

        return XCP_RX_READY | XCP_TX_READY;
    }

    /* Note that Xcp_ReadUploadData() may modify pCmdPacket->numBytes. */
    return Xcp_ReadUploadData( pSession, prevCmd, pCmdPacket->numBytes, &( pCmdPacket->numBytes ), pTxPacket, pTxPacketSize );
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

#endif /* (XCP_ENABLE) */
