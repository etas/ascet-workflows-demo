/**
*
* \file
*
* \brief Definitions specific to the PORTNOTE target
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
******************************************************************************/

#include "main.h"

#include "xcp_target.h"
#include "xcpcan_callbacks.h"
#include "xcp_auto_conf.h"
#include "xcp_debug.h"

#define CAN_ID_XCP_TX			0x300 /* This controller */
#define CAN_ID_XCP_DAQ_TX		0x301 /* This controller */
#define CAN_ID_XCP_RX			0x200 /* INCA */

extern CAN_HandleTypeDef hcan;
extern TIM_HandleTypeDef htim6;

extern volatile uint8_t balanceTube_doStep;

CAN_TxHeaderTypeDef xcpTxHeader;
uint32_t xcpTxMailbox;

#ifdef XCP_ENABLE

/**
 * This function copies bytes from one location to another.
 *
 * \param [in] pDest        The destination location.
 * \param [in] pSrc         The source location.
 * \param [in] numBytes     The number of bytes to be copied.
 *
 * \return pDest
 */
uint8* XCP_FN_TYPE Xcp_MemCopy(
    uint8*          pDest,
    const uint8*    pSrc,
    uint            numBytes
)
{
    /* PORTNOTE: Although it is possible simply to delegate to the library memcpy(), the user may wish to examine the
     * performance of memcpy() first. It might be possible for the user to do something clever to improve performance
     * for situations where pDest and pSrc are aligned conveniently.
	 */
	memcpy(pDest, pSrc, numBytes);

	return pDest;
}

/**
 * This function zeroes the bytes at a specified memory location.
 *
 * \param [in] pMemory      The memory location.
 * \param [in] numBytes     The number of bytes to be zeroed.
 */
void XCP_FN_TYPE Xcp_MemZero(
    uint8* pMemory,
    uint   numBytes
)
{
    /* PORTNOTE: Usually it is sufficient to delegate to the library memset(). */
	memset( pMemory, 0, numBytes );
}

/**
 * This function checks whether a CAN message ID has the format required by the CAN driver.
 * The pre-processor symbol XCPCAN_ALLOW_EXTENDED_MSG_IDS indicates whether extended CAN msg IDs should be
 * allowed in the current project.
 *
 * \param [in] canMsgId     A CAN message ID.
 *
 * \return
 *  - non-zero      The specified CAN message ID is valid.
 *  - zero          The specified CAN message ID is invalid.
 */
sint XCP_FN_TYPE Xcp_CheckCanId( uint32 canMsgId )
{
    return 1;
}

struct XcpCan_TxMsgObj {
	XcpCan_MsgObjId_t msgObjId;
	uint32 msgId;
};

struct XcpCan_TxMsgObj msgObjIdByTxMailbox[3] = {0};


