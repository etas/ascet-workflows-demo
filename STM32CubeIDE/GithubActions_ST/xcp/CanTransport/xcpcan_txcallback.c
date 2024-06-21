/**
*
* \file
*
* \brief Implements XcpCan_TxCallback().
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_txcallback.c 18723 2010-05-27 10:16:56Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"

void XcpCan_DoTransmit( uint sessionId, uint channelId );

#ifdef XCP_ON_CAN

#include "xcpcan_inf.h"
#include "xcpcan_auto_confpriv.h"
#include "xcpcan_priv.h"

/**
 * This function is called by the CAN driver whenever a CAN message is successfully transmitted on a message object which
 * is associated with the XCP slave driver. Recall that system requirement 41900 states that:
 *  "Each CAN message object which is used by the XCP slave driver must be reserved exclusively for the XCP slave driver."
 *
 * This function identifies and transmits the highest priority CAN message (i.e. the message with the lowest ID) which is
 * waiting to be sent on the newly-freed message object.
 *
 * Note that this function is called from within the CAN driver's TX confirmation interrupt handler and therefore
 * it cannot be re-entered or interrupted by transmission from the XCP driver. It *can* be interrupted by XcpCan_RxCallback().
 *
 * \param [in] msgObjId     The CAN message object which has successfully transmitted a message.
 */
