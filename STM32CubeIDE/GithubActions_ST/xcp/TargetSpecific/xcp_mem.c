/**
 * Target specific implementation for STM32F334R8TX.
 */

#include "xcp_mem.h"

/****************************************************************************
 * Memory symbol definition (defined by linker script)
 ****************************************************************************/

extern unsigned int _sascet_calibration_rom; // start address of ASCET characteristics (ROM, reference page)
extern unsigned int _eascet_calibration_rom; // end address of ASCET characteristics (ROM, reference page)
extern unsigned int _sascet_calibration_ram; // start address of ASCET characteristics (RAM, working page)

/****************************************************************************
 * Private defines
 ****************************************************************************/

#define REFERENCE_PAGE_START_ADDR	(uint8*) &_sascet_calibration_rom
#define REFERENCE_PAGE_END_ADDR		(uint8*) &_eascet_calibration_rom
#define WORKING_PAGE_START_ADDR		(uint8*) &_sascet_calibration_ram
#define WORKING_PAGE_END_ADDR		WORKING_PAGE_START_ADDR + CAL_PAGE_SIZE

#define CAL_PAGE_SIZE		(REFERENCE_PAGE_END_ADDR - REFERENCE_PAGE_START_ADDR)
#define CAL_PAGE_OFFSET		(WORKING_PAGE_START_ADDR - REFERENCE_PAGE_START_ADDR)

// see linker script...
#define CODE_PAGE_START_ADDR 0x08000000
#define CODE_PAGE_END_ADDR   0x08000000 + 63456

/****************************************************************************
 * Private variables
 ****************************************************************************/

static unsigned int activeEcuPageOffset = 0;

/****************************************************************************
 * Private function declarations
 ****************************************************************************/

static inline unsigned int isWorkingPageAddress(Xcp_Addr_t addr);
static inline unsigned int isReferencePageAddress(Xcp_Addr_t addr);

/****************************************************************************
 * Identifier + Git revision information (part of .hex file)
 ****************************************************************************/

#ifndef AGA_REVISION
	#error("Revision must be defined.")
#endif
__attribute__((section(".epk_sec")))
const char EPK[32] = "ASCET GitHub Actions (" AGA_REVISION ")";

/****************************************************************************
 * Public functions
 ****************************************************************************/

void XcpMem_Initialize() {
	XcpMem_CopyReferencePageToWorkingPage();
}

void XcpMem_SetEcuReferencePage() {
	activeEcuPageOffset = 0;
}

void XcpMem_SetEcuWorkingPage() {
	activeEcuPageOffset = CAL_PAGE_OFFSET;
}

unsigned int XcpMem_GetActiveEcuPageOffset() {
	return activeEcuPageOffset;
}

Xcp_Addr_t XcpMem_GetEffectiveAddress(Xcp_Addr_t addr) {
	if (isReferencePageAddress(addr)) {
		return addr + XcpMem_GetActiveEcuPageOffset();
	}
	return addr;
}

void XcpMem_CopyReferencePageToWorkingPage() {
	Xcp_MemCopy(
			WORKING_PAGE_START_ADDR /* srcAddr */,
			REFERENCE_PAGE_START_ADDR /* dstAddr*/ ,
			CAL_PAGE_SIZE /* numBytes*/ );
}

unsigned int XcpMem_IsWriteAllowed(Xcp_Addr_t addr, unsigned int numBytes) {
	return isWorkingPageAddress(addr) &&
			isWorkingPageAddress(addr + numBytes - 1);
}

/****************************************************************************
 * Private functions
 ****************************************************************************/

static inline unsigned int isReferencePageAddress(Xcp_Addr_t addr) {
	return ((uint32)addr >= (uint32)REFERENCE_PAGE_START_ADDR)
			&& ((uint32)addr < (uint32)REFERENCE_PAGE_END_ADDR);
}

static inline unsigned int isWorkingPageAddress(Xcp_Addr_t addr) {
	return ((uint32)addr >= (uint32)WORKING_PAGE_START_ADDR)
			&& ((uint32)addr < (uint32)WORKING_PAGE_END_ADDR);
}
