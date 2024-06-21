/**
*
* \file
*
* \brief Public definitions and declarations
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_pub.h 22409 2011-04-22 10:40:28Z olcritch $
*
******************************************************************************/

#ifndef _XCP_PUB_H
#define _XCP_PUB_H

#include "xcp_common.h"
#include "xcp_auto_confdefs.h"

/*
 * Define pre-processor symbols
 */

/* Return values for Xcp_Event() */
#define XCPEVENT_DAQSTIM_NOT_EXECUTED   0x00
#define XCPEVENT_DAQ_OVERLOAD           0x01
#define XCPEVENT_DTO_OVERFILL           0x02
#define XCPEVENT_MISSING_DTO            0x04
#define XCPEVENT_DAQSTIM_EXECUTED       0x08

/*
 * Define function-like macros
 */

#ifndef Xcp_DoStimForEvent
#ifdef XCP_ENABLE_STIM
    #define Xcp_DoStimForEvent( /* uint */ eventId ) ( Xcp_Event( eventId, 1 ) )
#else
    #define Xcp_DoStimForEvent( /* uint */ eventId ) /* Do nothing */
#endif
#endif

#ifndef Xcp_DoDaqForEvent
    #define Xcp_DoDaqForEvent( /* uint */ eventId ) ( Xcp_Event( eventId, 0 ) )
#endif

/*
 * Declare public functions
 */

#if defined __cplusplus || defined _cplusplus
extern "C" {
#endif

void XCP_FN_TYPE Xcp_Initialize   ( void );
void XCP_FN_TYPE Xcp_CmdProcessor ( void );
uint XCP_FN_TYPE Xcp_Event        ( uint eventId, uint isStim );

#if defined __cplusplus || defined _cplusplus
}
#endif

/* The static event API macros are generated in xcp_auto_conf.h */

#endif /* _XCP_PUB_H */
