/**
 * Copyright ETAS GmbH, Stuttgart, Germany. All rights reserved.
 *
 * Defines C type limits using ANSI-C limit names.
 */
#ifndef ESDL_LIMITS_H
#define ESDL_LIMITS_H

/* Limits of exact-width integer types */

#ifndef SINT8_MAX
#define SINT8_MAX (127)
#endif
#ifndef SINT8_MIN
#define SINT8_MIN (-SINT8_MAX -1)
#endif

#ifndef UINT8_MIN
#define UINT8_MIN (0u)
#endif
#ifndef UINT8_MAX
#define UINT8_MAX (255u)
#endif

#ifndef SINT16_MAX
#define SINT16_MAX (32767)
#endif
#ifndef SINT16_MIN
#define SINT16_MIN (-SINT16_MAX-1)
#endif

#ifndef UINT16_MIN
#define UINT16_MIN (0u)
#endif
#ifndef UINT16_MAX
#define UINT16_MAX (65535u)
#endif

#ifndef SINT32_MAX
#define SINT32_MAX (2147483647)
#endif
#ifndef SINT32_MIN
#define SINT32_MIN (-SINT32_MAX-1)
#endif

#ifndef UINT32_MIN
#define UINT32_MIN (0u)
#endif
#ifndef UINT32_MAX
#define UINT32_MAX (4294967295u)
#endif

/* Limits for quantized data */

#ifndef _ASD_MAXFLOAT
#define _ASD_MAXFLOAT   1.0e50
#endif
#ifndef _ASD_MINFLOAT
#define _ASD_MINFLOAT   -1.0e50
#endif

#endif /* ESDL_LIMITS_H */
