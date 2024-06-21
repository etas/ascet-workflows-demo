/**
*
* \file
*
* \brief Implements functions for transmitting CAN messages.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_txnext.c 18723 2010-05-27 10:16:56Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"

#ifdef XCP_ON_CAN

#include "xcpcan_inf.h"
#include "xcpcan_auto_confpriv.h"
#include "xcpcan_priv.h"

/**
 * This function transmits a CAN message containing the buffer which is at the head of a specified channel's queue
 * of buffers.
 *
 * The buffer is question is assumed to have the state XCPCAN_TXINPROGRESS. This function changes that state to
 * XCPCAN_TXRXFREE (thereby freeing the buffer) after XcpApp_CanTransmit() has returned.
 *
 * Note that:
 *  - This function assumes that it is allowed to discard the CAN message buffer after XcpApp_CanTransmit() returns.
 *  - This function cannot change the buffer state to XCPCAN_TXRXFREE until XcpApp_CanTransmit() has returned in case
 *    this task is pre-empted by another task which wishes to send a message on the same channel.
 *
 * \param [in] sessionId    The session associated with channelId.
 * \param [in] channelId    Transmit the buffer at the head of the queue for this channel.
 */
void XCP_FN_TYPE XcpCan_DoTransmit(
    uint sessionId,
    uint channelId
)
{
    XcpCan_SessionCfg_t* const pSessionCfg     = XCPCAN_SESSIONCFG( sessionId );
    XcpCan_ChannelCfg_t* const pChannelCfg     = pSessionCfg->pChannelCfgs + channelId;
    Xcp_StatePtr32 const       pCanPos         = &( pSessionCfg->pQueuePositions[ channelId ].ctCanPos );
    XcpCan_QueueBuf_t* const   pQueueBuffer    = pSessionCfg->pQueueBuffers + *pCanPos;
    Xcp_StatePtr8 const        pQueueBufState  = pSessionCfg->pQueueBufferStates + *pCanPos;

    /* Find the CAN msg ID which has been configured for the specified channel. This is not entirely straightforward,
     * because:
     *  - The specified channel may have been configured to use the default CAN TX msg ID. If this is the case, the
     *    channel's config will indicate that the CAN msg ID is XCPCAN_INVALID_MSGID, and we will use the CAN msg ID
     *    from the RESP channel instead.
     *    (We take this approach so that we can handle DAQ_STIM lists, where the value of the "default" CAN msg ID
     *    varies depending on whether the list is operating in DAQ mode or STIM mode).
     *  - The msg ID of a dynamic DAQ list can be set at runtime.
     * Fortunately these two possibilities are mutually exclusive.
     *
     * We assume that a DAQ CAN channel index can be translated to the equivalent DAQ list ID by subtracting XCP_FIRST_DAQ_CHANNEL.
     */

    uint32 configuredMsgId = pChannelCfg->msgId;

    if( XCPCAN_INVALID_MSGID == configuredMsgId )
    {
        /* Use the default CAN TX msg ID, i.e. the msg ID used by the RESP channel. */
        configuredMsgId = pSessionCfg->pChannelCfgs[ XCP_TX_CRM_CHANNEL ].msgId;
    }
#ifdef XCP_ENABLE_DYNDAQ
    else if( channelId >= XCP_FIRST_DAQ_CHANNEL &&
             Xcp_SessionConfigs[ sessionId ].maxDynDaqLists > 0 &&
             pSessionCfg->pDynDaqMsgIds[ channelId - XCP_FIRST_DAQ_CHANNEL ] != XCPCAN_INVALID_MSGID )
    {
        /* The current channel is associated with a dynamic DAQ list, and the list has a msg ID which was configured
         * at runtime. */
        configuredMsgId = pSessionCfg->pDynDaqMsgIds[ channelId - XCP_FIRST_DAQ_CHANNEL ];
    }

#endif /* XCP_ENABLE_DYNDAQ */

    /* Note that the CAN DLC is encoded in the top nibble of bufferState. */
    XcpApp_CanTransmit( pChannelCfg->msgObjId, configuredMsgId, (*pQueueBufState) >> 4, (Xcp_StatePtr8)pQueueBuffer->msgBuffer );

    /* Clear the queue buffer associated with the transmitted message. */
    pQueueBuffer->msgBuffer[0] = 0;
    pQueueBuffer->msgBuffer[1] = 0;

    /* Set buffer to free */
    *pQueueBufState = XCPCAN_TXRXFREE;

    /* Advance the current CAN buffer in the queue for the channel, wrapping if necessary. */
    if( *pCanPos != pChannelCfg->idxEnd )
    {
        ++( *pCanPos );
    }
    else
    {
        *pCanPos = pChannelCfg->idxStart;
    }
}

