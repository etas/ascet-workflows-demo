/**
 * Copyright ETAS GmbH, Stuttgart, Germany. All rights reserved.
 *
 * Provides base type definitions used in generated C code.
 */
#ifndef ESDL_TYPES_H
#define ESDL_TYPES_H

typedef unsigned char       boolean;
typedef signed char         sint8;          /*        -128 .. +127            */
typedef unsigned char       uint8;          /*           0 .. 255             */
typedef signed short        sint16;         /*      -32768 .. +32767          */
typedef unsigned short      uint16;         /*           0 .. 65535           */
typedef signed long         sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long       uint32;         /*           0 .. 4294967295      */
typedef float               float32;
typedef double              float64;

#ifndef false
    #define false 0u
#endif
#ifndef true
    #define true  1u
#endif

#ifndef FALSE
    #define FALSE 0u
#endif
#ifndef TRUE
    #define TRUE  1u
#endif

#endif /* ESDL_TYPES_H */