void XCP_FN_TYPE XcpCan_TxCallback(
    XcpCan_MsgObjId_t msgObjId
)
{
    uint                  channelId       = (uint)0xffffffff;
    uint                  sessionId       = (uint)0xffffffff;
    XcpCan_SessionCfg_t*  pSessionCfg;
    XcpCan_ChannelCfg_t*  pChannelCfg;
    XcpCan_QueuePos_t*    pQueuePositions;
    uint32                ctMsgId         = XCPCAN_INVALID_MSGID;
    uint32                configuredMsgId;
    uint32                respMsgId;
    uint                  i;
    uint                  j;
    Xcp_StatePtr8         pQueueBufState;

    if( 0 == --( XcpCan_TxPendingOnMsgObj[ msgObjId ] ) )
    {
        /* There is no message waiting to be sent on the newly-freed message object. */
        return;
    }

    /* Identify the highest priority CAN message (i.e. the message with the lowest ID) which is waiting to be
     * sent on the newly-freed message object.
     *
     * Throughout, we assume that:
     *  - A CAN channel index can be translated to the equivalent DAQ list ID by subtracting XCP_FIRST_DAQ_CHANNEL.
     *  - The first TX CAN channel in a session has index XCP_FIRST_TX_CHANNEL, which will be less than XCP_FIRST_DAQ_CHANNEL.
     *    (Recall that each session has a RESP channel and an EV channel, which have indices less than XCP_FIRST_DAQ_CHANNEL).
     *  - The last TX CAN channel in a session has index XcpCan_SessionCfg_t::lastTxChannel.
     */

    for( i = 0; i < XCP_NUM_SESSIONS; ++i )
    {
        /* Skip the current session unless it uses XCP-on-CAN. */
        if( XCP_CAN != Xcp_SessionConfigs[ i ].transportLayerId )
        {
            continue;
        }

        pSessionCfg     = XCPCAN_SESSIONCFG( i );
        pChannelCfg     = pSessionCfg->pChannelCfgs + XCP_FIRST_TX_CHANNEL;
        pQueuePositions = pSessionCfg->pQueuePositions + XCP_FIRST_TX_CHANNEL;
        respMsgId       = pSessionCfg->pChannelCfgs[ XCP_TX_CRM_CHANNEL ].msgId;

        /* Iterate over all TX channels for the current session. */
        for( j = XCP_FIRST_TX_CHANNEL; j <= pSessionCfg->lastTxChannel; ++j )
        {
            /* Does the current channel's current buffer contain a message which is:
             *  - waiting to be sent
             *  - and is associated with the newly-freed message object? */

            /* Note that while a buffer is waiting for transmission we store its length in the upper nibble of bufferState. */
            if( pChannelCfg->msgObjId == msgObjId &&
                ( pSessionCfg->pQueueBufferStates[ pQueuePositions->ctCanPos ] & 0x0f ) == XCPCAN_TXNOTSENT )
            {
                /* Find the CAN msg ID which has been configured for the current channel. This is not entirely straightforward,
                 * because:
                 *  - The current channel may have been configured to use the default CAN TX msg ID. If this is the case, the
                 *    channel's config will indicate that the CAN msg ID is XCPCAN_INVALID_MSGID, and we will use the CAN msg ID
                 *    from the RESP channel instead.
                 *    (We take this approach so that we can handle DAQ_STIM lists, where the value of the "default" CAN msg ID
                 *    varies depending on whether the list is operating in DAQ mode or STIM mode).
                 *  - The msg ID of a dynamic DAQ list can be set at runtime.
                 * Fortunately these two possibilities are mutually exclusive.
                 */

                configuredMsgId = pChannelCfg->msgId;

                if( XCPCAN_INVALID_MSGID == configuredMsgId )
                {
                    /* Use the default CAN TX msg ID, i.e. the msg ID used by the RESP channel. */
                    configuredMsgId = respMsgId;
                }
#ifdef XCP_ENABLE_DYNDAQ
                /* If:
                 *  - this session uses dynamic DAQ lists;
                 *  - and the current channel is a DAQ channel;
                 *  - and the current channel's CAN message ID has been configured at runtime.
                 */
                else if( pSessionCfg->pDynDaqMsgIds &&
                         j >= XCP_FIRST_DAQ_CHANNEL &&
                         pSessionCfg->pDynDaqMsgIds[ j - XCP_FIRST_DAQ_CHANNEL ] != XCPCAN_INVALID_MSGID )
                {
                    /* The current channel is associated with a dynamic DAQ list, and the list has a msg ID which was configured
                     * at runtime. */
                    configuredMsgId = pSessionCfg->pDynDaqMsgIds[ j - XCP_FIRST_DAQ_CHANNEL ];
                }
#endif /* XCP_ENABLE_DYNDAQ */

                /* Does the current channel's current buffer contain a message which has a higher priority (= lower msg ID)
                 * than any such message previously identified? */
                if( configuredMsgId < ctMsgId )
                {
                    sessionId = i;
                    channelId = j;
                    ctMsgId = configuredMsgId;
                }

                /* At this point we have found a CAN message which is waiting to be sent on the newly-freed message object.
                 * The question is: is this the highest priority such message in the current session?
                 *
                 * If XCP_ENABLE_DAQLIST_REORDERING is not defined we must iterate through every TX channel to discover the
                 * answer to this question. If XCP_ENABLE_DAQLIST_REORDERING is defined we can take a short-cut as described
                 * below. */

#ifdef XCP_ENABLE_DAQLIST_REORDERING
                /* At this point we have found a CAN message which is waiting to be sent on the newly-freed message object.
                 * The question is: is this the highest priority such message in the current session?
                 *
                 * We now note two facts:
                 *  - If the current session uses static DAQ lists the configuration tool will have ordered the DAQ channels
                 *    in ascending order of CAN message ID (i.e. descending order of priority).
                 *  - The loop which we are executing processes non-DAQ TX channels before it processes DAQ TX channels.
                 * 
                 * Therefore:
                 *  - if the current session uses static DAQ lists
                 *  - and if the current channel is a DAQ channel
                 * then we can be certain that the CAN message which we have found has the highest priority of any CAN message
                 * awaiting transmission (whether on a DAQ channel or a non-DAQ channel) in the current session.
                 */
                if( !pSessionCfg->pDynDaqMsgIds && j >= XCP_FIRST_DAQ_CHANNEL )
                {
                    break;
                }
#endif /* XCP_ENABLE_DAQLIST_REORDERING */
            }
            ++pChannelCfg;
            ++pQueuePositions;
        }
    }

    if( XCPCAN_INVALID_MSGID == ctMsgId )
    {
        /* There is no message waiting to be sent on the newly-freed message object.
         *
         * We really should not reach this point, because we checked above whether there were any messages waiting to be
         * sent on the newly-freed message object. */

        /* A tx is no longer in progress on this message object. */
        XcpCan_TxPendingOnMsgObj[ msgObjId ] = 0;

        return;
    }

    pSessionCfg    = XCPCAN_SESSIONCFG( sessionId );
    pQueueBufState = pSessionCfg->pQueueBufferStates + pSessionCfg->pQueuePositions[ channelId ].ctCanPos;

    /* While a buffer is waiting for transmission we store its length in the upper nibble of bufferState, so take
     * care to preserve that value while changing the state of the buffer. */
    *pQueueBufState &= 0xf0;
    *pQueueBufState |= XCPCAN_TXINPROGRESS;

    /* Transmit the message which we have identified. */
    XcpCan_DoTransmit( sessionId, channelId );

    return;
}

#endif /* XCP_ON_CAN */
