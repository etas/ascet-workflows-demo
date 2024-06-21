/**
 * Copyright ETAS GmbH, Stuttgart, Germany. All rights reserved.
 *
 * esdl.h is the main header file of the generated model code.
 * It provides:
 *  # definition of standard C types
 *  # type limits
 *  # interfaces for operating system services
 */
#ifndef ESDL_H
#define ESDL_H

/* compatibility level of the ESDL header files */
#define ESDL_HEADER_VERSION (7)

/* callback to user defined types, declarations etc. */
#include "esdl_usercfg.h"

/* operating system/scheduling related services */
#include "esdl_mutex.h"

/* contains additional service functions, which can be overridden in esdl_usercfg.h */
#include "esdl_services.h"

/* C base types used in generated code */
#if defined(ESDL_AUTOSAR_USE_RTE_TYPE)
    /* Access AUTOSAR types through the RTE header */
    #include "Rte_Type.h"
    /* Map internal boolean values true/false to AUTOSAR standard values TRUE/FALSE */
    #ifndef false
        #define false FALSE
    #endif
    #ifndef true
        #define true  TRUE
    #endif
#elif defined(ESDL_AUTOSAR_USE_STD_TYPES)
    /* Access AUTOSAR types through the Standard Types header */
    #include "Std_Types.h"
    /* Map internal boolean values true/false to AUTOSAR standard values TRUE/FALSE */
    #ifndef false
        #define false FALSE
    #endif
    #ifndef true
        #define true  TRUE
    #endif
#else
    #if defined(ESDL_CUSTOM_BASE_TYPES)
        /* Use customized base type definitions */
        #include ESDL_CUSTOM_BASE_TYPES
    #else
        /* Use native base type definitions */
        #include "esdl_types.h"
    #endif
#endif

/* C type limits */
#include "esdl_limits.h"

/* Legacy support for old ASCET6 interpolation services */
#if defined(ESDL_LEGACY_INTERPOLATION_LINEAR)
    #include "Linear.h"
#endif
#if defined(ESDL_LEGACY_INTERPOLATION_ROUNDED)
	#include "Rounded.h"
#endif

#endif /* ESDL_H */
