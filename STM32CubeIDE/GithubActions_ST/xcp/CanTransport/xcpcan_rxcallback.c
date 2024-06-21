/**
*
* \file
*
* \brief Implements RX callback function.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_rxcallback.c 18723 2010-05-27 10:16:56Z olcritch $
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
 * This function is called by the CAN driver whenever a CAN message is received on a message object which is associated
 * with the XCP slave driver. Recall that system requirement 41900 states that:
 *  "Each CAN message object which is used by the XCP slave driver must be reserved exclusively for the XCP slave driver."
 *
 * The function tries to assign the received message to one of the channels maintained by the CAN transport layer. If this
 * is not possible, the function silently discards the message.
 *
 * This function is called from the CAN driver's RX interrupt, so we do not need to worry about re-entrancy.
 *
 * \param [in] msgId        The CAN message ID of the received CAN message.
 * \param [in] msgLen       The length of the received CAN message.
 * \param [in] pMsgData     The received CAN message. The caller can discard this after the function returns.
 */
void XCP_FN_TYPE XcpCan_RxCallback(
    uint32  msgId,
    uint8   msgLen,
    uint8*  pMsgData
)
{
    Xcp_StatePtr32        pCtCanPos;
    uint                  channelId;
    uint                  sessionId;
    XcpCan_SessionCfg_t*  pSessionCfg;
    Xcp_StatePtr8         pQueueBufState;
    uint32                cmdMsgId;
#ifdef XCP_ENABLE_STIM
    uint32                configuredMsgId;
    XcpCan_ChannelCfg_t*  pChannelCfg;
    Xcp_DaqConfig_t*      pDaqCfg;
    Xcp_Daq_t*            pDaqState;
#endif /* XCP_ENABLE_STIM */

    /* Search all CAN channels for all sessions to try to identify the CAN channel to which the RX message belongs. */

    for( sessionId = 0; sessionId < XCP_NUM_SESSIONS; ++sessionId )
    {
        /* Skip the current session unless it uses XCP-on-CAN. */
        if( XCP_CAN != Xcp_SessionConfigs[ sessionId ].transportLayerId )
        {
            continue;
        }
        pSessionCfg = XCPCAN_SESSIONCFG( sessionId );
        cmdMsgId    = pSessionCfg->pChannelCfgs[ XCP_RX_CMD_CHANNEL ].msgId;

        /* Is the CAN message is a broadcast CMD_GET_SLAVE_ID? */
        if( msgId == pSessionCfg->broadcastMsgId &&
            pMsgData[0] == XCP_CMD_TRANSPORT_LAYER_CMD && pMsgData[1] == XCPCAN_CMD_GET_SLAVE_ID )
        {
            channelId = XCP_RX_CMD_CHANNEL;
            break;
        }
        /* Is the CAN message a command? Note that it is not sufficient just to check the message's PID since the message
         * could be:
         *  - a command message destined for another session;
         *  - a PID_OFF STIM message, with no valid PID. */
        else if( pMsgData[0] >= XCP_PID_CMD_LAST && msgId == cmdMsgId )
        {
            /* The CAN message belongs to the XCP_RX_CMD_CHANNEL channel. */
            channelId = XCP_RX_CMD_CHANNEL;
            break;
        }
#ifdef XCP_ENABLE_STIM
        else
        {
            /* The CAN message does not contain a command, therefore it must contain a STIM DTO packet.
             * We search the CAN channels associated with STIM lists to find the channel to which the RX message belongs.
             *
             * Throughout, we assume that:
             *  - A CAN channel index can be translated to the equivalent DAQ list ID by subtracting XCP_FIRST_DAQ_CHANNEL.
             *  - The first STIM CAN channel has index XcpCan_SessionCfg_t::firstRxStimChannel.
             *  - The last STIM CAN channel has index XcpCan_SessionCfg_t::numChannels - 1.
             */

            channelId   = pSessionCfg->firstRxStimChannel;
            pChannelCfg = pSessionCfg->pChannelCfgs + channelId;
            pDaqState   = Xcp_SessionConfigs[ sessionId ].pDaqStates + channelId - XCP_FIRST_DAQ_CHANNEL;
            pDaqCfg     = Xcp_SessionConfigs[ sessionId ].pDaqConfigs + channelId - XCP_FIRST_DAQ_CHANNEL;

            for( ; channelId < pSessionCfg->numChannels; ++channelId )
            {
                /* Skip the current channel if it corresponds to a DAQ list which is not running or is not a STIM list. */
                if(   ( XCP_DAQLISTMODE_RUNNING | XCP_DAQLISTMODE_DIRECTION ) != 
                    ( ( XCP_DAQLISTMODE_RUNNING | XCP_DAQLISTMODE_DIRECTION ) & pDaqState->daqListMode ) )
                {
                    ++pChannelCfg;
                    ++pDaqState;
                    ++pDaqCfg;
                    continue;
                }

                /* Find the CAN msg ID which has been configured for the current channel. This is not entirely straightforward,
                 * because:
                 *  - The current channel may have been configured to use the default CAN RX msg ID. If this is the case, the
                 *    channel's config will indicate that the CAN msg ID is XCPCAN_INVALID_MSGID, and we will use the CAN msg ID
                 *    from the CMD channel instead.
                 *    (We take this approach so that we can handle DAQ_STIM lists, where the value of the "default" CAN msg ID
                 *    varies depending on whether the list is operating in DAQ mode or STIM mode).
                 *  - The msg ID of a dynamic DAQ list can be set at runtime.
                 * Fortunately these two possibilities are mutually exclusive.
                 */

                configuredMsgId = pChannelCfg->msgId;

                if( XCPCAN_INVALID_MSGID == configuredMsgId )
                {
                    /* Use the default CAN RX msg ID, i.e. the msg ID used by the CMD channel. */
                    configuredMsgId = cmdMsgId;
                }
#ifdef XCP_ENABLE_DYNDAQ
                else if( pSessionCfg->pDynDaqMsgIds &&
                         pSessionCfg->pDynDaqMsgIds[ channelId - XCP_FIRST_DAQ_CHANNEL ] != XCPCAN_INVALID_MSGID )
                {
                    /* The current channel is associated with a dynamic DAQ list, and the list has a msg ID which was configured
                     * at runtime. */
                    configuredMsgId = pSessionCfg->pDynDaqMsgIds[ channelId - XCP_FIRST_DAQ_CHANNEL ];
                }
#endif /* XCP_ENABLE_DYNDAQ */

                if( configuredMsgId == msgId )
                {
                    /* We have found a CAN channel which shares the same message ID as the RX message.
                     * If:
                     *  - the PID of the RX message is within the PID range of the DAQ list associated with the
                     *    current channel, or
                     *  - the current channel is associated with a DAQ list configured for PID_OFF mode,
                     * then the RX message belongs to the current channel.*/

                    if( ( (uint8)( pMsgData[0] - pDaqCfg->firstPid ) < pDaqCfg->numOdt ) ||
                        ( pDaqState->daqListMode & XCP_DAQLISTMODE_PIDOFF ) )
                    {
                        /* The CAN message belongs to the current STIM channel. */
                        break;
                    }
                }
                ++pChannelCfg;
                ++pDaqState;
                ++pDaqCfg;
            }

            if( channelId < pSessionCfg->numChannels )
            {
                /* The inner loop successfully identified the STIM channel which is associated with the RX message. */
                break;
            }
        }
#endif /* XCP_ENABLE_STIM */
    }

    if( sessionId == XCP_NUM_SESSIONS )
    {
        /* The RX message is not associated with any of our CAN channels. */
        return;
    }

    /* If we reach this point, sessionId and channelId identify the session and channel for which the RX message is intended. */

    pCtCanPos       = &( pSessionCfg->pQueuePositions[ channelId ].ctCanPos );
    pQueueBufState  = pSessionCfg->pQueueBufferStates + *pCtCanPos;

    /* Copy the received message to the current CAN buffer for the channel, if the current CAN buffer is free. */
    if( *pQueueBufState == XCPCAN_TXRXFREE )
    {
        /* Copy msgLen bytes of data into the current CAN buffer for the channel */
        Xcp_MemCopy( (Xcp_StatePtr8)pSessionCfg->pQueueBuffers[ *pCtCanPos ].msgBuffer, pMsgData, msgLen );

        /* Set current queue buffer to XCPCAN_RXDATA */
        *pQueueBufState = XCPCAN_RXDATA;

        /* Last buffer in queue? */
        if( *pCtCanPos != pSessionCfg->pChannelCfgs[ channelId ].idxEnd )
        {
            /* next queue buffer */
            ++( *pCtCanPos );
        }
        else
        {
            /* Back to queue start */
            *pCtCanPos = pSessionCfg->pChannelCfgs[ channelId ].idxStart;
        }
    }

    return;
}

#endif /* XCP_ON_CAN */
