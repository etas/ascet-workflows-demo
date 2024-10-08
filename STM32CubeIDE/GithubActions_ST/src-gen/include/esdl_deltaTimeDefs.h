/******************************************************************************
 * DISCLAIMER
 * This code has been generated by ASCET-DEVELOPER Community Edition.
 * It shall be used only in projects for non commercial use.
 * See license terms and conditions under https://www.etas.com/en/products/download_center.php.
 ******************************************************************************/

/********************************************************************************
 * DO NOT EDIT!
 * AUTOMATICALLY GENERATED
 * DESCRIPTION:
 *   Definitions for delta time calculation
 ********************************************************************************/

#ifndef ESDL_DELTATIMEDEFS_H
#define ESDL_DELTATIMEDEFS_H

#include "esdl_types.h"

/**
 * This global variable contains the scaled (according to the used representation formula)
 * deltaT value (the time between to consecutive activations) of the currently running task.
 * The generated code for the ASCET model uses this variable directly to access that value.
 **/
#define ASCET_DELTA_T_SCALED_TYPE float
extern ASCET_DELTA_T_SCALED_TYPE ASD_DT_SCALED;

/**
 * Macro definition to set the global ASD_DT_SCALED variable. The provided rawDt argument is
 * expected to be an expression representing the deltaT in seconds. If identity formula is
 * used (default for float32/64 representations), the unit of that calculated value is stored
 * in seconds too.
 **/
#define ASCET_SET_MODEL_DT(rawDt) ASD_DT_SCALED = (rawDt)

/**
 * Macro definition to get the global ASD_DT_SCALED variable. The defined formula is reversely
 * applied to the stored value returning the time difference in seconds.
 **/
#define ASCET_GET_MODEL_DT() (ASD_DT_SCALED)

#endif /* ESDL_DELTATIMEDEFS_H */
