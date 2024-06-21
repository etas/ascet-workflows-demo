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
* \version $Id: xcp_priv.h 18551 2010-04-27 07:41:39Z olcritch $
*
******************************************************************************/

#ifndef _XCP_PRIV_H
#define _XCP_PRIV_H

#include "xcp_auto_confdefs.h"
#include "xcp_common.h"
/******************************************************************************
*
* Preprocessor definitions
*
******************************************************************************/

#define XCP_PROTOCOL_VERSION            0x01
#define XCP_DRIVER_VERSION_MAJOR        0x01
#define XCP_DRIVER_VERSION_MINOR        0x00

/* Transport layers */
#define XCP_TRANSPORTLAYER_CAN          0x01ul

/* Standard commands */
#define XCP_CMD_CONNECT                 0xFF
#define XCP_CMD_DISCONNECT              0xFE
#define XCP_CMD_GET_STATUS              0xFD
#define XCP_CMD_SYNCH                   0xFC
#define XCP_CMD_GET_COMM_MODE_INFO      0xFB
#define XCP_CMD_GET_ID                  0xFA
#define XCP_CMD_SET_REQUEST             0xF9
#define XCP_CMD_GET_SEED                0xF8
#define XCP_CMD_UNLOCK                  0xF7
#define XCP_CMD_SET_MTA                 0xF6
#define XCP_CMD_UPLOAD                  0xF5
#define XCP_CMD_SHORT_UPLOAD            0xF4
#define XCP_CMD_BUILD_CHECKSUM          0xF3
#define XCP_CMD_TRANSPORT_LAYER_CMD     0xF2
#define XCP_CMD_USER_CMD                0xF1

/* Calibration commands */
#define XCP_CMD_DOWNLOAD                0xF0
#define XCP_CMD_DOWNLOAD_NEXT           0xEF
#define XCP_CMD_DOWNLOAD_MAX            0xEE
#define XCP_CMD_SHORT_DOWNLOAD          0xED
#define XCP_CMD_MODIFY_BITS             0xEC

/* Page switching commands */
#define XCP_CMD_SET_CAL_PAGE            0xEB
#define XCP_CMD_GET_CAL_PAGE            0xEA
#define XCP_CMD_GET_PAG_PROCESSOR_INFO  0xE9
#define XCP_CMD_GET_SEGMENT_INFO        0xE8
#define XCP_CMD_GET_PAGE_INFO           0xE7
#define XCP_CMD_SET_SEGMENT_MODE        0xE6
#define XCP_CMD_GET_SEGMENT_MODE        0xE5
#define XCP_CMD_COPY_CAL_PAGE           0xE4

/* Data acquisition and stimulation commands */
#define XCP_CMD_CLEAR_DAQ_LIST          0xE3
#define XCP_CMD_SET_DAQ_PTR             0xE2
#define XCP_CMD_WRITE_DAQ               0xE1
#define XCP_CMD_SET_DAQ_LIST_MODE       0xE0
#define XCP_CMD_GET_DAQ_LIST_MODE       0xDF
#define XCP_CMD_START_STOP_DAQ_LIST     0xDE
#define XCP_CMD_START_STOP_SYNCH        0xDD
#define XCP_CMD_GET_DAQ_CLOCK           0xDC
#define XCP_CMD_READ_DAQ                0xDB
#define XCP_CMD_GET_DAQ_PROCESSOR_INFO  0xDA
#define XCP_CMD_GET_DAQ_RESOLUTION_INFO 0xD9
#define XCP_CMD_GET_DAQ_LIST_INFO       0xD8
#define XCP_CMD_GET_DAQ_EVENT_INFO      0xD7
#define XCP_CMD_FREE_DAQ                0xD6
#define XCP_CMD_ALLOC_DAQ               0xD5
#define XCP_CMD_ALLOC_ODT               0xD4
#define XCP_CMD_ALLOC_ODT_ENTRY         0xD3

