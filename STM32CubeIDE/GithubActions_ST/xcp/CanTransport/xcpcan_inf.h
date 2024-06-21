/**
*
* \file
*
* \brief This file declares all the APIs (i.e. interfaces) which the CAN transport layer requires from
* other components of the system.
*
* If another component does not provide a required API in the expected form then:
*   - either a shim must be written to translate between the required API and the provided API;
*   - or the CAN transport layer must be adapted to use the API which is available.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_inf.h 15558 2009-05-05 09:06:29Z olcritch $
*
******************************************************************************/

#ifndef _XCPCAN_INF_H
#define _XCPCAN_INF_H

#include "xcp.h"

/******************************************************************************
*
* APIs required from the CAN driver.
*
******************************************************************************/

/**
 * This function should transmit (or queue for transmission) the specified CAN message on the specified CAN message object.
 * The CAN driver can discard msgId if there is a 1-to-1 mapping from message object to message ID.
 *
 * The XCP slave driver assumes that:
 *  - The XCP slave driver can discard the contents of the buffer pBytes after this API call has returned.
 *  - The XCP slave driver has exclusive use of the specified CAN message object.
 *
 * \param [in] msgObjId     The ID of the CAN message object (i.e. CAN hardware buffer) to be used to send the message.
 * \param [in] msgId        The CAN message ID to be used for the message.
 * \param [in] numBytes     The DLC of the CAN message.
 * \param [in] pBytes       The payload of the CAN message.
 */
void XcpApp_CanTransmit( XcpCan_MsgObjId_t msgObjId, uint32 msgId, uint numBytes, Xcp_StatePtr8 pBytes );

#endif /* _XCPCAN_INF_H */
