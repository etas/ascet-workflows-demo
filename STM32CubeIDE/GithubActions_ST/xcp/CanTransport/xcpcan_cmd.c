/**
*
* \file
*
* \brief Implemenation of XCP commands which are specific to the CAN transport layer.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_cmd.c 18723 2010-05-27 10:16:56Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"

#ifdef XCP_ON_CAN

#include "xcpcan_auto_confpriv.h"
#include "xcpcan_priv.h"

/**
 * This function implements the CAN-specific XCP command GET_SLAVE_ID as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY                  This command was not expected and therefore was ignored.
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE XcpCan_CmdGetSlaveId(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  cmdSubCode;
        uint8  charX;
        uint8  charC;
        uint8  charP;
        uint8  mode;
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  echoX;
        uint8  echoC;
        uint8  echoP;
        uint8  rxCanMsgId[4];
    } ) RespPacket_t;

    const CmdPacket_t* const    pCmdPacket      = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const         pRespPacket     = (RespPacket_t*)pTxPacket;
    Xcp_StatePtr8 const         pEchoRequested  = &( XCPCAN_SESSION( sessionId )->echoRequested );
    uint32                      rxCanMsgId      = XCPCAN_SESSIONCFG( sessionId )->pChannelCfgs[ XCP_RX_CMD_CHANNEL ].msgId;

    const char echoChars[2][3] = { { 'X', 'C', 'P' }, { 0xff - 'X', 0xff - 'C', 0xff - 'P' } };

    /* We process the command only if it has the correct format and, in the case of a request for an inverse echo, we
     * have received a previous request for a non-inverse echo.
     *
     * Otherwise we silently ignore the command. */

    if( pCmdPacket->charX == 'X' &&
        pCmdPacket->charC == 'C' &&
        pCmdPacket->charP == 'P' &&
        ( 0 == pCmdPacket->mode || ( 1 == pCmdPacket->mode && *pEchoRequested ) ) )
    {
        /* We echo either 'X', 'C', 'P' or (0xff - 'X'), (0xff - 'C'), (0xff - 'P'), depending on whether we are
         * being asked for an echo (mode 0) or an inverse echo (mode 1). */

        pRespPacket->echoX      = echoChars[ pCmdPacket->mode ][ 0 ];
        pRespPacket->echoC      = echoChars[ pCmdPacket->mode ][ 1 ];
        pRespPacket->echoP      = echoChars[ pCmdPacket->mode ][ 2 ];

        pRespPacket->pid        = XCP_PID_RESPONSE;

        /* The following is necessary to ensure that the wire representation of our CAN RX msg ID is always
         * in little-endian (Intel) format, even on big-endian targets. */
        pRespPacket->rxCanMsgId[0] = (uint8)(   rxCanMsgId & 0x000000ff );
        pRespPacket->rxCanMsgId[1] = (uint8)( ( rxCanMsgId & 0x0000ff00 ) >> 8  );
        pRespPacket->rxCanMsgId[2] = (uint8)( ( rxCanMsgId & 0x00ff0000 ) >> 16 );
        pRespPacket->rxCanMsgId[3] = (uint8)( ( rxCanMsgId & 0xff000000 ) >> 24 );

        *pEchoRequested = pCmdPacket->mode ^ 1;

        *pTxPacketSize = 8;
        return ( XCP_RX_READY | XCP_TX_READY );
    }

    *pTxPacketSize = 0;
    return XCP_RX_READY;
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * This function implements the CAN-specific XCP command GET_DAQ_ID as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return XCP_RX_READY | XCP_TX_READY
 */
