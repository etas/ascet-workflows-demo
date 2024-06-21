/**
*
* \file
*
* \brief Definitions and declarations specific to the PORTNOTE target
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_target.h 18659 2010-05-18 07:47:27Z olcritch $
*
******************************************************************************/

#ifndef _XCP_TARGET_H
#define _XCP_TARGET_H

#include "xcp_common.h"
#include "xcp_auto_confdefs.h"

#if defined( XCP_ENV_RTAOSEK4 ) || defined( XCP_ENV_RTAOSEK5 ) || defined( XCP_ENV_ASCET )
    /* We are using RTA-OSEK (either standalone of via ASCET). */
#ifndef OS_OSEKCOMN_H
    /* We have not yet included an RTA-OSEK header, so do so now. */
    #include "osek.h"
#endif
#elif defined( XCP_ENV_RTAOS )
    /* We are using RTA-OS. */
    #include "Os.h"
#endif

/******************************************************************************
*
* Preprocessor definitions
*
******************************************************************************/

/* XCP_PACK() ensures that a given structure is packed with no gaps.
 *
 * Some compilers do not allow the user to specify that a structure should be packed with no gaps.
 * Such a compiler always uses the same rules to decide how to pack structures.
 *
 * In such a case, the user must manually inspect each usage of XCP_PACK() within the XCP slave driver
 * and satisfy himself that the compiler's default rules will, in fact, produce a closely-packed
 * structure. If this is the case, then the user may give XCP_PACK a trivial definition.
 */
#define XCP_PACK( type ) type

/* This macro prefixes every definition of a type which contains configuration (i.e. ROM data) for the XCP slave driver. */
#define XCP_CONFIG_TYPE const

/* This macro prefixes every definition of a type which contains state (i.e. RAM data) for the XCP slave driver. */
#define XCP_STATE_TYPE

/* This macro prefixes every definition of a function for the XCP slave driver. */
#define XCP_FN_TYPE

/* These macros enable or disable all interrupts and must be able to be nested.
 *
 * If we are using RTA-OSEK (either standalone or via ASCET) we can just delegate to the appropriate RTA-OSEK API.
 * Otherwise the user must supply his own implementation.
 */
#if defined( XCP_ENV_RTAOSEK4 ) || defined( XCP_ENV_RTAOSEK5 ) || defined( XCP_ENV_RTAOS ) || defined( XCP_ENV_ASCET )
    #define XCP_DISABLE_ALL_INTERRUPTS()    SuspendAllInterrupts()
    #define XCP_ENABLE_ALL_INTERRUPTS()     ResumeAllInterrupts()
#else
    #define XCP_DISABLE_ALL_INTERRUPTS()    // TODO
    #define XCP_ENABLE_ALL_INTERRUPTS()     // TODO
#endif

/* These macros indicate the size of the structs Xcp_OdtEntryCfg_t, Xcp_NvDaqState_t, Xcp_NvSession_t and Xcp_DaqDynConfig_t. */
#define sizeof_Xcp_OdtEntryCfg_t    1
#define sizeof_Xcp_NvDaqState_t     6
#define sizeof_Xcp_NvSession_t      12
#define sizeof_Xcp_DaqDynConfig_t   ( XCP_MAX_ODT_ENTRIES_DYNDAQ + 2 )

