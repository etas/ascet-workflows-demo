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
 * COMPONENT:...................hardware.HandDistanceSensor
 * REPRESENTATION:..............Automatic
 * DESCRIPTION:
 *    
 ******************************************************************************/


/*-----------------------------------------------------------------------------
 *    Defines
 *----------------------------------------------------------------------------*/

#define __ASD_REQUIRES_OS_INFACE

/*-----------------------------------------------------------------------------
 *    Include files
 *----------------------------------------------------------------------------*/

#include "hardware_HandDistanceSensor_Automatic.h"
#include "model_Signals_stm32f334r8.h"


/******************************************************************************
 * BEGIN: DEFINITION OF SUBSTRUCT VARIABLE 'hardware_HandDistanceSensor_CAL_MEM'
 * ----------------------------------------------------------------------------
 * memory class:.................................'CAL_MEM'
 * model name:...................................'hardware_HandDistanceSensor'
 * data set:.....................................'HARDWARE_HANDDISTANCESENSOR_AUTOMATIC_esdl_Data_Default'
 * ---------------------------------------------------------------------------*/
__attribute__((section(".ascet_calibration_rom")))
const volatile struct hardware_HandDistanceSensor_Automatic_CAL_MEM_SUBSTRUCT hardware_HandDistanceSensor_CAL_MEM = {
   /* struct element:'hardware_HandDistanceSensor_CAL_MEM.adcMax' (modeled as:'adcMax.hardware_HandDistanceSensor') */
   2000.0F,
   /* struct element:'hardware_HandDistanceSensor_CAL_MEM.adcMin' (modeled as:'adcMin.hardware_HandDistanceSensor') */
   800.0F
};
/* ----------------------------------------------------------------------------
 * END: DEFINITION OF SUBSTRUCT VARIABLE 'hardware_HandDistanceSensor_CAL_MEM'
 ******************************************************************************/

/******************************************************************************
 * DEFINITION OF COMPONENT VARIABLE OMITTED
 * ----------------------------------------------------------------------------
 * memory class:.................................'ROM'
 * model name:...................................'hardware_HandDistanceSensor'
 * reason:.......................................no local elements
 * ---------------------------------------------------------------------------*/







/******************************************************************************
 * BEGIN: SERAP (definition of data structures)
 * ---------------------------------------------------------------------------*/
/* Reference table structure of component 'hardware_HandDistanceSensor_Automatic' */
const volatile struct PTR_hardware_HandDistanceSensor_Automatic _SERAP_REF_hardware_HandDistanceSensor = {
   /* pointer to parameter 'hardware_HandDistanceSensor_CAL_MEM.adcMax' (modeled as:'adcMax.hardware_HandDistanceSensor') */
   &(hardware_HandDistanceSensor_CAL_MEM.adcMax),
   /* pointer to parameter 'hardware_HandDistanceSensor_CAL_MEM.adcMin' (modeled as:'adcMin.hardware_HandDistanceSensor') */
   &(hardware_HandDistanceSensor_CAL_MEM.adcMin)
};

/* Working table structure of component 'hardware_HandDistanceSensor_Automatic' */
const volatile struct PTR_hardware_HandDistanceSensor_Automatic _SERAP_WORK_hardware_HandDistanceSensor = {
   /* pointer to parameter 'hardware_HandDistanceSensor_CAL_MEM.adcMax' (modeled as:'adcMax.hardware_HandDistanceSensor') */
   &(hardware_HandDistanceSensor_CAL_MEM.adcMax),
   /* pointer to parameter 'hardware_HandDistanceSensor_CAL_MEM.adcMin' (modeled as:'adcMin.hardware_HandDistanceSensor') */
   &(hardware_HandDistanceSensor_CAL_MEM.adcMin)
};
/* ----------------------------------------------------------------------------
 * END: SERAP (definition of data structures)
 ******************************************************************************/


#define adcMax_VAL ((*(USE_PARAM_GLOBAL(float32, _SERAP_REF_hardware_HandDistanceSensor.adcMax))))
#define adcMin_VAL ((*(USE_PARAM_GLOBAL(float32, _SERAP_REF_hardware_HandDistanceSensor.adcMin))))


/******************************************************************************
 * BEGIN: FUNCTIONS OF COMPONENT
 ******************************************************************************/


/******************************************************************************
 * BEGIN: DEFINITION OF PROCESS 'hardware_HandDistanceSensor_Automatic_read'
 * ----------------------------------------------------------------------------
 * model name:...................................'read'
 * memory class:.................................'CODE'
 * ---------------------------------------------------------------------------*/
/* messages used by this process */
#define model_Signals_adcHandPosition__hardware_HandDistanceSensor_Automatic_read (model_Signals_adcHandPosition)
#define model_Signals_handPosition__hardware_HandDistanceSensor_Automatic_read (model_Signals_handPosition)


void hardware_HandDistanceSensor_Automatic_read (void)
{
   /* temp. variables */
   float32 _t1real32;

   _t1real32
      = hardware_MappingUtil_Automatic_map(model_Signals_adcHandPosition__hardware_HandDistanceSensor_Automatic_read, adcMin_VAL, adcMax_VAL, 0.0F, 1.0F);
   model_Signals_handPosition__hardware_HandDistanceSensor_Automatic_read
      = ((_t1real32 >= 0.0F) ? (((_t1real32 <= 1.0F) ? _t1real32 : 1.0F)) : 0.0F);
}
/* ----------------------------------------------------------------------------
 * END: DEFINITION OF PROCESS 'hardware_HandDistanceSensor_Automatic_read'
 ******************************************************************************/



/* ****************************************************************************
 * END: FUNCTIONS OF COMPONENT
 ******************************************************************************/


