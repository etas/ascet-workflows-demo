/**
 * Target specific implementation for STM32F334R8TX.
 */

#ifndef TARGETSPECIFIC_XCP_MEM_H_
#define TARGETSPECIFIC_XCP_MEM_H_

#include "xcp_target.h"

void XcpMem_Initialize();
void XcpMem_SetEcuReferencePage();
void XcpMem_SetEcuWorkingPage();
void XcpMem_CopyReferencePageToWorkingPage();
unsigned int XcpMem_GetActiveEcuPageOffset();
unsigned int XcpMem_IsWriteAllowed(Xcp_Addr_t addr, unsigned int numBytes);
Xcp_Addr_t XcpMem_GetEffectiveAddress(Xcp_Addr_t addr);

#endif /* TARGETSPECIFIC_XCP_MEM_H_ */