/* An ODT entry is configured at runtime via the WRITE_DAQ command. The following properties can be set:
 *  (1) the address of the data to be measured (or stimulated);
 *  (2) one of:
 *      (2a) the number of bytes of data to be measured (or stimulated) at the specified address;
 *           (this can be from 1 to 8 (for CAN) or 127 (for IP)).
 *      (2b) a bit offset specifying the location of the bit to be measured (or stimulated) at the specified address.
 *           (According to the XCP specification, the bit offset can be from 0 to 31, but the XCP slave driver modifies the
 *           specified address so that the bit offset is from 0 to 7).
 *
 * For each ODT entry the XCP slave driver provides two locations which can be used to store the above properties:
 *  - a uint8, referred to as the "ODT entry config";
 *  - an instance of Xcp_OdtEntryAddr_t, referred to as the "ODT entry address".
 *
 * The macros defined below are used to pack and unpack the ODT entry properties to/from the "ODT entry config" and
 * the "ODT entry address".
 *
 * A straightforward implementation of these macros is as follows:
 *  - Xcp_OdtEntryAddr_t is defined as a pointer type.
 *  - Property (1) is cast to a Xcp_OdtEntryAddr_t and stored in the "ODT entry address".
 *  - If property (2a) is set, it is stored in the "ODT entry config".
 *  - If property (2b) is set, it is stored in the "ODT entry config", and the uppermost bit of "ODT entry config" is set
 *    to indicate that the "ODT entry config" contains property (2b) and not (2a).
 *
 * The files SampleTarget/target.h and VS2005/target.h include such an implementation of these macros.
 *
 * This straightforward implementation is easy to understand, but it is wasteful of RAM since a full pointer is used to
 * store property (1), when it is quite likely that all possible values of (1) are concentrated in a relatively small
 * region of memory.
 *
 * However, on a resource-limited target it is possible to exploit the knowledge of the limited values of (1)
 * and define these macros so as to store the ODT properties more efficiently. This is of great importance in reducing
 * RAM usage, since many ODT entries may be defined simultaneously.
 *
 * Notes
 * -----
 *  - It is important that the following statement is always true:
 *      "The 'ODT entry config' has the value 0 iff no measurement (or stimulation) is configured for the ODT entry."
 *
 *  - The user can also exploit known limits of properties (2a) and (2b). For example, if the user knows that bitwise DAQ is
 *    never used, and that ODT entries are never longer than 4 bytes, he can assume that (2b) will never be set and that
 *    (2a) will only have values from 1 to 4.
 *
 * Example 1
 * ---------
 * For example, consider a 16-bit target which uses a 2K block of RAM to store all measurement variables. The following
 * implementation can be used to store the ODT entry properties:
 *  - Property (1) is adjusted so that it specifies an address with respect to the start of the 2K RAM region. This limits
 *    property (1) to 11 bits.
 *  - Xcp_OdtEntryAddr_t is defined as a uint8.
 *  - The lower 8 bits of property (1) are stored in the "ODT entry address" (which is now a uint8).
 *  - The "ODT entry config" is used as follows:
 *      - Bit 7 is set to 0 if property (2a) is set and 1 if property (2b) is set.
 *      - Bits 4-6 contain the upper 3 bits of property (1).
 *      - Bits 0-3 contain either property (2a) or property (2b)
 *
 * This allows the ODT entry properties to be stored in a total of 2 bytes.
 *
 * Example 2
 * ---------
 * For example, consider a 32-bit target which uses a 32K block of RAM to store all measurement variables. The following
 * implementation can be used to store the ODT entry properties:
 *  - Property (1) is adjusted so that it specifies an address with respect to the start of the 32K RAM region. This limits
 *    property (1) to 15 bits.
 *  - Xcp_OdtEntryAddr_t is defined as a uint16.
 *  - Property (1) is stored in the "ODT entry address" (which is now a uint16).
 *  - The "ODT entry config" is used as follows:
 *      - Bit 7 is set to 0 if property (2a) is set and 1 if property (2b) is set.
 *      - Bits 0-3 are used to store property (2a), if it is set
 *      - Bits 0-3 are used to store property (2b), if it is set
 *
 * This allows the ODT entry properties to be stored in a total of 3 bytes.
 */


/* This identifies the bit within an "ODT entry config" which indicates whether the "ODT entry config" describes a whole number
 * of bytes or a bit offset. */
#define XCP_ODTENTRY_SINGLE_BIT         0x80

/* This mask identifies the bits within an "ODT entry config" which contain a bit offset. Note that this macro is not used
 * outside this file. */
#define XCP_ODTENTRY_BITOFFSET_MASK     0x07

/* This function-like macro packs the properties of an ODT entry into the unit8 value referred to as the "ODT entry config".
 * The ODT entry in question refers to a whole number of bytes, not a bit offset.
 *
 * This macro will be called alongside XCP_PACK_ODTENTRYADDR_BYTE(), therefore these two macros can be used to distribute the
 * ODT entry properties between the "ODT entry config" and the "ODT entry address".
 *
 * See the comments above for an explanation of "ODT entry config" and "ODT entry address".
 *
 * \param[in] addr          The ODT entry address, as supplied to the XCP command WRITE_DAQ.
 * \param[in] addrExt       The ODT entry address extension, as supplied to the XCP command WRITE_DAQ.
 * \param[in] numBytes      The number of bytes to be measured (or stimulated) at the specified address.
 *
 * \return A uint8 which will be used as the "ODT entry config".
 */