uint XCP_FN_TYPE XcpCan_CmdGetDaqId(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  cmdSubCode;
        uint16 daqListId;
    } ) CmdPacket_t;

    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  canIdFixed;
        uint16 reserved;
        uint32 dtoCanMsgId;
    } ) RespPacket_t;

    const CmdPacket_t* const   pCmdPacket      = (CmdPacket_t*)pRxPacket;
    RespPacket_t* const        pRespPacket     = (RespPacket_t*)pTxPacket;
    const uint                 daqListId       = pCmdPacket->daqListId;
    XcpCan_SessionCfg_t* const pCanSessionCfg  = XCPCAN_SESSIONCFG( sessionId );

    /* Find the CAN msg ID which has been configured for the specified DAQ list. This is not entirely straightforward,
     * because:
     *  - The specified DAQ list may have been configured to use the "default" CAN msg ID. If this is the case, the
     *    channel's config will indicate that the CAN msg ID is XCPCAN_INVALID_MSGID. The "default" which is used depends
     *    on whether the DAQ list is in DAQ-mode or STIM-mode:
     *      - In DAQ mode, the default is to use the same ID as RESP packets.
     *      - In STIM mode, the default is to use the same ID as CMD packets.
     *  - The msg ID of a dynamic DAQ list can be set at runtime.
     * Fortunately these two possibilities are mutually exclusive.
     *
     * We start by assuming that the DAQ list's msg ID is fixed. */

    uint32 configuredMsgId = pCanSessionCfg->pChannelCfgs[ XCP_FIRST_DAQ_CHANNEL + daqListId ].msgId;

    pRespPacket->pid        = XCP_PID_RESPONSE;
    pRespPacket->canIdFixed = 1;

    if( XCPCAN_INVALID_MSGID == configuredMsgId )
    {
        /* The DAQ list should use the default CAN msg ID. Which "default" is used depends on whether the DAQ list is in
         * DAQ-mode or STIM-mode. */

        if( XCP_DAQLISTMODE_DIRECTION & Xcp_SessionConfigs[ sessionId ].pDaqStates[ daqListId ].daqListMode )
        {
            /* The DAQ list is in STIM-mode, so use the default CAN RX msg ID, i.e. the CAN msg ID which is used for CMD packets. */
            configuredMsgId = pCanSessionCfg->pChannelCfgs[ XCP_RX_CMD_CHANNEL ].msgId;
        }
        else
        {
            /* The DAQ list is in DAQ-mode, so use the default CAN TX msg ID, i.e. the CAN msg ID which is used for RESP packets. */
            configuredMsgId = pCanSessionCfg->pChannelCfgs[ XCP_TX_CRM_CHANNEL ].msgId;
        }
    }
#ifdef XCP_ENABLE_DYNDAQ
    else if( Xcp_SessionConfigs[ sessionId ].maxDynDaqLists > 0 )
    {
        /* The specified DAQ list is dynamic. */
        pRespPacket->canIdFixed = 0;

        if( pCanSessionCfg->pDynDaqMsgIds[ daqListId ] != XCPCAN_INVALID_MSGID )
        {
            /* The specified DAQ list has a msg ID which was configured at runtime. */
            configuredMsgId = pCanSessionCfg->pDynDaqMsgIds[ daqListId ];
        }
    }
#endif /* XCP_ENABLE_DYNDAQ */

    pRespPacket->dtoCanMsgId = configuredMsgId;

    *pTxPacketSize = 8;
    return ( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the CAN-specific XCP command SET_DAQ_ID. Only dynamic DAQ lists can have their
 * CAN message ID modified with this command; otherwise the command is as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return XCP_RX_READY | XCP_TX_READY
 */
uint XCP_FN_TYPE XcpCan_CmdSetDaqId(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  cmdSubCode;
        uint16 daqListId;
        uint32 dtoCanMsgId;
    } ) CmdPacket_t;

#ifdef XCP_ENABLE_DYNDAQ

    const CmdPacket_t* const    pCmdPacket  = (CmdPacket_t*)pRxPacket;

    if( pCmdPacket->daqListId < Xcp_Sessions[ sessionId ].numDynDaqLists )
    {
        /* The specified DAQ list is a valid dynamic DAQ list, so change its CAN msg ID. */

        if( !Xcp_CheckCanId( pCmdPacket->dtoCanMsgId ) )
        {
            /* The new CAN message ID does not have a valid format. */
            pTxPacket->pid = XCP_PID_ERROR;
            pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
            *pTxPacketSize = 2;
        }
        else
        {
            XCPCAN_SESSIONCFG( sessionId )->pDynDaqMsgIds[ pCmdPacket->daqListId ] = pCmdPacket->dtoCanMsgId;
            pTxPacket->pid = XCP_PID_RESPONSE;
            *pTxPacketSize = 1;
        }
    }
    else
#endif /* XCP_ENABLE_DYNDAQ */
    {
        /* The specified DAQ list is not a valid dynamic DAQ list, so this is an error. */

        pTxPacket->pid = XCP_PID_ERROR;
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        *pTxPacketSize = 2;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

/**
 * This function implements the XCP command TRANSPORT_LAYER_CMD. It does this by delegating to a function
 * appropriate to the particular command.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return Relayed from command function.
 */
uint XCP_FN_TYPE XcpCan_CmdProc(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    switch( pRxPacket->data[0] )
    {
    case XCPCAN_CMD_GET_SLAVE_ID:
        return XcpCan_CmdGetSlaveId ( sessionId, pRxPacket, pTxPacket, pTxPacketSize );

#ifdef XCP_ENABLE_OPTIONAL_CMDS

    case XCPCAN_CMD_GET_DAQ_ID:
        return XcpCan_CmdGetDaqId   ( sessionId, pRxPacket, pTxPacket, pTxPacketSize );
    case XCPCAN_CMD_SET_DAQ_ID:
        return XcpCan_CmdSetDaqId   ( sessionId, pRxPacket, pTxPacket, pTxPacketSize );

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

    default:
        return Xcp_CmdUnknown       ( sessionId, pRxPacket, pTxPacket, prevCmd, pTxPacketSize );
    }
}

#endif /* XCP_ON_CAN */
