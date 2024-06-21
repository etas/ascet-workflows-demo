/**
*
* \file
*
* \brief Implements XcpCan_GetRxBuf().
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_getrxbuf.c 18358 2010-03-25 13:57:40Z olcritch $
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
 * This function returns a pointer to the RX buffer at the head of the specified channel's
 * queue of buffers. Buffers are pushed onto the tail of the queue when the CAN driver calls XcpCan_RxCallback().
 *
 * Note that this function does not pop the buffer from the queue and that therefore a second call to
 * this function (with the same arguments) will return the same buffer.
 *
 * \param [in] sessionId    The ID of the session requesting an RX buffer.
 * \param [in] channelId    The ID of the channel for which an RX buffer is required.
 *
 * \return A pointer to the next available RX buffer, or 0 if no such buffer is available.
 */
Xcp_StatePtr8 XCP_FN_TYPE XcpCan_GetRxBuf(
    uint sessionId,
    uint channelId
)
{
    XcpCan_SessionCfg_t* const pSessionCfg   = XCPCAN_SESSIONCFG( sessionId );
    const uint32               ctXcpQueuePos = pSessionCfg->pQueuePositions[ channelId ].ctXcpPos;

    /* Does the current XCP buffer in the specified channel queue contain data to be received? */
    if( pSessionCfg->pQueueBufferStates[ ctXcpQueuePos ] == XCPCAN_RXDATA )
    {
        return (Xcp_StatePtr8)( pSessionCfg->pQueueBuffers[ ctXcpQueuePos ].msgBuffer );
    }

    return 0;
}

#endif /* XCP_ON_CAN */