/* PORTNOTE: read the above comments and review the appropriateness of this macro definition */
#define XCP_PACK_ODTENTRYCFG_BYTE( /* uint32 */addr, /* uint8 */addrExt, /* uint8 */numBytes ) \
    ( numBytes )

/* This function-like macro packs the properties of an ODT entry into the Xcp_OdtEntryAddr_t value referred to as the
 * "ODT entry address". The ODT entry in question refers to a whole number of bytes, not a bit offset.
 *
 * This macro will be called alongside XCP_PACK_ODTENTRYCFG_BYTE(), therefore these two macros can be used to distribute the
 * ODT entry properties between the "ODT entry config" and the "ODT entry address".
 *
 * See the comments above for an explanation of "ODT entry config" and "ODT entry address".
 *
 * \param[in] addr          The ODT entry address, as supplied to the XCP command WRITE_DAQ.
 * \param[in] addrExt       The ODT entry address extension, as supplied to the XCP command WRITE_DAQ.
 * \param[in] numBytes      The number of bytes to be measured (or stimulated) at the specified address.
 *
 * \return A Xcp_OdtEntryAddr_t which will be used as the "ODT entry address".
 */
/* PORTNOTE: read the above comments and review the appropriateness of this macro definition */
#define XCP_PACK_ODTENTRYADDR_BYTE( /* uint32 */addr, /* uint8 */addrExt, /* uint8 */numBytes )\
    ( (Xcp_OdtEntryAddr_t)( addr ) )

/* This function-like macro packs the properties of an ODT entry into the unit8 value referred to as the "ODT entry config".
 * The ODT entry in question refers to a bit offset, not a whole number of bytes.
 *
 * This macro will be called alongside XCP_PACK_ODTENTRYADDR_BYTE(), therefore these two macros can be used to distribute the
 * ODT entry properties between the "ODT entry config" and the "ODT entry address".
 *
 * See the comments above for an explanation of "ODT entry config" and "ODT entry address".
 *
 * \param[in] addr          The ODT entry address.
 * \param[in] addrExt       The ODT entry address extension.
 * \param[in] bitOffset     The offset of the bit to be measured (or stimulated) at the specified address, from 0 to 7.
 *
 * \return A uint8 which will be used as the "ODT entry config".
 */
/* PORTNOTE: read the above comments and review the appropriateness of this macro definition */
#define XCP_PACK_ODTENTRYCFG_BIT( /* uint32 */addr, /* uint8 */addrExt, /* uint8 */bitOffset )\
    ( XCP_ODTENTRY_SINGLE_BIT | ( bitOffset ) )

/* This function-like macro reverses the packing which was performed by XCP_PACK_ODTENTRYADDR_BYTE() and
 * XCP_PACK_ODTENTRYCFG_BYTE(). It takes an "ODT entry config" and extracts the number of bytes which the ODT entry
 * is configured to measure (or stimulate).
 *
 * See the comments above for an explanation of "ODT entry config" and "ODT entry address".
 *
 * \param[in] odtEntryAddr  The output of XCP_PACK_ODTENTRYADDR_BYTE()
 * \param[in] odtEntryCfg   The output of XCP_PACK_ODTENTRYCFG_BYTE()
 *
 * \return The number of bytes which the ODT entry is configured to measure (or stimulate).
 */
/* PORTNOTE: read the above comments and review the appropriateness of this macro definition */
#define XCP_UNPACK_ODTENTRY_NUMBYTES( /* Xcp_OdtEntryAddr_t */odtEntryAddr, /* uint8 */odtEntryCfg )\
    ( odtEntryCfg )

/* This function-like macro reverses the packing which was performed by XCP_PACK_ODTENTRYADDR_BYTE() and
 * XCP_PACK_ODTENTRYCFG_BYTE(). It takes an "ODT entry address" and extracts the address which the ODT entry
 * is configured to measure (or stimulate).
 *
 * See the comments above for an explanation of "ODT entry config" and "ODT entry address".
 *
 * \param[in] odtEntryAddr  The output of XCP_PACK_ODTENTRYADDR_BYTE()
 * \param[in] odtEntryCfg   The output of XCP_PACK_ODTENTRYCFG_BYTE()
 *
 * \return The address which the ODT entry is configured to measure (or stimulate).
 */
