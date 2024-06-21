/**
*
* \file
*
* \brief "Seed and key" XCP commands.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmdseednkey.c 18358 2010-03-25 13:57:40Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#if defined( XCP_ENABLE ) && defined( XCP_ENABLE_SEEDNKEY )

/* Possible states of the seed/key mechanism, and the associated values of Xcp_Session_t members, are:
 *
 *  State                   unlockResource      pRemainSeed     seedRemainBytes     pKey
 *  -----                   --------------      -----------     ---------------     ----
 *  GET_SEED not begun      0                   0               0                   0
 *  GET_SEED begun          >0                  >0              >0                  invalid
 *  GET_SEED finished       >0                  0               0                   0
 *  UNLOCK begun            >0                  invalid         0                   >0
 *
 * The mechanism is initially in the state "GET_SEED not begun" and reverts there when DISCONNECT occurs.
 *
 * If an UNLOCK sequence completes successfully the mechanism returns to the state "GET_SEED finished".
 *
 * If an UNLOCK sequence completes unsuccessfully then DISCONNECT occurs and the mechanism returns to the state
 * "GET_SEED not begun".
 *
 * If GET_SEED is received the mechanism immediately goes to the state "GET_SEED begun", no matter which state
 * it was in previously.
 *
 * Note that pRemainSeed and pKey are members of a union. pRemainSeed is valid in the state "GET_SEED begun";
 * pKey is valid in the state "UNLOCK begun". *Both* pKey and pRemainSeed are valid in the states "GET_SEED not begun"
 * and "GET_SEED finished" because both are 0.
 */

/**
 * This function implements the XCP command GET_SEED as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdGetSeed(
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
        uint8  mode;
        uint8  resource;
    } ) CmdPacket_t;

    const CmdPacket_t* const pCmdPacket = (CmdPacket_t*)pRxPacket;
    uint                     maxCtoLen  = Xcp_SessionConfigs[ sessionId ].maxCtoLen;
    Xcp_Session_t* const     pSession   = Xcp_Sessions + sessionId;
    Xcp_Seed_t*              pSeed;
    uint                     seedLen;

    *pTxPacketSize = 2;
    pTxPacket->pid = XCP_PID_RESPONSE;

    /* Is the XCP master trying to unlock a resource which is not currently protected? */
    if( 0 != pCmdPacket->resource && !( pCmdPacket->resource & pSession->ctResourceProtection ) )
    {
        pTxPacket->data[0] = 0;
        return XCP_RX_READY | XCP_TX_READY;
    }

    if( 0 == pCmdPacket->mode )
    {
        /* This is the first call to the GET_SEED command. */

        if( pCmdPacket->resource == XCP_RESOURCE_CAL_PAG ||
            pCmdPacket->resource == XCP_RESOURCE_DAQ ||
            pCmdPacket->resource == XCP_RESOURCE_STIM ||
            pCmdPacket->resource == XCP_RESOURCE_PGM )
        {
            /* We are entering the state "GET_SEED begun" (see above). */
            XcpApp_GetSeed( sessionId, pCmdPacket->resource, &( pSession->seedOrKey.pRemainSeed ), &( pSession->seedRemainBytes ) );

            pSession->unlockResource = pCmdPacket->resource;
        }
        else
        {
            /* The XCP master has requested the key for an unknown resource, or for more than a single resource. */
            pTxPacket->pid      = XCP_PID_ERROR;
            pTxPacket->data[0]  = XCP_ERR_OUT_OF_RANGE;
        }
    }
    else if( 0 == pSession->seedRemainBytes )
    {
        /* This is a subsequent call to the GET_SEED command, but we are not in the state "GET_SEED begun" (see above). */
        pTxPacket->pid      = XCP_PID_ERROR;
        pTxPacket->data[0]  = XCP_ERR_SEQUENCE;
    }

    /* Has an error occurred so far? */
    if( XCP_PID_ERROR == pTxPacket->pid )
    {
        return XCP_RX_READY | XCP_TX_READY;
    }

    /* We are now in the state "GET_SEED begun" (see above). */

    /* Get details of how much of the seed remains to be transmitted. */
    seedLen = pSession->seedRemainBytes;
    pSeed   = pSession->seedOrKey.pRemainSeed;

    if( seedLen > (uint)( maxCtoLen - 2 ) )
    {
        /* The seed is too big to fit in a single response packet, so transmit a portion of it only. Adjust seedLen to
         * give the length of this portion.
         *
         * Record how much of the seed is left so we can transmit the next portion in the next call to this command. */
        pSession->seedRemainBytes        = seedLen - ( maxCtoLen - 2 );
        seedLen                          = maxCtoLen - 2;
        pSession->seedOrKey.pRemainSeed += seedLen;
    }
    else
    {
        /* We can transmit the seed in a single response packet, so after this there will be none of the seed remaining.
         *
         * We are entering the state "GET_SEED finished" (see above). */
        pSession->seedRemainBytes       = 0;
        pSession->seedOrKey.pRemainSeed = 0;
    }

    /* Transmit the seed (or a portion of it). */
    *pTxPacketSize      = seedLen + 2;
    pTxPacket->data[0]  = (uint8)seedLen + pSession->seedRemainBytes;    /* The amount of seed remaining *including* this portion. */

    Xcp_MemCopy( pTxPacket->data + 1, pSeed, seedLen );

    return XCP_RX_READY | XCP_TX_READY;
}

