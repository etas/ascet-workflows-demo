/**
*
* \file
*
* \brief This file defines a body for each of the callback functions which the XCP slave driver expects the
* user to implement.
*
* By their nature these callbacks depend on the user's ECU application and cannot be implemented generically;
* so many of the supplied function bodies simply return an error. Others contain a sample implementation which
* may be suitable in certain limited circumstances.
*
* Areas which require further implementation or review are marked with "TODO" comments.
*
* Some callbacks are needed only if certain XCP functionality is enabled. Preprocessor symbols of the form
* XCP_ENABLE_XXX indicate which callbacks are required in which circumstances.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_callbacks.c 18567 2010-04-29 15:26:13Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"

#include "main.h"
#include "xcp_mem.h"
#include "xcp_debug.h"

#define REFERENCE_PAGE_ID	0	/* as defined in memorysegment.a2l */
#define WORKING_PAGE_ID		1	/* as defined in memorysegment.a2l */

static uint8 activeEcuCalPage  = REFERENCE_PAGE_ID;

/******************************************************************************
 *
 * General functions and types
 *
 *****************************************************************************/

/**
 * The XCP slave driver calls this function when the CONNECT command is received with a user-defined connection
 * mode. It does not expect this function to take any particular actions.
 *
 * \param [in] sessionId    The ID of the XCP session which is connecting.
 */
void XcpApp_OnUserDefinedCxn( uint sessionId )
{
}

/**
 * The XCP slave driver calls this function when the CONNECT command is received with a normal connection
 * mode. It does not expect this function to take any particular actions.
 *
 * \param [in] sessionId    The ID of the XCP session which is connecting.
 */
void XcpApp_OnNormalCxn( uint sessionId )
{
}

/**
 * The XCP slave driver calls this function when the DISCONNECT command is received, or when disconnection
 * occurs for any other reason. It does not expect this function to take any particular actions.
 *
 * \param [in] sessionId    The ID of the XCP session which is disconnecting.
 */
void XcpApp_OnDisconnect( uint sessionId )
{
}

#ifdef XCP_ENABLE_USER_CMD

/**
 * The XCP slave driver calls this function when the USER_CMD command is received, provided that support for USER_CMD is
 * enabled via the global XML configuration parameter XCP_ENABLE_USER_CMD.
 *
 * The XCP slave driver expects this function to process the USER_CMD and set its output parameters appropriately. The XCP slave
 * driver performs no validation on either the input parameters or the output parameters.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet. The first byte is 0xF1; the second byte is the sub-command code;
 *                              subsequent bytes are the sub-command parameters (if any).
 * \param [out] pTxPacket       The response packet. When using CAN, this buffer contains space for 8 bytes; when using IP, the
 *                              buffer's size is determined by the per-session XML configuration parameter XCPIP_MAXCTO. This buffer
 *                              must be filled with a valid XCP RES or ERR packet, as described in sections 1.1.3.2 and 1.1.3.3
 *                              of part 2 of the XCP specification.
 * \param [out] pTxPacketSize   The number of bytes actually used at pTxPacket.
 */
void XcpApp_UserCmd( uint sessionId, Xcp_StatePtr8 pRxPacket, Xcp_StatePtr8 pTxPacket, uint* pTxPacketSize )
{
}

#endif /* XCP_ENABLE_USER_CMD */

/******************************************************************************
 *
 * Calibration page switching functions and types
 *
 *****************************************************************************/

#ifdef XCP_ENABLE_CALPAG

/**
 * The XCP slave driver expects this function to set the current "ECU" calibration page for a specified segment.
 *
 * The XCP slave driver relies on this function to determine whether the given segment number and
 * page number are valid. Therefore this function should *always* validate its arguments.
 *
 * The XCP slave driver does not check page access permissions before calling this function. Therefore this
 * function should check these permissions and return CALPAGE_REQUESTINVALID if there is a problem.
 *
 * \param [in] dataSegment      The segment whose calibration page is to be changed.
 * \param [in] calPage          The new ECU calibration page.
 *
 * \return See description of Xcp_CalPageErr.
 */
