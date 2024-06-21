/**
*
* \file
*
* \brief Implements XcpCan_PeekRxBuf().
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_peekrxbuf.c 18551 2010-04-27 07:41:39Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"

#if defined( XCP_ON_CAN ) && defined( XCP_ENABLE_STIM )

#include "xcpcan_inf.h"
#include "xcpcan_auto_confpriv.h"
#include "xcpcan_priv.h"

/**
 * This function peeks into the queue of RX buffers on a specified channel.
 *
 * \param [in] sessionId    The ID of the session.
 * \param [in] channelId    The ID of the channel on which to peek.
 * \param [in] peekIdx      Peek into the queue of RX buffers at this depth. The caller guarantees this value
 *                          will never be larger than the number of elements in the queue.
 *
 * \return A pointer to the RX buffer at the specified depth in the queue, or 0 if no such buffer is available.
 */
Xcp_StatePtr8 XCP_FN_TYPE XcpCan_PeekRxBuf(
    uint sessionId,
    uint channelId,
    uint peekIdx
)
{
    XcpCan_SessionCfg_t* const pSessionCfg     = XCPCAN_SESSIONCFG( sessionId );
    XcpCan_ChannelCfg_t* const pChannelCfg     = pSessionCfg->pChannelCfgs + channelId;
    uint32                     ctXcpQueuePos   = pSessionCfg->pQueuePositions[ channelId ].ctXcpPos;

    /* Temporarily advance the current XCP buffer by peekIdx, wrapping if necessary. Note that peekIdx will
     * never be larger than the number of elements in the buffer queue. */

    ctXcpQueuePos += peekIdx;

    if( ctXcpQueuePos > pChannelCfg->idxEnd )
    {
        /* Wrap the queue index. */
        ctXcpQueuePos -= pChannelCfg->idxEnd;
        ctXcpQueuePos += pChannelCfg->idxStart - 1;
    }

    /* Does the peeked XCP buffer in the specified channel queue contain data to be received? */
    if( pSessionCfg->pQueueBufferStates[ ctXcpQueuePos ] == XCPCAN_RXDATA )
    {
        return (Xcp_StatePtr8)( pSessionCfg->pQueueBuffers[ ctXcpQueuePos ].msgBuffer );
    }

    return 0;
}

#endif /* XCP_ON_CAN && XCP_ENABLE_STIM */