/* PORTNOTE: read the above comments and review the appropriateness of this macro definition */
#define XCP_UNPACK_ODTENTRY_BYTEADDR( /* Xcp_OdtEntryAddr_t */odtEntryAddr, /* uint8 */odtEntryCfg )\
    ( (Xcp_Addr_t)( odtEntryAddr ) )

/* This function-like macro reverses the packing which was performed by XCP_PACK_ODTENTRYADDR_BYTE() and
 * XCP_PACK_ODTENTRYCFG_BIT(). It takes an "ODT entry config" and extracts the offset of the bit which the ODT entry
 * is configured to measure (or stimulate).
 *
 * See the comments above for an explanation of "ODT entry config" and "ODT entry address".
 *
 * \param[in] odtEntryAddr  The output of XCP_PACK_ODTENTRYADDR_BYTE()
 * \param[in] odtEntryCfg   The output of XCP_PACK_ODTENTRYCFG_BIT()
 *
 * \return The offset of the bit which the ODT entry is configured to measure (or stimulate).
 */
/* PORTNOTE: read the above comments and review the appropriateness of this macro definition */
#define XCP_UNPACK_ODTENTRY_BITOFFSET( /* Xcp_OdtEntryAddr_t */odtEntryAddr, /* uint8 */odtEntryCfg )\
    ( ( odtEntryCfg ) & XCP_ODTENTRY_BITOFFSET_MASK )

/******************************************************************************
*
* Type definitions
*
******************************************************************************/

#if !defined( XCP_ENV_ASCET ) && !defined( XCP_ENV_RTAOSEK5 ) && !defined( XCP_ENV_RTAOS )

/* We are using neither ASCET nor an Autosar build environment, so we must provide the following type definitions here since we
 * cannot obtained them from elsewhere. */
typedef unsigned char       uint8;              /* An unsigned 8-bit integer. */
typedef unsigned short      uint16;             /* An unsigned 16-bit integer. */
typedef unsigned long       uint32;             /* An unsigned 32-bit integer. */
typedef signed char         sint8;              /* A signed 8-bit integer. */
typedef short               sint16;             /* A signed 16-bit integer. */
typedef long                sint32;             /* A signed 32-bit integer. */

#endif

typedef uint8*              Xcp_Addr_t;         /* The type used for all pointers to DAQ, STIM or calibration memory. It must have a width of 1 byte. */
typedef uint8*              Xcp_OdtEntryAddr_t; /* The type of the "ODT entry address" (see the comments above). */
typedef uint8               XcpCan_MsgObjId_t;  /* The type of a CAN message object ID. */

/* PORTNOTE check that the following typedefs are still correct. */
typedef XCP_CONFIG_TYPE uint8*                  Xcp_CfgPtr8;        /* Instances of this type refer to a location of type XCP_CONFIG_TYPE. */
typedef XCP_CONFIG_TYPE uint16*                 Xcp_CfgPtr16;       /* Instances of this type refer to a location of type XCP_CONFIG_TYPE. */
typedef XCP_CONFIG_TYPE uint32*                 Xcp_CfgPtr32;       /* Instances of this type refer to a location of type XCP_CONFIG_TYPE. */
typedef XCP_STATE_TYPE  uint8*                  Xcp_StatePtr8;      /* Instances of this type refer to a location of type XCP_STATE_TYPE. */
typedef XCP_STATE_TYPE  uint16*                 Xcp_StatePtr16;     /* Instances of this type refer to a location of type XCP_STATE_TYPE. */
typedef XCP_STATE_TYPE  uint32*                 Xcp_StatePtr32;     /* Instances of this type refer to a location of type XCP_STATE_TYPE. */
/* We do not define typedefs for uint* and sint* since all instances of these types contain the address of a location on the stack,
 * which is assumed to be in the default memory space. */


typedef const uint8         Xcp_Seed_t;         /* The seed is an array of this type. */
typedef uint8               Xcp_Key_t;          /* The key buffer is an array of this type. */

/******************************************************************************
*
* Function definitions
*
******************************************************************************/

uint8*  Xcp_MemCopy         ( uint8* pDest, const uint8* pSrc, uint numBytes );
void    Xcp_MemZero         ( uint8* pMemory, uint numBytes );
sint    Xcp_CheckCanId      ( uint32 canMsgId );

#endif /* _XCP_TARGET_H */