Xcp_CalPageErr XcpApp_SetEcuCalPage( uint8 dataSegment, uint8 calPage )
{
	// We only have one segment...
	return XcpApp_SetEcuCalPageAllSegs(calPage);
}

/**
 * The XCP slave driver expects this function to set the current "ECU" calibration page for all segments.
 *
 * The XCP slave driver relies on this function to determine whether the given page number is valid.
 * Therefore this function should *always* validate its argument.
 *
 * The XCP slave driver does not check page access permissions before calling this function. Therefore this
 * function should check these permissions and return CALPAGE_REQUESTINVALID if there is a problem.
 *
 * \param [in] calPage          The new ECU calibration page for all segments.
 *
 * \return See description of Xcp_CalPageErr.
 */
Xcp_CalPageErr XcpApp_SetEcuCalPageAllSegs( uint8 calPage )
{
	if (calPage == REFERENCE_PAGE_ID)
	{
#ifdef XCP_COM_DEBUG
		printf("\t[SetEcuCalPageAllSegs]\tREFERENCE_PAGE\n");
		fflush(stdout);
#endif
		activeEcuCalPage = REFERENCE_PAGE_ID;
		XcpMem_SetEcuReferencePage();
	    return CALPAGE_OK;
	}
	if (calPage == WORKING_PAGE_ID)
	{
#ifdef XCP_COM_DEBUG

		printf("\t[SetEcuCalPageAllSegs]\tWORKING_PAGE\n");
		fflush(stdout);
#endif
		activeEcuCalPage = WORKING_PAGE_ID;
		XcpMem_SetEcuWorkingPage();
	    return CALPAGE_OK;
	}
	return CALPAGE_PAGEINVALID;
}

/**
 * The XCP slave driver expects this function to set the current "tool" (or "XCP") calibration page for a
 * specified segment.
 *
 * The XCP slave driver relies on this function to determine whether the given segment number or
 * page number is valid. Therefore this function should *always* validate its arguments.
 *
 * The XCP slave driver does not check page access permissions before calling this function. Therefore this
 * function should check these permissions and return CALPAGE_REQUESTINVALID if there is a problem.
 *
 * \param [in] dataSegment      The segment whose calibration page is to be changed.
 * \param [in] calPage          The new tool calibration page.
 *
 * \return See description of Xcp_CalPageErr.
 */
Xcp_CalPageErr XcpApp_SetToolCalPage( uint8 dataSegment, uint8 calPage )
{
	/*
	 * Nothing to do.
	 * We don't need to remember the active tool page
	 * since tool page and ECU page will always be the same.
	 * This is because we use XCP_WRITE_ACCESS_WITH_ECU_ONLY and XCP_READ_ACCESS_WITH_ECU_ONLY
	 * in the definitions within memorysegment.a2l.
	 */
    return CALPAGE_OK;
}

/**
 * The XCP slave driver expects this function to set the current "tool" (or "XCP") calibration page for
 * all segments.
 *
 * The XCP slave driver relies on this function to determine whether a given page number is valid.
 * Therefore this function should *always* validate its arguments.
 *
 * The XCP slave driver does not check page access permissions before calling this function. Therefore this
 * function should check these permissions and return CALPAGE_REQUESTINVALID if there is a problem.
 *
 * \param [in] calPage          The new tool calibration page for all segments.
 *
 * \return See description of Xcp_CalPageErr.
 */
Xcp_CalPageErr XcpApp_SetToolCalPageAllSegs( uint8 calPage )
{
	/*
	 * Nothing to do.
	 * We don't need to remember the active tool page
	 * since tool page and ECU page will always be the same.
	 * This is because we use XCP_WRITE_ACCESS_WITH_ECU_ONLY and XCP_READ_ACCESS_WITH_ECU_ONLY
	 * in the definitions within memorysegment.a2l.
	 */
    return CALPAGE_OK;
}

