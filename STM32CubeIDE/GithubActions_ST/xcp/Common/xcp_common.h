/**
*
* \file
*
* \brief Definitions and declarations common to the XCP slave driver and all transport layers.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_common.h 15953 2009-07-06 09:34:00Z olcritch $
*
******************************************************************************/

#ifndef _XCP_COMMON_H
#define _XCP_COMMON_H

#include "xcp_auto_confdefs.h"

#if defined( XCP_ENV_ASCET )

/* We are using ASCET so we can get uint, uint8, uint16, uint32, sint, sint8, sint16 and sint32 from the following header which is
 * distributed with ASCET. */
#include "os_inface.h"

#elif defined( XCP_ENV_RTAOS ) || defined ( XCP_ENV_RTAOSEK5 )

/* We are in an Autosar build environment so we can get uint8, uit16, uint32, sint8, sint16 and sint32 from Platform_types.h which
 * is available in an Autosar build environment. */

#include "Platform_types.h"

/* The following types are not defined in Platform_types.h so we must define them here. */
typedef unsigned int uint;
typedef int          sint;

#else /* !XCP_ENV_ASCET && !XCP_ENV_RTAOS && !XCP_ENV_RTAOSEK5 */

/* We are using neither ASCET nor an Autosar build environment, so uint8, uint16, uint32, sint8, sint16 and sint32 will be provided in
 * xcp_target.h. */

typedef unsigned int uint;
typedef int          sint;

#endif

/* Include common target-specific definitions and declarations. */
#include "xcp_target.h"

#endif /* _XCP_COMMON_H */