/* Non-volatile memory programming commands */
#define XCP_CMD_PROGRAM_START           0xD2
#define XCP_CMD_PROGRAM_CLEAR           0xD1
#define XCP_CMD_PROGRAM                 0xD0
#define XCP_CMD_PROGRAM_RESET           0xCF
#define XCP_CMD_GET_PGM_PROCESSOR_INFO  0xCE
#define XCP_CMD_GET_SECTOR_INFO         0xCD
#define XCP_CMD_PROGRAM_PREPARE         0xCC
#define XCP_CMD_PROGRAM_FORMAT          0xCB
#define XCP_CMD_PROGRAM_NEXT            0xCA
#define XCP_CMD_PROGRAM_MAX             0xC9
#define XCP_CMD_PROGRAM_VERIFY          0xC8

/* This is a special value for Xcp_Session_t::prevCmd which indicates that the previous command was in fact
 * the current command, i.e. the command is being processed a second time. */
#define XCP_CMD_CURR_CMD                0x01

/* Event codes. */
#define XCP_EV_RESUME_MODE              0x00
#define XCP_EV_CLEAR_DAQ                0x01
#define XCP_EV_STORE_DAQ                0x02
#define XCP_EV_STORE_CAL                0x03
#define XCP_EV_CMD_PENDING              0x05
#define XCP_EV_DAQ_OVERLOAD             0x06
#define XCP_EV_SESSION_TERMINATED       0x07
#define XCP_EV_USER                     0xFE
#define XCP_EV_TRANSPORT                0xFF

/* Error codes. */
#define XCP_ERR_CMD_SYNCH               0x00
#define XCP_ERR_CMD_BUSY                0x10
#define XCP_ERR_DAQ_ACTIVE              0x11
#define XCP_ERR_PGM_ACTIVE              0x12
#define XCP_ERR_CMD_UNKNOWN             0x20
#define XCP_ERR_CMD_SYNTAX              0x21
#define XCP_ERR_OUT_OF_RANGE            0x22
#define XCP_ERR_WRITE_PROTECTED         0x23
#define XCP_ERR_ACCESS_DENIED           0x24
#define XCP_ERR_ACCESS_LOCKED           0x25
#define XCP_ERR_PAGE_NOT_VALID          0x26
#define XCP_ERR_MODE_NOT_VALID          0x27
#define XCP_ERR_SEGMENT_NOT_VALID       0x28
#define XCP_ERR_SEQUENCE                0x29
#define XCP_ERR_DAQ_CONFIG              0x2A
#define XCP_ERR_MEMORY_OVERFLOW         0x30
#define XCP_ERR_GENERIC                 0x31
#define XCP_ERR_VERIFY                  0x32

/* Receive PIDs */
#define XCP_PID_CMD_FIRST               0xFF
#define XCP_PID_CMD_LAST                0xC0
#define MAX_CALPAGCMD_PID               0xF0
#define MAX_DAQCMD_PID                  0xE3
#define MAX_PGMCMD_PID                  0xD2
/* Other PIDs are for STIM-data */

/* Transmit PIDs */
#define XCP_PID_SERVICE_REQUEST         0xFC
#define XCP_PID_EVENT                   0xFD
#define XCP_PID_ERROR                   0xFE
#define XCP_PID_RESPONSE                0xFF
/* Other PIDs are for DAQ-data */

/* Resources (for seed & key) */
#define XCP_RESOURCE_CAL_PAG            0x01
#define XCP_RESOURCE_DAQ                0x04
#define XCP_RESOURCE_STIM               0x08
#define XCP_RESOURCE_PGM                0x10

/* Session states */
#define XCP_SESSION_STATE_STORE_CAL     0x01
#define XCP_SESSION_STATE_STORE_DAQ     0x04
#define XCP_SESSION_STATE_CLEAR_DAQ     0x08
#define XCP_SESSION_STATE_PGM           0x10    /* The XCP specification states that this bit position is unused, so we use it for our own purposes. */
#define XCP_SESSION_STATE_DAQ_RUNNING   0x40
#define XCP_SESSION_STATE_RESUME        0x80