/**
 * This function implements the XCP command UNLOCK as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdUnlock(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    Xcp_Session_t* const pSession    = Xcp_Sessions + sessionId;
    uint                 keyComplete = 0;

    /* Are we in the state "GET_SEED not begun" or the state "GET_SEED begun" (see above)? */
    if( 0 == pSession->unlockResource || 0 != pSession->seedRemainBytes )
    {
        *pTxPacketSize     = 2;
        pTxPacket->pid     = XCP_PID_ERROR;
        pTxPacket->data[0] = XCP_ERR_SEQUENCE;

        return XCP_RX_READY | XCP_TX_READY;
    }
    /* We are now in either the state "GET_SEED finished" or the state "UNLOCK begun" (see above). */

    if( !pSession->seedOrKey.pKey )
    {
        /* This is the first call to UNLOCK so get a key buffer.
         *
         * We are entering the state "UNLOCK begun" (see above). */

        XcpApp_GetKeyBuffer( sessionId, pSession->unlockResource, &( pSession->seedOrKey.pKey ), pRxPacket->data[0] );
    }
    /* We are now in the state "UNLOCK begun" (see above). */

    if( pRxPacket->data[0] > (uint)( Xcp_SessionConfigs[ sessionId ].maxCtoLen - 2 ) )
    {
        /* The key is too long to fit in the command packet; more key will be sent in another call to UNLOCK.
         *
         * Adjust the key length to reflect the amount of key present in the packet. */
        pRxPacket->data[0] = Xcp_SessionConfigs[ sessionId ].maxCtoLen - 2;
    }
    else
    {
        /* The key is completely present in the command packet. */
        keyComplete = 1;
    }

    /* Store the portion of key which we received in the command packet. */
    Xcp_MemCopy( pSession->seedOrKey.pKey, pRxPacket->data + 1, pRxPacket->data[0] );

    *pTxPacketSize = 2;
    pTxPacket->pid = XCP_PID_RESPONSE;

    if( keyComplete )
    {
        if( XcpApp_UnlockResource( sessionId, pSession->unlockResource ) )
        {
            /* We are entering the state "GET_SEED finished" (see above). */
            pSession->ctResourceProtection &= ~(pSession->unlockResource);
            pSession->seedOrKey.pKey        = 0;
            pTxPacket->data[0]              = pSession->ctResourceProtection;
        }
        else
        {
            /* We are entering the state "GET_SEED not begun" (see above). */
            Xcp_DoDisconnect( sessionId, pSession );

            pTxPacket->pid     = XCP_PID_ERROR;
            pTxPacket->data[0] = XCP_ERR_ACCESS_LOCKED;
        }
    }
    else
    {
        /* More of the key will be sent in another call to UNLOCK; adjust our key buffer pointer in readiness
         * for the next portion of the key. */
        pSession->seedOrKey.pKey += pRxPacket->data[0];

        pTxPacket->data[0] = pSession->ctResourceProtection;
    }

    return XCP_RX_READY | XCP_TX_READY;
}

#endif /* XCP_ENABLE && XCP_ENABLE_SEEDNKEY */
