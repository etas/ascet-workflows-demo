/**
*
* \file
*
* \brief Implements functions which initialize and reset state within the CAN transport layer.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_init.c 18358 2010-03-25 13:57:40Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_auto_confdefs.h"
#include "xcp_auto_conf.h"
#include "xcp_priv.h"

#ifdef XCP_ON_CAN

#include "xcpcan_inf.h"
#include "xcpcan_auto_confpriv.h"
#include "xcpcan_priv.h"

/**
 * This function resets the state maintained by the CAN transport layer for a specific DAQ list.
 *
 * This function assumes that the specified DAQ list has been stopped before this function is called.
 *
 * \param [in] sessionId    The ID of the session.
 * \param [in] daqListId    The ID of the DAQ list whose state is to be reset.
 */
void XCP_FN_TYPE XcpCan_ResetDaqList(
    uint sessionId,
    uint daqListId
)
{
    XcpCan_SessionCfg_t* const pCanSessionCfg  = XCPCAN_SESSIONCFG( sessionId );
    const uint                 channelId       = daqListId + XCP_FIRST_DAQ_CHANNEL;
    XcpCan_ChannelCfg_t* const pChannelCfg     = pCanSessionCfg->pChannelCfgs + channelId;
    uint32                     i;

    /* Prevent any further messages from being sent or received on the channel which is associated with the specified
     * DAQ list. */
    for( i = pChannelCfg->idxStart; i <= pChannelCfg->idxEnd; ++i )
    {
        /* We assume that this write is atomic. */
        pCanSessionCfg->pQueueBufferStates[ i ] = XCPCAN_TXRXFREE;
    }

    /* Reset both CAN and XCP queue positions for the channel to the start of the queue. */
    pCanSessionCfg->pQueuePositions[ channelId ].ctCanPos = pChannelCfg->idxStart;
    pCanSessionCfg->pQueuePositions[ channelId ].ctXcpPos = pChannelCfg->idxStart;

#ifdef XCP_ENABLE_DYNDAQ
    /* If the specified DAQ list is dynamic, reset its configured CAN msg ID. */
    if( Xcp_SessionConfigs[ sessionId ].maxDynDaqLists > 0 )
    {
        pCanSessionCfg->pDynDaqMsgIds[ daqListId ] = XCPCAN_INVALID_MSGID;
    }
#endif /* XCP_ENABLE_DYNDAQ */
}

/**
 * This function initialises the CAN transport layer. It must be called exactly once.
 */
void XCP_FN_TYPE XcpCan_Initialize( void )
{
    uint                  i;
    uint                  sessionId;
    Xcp_SessionConfig_t*  pSessionCfg       = Xcp_SessionConfigs;
    XcpCan_SessionCfg_t*  pCanSessionCfg;

    for( sessionId = 0; sessionId < XCP_NUM_SESSIONS; ++sessionId )
    {
        if( XCP_CAN == pSessionCfg->transportLayerId )
        {
            pCanSessionCfg = (XcpCan_SessionCfg_t*)( pSessionCfg->pTransportCfg );

            for( i = 0; i < pCanSessionCfg->numChannels; ++i )
            {
                /* Reset both CAN and XCP queue positions to the start of the queue. */
                pCanSessionCfg->pQueuePositions[ i ].ctCanPos = pCanSessionCfg->pChannelCfgs[ i ].idxStart;
                pCanSessionCfg->pQueuePositions[ i ].ctXcpPos = pCanSessionCfg->pChannelCfgs[ i ].idxStart;
            }

#ifdef XCP_ENABLE_DYNDAQ
            /* Reset all CAN msg IDs configured at runtime for dynamic DAQ lists. */
            for( i = 0; i < pSessionCfg->maxDynDaqLists; ++i )
            {
                pCanSessionCfg->pDynDaqMsgIds[ i ] = XCPCAN_INVALID_MSGID;
            }
#endif /* XCP_ENABLE_DYNDAQ */
        }

        ++pSessionCfg;
    }

    return;
}

#endif /* XCP_ON_CAN */