/* XCP checksum types */
#define XCP_CHECKSUM_TYPE_ADD_11        0x01
#define XCP_CHECKSUM_TYPE_ADD_12        0x02
#define XCP_CHECKSUM_TYPE_ADD_14        0x03
#define XCP_CHECKSUM_TYPE_ADD_22        0x04
#define XCP_CHECKSUM_TYPE_ADD_24        0x05
#define XCP_CHECKSUM_TYPE_ADD_44        0x06
#define XCP_CHECKSUM_TYPE_CRC_16        0x07
#define XCP_CHECKSUM_TYPE_CRC_16_CITT   0x08
#define XCP_CHECKSUM_TYPE_CRC_32        0x09
#define XCP_CHECKSUM_TYPE_USER          0xFF

/* return values for command functions */
#define XCP_RX_READY                    0x01ul
#define XCP_TX_READY                    0x02ul

/* Daq */

#define XCP_DAQLIST_UNDEF               0xFFFF

#define XCP_DAQLIST_START               0x01
#define XCP_DAQLIST_STOP                0x00
#define XCP_DAQLIST_SELECT              0x02

#define XCP_DAQLIST_SYNC_STOPALL        0x00
#define XCP_DAQLIST_SYNC_STARTSEL       0x01
#define XCP_DAQLIST_SYNC_STOPSEL        0x02

/* The bits of DAQ list mode. */
#define XCP_DAQLISTMODE_RESUME          0x80
#define XCP_DAQLISTMODE_RUNNING         0x40
#define XCP_DAQLISTMODE_PIDOFF          0x20
#define XCP_DAQLISTMODE_TIMESTAMP       0x10
#define XCP_DAQLISTMODE_DIRECTION       0x02
#define XCP_DAQLISTMODE_SELECTED        0x01

/* Values which indicate properties of a DAQ list. */
#define XCP_DAQLISTPROPERTY_DAQ         0x01        /* The list is available for DAQ. */
#define XCP_DAQLISTPROPERTY_STIM        0x02        /* The list is available for STIM. */
#define XCP_DAQLISTPROPERTY_DAQ_STIM    ( XCP_DAQLISTPROPERTY_DAQ | XCP_DAQLISTPROPERTY_STIM )
#define XCP_DAQLISTPROPERTY_EVENTFIXED  0x04        /* The event associated with the DAQ list cannot be changed. */

/* Segment modes. */
#define XCP_SEGMODE_FREEZE              0x01
#define XCP_SEGMODE_FREEZE_PENDING      0x80    /* The XCP specification states that this bit position is unused, so we use it for our own purposes. */

/* Endian-ness */
#define XCP_BYTE_ORDER_LITTLE_ENDIAN    0       /* We must use this value since it is mandated by the XCP specification. */
#define XCP_BYTE_ORDER_BIG_ENDIAN       1       /* We must use this value since it is mandated by the XCP specification. */

/* This number is written at the start of every block of session data which is stored in non-volatile memory during RESUME mode.
 * Its presence indicates that a valid session data block follows it in memory. */
#define XCP_NVMEM_MAGIC_NUMBER          0xdeadbeef

/* These are helper macros to access the transport-layer-specific state and configuration of a session. The transport-layer-specific
 * state and configuration is stored in this manner to allow uniform access, irrespective of the definition of the structures which
 * contain the state and configuation. */
#define XCPCAN_SESSIONCFG( sessionId )  ( (XcpCan_SessionCfg_t*)(Xcp_SessionConfigs[ sessionId ].pTransportCfg ) )
#define XCPCAN_SESSION( sessionId )     ( (XcpCan_Session_t*)(Xcp_SessionConfigs[ sessionId ].pTransport ) )
#define XCPIP_SESSIONCFG( sessionId )   ( (XcpIp_SessionCfg_t*)(Xcp_SessionConfigs[ sessionId ].pTransportCfg ) )
#define XCPIP_SESSION( sessionId )      ( (XcpIp_Session_t*)(Xcp_SessionConfigs[ sessionId ].pTransport ) )

