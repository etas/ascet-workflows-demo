/******************************************************************************
 * DISCLAIMER
 * This code has been generated by ASCET-DEVELOPER Community Edition.
 * It shall be used only in projects for non commercial use.
 * See license terms and conditions under https://www.etas.com/en/products/download_center.php.
 ******************************************************************************/

/******************************************************************************
 * DO NOT EDIT!
 * AUTOMATICALLY GENERATED BY:..ASCET-DEVELOPER Community Edition 7.9.0 Hotfix 1
 * CODE GENERATOR:..............6.4.7
 * COMPONENT:...................SystemLib.CounterTimer.StopWatch
 * REPRESENTATION:..............Automatic
 * DESCRIPTION:
 *    StopWatch increments the time counter by one dT.
 ******************************************************************************/
#ifndef _ASD_SYSTEMLIB_COUNTERTIMER_STOPWATCH_AUTOMATIC_H_
#define _ASD_SYSTEMLIB_COUNTERTIMER_STOPWATCH_AUTOMATIC_H_


/*-----------------------------------------------------------------------------
 *    Include files
 *----------------------------------------------------------------------------*/

#include "esdl.h"
#if (!defined(ESDL_HEADER_VERSION) || (ESDL_HEADER_VERSION < 7))
# error NOT COMPLIANT (< compliance level 7) VERSION OF esdl.h FOUND; To fix that, delete the old headers (esdl_<...>.h) in include folder and restart build again to get the new version of those files.
#endif
#include "chartab.h"


/* SERAP structure for SystemLib_CounterTimer_StopWatch_Automatic intentionally not created */
/* reason: no local parameters                                                */




/******************************************************************************
 * BEGIN: DEFINITION OF MEMORY CLASS STRUCTURE FOR CLASS 'SystemLib_CounterTimer_StopWatch_Automatic'
 * ----------------------------------------------------------------------------
 * memory class:.................................'RAM'
 * ---------------------------------------------------------------------------*/
struct SystemLib_CounterTimer_StopWatch_Automatic_RAM_SUBSTRUCT {
   float32 timeCounter;
};
/* ----------------------------------------------------------------------------
 * END: DEFINITION OF MEMORY CLASS STRUCTURE FOR CLASS 'SystemLib_CounterTimer_StopWatch_Automatic'
 ******************************************************************************/


/******************************************************************************
 * BEGIN: DEFINITION OF MAIN STRUCTURE FOR CLASS 'SystemLib_CounterTimer_StopWatch_Automatic'
 * ----------------------------------------------------------------------------
 * memory class:.................................'ROM'
 * ---------------------------------------------------------------------------*/
struct SystemLib_CounterTimer_StopWatch_Automatic {
   struct SystemLib_CounterTimer_StopWatch_Automatic_RAM_SUBSTRUCT * SystemLib_CounterTimer_StopWatch_Automatic_RAM;
};
/* ----------------------------------------------------------------------------
 * END: DEFINITION OF MAIN STRUCTURE FOR CLASS 'SystemLib_CounterTimer_StopWatch_Automatic'
 ******************************************************************************/

/* Following DEFINE signalizes the completion of definition                   */
/* of data structs for component: .SystemLib_CounterTimer_StopWatch_Automatic */
#define _SystemLib_CounterTimer_StopWatch_Automatic_TYPE_DEF_




/******************************************************************************
 * BEGIN: declaration of global C functions defined by class SystemLib_CounterTimer_StopWatch_Automatic
 ******************************************************************************/
extern void SystemLib_CounterTimer_StopWatch_Automatic_compute ( const struct SystemLib_CounterTimer_StopWatch_Automatic * self);
extern void SystemLib_CounterTimer_StopWatch_Automatic_reset ( const struct SystemLib_CounterTimer_StopWatch_Automatic * self);
extern float32 SystemLib_CounterTimer_StopWatch_Automatic_value ( const struct SystemLib_CounterTimer_StopWatch_Automatic * self);


/* BEGIN: extern declarations for SERAP */
/* END: extern declarations for SERAP */



#endif /* _ASD_SYSTEMLIB_COUNTERTIMER_STOPWATCH_AUTOMATIC_H_ */