void XcpApp_CanTransmit(XcpCan_MsgObjId_t msgObjId, uint32 msgId, uint numBytes,
		Xcp_StatePtr8 pBytes) {
	xcpTxHeader.StdId = msgId;
	xcpTxHeader.RTR = CAN_RTR_DATA;
	xcpTxHeader.IDE = CAN_ID_STD;
	xcpTxHeader.DLC = numBytes;
	xcpTxHeader.TransmitGlobalTime = DISABLE;

#ifdef XCP_COM_DEBUG
	if (msgId == CAN_ID_XCP_TX) {
		printf("\t[%03lx] ", msgId);
		for (uint8 i = 0; i < numBytes; i++) {
			printf("%02X ", pBytes[i]);
		}
		printf("\n");
		fflush(stdout);
	}
#ifdef XCP_DAQ_DEBUG
	else if (msgId == CAN_ID_XCP_DAQ_TX) {
		printf("\t[%03lx] ", msgId);
		for (uint8 i = 0; i < numBytes; i++) {
			printf("%02X ", pBytes[i]);
		}
		printf("\n");
		fflush(stdout);
	}
#endif
#endif

	uint32_t time_ms = HAL_GetTick();
	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) <= 0) {
		/* wait until tx mailbox is free */
		uint32_t dT_ms = HAL_GetTick() - time_ms;
		if (dT_ms >= 4) {
#ifdef XCP_COM_DEBUG
		printf("CAN TX Error");
#endif
		return;
		}
	}
	HAL_CAN_AddTxMessage(&hcan, &xcpTxHeader, pBytes, &xcpTxMailbox);

	uint32_t index = xcpTxMailbox >> 1;
	if (index >= 0 && index < 3) {
		msgObjIdByTxMailbox[index].msgObjId = msgObjId;
		msgObjIdByTxMailbox[index].msgId = msgId;
	} else {
#ifdef XCP_COM_DEBUG
		printf("Mailbox Error");
#endif
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ST Interrupt Callbacks
//////////////////////////////////////////////////////////////////////////////////////////
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan) {
#ifdef XCP_COM_DEBUG
	uint32 msgId = msgObjIdByTxMailbox[0].msgId;
	if (msgId == CAN_ID_XCP_TX) {
		fflush(stdout);
		printf("\t[%03lx] TX0 complete\n", msgId);
		fflush(stdout);
	}
#ifdef XCP_DAQ_DEBUG
	else if (msgId == CAN_ID_XCP_DAQ_TX) {
		fflush(stdout);
		printf("\t[%03lx] TX0 complete\n", msgId);
		fflush(stdout);
	}
#endif
#endif
	XcpCan_TxCallback(msgObjIdByTxMailbox[0].msgObjId);
}

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan) {
#ifdef XCP_COM_DEBUG
	uint32 msgId = msgObjIdByTxMailbox[1].msgId;
	if (msgId == CAN_ID_XCP_TX) {
		fflush(stdout);
		printf("\t[%03lx] TX1 complete\n", msgId);
		fflush(stdout);
	}
#ifdef XCP_DAQ_DEBUG
	else if (msgId == CAN_ID_XCP_DAQ_TX) {
		fflush(stdout);
		printf("\t[%03lx] TX1 complete\n", msgId);
		fflush(stdout);
	}
#endif
#endif
	XcpCan_TxCallback(msgObjIdByTxMailbox[1].msgObjId);
}

void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan) {
#ifdef XCP_COM_DEBUG
	uint32 msgId = msgObjIdByTxMailbox[2].msgId;
	if (msgId == CAN_ID_XCP_TX) {
		fflush(stdout);
		printf("\t[%03lx] TX2 complete\n", msgId);
		fflush(stdout);
	}
#ifdef XCP_DAQ_DEBUG
	else if (msgId == CAN_ID_XCP_DAQ_TX) {
		fflush(stdout);
		printf("\t[%03lx] TX2 complete\n", msgId);
		fflush(stdout);
	}
#endif
#endif
	XcpCan_TxCallback(msgObjIdByTxMailbox[2].msgObjId);
}

/**
 * Called when CAN data received
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	CAN_RxHeaderTypeDef rxHeader;
	uint8_t rxData[8];
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData);
	switch (rxHeader.StdId) {
		case CAN_ID_XCP_RX: {
			XcpCan_RxCallback(CAN_ID_XCP_RX, rxHeader.DLC, rxData);
#ifdef XCP_COM_DEBUG
			fflush(stdout);
			printf("[%03lx] ", rxHeader.StdId);
			for (int i = 0; i < rxHeader.DLC; i++) {
				printf("%02X ", rxData[i]);
			}
			printf("\n");
			fflush(stdout);
#endif
			break;
		}
	}
}
/**
 * Called every millisecond
 */
uint32_t counter_ms = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == htim6.Instance) {
		counter_ms++;
		if (counter_ms) {
			__NOP();
		}

		static uint32_t task_timer_ms = 0;
		task_timer_ms++;
		if (task_timer_ms >= 5) {
			balanceTube_doStep = 1;
			task_timer_ms = 0;
		}

		static uint32_t daq_timer_ms = 0;
		daq_timer_ms++;
		if (daq_timer_ms >= 2) {
			Xcp_DoDaqForEvent_2ms();
			daq_timer_ms = 0;
		}
	}
}

/**
 * The XCP slave driver expects this function to return the current value of a counter which has the period
 * of the DAQ clock. The preprocessor symbols XCP_TIMESTAMP_UNIT and XCP_TIMESTAMP_TICKS indicate the
 * required period of the counter.
 *
 * \return The current value of the counter. The value must use at least the number of bytes indicated by the
 * largest value of XCP_TIMESTAMP_SIZE in the XCP slave driver's configuration.
 */
uint32 XcpApp_GetTimestamp( void )
{
    return counter_ms;
}

//////////////////////////////////////////////////////////////////////////////////////////

#endif /* XCP_ENABLE */