/* For each session, the transport layer's channels are organised as follows:
 * 
 *      CMD channel
 *      EV channel
 *      RESP channel
 *      DAQ list channel
 *      DAQ list channel
 *      DAQ list channel
 *      ...
 */
#define XCP_RX_CMD_CHANNEL      0
#define XCP_TX_EVENT_CHANNEL    1
#define XCP_TX_CRM_CHANNEL      2
#define XCP_FIRST_DAQ_CHANNEL   3
#define XCP_FIRST_TX_CHANNEL    XCP_TX_EVENT_CHANNEL

/******************************************************************************
*
* Type definitions
*
******************************************************************************/

/* This type holds the configuration of an ODT entry. In some circumstances it can also hold part of the address associated with
 * the ODT entry. */
typedef XCP_STATE_TYPE uint8 Xcp_OdtEntryCfg_t;

/* This type represent the session data stored in non-volatile (NV) memory for RESUME mode. */
typedef struct
{
    uint32  magicNumber;            /* This is always equal to XCP_NVRAM_MAGIC_NUMBER and is used to indicate that a valid session data block follows. */
    uint16  sessionCfgId;
    uint16  numDynDaqLists;
    uint16  numResumeDaqLists;
} Xcp_NvSession_t;

/* This type represent the DAQ data stored in non-volatile (NV) memory for RESUME mode. */
typedef struct
{
    uint8  maxOdtIdUsed;
    uint8  daqListMode;
    uint16 daqListId;
    uint16 daqEvent;
} Xcp_NvDaqState_t;

/* This type stores the ID of an XCP slave. */
typedef XCP_CONFIG_TYPE struct
{
    uint8       len;
    Xcp_CfgPtr8 idString;
} Xcp_SlaveId_t;

/* This type represents a generic XCP packet */
typedef XCP_STATE_TYPE XCP_PACK( struct
{
    uint8 pid;
    uint8 data[1];  /* Strictly speaking, there may be more than 1 data byte. However, we only declare
                     * 1 to encourage the compiler to pack the structure on byte boundaries. This works
                     * because we never declare instances of this type, only pointers to pre-allocated buffers */
} ) Xcp_Packet_t;

/* The configuration of a PAGE. */
typedef XCP_CONFIG_TYPE struct
{
    uint8 initSegment;                      /* The ID of the init segment for this page. */
} Xcp_PageConfig_t;

/* The configuration of a SEGMENT. */
typedef XCP_CONFIG_TYPE struct
{
    Xcp_PageConfig_t* pPageConfigs;         /* The configuration of the pages in this segment.  */
    uint8             numPages;             /* The number of pages in this segment.             */
} Xcp_SegConfig_t;

/* The state of a SEGMENT. */
typedef XCP_STATE_TYPE struct
{
    uint8 mode;                             /* The mode of the segment, as defined by the XCP spec  */
    uint8 toolPage;                         /* The ID of the current tool page for the segment      */
} Xcp_SegState_t;

/* The state of a DAQ list. */
typedef XCP_STATE_TYPE struct
{
    uint8   daqListMode;                    /* The mode of the DAQ list, as defined by the XCP spec. */
    uint8   maxOdtIdUsed;                   /* The maximum ODT ID which has been configured (via WRITE_DAQ) for this DAQ list. */
    uint16  daqEvent;                       /* The event currently associated with the DAQ list. */
} Xcp_Daq_t;