/**
 * The XCP slave driver expects this function to return the current "ECU" calibration page for a given segment.
 *
 * The XCP slave driver tracks the current "tool" calibration page for each segment to allow it to implement
 * page freezing. Therefore there is no analogous XcpApp_GetToolCalPage() function.
 *
 * \param [in] dataSegment      The segment whose ECU page is required.
 *
 * \return The current ECU page for the given segment.
 */
uint8 XcpApp_GetEcuCalPage( uint8 dataSegment )
{
#ifdef XCP_COM_DEBUG
	printf("\t[GetEcuCalPage]\n");
	fflush(stdout);
#endif
    return activeEcuCalPage;
}

#endif /* XCP_ENABLE_CALPAG */

/******************************************************************************
 *
 * Calibration memory access functions and types
 *
 *****************************************************************************/

#ifdef XCP_ENABLE_CALPAG

/**
 * The XCP slave driver expects this function to write data to calibration memory. The function is expected
 * to write the data to the current "tool" (or "XCP") page of the appropriate segment of calibration memory.
 *
 * \param [in] mta          The address to which data should be written.
 * \param [in] numBytes     The number of bytes at pBytes.
 * \param [in] pBytes       The data to be written to mta.
 *
 * \return See description of Xcp_CalMemState.
 */
Xcp_CalMemState XcpApp_CalMemWrite( Xcp_Addr_t mta, uint32 numBytes, Xcp_StatePtr8 pBytes )
{
	Xcp_Addr_t dstAddr = XcpMem_GetEffectiveAddress(mta);
	if (!XcpMem_IsWriteAllowed(dstAddr, numBytes)) {
#ifdef XCP_COM_DEBUG
		printf("\t[CalMemWrite]\t0x%08lx L=%lu --> CALMEM_REQUESTNOTVALID\n", (uint32) dstAddr, numBytes);
		fflush(stdout);
#endif
		return CALMEM_REQUESTNOTVALID;
	}
#ifdef XCP_COM_DEBUG
		printf("\t[CalMemWrite]\t0x%08lx L=%lu\n", (uint32) dstAddr, numBytes);
		fflush(stdout);
#endif
	Xcp_MemCopy( dstAddr, pBytes, numBytes );
	return CALMEM_FINISHED;
}

#endif /* XCP_ENABLE_CALPAG */

/**
 * The XCP slave driver expects this function to read data from calibration memory. The function is expected
 * to read the data from the current "tool" (or "XCP") page of the appropriate segment of calibration memory.
 *
 * \param [in] mta          The address from which data should be read.
 * \param [in] numBytes     The number of bytes to be read.
 * \param [in] pBytes       A buffer to hold the bytes which are read.
 *
 * \return See description of Xcp_CalMemState.
 */
Xcp_CalMemState XcpApp_CalMemRead( Xcp_Addr_t mta, uint32 numBytes, Xcp_StatePtr8 pBytes )
{
	Xcp_Addr_t srcAddr = XcpMem_GetEffectiveAddress(mta);
	Xcp_MemCopy(pBytes, srcAddr, numBytes);
#ifdef XCP_COM_DEBUG
	printf("\t[CalMemRead]\t0x%08lx L=%lu\n", (uint32) srcAddr, numBytes);
	fflush(stdout);
#endif
	return CALMEM_FINISHED;
}

/**
 * The XCP slave driver expects this function to calculate a checksum over a region of memory. The function is expected
 * to use the current "tool" (or "XCP") page of the appropriate segment of calibration memory.
 *
 * \param [in] address          The address of the memory region for the checksum.
 * \param [in] numBytes         The size of the memory region for the checksum. The XCP slave driver will have validated this parameter already.
 * \param [out] pChecksumType   The type of checksum which was calculated. This should be expressed as described in the specification of the BUILD_CHECKSUM command.
 * \param [out] pChecksum       The checksum result.
 *
 * \return See description of Xcp_CalMemState.
 */
