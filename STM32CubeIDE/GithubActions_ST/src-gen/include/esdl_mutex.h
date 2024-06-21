#ifndef ESDL_MUTEX_H
#define ESDL_MUTEX_H
/**
 * Copyright ETAS GmbH, Stuttgart, Germany. All rights reserved.
 *
 * This header file provides required real-time definitions from the underlying operating system.
 * ASCET-generated code uses OSEK - API:
 * - void DisableAllInterrupts(void)
 * - void EnableAllInterrupts(void)
 * - void SuspendAllInterrupts(void)
 * - void ResumeAllInterrupts(void)
 * to enter some critical sections for message caching.
 *
 * SuspendAllInterrupts() - shall disable all interrupts on the device up to and
 *                          including the interrupt priority of the highest priority interrupt.
 * ResumeAllInterrupts() -  shall enable the interrupts again.
 */

#include "esdl_usercfg.h"
#ifdef ESDL_PLATFORM_INTERNAL_BUILD
	#include "platform_defs.h"
#endif

#if defined(OSENV_RTAOS40) || defined(OSENV_RTAOS30)
	/* Use AUTOSAR OS */
	#include "Os.h"

#elif defined(OSENV_RTAOSEK)
	/* Use the RTA-OSEK version of OSEK API
	 * This may work for other OSEK implementations
	 * and assumes an OSEK OS 2.2.3 compatible API
	 */
	#include "osek.h"

#elif defined(OSENV_SINGLE_THREADED)
	/* Mock OSEK OS environment for single threaded execution.
	 */
	#define ESDL_MISRA_NOP() do {} while(0)
	#define SuspendAllInterrupts() ESDL_MISRA_NOP()
	#define ResumeAllInterrupts() ESDL_MISRA_NOP()
	#define DisableAllInterrupts() ESDL_MISRA_NOP()
	#define EnableAllInterrupts() ESDL_MISRA_NOP()

#elif defined(OSENV_USER_UNSUPPORTED)
	/* Use a generic OSEK OS environment.
	 * Operating system dependencies will be handled somewhere outside of this header file by
	 * user code. User can signal this configuration by defining OSENV_USER_UNSUPPORTED macro
	 * e.g.: via esdl_usercfg.h
	 */

#else
	/* If the compiler has reached this code here, it's an indication
	 * for an insufficient configuration for an underling operating system.
	 * So break compilation.
	 */
	#error Potentially unsafe message caching. Race conditions may occur in multi-threaded environments. See esdl_mutex.h for options

#endif /* OSENV_SINGLE_THREADED */

#if !defined(ESDL_USER_MEMCPY) || !defined(RTE_LIBC_MEMCPY)
	/* Message copy caching needs a memcpy, with identical behavior to that provided in the
	 * standard C library for fast caching of composite data elements
	 * Expectation is: user can bind memcpy() via esdl_usercfg.h and singal this by defining ESDL_USER_MEMCPY or RTE_LIBC_MEMCPY
	 * Otherwise use C standard library function from string.h
	 */
	#include "string.h"
#endif

#endif /* ESDL_MUTEX_H */