/* The configuration of a DAQ list. */
typedef XCP_CONFIG_TYPE struct
{
    uint8           firstPid;               /* The first PID used by this DAQ list. */
    uint8           numOdt;                 /* For a static DAQ list, the number of ODTs in the list. For a dynamic DAQ, the max number of ODTs in the list. */
    uint16          idxDaqStart;            /* The start of this DAQ list's section of Xcp_SessionConfig_t::pOdtEntryAddrs and Xcp_SessionConfig_t::pOdtEntryCfgs */
    uint8           numOdtEntries;          /* For a static DAQ, the number of ODT entries in each ODT. For a dynamic DAQ, the max number of ODT entries in each ODT. */
    uint8           properties;             /* Properties of the DAQ list. At least one of XCP_DAQLISTPROPERTY_DAQ or XCP_DAQLISTPROPERTY_STIM must be set. */
    uint16          defaultEvent;           /* The default event channel used for the DAQ list. */
} Xcp_DaqConfig_t;

#ifdef XCP_ENABLE_DYNDAQ

/* The configuration of a dynamic DAQ list. Unlike most other configuration, this is intended to be stored in RAM. */
typedef XCP_STATE_TYPE struct
{
    uint8           numOdt;                 /* The number of dynamic ODTs actually used; Xcp_DaqConfig_t::numOdt are available. */

    /* The length of this array is the maximum required for all sessions, in order to allow us to have a single
     * type definition for all sessions.
     * If two sessions use dynamic DAQs but have unequal value for the maximum number of ODT entries per ODT then
     * RAM will be wasted by one of the sessions. */
    uint8           odtEntryNums[ XCP_MAX_ODT_ENTRIES_DYNDAQ ]; /* Element n gives the number of ODT entries in ODT n. */
} Xcp_DaqDynConfig_t;

#endif /* XCP_ENABLE_DYNDAQ */

/* The state of a session. */
typedef XCP_STATE_TYPE struct
{
    Xcp_Addr_t          mta;                    /* Current MTA                                          */
    uint8               sessionStatus;          /* Current session status as defined in GET_STATUS; note the DAQ_RUNNING bit is calculated on demand */
#ifdef XCP_ENABLE_SEEDNKEY
    uint8               ctResourceProtection;   /* Current resource protection: bit set = protected     */
    uint8               unlockResource;         /* Resource to be unlocked with UNLOCK                  */
    uint8               seedRemainBytes;        /* Number of bytes at pRemainSeed.                      */
    union{                                      /* This union is used to reduce storage space.          */
        Xcp_Key_t*      pKey;                   /* Location for UNLOCK to store next portion of key.    */
        Xcp_Seed_t*     pRemainSeed;            /* The remaining seed to be sent via GET_SEED.          */
    } seedOrKey;
#endif
#ifdef XCP_ENABLE_RESUME
    uint16              sessionCfgId;           /* Unique identification of DAQ configuration; used during RESUME. */
#endif
    uint16              ctDaqListId;            /* Working DAQ, set by SET_DAQ_PTR                      */
    uint8               ctOdtId;                /* Working ODT, set by SET_DAQ_PTR                      */
    uint8               ctOdtEntryId;           /* Working ODT entry, set by SET_DAQ_PTR                */
    uint8               isConnected;            /* Current connection state                             */
    uint8               prevCmd;                /* The PID of the previously-processed command, or XCP_CMD_CURR_CMD if the previous command is being re-processed. */
    uint8               timeoutCounter;         /* Timeout counter for sending EV_CMD_PENDING           */
    uint8               downloadRemainBytes;    /* The number of remaining download (or flash) bytes in master block mode. */
    uint16              numDynDaqLists;         /* Number of dynamic DAQ lists which have been defined. */
} Xcp_Session_t;

/* Identifiers for the supported transport layers. */
typedef enum
{
    XCP_CAN = 0,
    XCP_IP
} Xcp_TransportLayer_t;

