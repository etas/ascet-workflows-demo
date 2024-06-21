/**
*
* \file
*
* \brief Implements XcpCan_RxNext().
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_rxnext.c 18358 2010-03-25 13:57:40Z olcritch $
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
 * This function pops (and discards) the RX buffer at the head of the specified channel's queue of buffers.
 *
 * \param [in] sessionId    The ID of the session associated with channelId.
 * \param [in] channelId    The ID of the channel whose RX buffer is to be discarded.
 */
void XCP_FN_TYPE XcpCan_RxNext(
    uint sessionId,
    uint channelId
)
{
    XcpCan_SessionCfg_t* const pSessionCfg     = XCPCAN_SESSIONCFG( sessionId );
    Xcp_StatePtr32             pXcpQueuePos    = &( pSessionCfg->pQueuePositions[ channelId ].ctXcpPos );
    Xcp_StatePtr8              pQueueBufState  = pSessionCfg->pQueueBufferStates + *pXcpQueuePos;

    /* Does the current XCP buffer of the specified channel contain a received message? */
    if( *pQueueBufState == XCPCAN_RXDATA )
    {
        *pQueueBufState = XCPCAN_TXRXFREE;

        /* Advance the current XCP queue position to the next entry in the queue,
         * wrapping if necessary. */
        if( *pXcpQueuePos != pSessionCfg->pChannelCfgs[ channelId ].idxEnd )
        {
            ++( *pXcpQueuePos );
        }
        else
        {
            *pXcpQueuePos = pSessionCfg->pChannelCfgs[ channelId ].idxStart;
        }
    }
    return;
}

#endif /* XCP_ON_CAN */
