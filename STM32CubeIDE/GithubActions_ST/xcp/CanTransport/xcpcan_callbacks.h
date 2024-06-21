/**
*
* \file
*
* \brief Declaration of callbacks implemented by the CAN transport layer.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_callbacks.h 15527 2009-04-20 08:07:27Z olcritch $
*
******************************************************************************/

#ifndef _XCPCAN_CALLBACK_H
#define _XCPCAN_CALLBACK_H

#include "xcp_target.h"

#if defined __cplusplus || defined _cplusplus
extern "C" {
#endif

void XCP_FN_TYPE XcpCan_RxCallback( uint32 msgId, uint8 msgLen, uint8* pMsgData );
void XCP_FN_TYPE XcpCan_TxCallback( XcpCan_MsgObjId_t msgObjId );

#if defined __cplusplus || defined _cplusplus
}
#endif

#endif /* _XCPCAN_CALLBACK_H */