/* The configuration of a session. */
typedef XCP_CONFIG_TYPE struct
{
    const void*             pTransportCfg;          /* The configuration of the transport layer associated with this session */
    void*                   pTransport;             /* The state of the transport layer associated with this session */
    /* The following point to functions within the transport layer associated with the session. */
    Xcp_StatePtr8 XCP_FN_TYPE (*pGetTxBuf)      ( uint sessionId, uint channelId );
    Xcp_StatePtr8 XCP_FN_TYPE (*pGetRxBuf)      ( uint sessionId, uint channelId );
#ifdef XCP_ENABLE_STIM
    Xcp_StatePtr8 XCP_FN_TYPE (*pPeekRxBuf)     ( uint sessionId, uint channelId, uint peekIdx );
#endif
    void          XCP_FN_TYPE (*pTxNext)        ( uint sessionId, uint channelId, uint bufferLen );
    void          XCP_FN_TYPE (*pRxNext)        ( uint sessionId, uint channelId );
    uint          XCP_FN_TYPE (*pCmdProc)       ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
#ifdef XCP_ENABLE_RESUME
    uint          XCP_FN_TYPE (*pPrepareResume) ( uint sessionId, uint daqListId, uint nvIdx );
    uint          XCP_FN_TYPE (*pDoResume)      ( uint sessionId, uint daqListId, uint nvIdx );
#endif
    void          XCP_FN_TYPE (*pResetDaqList)  ( uint sessionId, uint daqListId );

    /* Each of the following two data members points to an array which has one element per ODT entry for all ODTs
     * in all DAQ lists in the session. If the session uses dynamic DAQ lists, the array has space for each DAQ list
     * to have its maximum possible number of ODTs and ODT entries. If a particular dynamic DAQ uses fewer than the
     * maximum, the array will be sparsely populated. */
    Xcp_OdtEntryAddr_t*     pOdtEntryAddrs;         /* Each element of this array gives the address associated with an ODT entry. */
    Xcp_OdtEntryCfg_t*      pOdtEntryCfgs;          /* Each element of this array gives the configuration of an ODT entry. */

    Xcp_DaqConfig_t*        pDaqConfigs;            /* An array of DAQ configurations.                              */
#ifdef XCP_ENABLE_DYNDAQ
    Xcp_DaqDynConfig_t*     pDaqDynConfigs;         /* An array of dynamic DAQ configurations.                      */
#endif
    Xcp_Daq_t*              pDaqStates;             /* An array of DAQ states.                                      */
    uint16                  numStatDaqLists;        /* The number of static DAQ lists.                              */
    uint16                  maxDynDaqLists;         /* The max number of dynamic DAQ lists.                         */
    uint32                  totOdtEntries;          /* Total number of ODT entries in all ODTs in all DAQ lists     */
    uint16                  maxDtoLen;              /* Maximum size of a DTO.                                       */
    uint8                   maxCtoLen;              /* Maximum size of a CTO.                                       */
    uint8                   defResourceProtection;  /* Default resource protection: bit set = protected             */
    uint8                   eventPendingTimeout;    /* Timeout (measured in mutiples of Xcp_Command_Proc() tick) before EV_CMD_PENDING will be sent. */
    uint8                   numBytesTimestamp;      /* The number of bytes in the DAQ timestamp (0, 1, 2 or 4).     */
    uint8                   maxOdtEntryLen;         /* The maximum length of an ODT entry in bytes                  */
#ifdef XCP_ENABLE_CALPAG
    uint8                   numSegs;                /* The number of segments belonging to the session              */
    Xcp_SegConfig_t*        pSegConfigs;            /* The configuration of the segments belonging to the session   */
    Xcp_SegState_t*         pSegStates;             /* The states of the segments belonging to the session          */
#endif
#ifdef XCP_ENABLE_RESUME
    uint                    nvStartIdx;             /* The index within the NV memory region at which we store the session's RESUME data */
#endif
    Xcp_TransportLayer_t    transportLayerId;       /* An identifier for the transport layer associated with this session */
} Xcp_SessionConfig_t;

/******************************************************************************
*
* Variables
*
******************************************************************************/