Xcp_CalMemState XcpApp_CalMemGetChecksum( Xcp_Addr_t address, uint32 numBytes, Xcp_StatePtr8 pChecksumType, Xcp_StatePtr32 pChecksum )
{
	Xcp_Addr_t startAddr = XcpMem_GetEffectiveAddress(address);
#ifdef XCP_COM_DEBUG
	printf("\t[CalMemGetChecksum] 0x%08lx L=%lu\n", (uint32) (startAddr),
			numBytes);
#endif
	uint32_t checksum = 0;
	for (uint32_t i = 0; i < numBytes; i++) {
		checksum += *startAddr;
		startAddr++;
	}
	*pChecksum = (uint32_t) checksum;
	*pChecksumType = 3;
	return CALMEM_FINISHED;
}

/**
 * If a previous request to access calibration memory has returned CALMEM_BUSY, at a later point in time
 * the XCP slave driver may call this function to get information on the progress of the previous
 * request.
 *
 * \return See description of Xcp_CalMemState.
 */
Xcp_CalMemState XcpApp_CalMemGetRequestState( void )
{
    // CALMEM_BUSY not used.
    return CALMEM_FINISHED;
}

#ifdef XCP_ENABLE_CALPAG

/**
 * The XCP slave driver expects this function to manipulate the bits at a given address according to the
 * algorithm given in the specification of the MODIFY_BITS command. The function is expected
 * to use the current "tool" (or "XCP") page of the appropriate segment of calibration memory.
 *
 * \param [in] mta              The address at which the bits should be manipulated.
 * \param [in] numShiftBits     See the specification of the MODIFY_BITS command.
 * \param [in] andMask          See the specification of the MODIFY_BITS command.
 * \param [in] xorMask          See the specification of the MODIFY_BITS command.
 *
 * \return See description of Xcp_CalMemState.
 */
Xcp_CalMemState XcpApp_CalMemModifyBits( Xcp_Addr_t mta, uint8 numShiftBits, uint16 andMask, uint16 xorMask )
{
#ifdef XCP_COM_DEBUG
		printf("\t[CalMemModifyBits] UNSUPPORTED\n");
#endif
    return CALMEM_REQUESTNOTVALID;
}

/**
 * The XCP slave driver expects this function to copy the contents of the specified source page to the
 * specified destination page.
 *
 * \param [in] destSegmentId        The destination segment for the copy operation.
 * \param [in] destPageId           The destination page for the copy operation.
 * \param [in] sourceSegmentId      The source segment for the copy operation.
 * \param [in] sourcePageId         The source page for the copy operation.
 *
 * \return See description of Xcp_CalMemState.
 */
Xcp_CalMemState XcpApp_CalPageCopy( uint8 destSegmentId, uint8 destPageId, uint8 sourceSegmentId, uint8 sourcePageId )
{
	UNUSED(destSegmentId);
	UNUSED(sourceSegmentId);

	// copy reference page to working page
	if (sourcePageId == REFERENCE_PAGE_ID
			&& destPageId == WORKING_PAGE_ID)
	{
		XcpMem_CopyReferencePageToWorkingPage();
	    return CALMEM_FINISHED;
	}
    return CALMEM_REQUESTNOTVALID;
}

#endif /* XCP_ENABLE_CALPAG */

#ifdef XCP_ENABLE_PAGEFREEZE

/**
 * The XCP slave driver expects this function to copy the contents of the current "tool" page of the specified
 * segment into PAGE 0 of the specified INIT_SEGMENT.
 *
 * \param [in] segmentId        The segment which is to be frozen.
 * \param [in] initSegmentId    The INIT_SEGMENT for the freeze request.
 *
 * \return See description of Xcp_CalMemState.
 */
Xcp_CalMemState XcpApp_CalSegFreeze( uint8 segmentId, uint8 initSegmentId )
{
    /* TODO: provide implementation */
    return CALMEM_REQUESTNOTVALID;
}

#endif /* XCP_ENABLE_PAGEFREEZE */

