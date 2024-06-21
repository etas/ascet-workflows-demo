/**
*
* \file
*
* \brief Implements XcpCan_GetTxBuf().
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_gettxbuf.c 18358 2010-03-25 13:57:40Z olcritch $
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
 * This function returns a pointer to the TX buffer at the tail of the specified channel's
 * queue of buffers.
 *
 * Note that this function does not modify the queue's state and that therefore a second call to
 * this function (with the same arguments) will return the same buffer.
 *
 * \param [in] sessionId    The ID of the session requesting an RX buffer.
 * \param [in] channelId    The ID of the channel for which an RX buffer is required.
 *
 * \return A pointer to the next available RX buffer, or 0 if no such buffer is available.
 */
Xcp_StatePtr8 XCP_FN_TYPE XcpCan_GetTxBuf(
    uint sessionId,
    uint channelId
)
{
    XcpCan_SessionCfg_t* const pSessionCfg     = XCPCAN_SESSIONCFG( sessionId );
    const uint32               ctXcpQueuePos   = pSessionCfg->pQueuePositions[ channelId ].ctXcpPos;
    Xcp_StatePtr8 const        pQueueBufState  = pSessionCfg->pQueueBufferStates + ctXcpQueuePos;

    /* Is the current XCP buffer in the specified channel queue free or already allocated?
     *
     * (Note that if this method is called twice for the same channel, with no intervening call to
     * XcpCan_TxNext(), we will allocate the same buffer twice.) */

    if( ( *pQueueBufState == XCPCAN_TXRXFREE ) ||
        ( *pQueueBufState == XCPCAN_TXALLOC ) )
    {
        *pQueueBufState = XCPCAN_TXALLOC;

        return (Xcp_StatePtr8)( pSessionCfg->pQueueBuffers[ ctXcpQueuePos ].msgBuffer );
    }

    return 0;
}

#endif /* XCP_ON_CAN */