/* Definitions of the following will be generated by the configuration tool. */
extern Xcp_SessionConfig_t    Xcp_SessionConfigs[];
extern Xcp_SlaveId_t          Xcp_SlaveIdStrings[];
extern Xcp_Session_t          Xcp_Sessions[];

/******************************************************************************
*
* Prototypes
*
******************************************************************************/

/* Standard commands */
extern uint XCP_FN_TYPE Xcp_CmdConnect            ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdDisconnect         ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetStatus          ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdSynch              ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdSetMta             ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdUpload             ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdBuildChecksum      ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdShortUpload        ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetId              ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetCommModeInfo    ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdTransportLayer     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdSetRequest         ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetSeed            ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdUnlock             ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdUser               ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );

/* Calibration commands */
extern uint XCP_FN_TYPE Xcp_CmdDownload           ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdDownloadNext       ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdDownloadMax        ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdModifyBits         ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );

/* Page switching commands */
extern uint XCP_FN_TYPE Xcp_CmdSetCalPage         ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetCalPage         ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdCopyCalPage        ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetPagProcInfo     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdSetSegmentMode     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetSegmentMode     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );

/* Data acquisition and stimulation commands */
extern uint XCP_FN_TYPE Xcp_CmdClearDaqList       ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdSetDaqPtr          ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdWriteDaq           ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdSetDaqListMode     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetDaqListMode     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdStartStopDaqList   ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdStartStopSync      ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetDaqClock        ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdFreeDaq            ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdAllocDaq           ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdAllocOdt           ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdAllocOdtEntry      ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetDaqProcInfo     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetDaqResInfo      ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdGetDaqListInfo     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );

/* Flash programming commands */
extern uint XCP_FN_TYPE Xcp_CmdProgramStart       ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdProgramClear       ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdProgram            ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdProgramNext        ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdProgramMax         ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdProgramReset       ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdProgramPrepare     ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );
extern uint XCP_FN_TYPE Xcp_CmdProgramFormat      ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );

/* Commands not implemented */
extern uint XCP_FN_TYPE Xcp_CmdUnknown            ( uint sessionId, Xcp_Packet_t* pRxPacket, Xcp_Packet_t* pTxPacket, uint prevCmd, uint* pTxPacketSize );


extern uint XCP_FN_TYPE Xcp_DaqProcessor    ( const uint daqListId, const uint sessionId, Xcp_SessionConfig_t* const pSessionCfg );
extern uint XCP_FN_TYPE Xcp_StimProcessor   ( const uint daqListId, const uint sessionId, Xcp_SessionConfig_t* const pSessionCfg );

extern void XCP_FN_TYPE Xcp_GetTimestamp    ( Xcp_StatePtr8 pTimestamp, uint numBytesTimestamp );
extern void XCP_FN_TYPE Xcp_DoDisconnect    ( uint sessionId, Xcp_Session_t* pSession );
extern void XCP_FN_TYPE Xcp_ResetDaqList    ( uint sessionId, uint daqListId );

/* If we do not support "seed and key" functionality we remap all "seed and key" commands to XcpCmdUnknown() */
#ifndef XCP_ENABLE_SEEDNKEY
    #define Xcp_CmdUnlock   Xcp_CmdUnknown
    #define Xcp_CmdGetSeed  Xcp_CmdUnknown
#endif /* !XCP_ENABLE_SEEDNKEY */

/* If we do not support the PGM resource we remap all PGM commands to XcpCmdUnknown() */
#ifndef XCP_ENABLE_PGM
    #define Xcp_CmdProgramStart     Xcp_CmdUnknown
    #define Xcp_CmdProgramClear     Xcp_CmdUnknown
    #define Xcp_CmdProgram          Xcp_CmdUnknown
    #define Xcp_CmdProgramNext      Xcp_CmdUnknown
    #define Xcp_CmdProgramMax       Xcp_CmdUnknown
    #define Xcp_CmdProgramReset     Xcp_CmdUnknown
    #define Xcp_CmdProgramPrepare   Xcp_CmdUnknown
    #define Xcp_CmdProgramFormat    Xcp_CmdUnknown
