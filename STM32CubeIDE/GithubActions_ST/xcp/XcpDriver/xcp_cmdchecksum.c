/**
*
* \file
*
* \brief XCP command BUILD_CHECKSUM
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmdchecksum.c 17051 2009-11-24 09:37:39Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#ifdef XCP_ENABLE

/**
 * This function implements the XCP command BUILD_CHECKSUM as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 *  - 0                             The user application is processing a checksum request asynchronously. The command processor will
 *                                  mark this command as being pending and will process it again on the next tick.
 *                                  No response will be transmitted to the master.
 */
uint XCP_FN_TYPE Xcp_CmdBuildChecksum(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8   pid;
        uint8   reserved1;
        uint8   reserved2;
        uint8   reserved3;
        uint32  blockSize;
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  checksumType;
        uint8  reserved1;
        uint8  reserved2;
        uint32 checksum;
    } ) RespPacketPositive_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  errorCode;
        uint8  reserved1;
        uint8  reserved2;
        uint32 maxBlockSize;
    } ) RespPacketNegative_t;

    const CmdPacket_t* const    pCmdPacket          = (CmdPacket_t*)pRxPacket;
    RespPacketPositive_t* const pRespPacketPositive = (RespPacketPositive_t*)pTxPacket;
    RespPacketNegative_t* const pRespPacketNegative = (RespPacketNegative_t*)pTxPacket;
    Xcp_CalMemState             checksumResult;
    uint                        retVal              = XCP_RX_READY | XCP_TX_READY;

    *pTxPacketSize = 8;

    /* Is the caller requesting a block size which is too big?*/
    if( pCmdPacket->blockSize > XCP_MAX_CHECKSUM_BLOCKSIZE )
    {
        pRespPacketNegative->pid          = XCP_PID_ERROR;
        pRespPacketNegative->errorCode    = XCP_ERR_OUT_OF_RANGE;
        pRespPacketNegative->maxBlockSize = XCP_MAX_CHECKSUM_BLOCKSIZE;

        return XCP_RX_READY | XCP_TX_READY;
    }

    if( prevCmd != XCP_CMD_CURR_CMD )
    {
        /* This is the first time we have processed this command packet, so we ask the application to build the checksum. */
        checksumResult = XcpApp_CalMemGetChecksum( Xcp_Sessions[ sessionId ].mta, pCmdPacket->blockSize, &( pRespPacketPositive->checksumType ), &( pRespPacketPositive->checksum ) );
    }
    else
    {
        /* We have already processed this command packet at least once before, and therefore we have already
         * asked the application to calculate the checksum.
         * 
         * Now we check to see what progress the application has made. */
        checksumResult = XcpApp_CalMemGetRequestState();
    }

    switch( checksumResult )
    {
        case CALMEM_FINISHED:
            /* The application has finished building the checksum. */
            Xcp_Sessions[ sessionId ].mta += pCmdPacket->blockSize;

            pRespPacketPositive->pid = XCP_PID_RESPONSE;
            break;

        case CALMEM_BUSY:
            /* The application has not yet finished building the checksum.
             * The command processor will mark this command as being pending and will process it again on
             * the next tick. No response will be transmitted to the master. */
            retVal = 0ul;
            *pTxPacketSize = 0;
            break;

        case CALMEM_REJECTED:
            /* The application is temporarily unable to build the checksum. The master may re-try. */
            pTxPacket->data[0] = XCP_ERR_CMD_BUSY;
            pTxPacket->pid     = XCP_PID_ERROR;
            *pTxPacketSize     = 2;
            break;

        case CALMEM_REQUESTNOTVALID:
        default:
            pRespPacketNegative->pid          = XCP_PID_ERROR;
            pRespPacketNegative->errorCode    = XCP_ERR_OUT_OF_RANGE;
            pRespPacketNegative->maxBlockSize = XCP_MAX_CHECKSUM_BLOCKSIZE;
    }

    return retVal;
}

#endif /* XCP_ENABLE */