/******************************************************************************
 *
 * Measurement functions and types
 *
 *****************************************************************************/


/**
 * The XCP slave driver expects this function to convert an address of the form (address, extension) as supplied
 * by an XCP command into a pointer to the specified memory location.
 *
 * The (address, extension) pair can be supplied by any of the following XCP commands:
 *  - SET_MTA
 *  - SHORT_UPLOAD
 * Therefore the address may refer to a memory location in any type of memory.
 *
 * \param [in] address      The address to be converted.
 * \param [in] extension    The address extension to be converted.
 *
 * \return
 *  - A pointer to the specified location in memory. The pointer must refer to a single byte in memory.
 *  - 0 if the XCP tool is not permitted to access the specified address, or if the specified address is invalid.
 */
Xcp_Addr_t XcpApp_ConvertAddress( uint32 address, uint8 extension )
{
    /* Assume that no conversion is required. */
    return (Xcp_Addr_t)address;
}

/**
 * The XCP slave driver expects this function to indicate whether the specified memory region can be measured
 * or stimulated as part of a DAQ or STIM list.
 *
 * \param [in] address      The address of the memory region to be measured or stimulated.
 * \param [in] extension    The address extension of the memory region to be measured or stimulated.
 * \param [in] numBytes     The length of the memory region to be measured or stimulated.
 *
 * \return
 *  - zero      The specified memory region cannot be measured or stimulated.
 *  - non-zero  Otherwise.
 */
sint XcpApp_IsRegionMeasurable( uint32 address, uint8 extension, uint32 numBytes )
{
    /* Assume that all memory can be measured and stimulated. */
    return -1;
}

/******************************************************************************
 *
 * Non-volatile memory functions and types
 *
 *****************************************************************************/

#ifdef XCP_ENABLE_RESUME

/**
 * The XCP slave driver expects this function to write data to a pre-allocated region of non-volatile (NV) memory.
 * The size of the region is given by the preprocessor symbol XCP_NV_REGION_SIZE.
 *
 * \param [in] offset       The offset within the NV memory region at which the data is to be written.
 * \param [in] pData        The data to be written to the NV memory region.
 * \param [in] numBytes     The number of bytes at pData.
 */
void XcpApp_NvMemWrite( uint offset, Xcp_StatePtr8 pData, uint numBytes )
{
    /* TODO: provide implementation */
}

/**
 * The XCP slave driver expects this function to read data from a pre-allocated region of non-volatile (NV) memory.
 * The size of the region is given by the preprocessor symbol XCP_NV_REGION_SIZE.
 *
 * \param [in] offset       The offset within the NV memory region from which the data is to be read.
 * \param [in] pData        A buffer to receive the data which is read.
 * \param [in] numBytes     The number of bytes to be read.
 */
void XcpApp_NvMemRead( uint offset, Xcp_StatePtr8 pData, uint numBytes )
{
    /* TODO: provide implementation */
}

/**
 * The XCP slave driver expects this function to clear data from a pre-allocated region of non-volatile (NV) memory.
 * The size of the region is given by the preprocessor symbol XCP_NV_REGION_SIZE. Cleared data should be set to 0.
 *
 * \param [in] offset       The offset within the NV memory region at which the data is to be cleared.
 * \param [in] numBytes     The number of bytes to be cleared.
 */
void XcpApp_NvMemClear( uint offset, uint numBytes )
{
    /* TODO: provide implementation */
}

#endif /* XCP_ENABLE_RESUME */

/******************************************************************************
 *
 * Seed and key functions and types
 *
 *****************************************************************************/

#ifdef XCP_ENABLE_SEEDNKEY

/* We hard-code some example seeds. */
static const uint8 seeds[4][5] = { { 0x01, 0x02, 0x03, 0x04, 0x05 },    /* PGM seed */
                                   { 0x11, 0x12, 0x13, 0x14, 0x15 },    /* STIM seed */
                                   { 0x21, 0x22, 0x23, 0x24, 0x25 },    /* DAQ seed */
                                   { 0x31, 0x32, 0x33, 0x34, 0x35 } };  /* CAL/PAG seed */