#endif /* !XCP_ENABLE_PGM */

/* If we do not support the CALPAG resource we remap all CALPAG commands to XcpCmdUnknown() */
#ifndef XCP_ENABLE_CALPAG
    #define Xcp_CmdSetCalPage       Xcp_CmdUnknown
    #define Xcp_CmdGetCalPage       Xcp_CmdUnknown
    #define Xcp_CmdCopyCalPage      Xcp_CmdUnknown
    #define Xcp_CmdGetPagProcInfo   Xcp_CmdUnknown
    #define Xcp_CmdSetSegmentMode   Xcp_CmdUnknown
    #define Xcp_CmdGetSegmentMode   Xcp_CmdUnknown

    #define Xcp_CmdDownload         Xcp_CmdUnknown
    #define Xcp_CmdDownloadNext     Xcp_CmdUnknown
    #define Xcp_CmdDownloadMax      Xcp_CmdUnknown
    #define Xcp_CmdModifyBits       Xcp_CmdUnknown
#endif /* !XCP_ENABLE_CALPAG */

/* If we do not support page freezing we remap the associated functions to XcpCmdUnknown() */
#ifndef XCP_ENABLE_PAGEFREEZE
    #define Xcp_CmdSetSegmentMode   Xcp_CmdUnknown
    #define Xcp_CmdGetSegmentMode   Xcp_CmdUnknown
#endif /* !XCP_ENABLE_PAGEFREEZE */

/* If we do not support various optional commands we remap them to XcpCmdUnknown() */
#ifndef XCP_ENABLE_OPTIONAL_CMDS
    #define Xcp_CmdDownloadMax      Xcp_CmdUnknown
    #define Xcp_CmdGetCommModeInfo  Xcp_CmdUnknown
    #define Xcp_CmdGetDaqListInfo   Xcp_CmdUnknown
    #define Xcp_CmdGetDaqProcInfo   Xcp_CmdUnknown
    #define Xcp_CmdGetDaqResInfo    Xcp_CmdUnknown
    #define Xcp_CmdGetId            Xcp_CmdUnknown
    #define Xcp_CmdGetPagProcInfo   Xcp_CmdUnknown
    #define Xcp_CmdProgramFormat    Xcp_CmdUnknown
    #define Xcp_CmdProgramMax       Xcp_CmdUnknown
    #define Xcp_CmdProgramPrepare   Xcp_CmdUnknown
    #define Xcp_CmdShortUpload      Xcp_CmdUnknown
    #define Xcp_CmdGetDaqListMode   Xcp_CmdUnknown
#endif /* !XCP_ENABLE_OPTIONAL_CMDS */

/* If we do not support dynamic DAQ lists we remap all dynamic DAQ commands to XcpCmdUnknown() */
#ifndef XCP_ENABLE_DYNDAQ
    #define Xcp_CmdAllocDaq         Xcp_CmdUnknown
    #define Xcp_CmdAllocOdt         Xcp_CmdUnknown
    #define Xcp_CmdFreeDaq          Xcp_CmdUnknown
    #define Xcp_CmdAllocOdtEntry    Xcp_CmdUnknown
#endif /* !XCP_ENABLE_DYNDAQ */

/* If we support neither RESUME nor page freezing we remap SET_REQUEST to XcpCmdUnknown() */
#if !defined( XCP_ENABLE_PAGEFREEZE ) && !defined( XCP_ENABLE_RESUME )
    #define Xcp_CmdSetRequest       Xcp_CmdUnknown
#endif /* !XCP_ENABLE_PAGEFREEZE && !XCP_ENABLE_RESUME */

/* If we do not support USER_CMD we remap USER_CMD to XcpCmdUnknown() */
#if !defined( XCP_ENABLE_USER_CMD )
    #define Xcp_CmdUser             Xcp_CmdUnknown
#endif /* !XCP_ENABLE_USER_CMD */

#endif /* _XCP_PRIV_H */