/**
 * This function performs three operations:
 *  1) It records the length of the buffer which is currently at the tail of the specified channel's queue
 *     of TX buffers.
 *  2) It places a new, empty buffer onto the tail of the specified channel's queue of TX buffers.
 *  3) It examines the buffer at the head of the specified channel's queue of TX buffers. If this buffer
 *     is awaiting transmission, and if the required CAN message object is available, the function transmits
 *     the buffer.
 *
 * \param [in] sessionId    The session associated with channelId.
 * \param [in] channelId    Transmit the buffer at the head of the queue for this channel.
 * \param [in] bufferLen    The length of the buffer currently at the tail of the channel's queue of TX buffers.
 */
void XCP_FN_TYPE XcpCan_TxNext(
    uint sessionId,
    uint channelId,
    uint bufferLen
)
{
    uint                       doTransmit      = 0;
    XcpCan_SessionCfg_t* const pSessionCfg     = XCPCAN_SESSIONCFG( sessionId );
    XcpCan_QueuePos_t* const   pQueuePositions = pSessionCfg->pQueuePositions + channelId;
    XcpCan_ChannelCfg_t* const pChannelCfg     = pSessionCfg->pChannelCfgs + channelId;
    const uint                 msgObjId        = pChannelCfg->msgObjId;
    Xcp_StatePtr8              pQueueBufState  = pSessionCfg->pQueueBufferStates + pQueuePositions->ctXcpPos;

    /* While a buffer is waiting for transmission we store its length in the upper nibble of bufferState. */
    *pQueueBufState = XCPCAN_TXNOTSENT | ( bufferLen << 4 );

    /* Advance the current XCP queue position to the next entry in the queue, wrapping if necessary. */
    if( pQueuePositions->ctXcpPos != pChannelCfg->idxEnd )
    {
        ++( pQueuePositions->ctXcpPos );
    }
    else
    {
        pQueuePositions->ctXcpPos = pChannelCfg->idxStart;
    }

    /* Is:
     *  - the entry at the current CAN position still waiting to be sent to the CAN driver,
     *  - and the CAN message object for the specified channel available for TX? (We assume that the CAN driver has no
     *    ability to buffer a message which is to be sent on a message object which is already in use).
     * If so, transmit the entry at the current CAN position in the queue.
     *
     * We disable interrupts to make this function re-entrant, and to guard against interruption from
     * TX confirmation. */
    XCP_DISABLE_ALL_INTERRUPTS();

    pQueueBufState = pSessionCfg->pQueueBufferStates + pQueuePositions->ctCanPos;

	if( XCPCAN_TXNOTSENT == ( (*pQueueBufState) & 0x0f ) && 0 == XcpCan_TxPendingOnMsgObj[ msgObjId ] )
	{
        /* While a buffer is waiting for transmission we store its length in the upper nibble of bufferState, so take
         * care to preserve that value while changing the state of the buffer.
         *
         * We need to change the buffer's state so that it is != XCPCAN_TXNOTSENT in case XcpCan_TxCallback() is called as
         * soon as we call XcpApp_CanTransmit().
         */
        *pQueueBufState &= 0xf0;
        *pQueueBufState |= XCPCAN_TXINPROGRESS;

		doTransmit = 1;
	}

    ++( XcpCan_TxPendingOnMsgObj[ msgObjId ] );

    XCP_ENABLE_ALL_INTERRUPTS();

	if( doTransmit )
    {
        XcpCan_DoTransmit( sessionId, channelId );
    }
    return;
}

#endif /* XCP_ON_CAN */
