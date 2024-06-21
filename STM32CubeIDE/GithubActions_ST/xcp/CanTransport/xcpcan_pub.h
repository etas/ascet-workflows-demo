/**
*
* \file
*
* \brief Public definitions and declarations of functions intended to be called by the XCP protocol layer.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_pub.h 17051 2009-11-24 09:37:39Z olcritch $
*
******************************************************************************/

#ifndef _XCPCAN_PUB_H
#define _XCPCAN_PUB_H

void          XCP_FN_TYPE XcpCan_Initialize       ( void );
Xcp_StatePtr8 XCP_FN_TYPE XcpCan_GetRxBuf         ( uint sessionId, uint channelId );
Xcp_StatePtr8 XCP_FN_TYPE XcpCan_PeekRxBuf        ( uint sessionId, uint channelId, uint peekIdx );
void          XCP_FN_TYPE XcpCan_RxNext           ( uint sessionId, uint channelId );
Xcp_StatePtr8 XCP_FN_TYPE XcpCan_GetTxBuf         ( uint sessionId, uint channelId );
void          XCP_FN_TYPE XcpCan_TxNext           ( uint sessionId, uint channelId, uint bufferLen );
uint          XCP_FN_TYPE XcpCan_CmdProc          ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
uint          XCP_FN_TYPE XcpCan_PrepareResume    ( uint sessionId, uint daqListId, uint nvIdx );
uint          XCP_FN_TYPE XcpCan_DoResume         ( uint sessionId, uint daqListId, uint nvIdx );
void          XCP_FN_TYPE XcpCan_ResetDaqList     ( uint sessionId, uint daqListId );

#endif /* _XCPCAN_PUB_H */
