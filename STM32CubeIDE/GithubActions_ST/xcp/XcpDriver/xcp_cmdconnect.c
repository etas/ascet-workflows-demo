/**
*
* \file
*
* \brief XCP connection commands.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmdconnect.c 18661 2010-05-18 07:50:50Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#ifdef XCP_ENABLE

/**
 * This function implements the XCP command CONNECT as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdConnect(
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
        uint8  cxnMode;
    } ) CmdPacket_t;

	typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  resourcesAvailable;
        uint8  commModeBasic;
        uint8  maxCto;
        uint16 maxDto;
        uint8  protocolLayerVer;
        uint8  transportLayerVer;
    } ) RespPacket_t;

    const CmdPacket_t* const   pCmdPacket  = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const        pRespPacket = (RespPacket_t*) pTxPacket;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;

    /* Notify the user application of our connection mode. */
    if( 1 == pCmdPacket->cxnMode )
    {
        XcpApp_OnUserDefinedCxn( sessionId );
    }
    else
    {
        XcpApp_OnNormalCxn( sessionId );
    }

    pRespPacket->pid                = XCP_PID_RESPONSE;
    pRespPacket->resourcesAvailable = XCP_RESOURCES_AVAILABLE;
    pRespPacket->commModeBasic      = 0x80 |    /* OPTIONAL */
                                      0x40 |    /* SLAVE_BLOCK_MODE */
                                      0x00 |    /* ADDRESS_GRANULARITY = BYTE*/
                                      XCP_TARGET_BYTE_ORDER;
                                      
    pRespPacket->maxCto             = pSessionCfg->maxCtoLen;
    pRespPacket->maxDto             = pSessionCfg->maxDtoLen;
    pRespPacket->protocolLayerVer   = XCP_PROTOCOL_VERSION;
    pRespPacket->transportLayerVer  = 1;

    Xcp_Sessions[ sessionId ].isConnected = 1;

    *pTxPacketSize = 8;
    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function resets various parts of the state of a DAQ list.
 *
 * \param [in] sessionId    The ID of the session.
 * \param [in] daqListId    The ID of the DAQ list whose state is to be reset.
 */
void XCP_FN_TYPE Xcp_ResetDaqList(
    uint sessionId,
    uint daqListId
)
{
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;
    Xcp_Daq_t* const           pDaqState   = pSessionCfg->pDaqStates + daqListId;
    Xcp_DaqConfig_t* const     pDaqConfig  = pSessionCfg->pDaqConfigs + daqListId;

    /* Clear the state of the DAQ list.
     * Note that it is important that the first action we take causes the DAQ list to stop running. */

    pDaqState->daqListMode  = 0;
    pDaqState->maxOdtIdUsed = 0;
    pDaqState->daqEvent     = pDaqConfig->defaultEvent;

    /* Set an appropriate default direction for the DAQ list.
     * (If the DAQ list supports both DAQ and STIM we default to DAQ). */
    if( pDaqConfig->properties & XCP_DAQLISTPROPERTY_DAQ )
    {
        pDaqState->daqListMode &= ~XCP_DAQLISTMODE_DIRECTION;
    }
    else
    {
        pDaqState->daqListMode |= XCP_DAQLISTMODE_DIRECTION;
    }

    /* Reset any DAQ list state held by the transport layer. It is important that the DAQ list is stopped before
     * doing this. */
    pSessionCfg->pResetDaqList( sessionId, daqListId );
}

/**
 * This function disconnects the specified session and resets all session-specific state.
 *
 * \param [in] sessionId        The index of the session.
 * \param [in] pSession         The state of the session.
 */
void XCP_FN_TYPE Xcp_DoDisconnect(
    uint            sessionId,
    Xcp_Session_t*  pSession
)
{
    uint                       daqListId;
    Xcp_SessionConfig_t* const pSessionCfg = Xcp_SessionConfigs + sessionId;

    /* Notify the user application. */
    XcpApp_OnDisconnect( sessionId );

    /* Clear the state of all DAQ lists. */
    for( daqListId = 0; daqListId < (uint)pSessionCfg->numStatDaqLists + (uint)pSession->numDynDaqLists; ++daqListId )
    {
        Xcp_ResetDaqList( sessionId, daqListId );
    }

#ifdef XCP_ENABLE_DYNDAQ
    /* Reset dynamic DAQ list state. */
    Xcp_MemZero( (Xcp_StatePtr8)( pSessionCfg->pDaqDynConfigs ), pSession->numDynDaqLists * sizeof( Xcp_DaqDynConfig_t ) );
#endif

    /* Clear ODT entries. */
    Xcp_MemZero( (Xcp_StatePtr8)( pSessionCfg->pOdtEntryAddrs ), (uint)( pSessionCfg->totOdtEntries * sizeof( Xcp_OdtEntryAddr_t ) ) );
    Xcp_MemZero( (Xcp_StatePtr8)( pSessionCfg->pOdtEntryCfgs ) , (uint)( pSessionCfg->totOdtEntries * sizeof( uint8 ) ) );

    /* Reset session state. */
    pSession->sessionStatus         = 0;
    pSession->isConnected           = 0;
    pSession->ctDaqListId           = XCP_DAQLIST_UNDEF;
    pSession->numDynDaqLists        = 0;
    pSession->downloadRemainBytes   = 0;
#ifdef XCP_ENABLE_SEEDNKEY
    pSession->ctResourceProtection  = pSessionCfg->defResourceProtection;
    pSession->unlockResource        = 0;
    pSession->seedOrKey.pRemainSeed = 0;
    pSession->seedRemainBytes       = 0;
    pSession->seedOrKey.pKey        = 0;
#endif /* XCP_ENABLE_SEEDNKEY */
#ifdef XCP_ENABLE_RESUME
    pSession->sessionCfgId          = 0;
#endif /* XCP_ENABLE_RESUME */
}

/**
 * This function implements the XCP command DISCONNECT as described in the XCP specification.
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
uint XCP_FN_TYPE Xcp_CmdDisconnect(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    Xcp_Session_t* const pSession = Xcp_Sessions + sessionId;

    if( pSession->sessionStatus & XCP_SESSION_STATE_PGM )
    {
        /* Flash programming is in progress so we cannot disconnect. */
        pTxPacket->pid     = XCP_PID_ERROR;
        pTxPacket->data[0] = XCP_ERR_PGM_ACTIVE;
        *pTxPacketSize     = 2;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    Xcp_DoDisconnect( sessionId, pSession );

    pTxPacket->pid = XCP_PID_RESPONSE;
    *pTxPacketSize = 1;
    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE */
