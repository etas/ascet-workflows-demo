/**
*
* \file
*
* \brief Internal definitions and declarations
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_priv.h 18723 2010-05-27 10:16:56Z olcritch $
*
******************************************************************************/

#ifndef _XCPCAN_PRIV_H
#define _XCPCAN_PRIV_H

/******************************************************************************
*
* Preprocessor definitions
*
******************************************************************************/

#define XCPCAN_INVALID_MSGID        (0xffffffff)
#define XCPCAN_INVALID_MSGOBJID     (XcpCan_MsgObjId_t)(0xffffffff)

/* Transport layer command subcodes. */
#define XCPCAN_CMD_GET_SLAVE_ID         0xFF
#define XCPCAN_CMD_GET_DAQ_ID           0xFE
#define XCPCAN_CMD_SET_DAQ_ID           0xFD

/******************************************************************************
*
* Type definitions
*
******************************************************************************/

/* This holds the state of an instance of XcpCan_QueueBuf_t. The lower 4 bits contain a value from XcpCan_QueueBufStates_t.
 * If this value is XCPCAN_TXNOTSENT or XCPCAN_TXINPROGRESS the upper 4 bits indicate the number of bytes currently used in
 * the associated instance of XcpCan_QueueBuf_t. */
typedef XCP_STATE_TYPE uint8 XcpCan_QueueBufProps_t;

/* This holds a CAN message ID which was assigned to a dynamic DAQ list at runtime. */
typedef XCP_STATE_TYPE uint32 XcpCan_DynDaqMsgId_t;

typedef enum
{
    XCPCAN_TXRXFREE = 0,           /* The buffer is available to store TX or RX data. */
    XCPCAN_TXALLOC,                /* The buffer has been allocated to store TX data, but it is not yet ready to be transmitted. */
    XCPCAN_TXNOTSENT,              /* The buffer is ready to be transmitted. */
    XCPCAN_TXINPROGRESS,           /* The buffer is being transmitted. */
    XCPCAN_RXDATA                  /* The buffer is contains RX data. */
} XcpCan_QueueBufStates_t;

typedef struct
{
    uint32                  msgBuffer[2];   /* We need 8 bytes of storage aligned on a natural boundary, and this is a convenient way to allocate it. */
} XcpCan_QueueBuf_t;

typedef XCP_STATE_TYPE struct
{
    /* For a TX queue this represents the tail of the queue. The XCP slave driver writes CAN messages into the queue
     * at this position in the session's buffer array.
     * For an RX queue this represents the head of the queue. The XCP slave driver reads CAN messages from the queue
     * at this position in the session's buffer array. */
    uint32                  ctXcpPos;

    /* For a TX queue this represents the head of the queue. The CAN driver reads CAN messages from the queue
     * at this position in the session's buffer array.
     * For an RX queue this represents the tail of the queue. The CAN driver writes CAN messages into the queue
     * at this position in the session's buffer array. */
    uint32                  ctCanPos;
} XcpCan_QueuePos_t;

typedef XCP_CONFIG_TYPE struct
{
    uint32                  idxStart;   /* The first element of this channel's queue space in the array pointed to by XcpCan_SessionCfg_t::pQueueBuffers */
    uint32                  idxEnd;     /* The last element of this channel's queue space in the array pointed to by XcpCan_SessionCfg_t::pQueueBuffers */
    uint32                  msgId;      /* The CAN message ID used for sending or receiving messages on this channel. If this channel is used for a dynamic DAQ list, this may be overridden at runtime. */
    XcpCan_MsgObjId_t       msgObjId;   /* The CAN message object used for sending messages on this channel. */
} XcpCan_ChannelCfg_t;

typedef XCP_CONFIG_TYPE struct
{
    XcpCan_ChannelCfg_t*        pChannelCfgs;       /* Points to an array with one entry per channel. */
    XcpCan_QueuePos_t*          pQueuePositions;    /* Points to an array with one entry per channel. */
    XcpCan_QueueBuf_t*          pQueueBuffers;      /* Points to an array with one entry per queue element. */
    XcpCan_QueueBufProps_t*     pQueueBufferStates; /* Points to an array with one entry per queue element. */
    XcpCan_DynDaqMsgId_t*       pDynDaqMsgIds;      /* The CAN msg IDs configured for dynamic DAQ lists. */
    uint32                      broadcastMsgId;     /* The CAN msg ID configured for broadcast messages. */
    uint16                      numChannels;
    uint16                      firstRxStimChannel; /* The first channel corresponding to a STIM or DAQ/STIM list */
    uint16                      lastTxChannel;   /* The last channel corresponding to a DAQ or DAQ/STIM list */
} XcpCan_SessionCfg_t;

typedef XCP_STATE_TYPE struct
{
    uint8                       echoRequested;      /* Indicates whether the GET_SLAVE_ID command has requested an echo. */
} XcpCan_Session_t;

/******************************************************************************
*
* Extern declarations
*
******************************************************************************/

extern XCP_STATE_TYPE uint8   XcpCan_TxPendingOnMsgObj[];

#endif /* _XCPCAN_PRIV_H */
