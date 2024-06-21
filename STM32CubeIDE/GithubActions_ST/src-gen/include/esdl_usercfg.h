/**
 *  The content of this header can be customized.
 *  Any definitions in this file will be visible to all generated source files.
 *  This file will not be overridden by the ASCET code generator.
 */
#ifndef ESDL_USERCFG_H
#define ESDL_USERCFG_H

#define PTR_model_GameController_Automatic PTR_MODEL_GAMECONTROLLER_AUTOMATIC
#define PTR_model_LedController_stm32f334r8 PTR_MODEL_LEDCONTROLLER_STM32F334R8
#define PTR_model_ServoController_Automatic PTR_MODEL_SERVOCONTROLLER_AUTOMATIC
#define PTR_model_MainClass_stm32f334r8 PTR_MODEL_MAINCLASS_STM32F334R8

#define DisableAllInterrupts()
#define EnableAllInterrupts()

#include "xcp_mem.h"

#ifdef _ASD_SERAP_DEF
#define USE_PARAM_GLOBAL(TYPE, VARIABLE) (TYPE *)(*(unsigned int *)((unsigned int)&VARIABLE) + XcpMem_GetActiveEcuPageOffset())
#endif

#endif /* ESDL_USERCFG_H */