/* The buffer which the XCP slave driver will fill with a key */
static uint8 keyBuffer[5];

/**
 * The XCP slave driver expects this function to calculate a seed for the specified ECU resource.
 *
 * The buffer which contains the seed is owned by this function and must be retained at least until:
 *  - either this function is called again for the same session;
 *  - or the function XcpApp_GetKeyBuffer() is called for the same session.
 *
 * This function must be able to support different seed buffers simultaneously for each session,
 * but not for each resource within a session.
 *
 * \param [in] sessionId    The XCP session which is requesting a seed.
 * \param [in] resource     The XCP resource with which the seed is associated.
 * \param [out] ppSeed      The seed.
 * \param [out] pSeedLen    The length of the seed.
 */
void XcpApp_GetSeed( uint sessionId, uint8 resource, Xcp_Seed_t* XCP_STATE_TYPE * ppSeed, Xcp_StatePtr8 pSeedLen )
{
    /* TODO: review this implementation */

    switch( resource )
    {
    case 0x10:
        /* We are being asked for the PGM seed. */
        *ppSeed = seeds[0];
        break;
    case 0x08:
        /* We are being asked for the STIM seed. */
        *ppSeed = seeds[1];
        break;
    case 0x04:
        /* We are being asked for the DAQ seed. */
        *ppSeed = seeds[2];
        break;
    case 0x01:
        /* We are being asked for the CAL/PAG seed. */
        *ppSeed = seeds[3];
        break;
    }

    /* The seed is always 5 bytes long. */
    *pSeedLen = 5;
}

/**
 * The XCP slave driver expects this function to allocate a buffer to be used by the XCP slave
 * driver to store a key. The key corresponds to the seed provided by the previous call to XcpApp_GetSeed(). 
 *
 * The buffer which contains the key is owned by this function and must be retained at least until:
 *  - either the function is called again for the same session;
 *  - or the function XcpApp_UnlockResource() is called for the same session;
 *  - or the function XcpApp_GetSeed() is called for the same session.
 *
 * The function must be able to support different key buffers simultaneously for each session,
 * but not for each resource within a session.
 *
 * \param [in] sessionId    The XCP session which is requesting a key buffer.
 * \param [in] resource     The XCP resource with which the key buffer is associated.
 * \param [out] ppKey       The key buffer.
 * \param [in] keyLen       The length of the key buffer.
 */
void XcpApp_GetKeyBuffer( uint sessionId, uint8 resource, Xcp_Key_t* XCP_STATE_TYPE * ppKey, uint8 keyLen )
{
    /* TODO: review this implementation */

    /* Hand out our one-and-only key buffer. We assume that we are using the example XcpSeedNKey.dll, therefore
     * the key is the same length as the seed, therefore the key buffer must be 5 bytes long. */
    *ppKey = keyBuffer;
}

/**
 * The XCP slave driver expects this function to check whether the previous seed issued by XcpApp_GetSeed()
 * (for the same session) corresponds to the key now present in the previous buffer issued
 * by XcpApp_GetKeyBuffer() (for the same session).
 *
 * \param [in] sessionId    The XCP session which is requesting the unlock.
 * \param [in] resource     The XCP resource which is to be unlocked.
 *
 * \return A boolean indicating whether the specified resource should be unlocked for the specified session.
 */
sint XcpApp_UnlockResource( uint sessionId, uint8 resource )
{
    /* TODO: review this implementation */

    int i;

    /* Modify the resource argument to become an index into the array of seeds. */
    switch( resource )
    {
    case 0x10:
        /* We are being asked for the PGM seed. */
        resource = 0;
        break;
    case 0x08:
        /* We are being asked for the STIM seed. */
        resource = 1;
        break;
    case 0x04:
        /* We are being asked for the DAQ seed. */
        resource = 2;
        break;
    case 0x01:
        /* We are being asked for the CAL/PAG seed. */
        resource = 3;
        break;
    }

    /* Compare the key buffer with the appropriate entry in the array of seeds. We assume that we are using the
     * example XcpSeedNKey.dll, therefore:
     *  - the key is the same length as the seed, and both are 5 bytes long;
     *  - the key and the seed should be equal. */
    for( i = 0; i < 5; ++i )
    {
        if( keyBuffer[i] != seeds[resource][i] )
        {
            /* The key buffer and the seed differ. */
            return 0;
        }
    }

    /* The key buffer and the seed are the same. */
    return -1;
}

#endif /* XCP_ENABLE_SEEDNKEY */

/******************************************************************************
 *
 * Flashing functions and types
 *
 *****************************************************************************/

#ifdef XCP_ENABLE_PGM

/**
 * The XCP slave driver expects this function to perform the operations expected by the PROGRAM_START command.
 *
 * \param [in] mta      The current MTA.
 *
 * \return See description of Xcp_ProgramState.
 */
Xcp_ProgramState XcpApp_ProgramStart( Xcp_Addr_t mta )
{
    /* TODO: provide implementation */
    return PROGRAM_INVALIDSTATE;
}

/**
 * The XCP slave driver expects this function to perform the operations expected by the PROGRAM_CLEAR command.
 *
 * \param [in] mta      The current MTA.
 * \param [in] length   The length of the range to be cleared.
 *
 * \return See description of Xcp_ProgramState.
 */
Xcp_ProgramState XcpApp_ProgramClear( Xcp_Addr_t mta, uint32 length )
{
    /* TODO: provide implementation */
    return PROGRAM_INVALIDSTATE;
}

/**
 * The XCP slave driver expects this function to program data into flash memory. The function may program the
 * data immediately, or it may buffer the data and program an entire block on a subsequent invocation.
 *
 * \param [in] mta          The address at which data should be programmed.
 * \param [in] numBytes     The number of bytes at pBytes. This may be 0 to indicate the end of a memory segment.
 * \param [in] pBytes       The data to be programmed.
 *
 * \return See description of Xcp_ProgramState.
 */
Xcp_ProgramState XcpApp_Program( Xcp_Addr_t mta, uint8 numBytes, Xcp_StatePtr8 pBytes )
{
    /* TODO: provide implementation */
    return PROGRAM_INVALIDSTATE;
}

/**
 * The XCP slave driver expects this function to perform the operations expected by the PROGRAM_RESET command.
 * This function may reset the device.
 *
 * \return See description of Xcp_ProgramState.
 */
Xcp_ProgramState XcpApp_ProgramReset( void )
{
    /* TODO: provide implementation */
    return PROGRAM_INVALIDSTATE;
}

/**
 * If a previous request to program flash memory has returned PROGRAM_BUSY, at a later point in time
 * the XCP slave driver may call this function to get information on the progress of the previous
 * request.
 *
 * \return See description of Xcp_ProgramState.
 */
Xcp_ProgramState XcpApp_ProgramGetRequestState( void )
{
    /* TODO: review implementation. This implementation is only adequate if no XcpApp_ProgramXXX() functions return PROGRAM_BUSY. */
    return PROGRAM_INVALIDSTATE;
}

#ifdef XCP_ENABLE_OPTIONAL_CMDS

/**
 * The XCP slave driver expects this function to perform the operations expected by the PROGRAM_PREPARE command.
 *
 * \param [in] mta          The current MTA.
 * \param [in] codeSize     The size of the code block which will be downloaded to the MTA after the PROGRAM_PREPARE command completes.
 *
 * \return See description of Xcp_ProgramState.
 */
Xcp_ProgramState XcpApp_ProgramPrepare( Xcp_Addr_t mta, uint16 codeSize )
{
    /* TODO: provide implementation */
    return PROGRAM_INVALIDSTATE;
}

#endif /* XCP_ENABLE_OPTIONAL_CMDS */

#endif /* XCP_ENABLE_PGM */
