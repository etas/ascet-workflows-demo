#ifndef ESDL_LINEAR_INTERPOLATION_H
#define ESDL_LINEAR_INTERPOLATION_H
/**
 * Copyright ETAS GmbH, Stuttgart, Germany. All rights reserved.
 *
 * Function signatures for linear interpolation services, provided here as an example.
 *
 * WARNING!
 * The interpolation routines are provided for example only.
 * It is not permitted to use them in production code or within
 * ECUs running in any vehicles.
 * THE ETAS GROUP OF COMPANIES AND THEIR REPRESENTATIVES, AGENTS
 * AND AFFILIATED COMPANIES SHALL NOT BE LIABLE FOR ANY DAMAGE OR
 * INJURY CAUSED BY USE OF THIS ROUTINES.
 */
#include "esdl_types.h"

#ifndef ESDL_PLATFORM_INTERNAL_BUILD
#error THESE INTERPOLATION ROUTINES ARE FOR EXAMPLE ONLY! DO NOT USE THIS HEADER FILE IN PRODUCTION CODE! DO NOT USE THIS CODE IN ECUS RUNNING IN ANY VEHICLE!
#endif

/**
 * def ESDL_LINEAR_PTR_TYPE *
 *
 * Define how to represent a pointer to the axis/values.
 * In most cases this is simply a normal C pointer '*'
 * If the compiler uses special intrinsics to mark pointers and "near"
 * or "far" then these intrinsics can be used here.
 * For example, 16-bit devices with banked memory/extended memory might
 * required a qualifier like '* __far' or 'near *'.
 * Read your compiler documentation for additional guidance.
 **/

#define ESDL_LINEAR_PTR_TYPE *

/**
 * def ESDL_LINEAR_INTPOL_THRESHOLD_COUNT 64
 *
 *  Define the threshold number of axis point for deciding whether to use a
 *  linear or a binary search algorithm when searching axis distributions.
 *  If the number of axis points is less than this value a linear search is
 *  used. If the number of axis points is greater than or equal to this value
 *   a binary search.
 **/

#define ESDL_LINEAR_INTPOL_THRESHOLD_COUNT 64

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Axis (distribution) search functions for each type combination
 **/
void ESDL_Linear_Search_u8(const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, uint8 x, const volatile uint8 ESDL_LINEAR_PTR_TYPE ESDL_LINEAR_PTR_TYPE pSearchIndex);
void ESDL_Linear_Search_s8(const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, sint8 x, const volatile sint8 ESDL_LINEAR_PTR_TYPE ESDL_LINEAR_PTR_TYPE pSearchIndex);
void ESDL_Linear_Search_u16(const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, uint16 x, const volatile uint16 ESDL_LINEAR_PTR_TYPE ESDL_LINEAR_PTR_TYPE pSearchIndex);
void ESDL_Linear_Search_s16(const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, sint16 x, const volatile sint16 ESDL_LINEAR_PTR_TYPE ESDL_LINEAR_PTR_TYPE pSearchIndex);
void ESDL_Linear_Search_u32(const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, uint32 x, const volatile uint32 ESDL_LINEAR_PTR_TYPE ESDL_LINEAR_PTR_TYPE pSearchIndex);
void ESDL_Linear_Search_s32(const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, sint32 x, const volatile sint32 ESDL_LINEAR_PTR_TYPE ESDL_LINEAR_PTR_TYPE pSearchIndex);
void ESDL_Linear_Search_r32(const volatile float32 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, float32 x, const volatile float32 ESDL_LINEAR_PTR_TYPE ESDL_LINEAR_PTR_TYPE pSearchIndex);
void ESDL_Linear_Search_r64(const volatile float64 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, float64 x, const volatile float64 ESDL_LINEAR_PTR_TYPE ESDL_LINEAR_PTR_TYPE pSearchIndex);


void ESDL_Linear_Distr_Search_u8(const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, uint8 x, uint8 ESDL_LINEAR_PTR_TYPE searchIndex, uint8 ESDL_LINEAR_PTR_TYPE offset, uint8 ESDL_LINEAR_PTR_TYPE distance);
void ESDL_Linear_Distr_Search_s8(const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, sint8 x, uint8 ESDL_LINEAR_PTR_TYPE searchIndex, uint8 ESDL_LINEAR_PTR_TYPE offset, uint8 ESDL_LINEAR_PTR_TYPE distance);
void ESDL_Linear_Distr_Search_u16(const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, uint16 x, uint16 ESDL_LINEAR_PTR_TYPE searchIndex, uint16 ESDL_LINEAR_PTR_TYPE offset, uint16 ESDL_LINEAR_PTR_TYPE distance);
void ESDL_Linear_Distr_Search_s16(const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, sint16 x, uint16 ESDL_LINEAR_PTR_TYPE searchIndex, uint16 ESDL_LINEAR_PTR_TYPE offset, uint16 ESDL_LINEAR_PTR_TYPE distance);
void ESDL_Linear_Distr_Search_u32(const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, uint32 x, uint16 ESDL_LINEAR_PTR_TYPE searchIndex, uint32 ESDL_LINEAR_PTR_TYPE offset, uint32 ESDL_LINEAR_PTR_TYPE distance);
void ESDL_Linear_Distr_Search_s32(const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, sint32 x, uint16 ESDL_LINEAR_PTR_TYPE searchIndex, uint32 ESDL_LINEAR_PTR_TYPE offset, uint32 ESDL_LINEAR_PTR_TYPE distance);
void ESDL_Linear_Distr_Search_r32(const volatile float32 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, float32 x, uint16 ESDL_LINEAR_PTR_TYPE searchIndex, float32 ESDL_LINEAR_PTR_TYPE offset, float32 ESDL_LINEAR_PTR_TYPE distance);
void ESDL_Linear_Distr_Search_r64(const volatile float64 ESDL_LINEAR_PTR_TYPE xDist, uint16 xVecLen, float64 x, uint16 ESDL_LINEAR_PTR_TYPE searchIndex, float64 ESDL_LINEAR_PTR_TYPE offset, float64 ESDL_LINEAR_PTR_TYPE distance);

/* Map default axis search call backs used when no map/curve uses the axis to the axis search functions */
#define Distribution_search_u8(xDist,xVecLen,x,searchIndex,offset,distance) ESDL_Linear_Distr_Search_u8(xDist,xVecLen,x,searchIndex,offset,distance)
#define Distribution_search_s8(xDist,xVecLen,x,searchIndex,offset,distance) ESDL_Linear_Distr_Search_s8(xDist,xVecLen,x,searchIndex,offset,distance)
#define Distribution_search_u16(xDist,xVecLen,x,searchIndex,offset,distance) ESDL_Linear_Distr_Search_u16(xDist,xVecLen,x,searchIndex,offset,distance)
#define Distribution_search_s16(xDist,xVecLen,x,searchIndex,offset,distance) ESDL_Linear_Distr_Search_s16(xDist,xVecLen,x,searchIndex,offset,distance)
#define Distribution_search_u32(xDist,xVecLen,x,searchIndex,offset,distance) ESDL_Linear_Distr_Search_u32(xDist,xVecLen,x,searchIndex,offset,distance)
#define Distribution_search_s32(xDist,xVecLen,x,searchIndex,offset,distance) ESDL_Linear_Distr_Search_s32(xDist,xVecLen,x,searchIndex,offset,distance)
#define Distribution_search_r32(xDist,xVecLen,x,searchIndex,offset,distance) ESDL_Linear_Distr_Search_r32(xDist,xVecLen,x,searchIndex,offset,distance)
#define Distribution_search_r64(xDist,xVecLen,x,searchIndex,offset,distance) ESDL_Linear_Distr_Search_r64(xDist,xVecLen,x,searchIndex,offset,distance)

/**
 * @brief   Curve (1-Dimensional) Interpolation: CharTable1 / GroupTable1 / CharTableFixed1
 **/


/* Signature combination: u8u8 */

uint8 ESDL_Linear_CharTable1_getAt_u8u8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
uint8 ESDL_Linear_CharTableFixed1_getAt_u8u8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
uint8 ESDL_Linear_GroupTable1_getAt_u8u8(const volatile uint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

uint8 ESDL_Linear_Interpolate_u8u8(uint8 Z0, uint8 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: u8s8 */

sint8 ESDL_Linear_CharTable1_getAt_u8s8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
sint8 ESDL_Linear_CharTableFixed1_getAt_u8s8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
sint8 ESDL_Linear_GroupTable1_getAt_u8s8(const volatile sint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

sint8 ESDL_Linear_Interpolate_u8s8(sint8 Z0, sint8 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: u8u16 */

uint16 ESDL_Linear_CharTable1_getAt_u8u16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
uint16 ESDL_Linear_CharTableFixed1_getAt_u8u16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
uint16 ESDL_Linear_GroupTable1_getAt_u8u16(const volatile uint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

uint16 ESDL_Linear_Interpolate_u8u16(uint16 Z0, uint16 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: u8s16 */

sint16 ESDL_Linear_CharTable1_getAt_u8s16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
sint16 ESDL_Linear_CharTableFixed1_getAt_u8s16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
sint16 ESDL_Linear_GroupTable1_getAt_u8s16(const volatile sint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

sint16 ESDL_Linear_Interpolate_u8s16(sint16 Z0, sint16 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: u8u32 */

uint32 ESDL_Linear_CharTable1_getAt_u8u32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
uint32 ESDL_Linear_CharTableFixed1_getAt_u8u32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
uint32 ESDL_Linear_GroupTable1_getAt_u8u32(const volatile uint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

uint32 ESDL_Linear_Interpolate_u8u32(uint32 Z0, uint32 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: u8s32 */

sint32 ESDL_Linear_CharTable1_getAt_u8s32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
sint32 ESDL_Linear_CharTableFixed1_getAt_u8s32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x);
sint32 ESDL_Linear_GroupTable1_getAt_u8s32(const volatile sint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

sint32 ESDL_Linear_Interpolate_u8s32(sint32 Z0, sint32 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: s8u8 */

uint8 ESDL_Linear_CharTable1_getAt_s8u8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
uint8 ESDL_Linear_CharTableFixed1_getAt_s8u8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
uint8 ESDL_Linear_GroupTable1_getAt_s8u8(const volatile uint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

uint8 ESDL_Linear_Interpolate_s8u8(uint8 Z0, uint8 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: s8s8 */

sint8 ESDL_Linear_CharTable1_getAt_s8s8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
sint8 ESDL_Linear_CharTableFixed1_getAt_s8s8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
sint8 ESDL_Linear_GroupTable1_getAt_s8s8(const volatile sint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

sint8 ESDL_Linear_Interpolate_s8s8(sint8 Z0, sint8 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: s8u16 */

uint16 ESDL_Linear_CharTable1_getAt_s8u16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
uint16 ESDL_Linear_CharTableFixed1_getAt_s8u16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
uint16 ESDL_Linear_GroupTable1_getAt_s8u16(const volatile uint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

uint16 ESDL_Linear_Interpolate_s8u16(uint16 Z0, uint16 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: s8s16 */

sint16 ESDL_Linear_CharTable1_getAt_s8s16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
sint16 ESDL_Linear_CharTableFixed1_getAt_s8s16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
sint16 ESDL_Linear_GroupTable1_getAt_s8s16(const volatile sint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

sint16 ESDL_Linear_Interpolate_s8s16(sint16 Z0, sint16 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: s8u32 */

uint32 ESDL_Linear_CharTable1_getAt_s8u32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
uint32 ESDL_Linear_CharTableFixed1_getAt_s8u32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
uint32 ESDL_Linear_GroupTable1_getAt_s8u32(const volatile uint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

uint32 ESDL_Linear_Interpolate_s8u32(uint32 Z0, uint32 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: s8s32 */

sint32 ESDL_Linear_CharTable1_getAt_s8s32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
sint32 ESDL_Linear_CharTableFixed1_getAt_s8s32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x);
sint32 ESDL_Linear_GroupTable1_getAt_s8s32(const volatile sint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint8 deltaX, uint8 distX);

/* Forward declaration of internal function */

sint32 ESDL_Linear_Interpolate_s8s32(sint32 Z0, sint32 Z1, uint8 deltaX, uint8 dX);


/* Signature combination: u16u8 */

uint8 ESDL_Linear_CharTable1_getAt_u16u8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
uint8 ESDL_Linear_CharTableFixed1_getAt_u16u8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
uint8 ESDL_Linear_GroupTable1_getAt_u16u8(const volatile uint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

uint8 ESDL_Linear_Interpolate_u16u8(uint8 Z0, uint8 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: u16s8 */

sint8 ESDL_Linear_CharTable1_getAt_u16s8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
sint8 ESDL_Linear_CharTableFixed1_getAt_u16s8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
sint8 ESDL_Linear_GroupTable1_getAt_u16s8(const volatile sint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

sint8 ESDL_Linear_Interpolate_u16s8(sint8 Z0, sint8 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: u16u16 */

uint16 ESDL_Linear_CharTable1_getAt_u16u16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
uint16 ESDL_Linear_CharTableFixed1_getAt_u16u16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
uint16 ESDL_Linear_GroupTable1_getAt_u16u16(const volatile uint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

uint16 ESDL_Linear_Interpolate_u16u16(uint16 Z0, uint16 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: u16s16 */

sint16 ESDL_Linear_CharTable1_getAt_u16s16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
sint16 ESDL_Linear_CharTableFixed1_getAt_u16s16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
sint16 ESDL_Linear_GroupTable1_getAt_u16s16(const volatile sint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

sint16 ESDL_Linear_Interpolate_u16s16(sint16 Z0, sint16 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: u16u32 */

uint32 ESDL_Linear_CharTable1_getAt_u16u32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
uint32 ESDL_Linear_CharTableFixed1_getAt_u16u32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
uint32 ESDL_Linear_GroupTable1_getAt_u16u32(const volatile uint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

uint32 ESDL_Linear_Interpolate_u16u32(uint32 Z0, uint32 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: u16s32 */

sint32 ESDL_Linear_CharTable1_getAt_u16s32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
sint32 ESDL_Linear_CharTableFixed1_getAt_u16s32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x);
sint32 ESDL_Linear_GroupTable1_getAt_u16s32(const volatile sint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

sint32 ESDL_Linear_Interpolate_u16s32(sint32 Z0, sint32 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: s16u8 */

uint8 ESDL_Linear_CharTable1_getAt_s16u8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
uint8 ESDL_Linear_CharTableFixed1_getAt_s16u8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
uint8 ESDL_Linear_GroupTable1_getAt_s16u8(const volatile uint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

uint8 ESDL_Linear_Interpolate_s16u8(uint8 Z0, uint8 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: s16s8 */

sint8 ESDL_Linear_CharTable1_getAt_s16s8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
sint8 ESDL_Linear_CharTableFixed1_getAt_s16s8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
sint8 ESDL_Linear_GroupTable1_getAt_s16s8(const volatile sint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

sint8 ESDL_Linear_Interpolate_s16s8(sint8 Z0, sint8 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: s16u16 */

uint16 ESDL_Linear_CharTable1_getAt_s16u16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
uint16 ESDL_Linear_CharTableFixed1_getAt_s16u16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
uint16 ESDL_Linear_GroupTable1_getAt_s16u16(const volatile uint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

uint16 ESDL_Linear_Interpolate_s16u16(uint16 Z0, uint16 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: s16s16 */

sint16 ESDL_Linear_CharTable1_getAt_s16s16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
sint16 ESDL_Linear_CharTableFixed1_getAt_s16s16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
sint16 ESDL_Linear_GroupTable1_getAt_s16s16(const volatile sint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

sint16 ESDL_Linear_Interpolate_s16s16(sint16 Z0, sint16 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: s16u32 */

uint32 ESDL_Linear_CharTable1_getAt_s16u32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
uint32 ESDL_Linear_CharTableFixed1_getAt_s16u32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
uint32 ESDL_Linear_GroupTable1_getAt_s16u32(const volatile uint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

uint32 ESDL_Linear_Interpolate_s16u32(uint32 Z0, uint32 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: s16s32 */

sint32 ESDL_Linear_CharTable1_getAt_s16s32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
sint32 ESDL_Linear_CharTableFixed1_getAt_s16s32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x);
sint32 ESDL_Linear_GroupTable1_getAt_s16s32(const volatile sint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint16 deltaX, uint16 distX);

/* Forward declaration of internal function */

sint32 ESDL_Linear_Interpolate_s16s32(sint32 Z0, sint32 Z1, uint16 deltaX, uint16 dX);


/* Signature combination: u32u8 */

uint8 ESDL_Linear_CharTable1_getAt_u32u8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
uint8 ESDL_Linear_CharTableFixed1_getAt_u32u8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
uint8 ESDL_Linear_GroupTable1_getAt_u32u8(const volatile uint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

uint8 ESDL_Linear_Interpolate_u32u8(uint8 Z0, uint8 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: u32s8 */

sint8 ESDL_Linear_CharTable1_getAt_u32s8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
sint8 ESDL_Linear_CharTableFixed1_getAt_u32s8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
sint8 ESDL_Linear_GroupTable1_getAt_u32s8(const volatile sint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

sint8 ESDL_Linear_Interpolate_u32s8(sint8 Z0, sint8 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: u32u16 */

uint16 ESDL_Linear_CharTable1_getAt_u32u16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
uint16 ESDL_Linear_CharTableFixed1_getAt_u32u16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
uint16 ESDL_Linear_GroupTable1_getAt_u32u16(const volatile uint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

uint16 ESDL_Linear_Interpolate_u32u16(uint16 Z0, uint16 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: u32s16 */

sint16 ESDL_Linear_CharTable1_getAt_u32s16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
sint16 ESDL_Linear_CharTableFixed1_getAt_u32s16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
sint16 ESDL_Linear_GroupTable1_getAt_u32s16(const volatile sint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

sint16 ESDL_Linear_Interpolate_u32s16(sint16 Z0, sint16 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: u32u32 */

uint32 ESDL_Linear_CharTable1_getAt_u32u32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
uint32 ESDL_Linear_CharTableFixed1_getAt_u32u32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
uint32 ESDL_Linear_GroupTable1_getAt_u32u32(const volatile uint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

uint32 ESDL_Linear_Interpolate_u32u32(uint32 Z0, uint32 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: u32s32 */

sint32 ESDL_Linear_CharTable1_getAt_u32s32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
sint32 ESDL_Linear_CharTableFixed1_getAt_u32s32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x);
sint32 ESDL_Linear_GroupTable1_getAt_u32s32(const volatile sint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

sint32 ESDL_Linear_Interpolate_u32s32(sint32 Z0, sint32 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: s32u8 */

uint8 ESDL_Linear_CharTable1_getAt_s32u8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
uint8 ESDL_Linear_CharTableFixed1_getAt_s32u8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
uint8 ESDL_Linear_GroupTable1_getAt_s32u8(const volatile uint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

uint8 ESDL_Linear_Interpolate_s32u8(uint8 Z0, uint8 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: s32s8 */

sint8 ESDL_Linear_CharTable1_getAt_s32s8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
sint8 ESDL_Linear_CharTableFixed1_getAt_s32s8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
sint8 ESDL_Linear_GroupTable1_getAt_s32s8(const volatile sint8 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

sint8 ESDL_Linear_Interpolate_s32s8(sint8 Z0, sint8 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: s32u16 */

uint16 ESDL_Linear_CharTable1_getAt_s32u16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
uint16 ESDL_Linear_CharTableFixed1_getAt_s32u16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
uint16 ESDL_Linear_GroupTable1_getAt_s32u16(const volatile uint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

uint16 ESDL_Linear_Interpolate_s32u16(uint16 Z0, uint16 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: s32s16 */

sint16 ESDL_Linear_CharTable1_getAt_s32s16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
sint16 ESDL_Linear_CharTableFixed1_getAt_s32s16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
sint16 ESDL_Linear_GroupTable1_getAt_s32s16(const volatile sint16 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

sint16 ESDL_Linear_Interpolate_s32s16(sint16 Z0, sint16 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: s32u32 */

uint32 ESDL_Linear_CharTable1_getAt_s32u32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
uint32 ESDL_Linear_CharTableFixed1_getAt_s32u32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
uint32 ESDL_Linear_GroupTable1_getAt_s32u32(const volatile uint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

uint32 ESDL_Linear_Interpolate_s32u32(uint32 Z0, uint32 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: s32s32 */

sint32 ESDL_Linear_CharTable1_getAt_s32s32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
sint32 ESDL_Linear_CharTableFixed1_getAt_s32s32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x);
sint32 ESDL_Linear_GroupTable1_getAt_s32s32(const volatile sint32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, uint32 deltaX, uint32 distX);

/* Forward declaration of internal function */

sint32 ESDL_Linear_Interpolate_s32s32(sint32 Z0, sint32 Z1, uint32 deltaX, uint32 dX);


/* Signature combination: r32r32 */

float32 ESDL_Linear_CharTable1_getAt_r32r32(uint16 xVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE xDist, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float32 x);
float32 ESDL_Linear_CharTableFixed1_getAt_r32r32(uint16 xVecLen, float32 xOffset, float32 xDistance, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float32 x);
float32 ESDL_Linear_GroupTable1_getAt_r32r32(const volatile float32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, float32 deltaX, float32 distX);

/* Forward declaration of internal function */

float32 ESDL_Linear_Interpolate_r32r32(float32 Z0, float32 Z1, float32 deltaX, float32 dX);


/* Signature combination: r64r64 */

float64 ESDL_Linear_CharTable1_getAt_r64r64(uint16 xVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE xDist, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float64 x);
float64 ESDL_Linear_CharTableFixed1_getAt_r64r64(uint16 xVecLen, float64 xOffset, float64 xDistance, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float64 x);
float64 ESDL_Linear_GroupTable1_getAt_r64r64(const volatile float64 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, float64 deltaX, float64 distX);

/* Forward declaration of internal function */

float64 ESDL_Linear_Interpolate_r64r64(float64 Z0, float64 Z1, float64 deltaX, float64 dX);


/* Signature combination: r32r64 */

float64 ESDL_Linear_CharTable1_getAt_r32r64(uint16 xVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE xDist, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float32 x);
float64 ESDL_Linear_CharTableFixed1_getAt_r32r64(uint16 xVecLen, float32 xOffset, float32 xDistance, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float32 x);
float64 ESDL_Linear_GroupTable1_getAt_r32r64(const volatile float64 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, float32 deltaX, float32 distX);

/* Forward declaration of internal function */

float64 ESDL_Linear_Interpolate_r32r64(float64 Z0, float64 Z1, float32 deltaX, float32 dX);


/* Signature combination: r64r32 */

float32 ESDL_Linear_CharTable1_getAt_r64r32(uint16 xVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE xDist, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float64 x);
float32 ESDL_Linear_CharTableFixed1_getAt_r64r32(uint16 xVecLen, float64 xOffset, float64 xDistance, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float64 x);
float32 ESDL_Linear_GroupTable1_getAt_r64r32(const volatile float32 ESDL_LINEAR_PTR_TYPE val, uint16 searchIndex, float64 deltaX, float64 distX);

/* Forward declaration of internal function */

float32 ESDL_Linear_Interpolate_r64r32(float32 Z0, float32 Z1, float64 deltaX, float64 dX);

/*
 * Definition of macros for not implemented type combinations force compilation abort
 * with a more coherent error message.
 * MISRA rules are not important here as the code should not compile if one of these macros
 * is present.
 */
#define ESDL_Linear_CharTable1_getAt_r32s16(CT,X)                          ESDL_Linear_CharTable1_getAt_r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r32s16(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r32s16(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r32s32(CT,X)                          ESDL_Linear_CharTable1_getAt_r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r32s32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r32s32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r32s8(CT,X)                          ESDL_Linear_CharTable1_getAt_r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r32s8(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r32s8(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r32u16(CT,X)                          ESDL_Linear_CharTable1_getAt_r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r32u16(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r32u16(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r32u32(CT,X)                          ESDL_Linear_CharTable1_getAt_r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r32u32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r32u32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r32u8(CT,X)                          ESDL_Linear_CharTable1_getAt_r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r32u8(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r32u8(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r64s16(CT,X)                          ESDL_Linear_CharTable1_getAt_r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r64s16(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r64s16(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r64s32(CT,X)                          ESDL_Linear_CharTable1_getAt_r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r64s32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r64s32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r64s8(CT,X)                          ESDL_Linear_CharTable1_getAt_r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r64s8(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r64s8(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r64u16(CT,X)                          ESDL_Linear_CharTable1_getAt_r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r64u16(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r64u16(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r64u32(CT,X)                          ESDL_Linear_CharTable1_getAt_r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r64u32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r64u32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_r64u8(CT,X)                          ESDL_Linear_CharTable1_getAt_r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_r64u8(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_r64u8(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_s16r32(CT,X)                          ESDL_Linear_CharTable1_getAt_s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_s16r32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_s16r32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_s16r64(CT,X)                          ESDL_Linear_CharTable1_getAt_s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_s16r64(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_s16r64(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_s32r32(CT,X)                          ESDL_Linear_CharTable1_getAt_s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_s32r32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_s32r32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_s32r64(CT,X)                          ESDL_Linear_CharTable1_getAt_s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_s32r64(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_s32r64(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_s8r32(CT,X)                          ESDL_Linear_CharTable1_getAt_s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_s8r32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_s8r32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_s8r64(CT,X)                          ESDL_Linear_CharTable1_getAt_s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_s8r64(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_s8r64(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_u16r32(CT,X)                          ESDL_Linear_CharTable1_getAt_u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_u16r32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_u16r32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_u16r64(CT,X)                          ESDL_Linear_CharTable1_getAt_u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_u16r64(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_u16r64(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_u32r32(CT,X)                          ESDL_Linear_CharTable1_getAt_u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_u32r32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_u32r32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_u32r64(CT,X)                          ESDL_Linear_CharTable1_getAt_u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_u32r64(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_u32r64(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_u8r32(CT,X)                          ESDL_Linear_CharTable1_getAt_u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_u8r32(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_u8r32(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable1_getAt_u8r64(CT,X)                          ESDL_Linear_CharTable1_getAt_u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed1_getAt_u8r64(CT,X)                     ESDL_Linear_CharTableFixed1_getAt_u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable1_getAt_u8r64(GT,searchIndex,deltaX,distX)  ESDL_Linear_GroupTable1_getAt_u8r64__INVALID_TYPE_COMBINATION

/**
 * @brief   Map (2-Dimensional) Interpolation: CharTable1 / GroupTable1 / CharTableFixed1
 **/

/* signature combination: u8u8u8 */

uint8 ESDL_Linear_CharTable2_getAt_u8u8u8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u8u8u8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_u8u8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8u8s8 */

sint8 ESDL_Linear_CharTable2_getAt_u8u8s8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u8u8s8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_u8u8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8u8u16 */

uint16 ESDL_Linear_CharTable2_getAt_u8u8u16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u8u8u16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_u8u8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8u8s16 */

sint16 ESDL_Linear_CharTable2_getAt_u8u8s16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u8u8s16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_u8u8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8u8u32 */

uint32 ESDL_Linear_CharTable2_getAt_u8u8u32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u8u8u32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_u8u8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8u8s32 */

sint32 ESDL_Linear_CharTable2_getAt_u8u8s32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u8u8s32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_u8u8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8s8u8 */

uint8 ESDL_Linear_CharTable2_getAt_u8s8u8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u8s8u8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_u8s8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8s8s8 */

sint8 ESDL_Linear_CharTable2_getAt_u8s8s8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u8s8s8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_u8s8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8s8u16 */

uint16 ESDL_Linear_CharTable2_getAt_u8s8u16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u8s8u16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_u8s8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8s8s16 */

sint16 ESDL_Linear_CharTable2_getAt_u8s8s16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u8s8s16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_u8s8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8s8u32 */

uint32 ESDL_Linear_CharTable2_getAt_u8s8u32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u8s8u32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_u8s8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8s8s32 */

sint32 ESDL_Linear_CharTable2_getAt_u8s8s32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u8s8s32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_u8s8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u8u16u8 */

uint8 ESDL_Linear_CharTable2_getAt_u8u16u8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u8u16u8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_u8u16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8u16s8 */

sint8 ESDL_Linear_CharTable2_getAt_u8u16s8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u8u16s8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_u8u16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8u16u16 */

uint16 ESDL_Linear_CharTable2_getAt_u8u16u16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u8u16u16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_u8u16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8u16s16 */

sint16 ESDL_Linear_CharTable2_getAt_u8u16s16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u8u16s16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_u8u16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8u16u32 */

uint32 ESDL_Linear_CharTable2_getAt_u8u16u32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u8u16u32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_u8u16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8u16s32 */

sint32 ESDL_Linear_CharTable2_getAt_u8u16s32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u8u16s32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_u8u16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8s16u8 */

uint8 ESDL_Linear_CharTable2_getAt_u8s16u8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u8s16u8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_u8s16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8s16s8 */

sint8 ESDL_Linear_CharTable2_getAt_u8s16s8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u8s16s8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_u8s16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8s16u16 */

uint16 ESDL_Linear_CharTable2_getAt_u8s16u16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u8s16u16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_u8s16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8s16s16 */

sint16 ESDL_Linear_CharTable2_getAt_u8s16s16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u8s16s16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_u8s16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8s16u32 */

uint32 ESDL_Linear_CharTable2_getAt_u8s16u32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u8s16u32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_u8s16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8s16s32 */

sint32 ESDL_Linear_CharTable2_getAt_u8s16s32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u8s16s32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_u8s16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u8u32u8 */

uint8 ESDL_Linear_CharTable2_getAt_u8u32u8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u8u32u8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_u8u32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8u32s8 */

sint8 ESDL_Linear_CharTable2_getAt_u8u32s8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u8u32s8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_u8u32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8u32u16 */

uint16 ESDL_Linear_CharTable2_getAt_u8u32u16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u8u32u16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_u8u32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8u32s16 */

sint16 ESDL_Linear_CharTable2_getAt_u8u32s16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u8u32s16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_u8u32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8u32u32 */

uint32 ESDL_Linear_CharTable2_getAt_u8u32u32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u8u32u32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_u8u32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8u32s32 */

sint32 ESDL_Linear_CharTable2_getAt_u8u32s32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u8u32s32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, uint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_u8u32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8s32u8 */

uint8 ESDL_Linear_CharTable2_getAt_u8s32u8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u8s32u8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_u8s32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8s32s8 */

sint8 ESDL_Linear_CharTable2_getAt_u8s32s8(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u8s32s8(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_u8s32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8s32u16 */

uint16 ESDL_Linear_CharTable2_getAt_u8s32u16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u8s32u16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_u8s32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8s32s16 */

sint16 ESDL_Linear_CharTable2_getAt_u8s32s16(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u8s32s16(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_u8s32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8s32u32 */

uint32 ESDL_Linear_CharTable2_getAt_u8s32u32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u8s32u32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_u8s32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u8s32s32 */

sint32 ESDL_Linear_CharTable2_getAt_u8s32s32(uint16 xVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u8s32s32(uint16 xVecLen, uint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint8 x, sint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_u8s32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8u8u8 */

uint8 ESDL_Linear_CharTable2_getAt_s8u8u8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s8u8u8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_s8u8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8u8s8 */

sint8 ESDL_Linear_CharTable2_getAt_s8u8s8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s8u8s8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_s8u8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8u8u16 */

uint16 ESDL_Linear_CharTable2_getAt_s8u8u16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s8u8u16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_s8u8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8u8s16 */

sint16 ESDL_Linear_CharTable2_getAt_s8u8s16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s8u8s16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_s8u8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8u8u32 */

uint32 ESDL_Linear_CharTable2_getAt_s8u8u32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s8u8u32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_s8u8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8u8s32 */

sint32 ESDL_Linear_CharTable2_getAt_s8u8s32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s8u8s32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_s8u8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8s8u8 */

uint8 ESDL_Linear_CharTable2_getAt_s8s8u8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s8s8u8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_s8s8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8s8s8 */

sint8 ESDL_Linear_CharTable2_getAt_s8s8s8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s8s8s8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_s8s8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8s8u16 */

uint16 ESDL_Linear_CharTable2_getAt_s8s8u16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s8s8u16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_s8s8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8s8s16 */

sint16 ESDL_Linear_CharTable2_getAt_s8s8s16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s8s8s16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_s8s8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8s8u32 */

uint32 ESDL_Linear_CharTable2_getAt_s8s8u32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s8s8u32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_s8s8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8s8s32 */

sint32 ESDL_Linear_CharTable2_getAt_s8s8s32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s8s8s32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_s8s8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s8u16u8 */

uint8 ESDL_Linear_CharTable2_getAt_s8u16u8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s8u16u8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_s8u16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8u16s8 */

sint8 ESDL_Linear_CharTable2_getAt_s8u16s8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s8u16s8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_s8u16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8u16u16 */

uint16 ESDL_Linear_CharTable2_getAt_s8u16u16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s8u16u16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_s8u16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8u16s16 */

sint16 ESDL_Linear_CharTable2_getAt_s8u16s16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s8u16s16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_s8u16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8u16u32 */

uint32 ESDL_Linear_CharTable2_getAt_s8u16u32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s8u16u32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_s8u16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8u16s32 */

sint32 ESDL_Linear_CharTable2_getAt_s8u16s32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s8u16s32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_s8u16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8s16u8 */

uint8 ESDL_Linear_CharTable2_getAt_s8s16u8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s8s16u8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_s8s16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8s16s8 */

sint8 ESDL_Linear_CharTable2_getAt_s8s16s8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s8s16s8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_s8s16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8s16u16 */

uint16 ESDL_Linear_CharTable2_getAt_s8s16u16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s8s16u16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_s8s16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8s16s16 */

sint16 ESDL_Linear_CharTable2_getAt_s8s16s16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s8s16s16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_s8s16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8s16u32 */

uint32 ESDL_Linear_CharTable2_getAt_s8s16u32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s8s16u32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_s8s16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8s16s32 */

sint32 ESDL_Linear_CharTable2_getAt_s8s16s32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s8s16s32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_s8s16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s8u32u8 */

uint8 ESDL_Linear_CharTable2_getAt_s8u32u8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s8u32u8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_s8u32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8u32s8 */

sint8 ESDL_Linear_CharTable2_getAt_s8u32s8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s8u32s8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_s8u32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8u32u16 */

uint16 ESDL_Linear_CharTable2_getAt_s8u32u16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s8u32u16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_s8u32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8u32s16 */

sint16 ESDL_Linear_CharTable2_getAt_s8u32s16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s8u32s16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_s8u32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8u32u32 */

uint32 ESDL_Linear_CharTable2_getAt_s8u32u32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s8u32u32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_s8u32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8u32s32 */

sint32 ESDL_Linear_CharTable2_getAt_s8u32s32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s8u32s32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, uint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_s8u32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8s32u8 */

uint8 ESDL_Linear_CharTable2_getAt_s8s32u8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s8s32u8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_s8s32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8s32s8 */

sint8 ESDL_Linear_CharTable2_getAt_s8s32s8(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s8s32s8(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_s8s32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8s32u16 */

uint16 ESDL_Linear_CharTable2_getAt_s8s32u16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s8s32u16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_s8s32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8s32s16 */

sint16 ESDL_Linear_CharTable2_getAt_s8s32s16(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s8s32s16(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_s8s32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8s32u32 */

uint32 ESDL_Linear_CharTable2_getAt_s8s32u32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s8s32u32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_s8s32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s8s32s32 */

sint32 ESDL_Linear_CharTable2_getAt_s8s32s32(uint16 xVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s8s32s32(uint16 xVecLen, sint8 xOffset, uint8 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint8 x, sint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_s8s32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint8 deltaX, uint8 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16u8u8 */

uint8 ESDL_Linear_CharTable2_getAt_u16u8u8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u16u8u8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_u16u8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16u8s8 */

sint8 ESDL_Linear_CharTable2_getAt_u16u8s8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u16u8s8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_u16u8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16u8u16 */

uint16 ESDL_Linear_CharTable2_getAt_u16u8u16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u16u8u16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_u16u8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16u8s16 */

sint16 ESDL_Linear_CharTable2_getAt_u16u8s16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u16u8s16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_u16u8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16u8u32 */

uint32 ESDL_Linear_CharTable2_getAt_u16u8u32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u16u8u32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_u16u8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16u8s32 */

sint32 ESDL_Linear_CharTable2_getAt_u16u8s32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u16u8s32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_u16u8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16s8u8 */

uint8 ESDL_Linear_CharTable2_getAt_u16s8u8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u16s8u8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_u16s8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16s8s8 */

sint8 ESDL_Linear_CharTable2_getAt_u16s8s8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u16s8s8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_u16s8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16s8u16 */

uint16 ESDL_Linear_CharTable2_getAt_u16s8u16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u16s8u16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_u16s8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16s8s16 */

sint16 ESDL_Linear_CharTable2_getAt_u16s8s16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u16s8s16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_u16s8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16s8u32 */

uint32 ESDL_Linear_CharTable2_getAt_u16s8u32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u16s8u32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_u16s8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16s8s32 */

sint32 ESDL_Linear_CharTable2_getAt_u16s8s32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u16s8s32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_u16s8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u16u16u8 */

uint8 ESDL_Linear_CharTable2_getAt_u16u16u8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u16u16u8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_u16u16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16u16s8 */

sint8 ESDL_Linear_CharTable2_getAt_u16u16s8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u16u16s8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_u16u16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16u16u16 */

uint16 ESDL_Linear_CharTable2_getAt_u16u16u16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u16u16u16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_u16u16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16u16s16 */

sint16 ESDL_Linear_CharTable2_getAt_u16u16s16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u16u16s16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_u16u16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16u16u32 */

uint32 ESDL_Linear_CharTable2_getAt_u16u16u32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u16u16u32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_u16u16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16u16s32 */

sint32 ESDL_Linear_CharTable2_getAt_u16u16s32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u16u16s32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_u16u16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16s16u8 */

uint8 ESDL_Linear_CharTable2_getAt_u16s16u8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u16s16u8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_u16s16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16s16s8 */

sint8 ESDL_Linear_CharTable2_getAt_u16s16s8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u16s16s8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_u16s16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16s16u16 */

uint16 ESDL_Linear_CharTable2_getAt_u16s16u16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u16s16u16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_u16s16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16s16s16 */

sint16 ESDL_Linear_CharTable2_getAt_u16s16s16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u16s16s16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_u16s16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16s16u32 */

uint32 ESDL_Linear_CharTable2_getAt_u16s16u32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u16s16u32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_u16s16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16s16s32 */

sint32 ESDL_Linear_CharTable2_getAt_u16s16s32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u16s16s32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_u16s16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u16u32u8 */

uint8 ESDL_Linear_CharTable2_getAt_u16u32u8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u16u32u8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_u16u32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16u32s8 */

sint8 ESDL_Linear_CharTable2_getAt_u16u32s8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u16u32s8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_u16u32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16u32u16 */

uint16 ESDL_Linear_CharTable2_getAt_u16u32u16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u16u32u16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_u16u32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16u32s16 */

sint16 ESDL_Linear_CharTable2_getAt_u16u32s16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u16u32s16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_u16u32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16u32u32 */

uint32 ESDL_Linear_CharTable2_getAt_u16u32u32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u16u32u32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_u16u32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16u32s32 */

sint32 ESDL_Linear_CharTable2_getAt_u16u32s32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u16u32s32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, uint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_u16u32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16s32u8 */

uint8 ESDL_Linear_CharTable2_getAt_u16s32u8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u16s32u8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_u16s32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16s32s8 */

sint8 ESDL_Linear_CharTable2_getAt_u16s32s8(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u16s32s8(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_u16s32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16s32u16 */

uint16 ESDL_Linear_CharTable2_getAt_u16s32u16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u16s32u16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_u16s32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16s32s16 */

sint16 ESDL_Linear_CharTable2_getAt_u16s32s16(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u16s32s16(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_u16s32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16s32u32 */

uint32 ESDL_Linear_CharTable2_getAt_u16s32u32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u16s32u32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_u16s32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u16s32s32 */

sint32 ESDL_Linear_CharTable2_getAt_u16s32s32(uint16 xVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u16s32s32(uint16 xVecLen, uint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint16 x, sint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_u16s32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16u8u8 */

uint8 ESDL_Linear_CharTable2_getAt_s16u8u8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s16u8u8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_s16u8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16u8s8 */

sint8 ESDL_Linear_CharTable2_getAt_s16u8s8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s16u8s8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_s16u8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16u8u16 */

uint16 ESDL_Linear_CharTable2_getAt_s16u8u16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s16u8u16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_s16u8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16u8s16 */

sint16 ESDL_Linear_CharTable2_getAt_s16u8s16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s16u8s16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_s16u8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16u8u32 */

uint32 ESDL_Linear_CharTable2_getAt_s16u8u32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s16u8u32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_s16u8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16u8s32 */

sint32 ESDL_Linear_CharTable2_getAt_s16u8s32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s16u8s32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_s16u8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16s8u8 */

uint8 ESDL_Linear_CharTable2_getAt_s16s8u8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s16s8u8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_s16s8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16s8s8 */

sint8 ESDL_Linear_CharTable2_getAt_s16s8s8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s16s8s8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_s16s8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16s8u16 */

uint16 ESDL_Linear_CharTable2_getAt_s16s8u16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s16s8u16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_s16s8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16s8s16 */

sint16 ESDL_Linear_CharTable2_getAt_s16s8s16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s16s8s16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_s16s8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16s8u32 */

uint32 ESDL_Linear_CharTable2_getAt_s16s8u32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s16s8u32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_s16s8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16s8s32 */

sint32 ESDL_Linear_CharTable2_getAt_s16s8s32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s16s8s32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_s16s8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s16u16u8 */

uint8 ESDL_Linear_CharTable2_getAt_s16u16u8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s16u16u8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_s16u16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16u16s8 */

sint8 ESDL_Linear_CharTable2_getAt_s16u16s8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s16u16s8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_s16u16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16u16u16 */

uint16 ESDL_Linear_CharTable2_getAt_s16u16u16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s16u16u16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_s16u16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16u16s16 */

sint16 ESDL_Linear_CharTable2_getAt_s16u16s16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s16u16s16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_s16u16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16u16u32 */

uint32 ESDL_Linear_CharTable2_getAt_s16u16u32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s16u16u32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_s16u16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16u16s32 */

sint32 ESDL_Linear_CharTable2_getAt_s16u16s32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s16u16s32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_s16u16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16s16u8 */

uint8 ESDL_Linear_CharTable2_getAt_s16s16u8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s16s16u8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_s16s16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16s16s8 */

sint8 ESDL_Linear_CharTable2_getAt_s16s16s8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s16s16s8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_s16s16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16s16u16 */

uint16 ESDL_Linear_CharTable2_getAt_s16s16u16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s16s16u16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_s16s16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16s16s16 */

sint16 ESDL_Linear_CharTable2_getAt_s16s16s16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s16s16s16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_s16s16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16s16u32 */

uint32 ESDL_Linear_CharTable2_getAt_s16s16u32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s16s16u32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_s16s16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16s16s32 */

sint32 ESDL_Linear_CharTable2_getAt_s16s16s32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s16s16s32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_s16s16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s16u32u8 */

uint8 ESDL_Linear_CharTable2_getAt_s16u32u8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s16u32u8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_s16u32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16u32s8 */

sint8 ESDL_Linear_CharTable2_getAt_s16u32s8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s16u32s8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_s16u32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16u32u16 */

uint16 ESDL_Linear_CharTable2_getAt_s16u32u16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s16u32u16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_s16u32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16u32s16 */

sint16 ESDL_Linear_CharTable2_getAt_s16u32s16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s16u32s16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_s16u32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16u32u32 */

uint32 ESDL_Linear_CharTable2_getAt_s16u32u32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s16u32u32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_s16u32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16u32s32 */

sint32 ESDL_Linear_CharTable2_getAt_s16u32s32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s16u32s32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, uint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_s16u32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16s32u8 */

uint8 ESDL_Linear_CharTable2_getAt_s16s32u8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s16s32u8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_s16s32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16s32s8 */

sint8 ESDL_Linear_CharTable2_getAt_s16s32s8(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s16s32s8(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_s16s32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16s32u16 */

uint16 ESDL_Linear_CharTable2_getAt_s16s32u16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s16s32u16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_s16s32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16s32s16 */

sint16 ESDL_Linear_CharTable2_getAt_s16s32s16(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s16s32s16(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_s16s32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16s32u32 */

uint32 ESDL_Linear_CharTable2_getAt_s16s32u32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s16s32u32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_s16s32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s16s32s32 */

sint32 ESDL_Linear_CharTable2_getAt_s16s32s32(uint16 xVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s16s32s32(uint16 xVecLen, sint16 xOffset, uint16 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint16 x, sint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_s16s32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint16 deltaX, uint16 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32u8u8 */

uint8 ESDL_Linear_CharTable2_getAt_u32u8u8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u32u8u8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_u32u8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32u8s8 */

sint8 ESDL_Linear_CharTable2_getAt_u32u8s8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u32u8s8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_u32u8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32u8u16 */

uint16 ESDL_Linear_CharTable2_getAt_u32u8u16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u32u8u16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_u32u8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32u8s16 */

sint16 ESDL_Linear_CharTable2_getAt_u32u8s16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u32u8s16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_u32u8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32u8u32 */

uint32 ESDL_Linear_CharTable2_getAt_u32u8u32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u32u8u32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_u32u8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32u8s32 */

sint32 ESDL_Linear_CharTable2_getAt_u32u8s32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u32u8s32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_u32u8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32s8u8 */

uint8 ESDL_Linear_CharTable2_getAt_u32s8u8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u32s8u8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_u32s8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32s8s8 */

sint8 ESDL_Linear_CharTable2_getAt_u32s8s8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u32s8s8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_u32s8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32s8u16 */

uint16 ESDL_Linear_CharTable2_getAt_u32s8u16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u32s8u16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_u32s8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32s8s16 */

sint16 ESDL_Linear_CharTable2_getAt_u32s8s16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u32s8s16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_u32s8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32s8u32 */

uint32 ESDL_Linear_CharTable2_getAt_u32s8u32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u32s8u32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_u32s8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32s8s32 */

sint32 ESDL_Linear_CharTable2_getAt_u32s8s32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u32s8s32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_u32s8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: u32u16u8 */

uint8 ESDL_Linear_CharTable2_getAt_u32u16u8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u32u16u8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_u32u16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32u16s8 */

sint8 ESDL_Linear_CharTable2_getAt_u32u16s8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u32u16s8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_u32u16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32u16u16 */

uint16 ESDL_Linear_CharTable2_getAt_u32u16u16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u32u16u16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_u32u16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32u16s16 */

sint16 ESDL_Linear_CharTable2_getAt_u32u16s16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u32u16s16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_u32u16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32u16u32 */

uint32 ESDL_Linear_CharTable2_getAt_u32u16u32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u32u16u32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_u32u16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32u16s32 */

sint32 ESDL_Linear_CharTable2_getAt_u32u16s32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u32u16s32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_u32u16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32s16u8 */

uint8 ESDL_Linear_CharTable2_getAt_u32s16u8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u32s16u8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_u32s16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32s16s8 */

sint8 ESDL_Linear_CharTable2_getAt_u32s16s8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u32s16s8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_u32s16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32s16u16 */

uint16 ESDL_Linear_CharTable2_getAt_u32s16u16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u32s16u16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_u32s16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32s16s16 */

sint16 ESDL_Linear_CharTable2_getAt_u32s16s16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u32s16s16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_u32s16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32s16u32 */

uint32 ESDL_Linear_CharTable2_getAt_u32s16u32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u32s16u32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_u32s16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32s16s32 */

sint32 ESDL_Linear_CharTable2_getAt_u32s16s32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u32s16s32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_u32s16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: u32u32u8 */

uint8 ESDL_Linear_CharTable2_getAt_u32u32u8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u32u32u8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_u32u32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32u32s8 */

sint8 ESDL_Linear_CharTable2_getAt_u32u32s8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u32u32s8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_u32u32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32u32u16 */

uint16 ESDL_Linear_CharTable2_getAt_u32u32u16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u32u32u16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_u32u32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32u32s16 */

sint16 ESDL_Linear_CharTable2_getAt_u32u32s16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u32u32s16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_u32u32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32u32u32 */

uint32 ESDL_Linear_CharTable2_getAt_u32u32u32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u32u32u32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_u32u32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32u32s32 */

sint32 ESDL_Linear_CharTable2_getAt_u32u32s32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u32u32s32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, uint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_u32u32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32s32u8 */

uint8 ESDL_Linear_CharTable2_getAt_u32s32u8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_u32s32u8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_u32s32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32s32s8 */

sint8 ESDL_Linear_CharTable2_getAt_u32s32s8(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_u32s32s8(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_u32s32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32s32u16 */

uint16 ESDL_Linear_CharTable2_getAt_u32s32u16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_u32s32u16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_u32s32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32s32s16 */

sint16 ESDL_Linear_CharTable2_getAt_u32s32s16(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_u32s32s16(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_u32s32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32s32u32 */

uint32 ESDL_Linear_CharTable2_getAt_u32s32u32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_u32s32u32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_u32s32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: u32s32s32 */

sint32 ESDL_Linear_CharTable2_getAt_u32s32s32(uint16 xVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_u32s32s32(uint16 xVecLen, uint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, uint32 x, sint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_u32s32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32u8u8 */

uint8 ESDL_Linear_CharTable2_getAt_s32u8u8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s32u8u8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_s32u8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32u8s8 */

sint8 ESDL_Linear_CharTable2_getAt_s32u8s8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s32u8s8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_s32u8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32u8u16 */

uint16 ESDL_Linear_CharTable2_getAt_s32u8u16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s32u8u16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_s32u8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32u8s16 */

sint16 ESDL_Linear_CharTable2_getAt_s32u8s16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s32u8s16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_s32u8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32u8u32 */

uint32 ESDL_Linear_CharTable2_getAt_s32u8u32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s32u8u32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_s32u8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32u8s32 */

sint32 ESDL_Linear_CharTable2_getAt_s32u8s32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s32u8s32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_s32u8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32s8u8 */

uint8 ESDL_Linear_CharTable2_getAt_s32s8u8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s32s8u8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
uint8 ESDL_Linear_GroupTable2_getAt_s32s8u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32s8s8 */

sint8 ESDL_Linear_CharTable2_getAt_s32s8s8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s32s8s8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
sint8 ESDL_Linear_GroupTable2_getAt_s32s8s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32s8u16 */

uint16 ESDL_Linear_CharTable2_getAt_s32s8u16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s32s8u16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
uint16 ESDL_Linear_GroupTable2_getAt_s32s8u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32s8s16 */

sint16 ESDL_Linear_CharTable2_getAt_s32s8s16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s32s8s16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
sint16 ESDL_Linear_GroupTable2_getAt_s32s8s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32s8u32 */

uint32 ESDL_Linear_CharTable2_getAt_s32s8u32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s32s8u32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
uint32 ESDL_Linear_GroupTable2_getAt_s32s8u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32s8s32 */

sint32 ESDL_Linear_CharTable2_getAt_s32s8s32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint8 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s32s8s32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint8 yOffset, uint8 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint8 y);
sint32 ESDL_Linear_GroupTable2_getAt_s32s8s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint8 deltaY, uint8 distY, uint16 yVecLen);

/* signature combination: s32u16u8 */

uint8 ESDL_Linear_CharTable2_getAt_s32u16u8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s32u16u8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_s32u16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32u16s8 */

sint8 ESDL_Linear_CharTable2_getAt_s32u16s8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s32u16s8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_s32u16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32u16u16 */

uint16 ESDL_Linear_CharTable2_getAt_s32u16u16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s32u16u16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_s32u16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32u16s16 */

sint16 ESDL_Linear_CharTable2_getAt_s32u16s16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s32u16s16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_s32u16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32u16u32 */

uint32 ESDL_Linear_CharTable2_getAt_s32u16u32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s32u16u32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_s32u16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32u16s32 */

sint32 ESDL_Linear_CharTable2_getAt_s32u16s32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s32u16s32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_s32u16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32s16u8 */

uint8 ESDL_Linear_CharTable2_getAt_s32s16u8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s32s16u8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
uint8 ESDL_Linear_GroupTable2_getAt_s32s16u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32s16s8 */

sint8 ESDL_Linear_CharTable2_getAt_s32s16s8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s32s16s8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
sint8 ESDL_Linear_GroupTable2_getAt_s32s16s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32s16u16 */

uint16 ESDL_Linear_CharTable2_getAt_s32s16u16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s32s16u16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
uint16 ESDL_Linear_GroupTable2_getAt_s32s16u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32s16s16 */

sint16 ESDL_Linear_CharTable2_getAt_s32s16s16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s32s16s16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
sint16 ESDL_Linear_GroupTable2_getAt_s32s16s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32s16u32 */

uint32 ESDL_Linear_CharTable2_getAt_s32s16u32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s32s16u32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
uint32 ESDL_Linear_GroupTable2_getAt_s32s16u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32s16s32 */

sint32 ESDL_Linear_CharTable2_getAt_s32s16s32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint16 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s32s16s32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint16 yOffset, uint16 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint16 y);
sint32 ESDL_Linear_GroupTable2_getAt_s32s16s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint16 deltaY, uint16 distY, uint16 yVecLen);

/* signature combination: s32u32u8 */

uint8 ESDL_Linear_CharTable2_getAt_s32u32u8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s32u32u8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_s32u32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32u32s8 */

sint8 ESDL_Linear_CharTable2_getAt_s32u32s8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s32u32s8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_s32u32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32u32u16 */

uint16 ESDL_Linear_CharTable2_getAt_s32u32u16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s32u32u16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_s32u32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32u32s16 */

sint16 ESDL_Linear_CharTable2_getAt_s32u32s16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s32u32s16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_s32u32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32u32u32 */

uint32 ESDL_Linear_CharTable2_getAt_s32u32u32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s32u32u32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_s32u32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32u32s32 */

sint32 ESDL_Linear_CharTable2_getAt_s32u32s32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile uint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s32u32s32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, uint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, uint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_s32u32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32s32u8 */

uint8 ESDL_Linear_CharTable2_getAt_s32s32u8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
uint8 ESDL_Linear_CharTableFixed2_getAt_s32s32u8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
uint8 ESDL_Linear_GroupTable2_getAt_s32s32u8 (const volatile uint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32s32s8 */

sint8 ESDL_Linear_CharTable2_getAt_s32s32s8(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
sint8 ESDL_Linear_CharTableFixed2_getAt_s32s32s8(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint8 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
sint8 ESDL_Linear_GroupTable2_getAt_s32s32s8 (const volatile sint8 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32s32u16 */

uint16 ESDL_Linear_CharTable2_getAt_s32s32u16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
uint16 ESDL_Linear_CharTableFixed2_getAt_s32s32u16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
uint16 ESDL_Linear_GroupTable2_getAt_s32s32u16 (const volatile uint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32s32s16 */

sint16 ESDL_Linear_CharTable2_getAt_s32s32s16(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
sint16 ESDL_Linear_CharTableFixed2_getAt_s32s32s16(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint16 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
sint16 ESDL_Linear_GroupTable2_getAt_s32s32s16 (const volatile sint16 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32s32u32 */

uint32 ESDL_Linear_CharTable2_getAt_s32s32u32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
uint32 ESDL_Linear_CharTableFixed2_getAt_s32s32u32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile uint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
uint32 ESDL_Linear_GroupTable2_getAt_s32s32u32 (const volatile uint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: s32s32s32 */

sint32 ESDL_Linear_CharTable2_getAt_s32s32s32(uint16 xVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile sint32 ESDL_LINEAR_PTR_TYPE yDist, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
sint32 ESDL_Linear_CharTableFixed2_getAt_s32s32s32(uint16 xVecLen, sint32 xOffset, uint32 xDistance, uint16 yVecLen, sint32 yOffset, uint32 yDistance, const volatile sint32 ESDL_LINEAR_PTR_TYPE zVal, sint32 x, sint32 y);
sint32 ESDL_Linear_GroupTable2_getAt_s32s32s32 (const volatile sint32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, uint32 deltaX, uint32 distX, uint16 xVecLen, uint16 idx_Y, uint32 deltaY, uint32 distY, uint16 yVecLen);

/* signature combination: r32r32r32 */

float32 ESDL_Linear_CharTable2_getAt_r32r32r32(uint16 xVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE yDist, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float32 x, float32 y);
float32 ESDL_Linear_CharTableFixed2_getAt_r32r32r32(uint16 xVecLen, float32 xOffset, float32 xDistance, uint16 yVecLen, float32 yOffset, float32 yDistance, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float32 x, float32 y);
float32 ESDL_Linear_GroupTable2_getAt_r32r32r32 (const volatile float32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, float32 deltaX, float32 distX, uint16 xVecLen, uint16 idx_Y, float32 deltaY, float32 distY, uint16 yVecLen);

/* signature combination: r32r32r64 */

float64 ESDL_Linear_CharTable2_getAt_r32r32r64(uint16 xVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE yDist, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float32 x, float32 y);
float64 ESDL_Linear_CharTableFixed2_getAt_r32r32r64(uint16 xVecLen, float32 xOffset, float32 xDistance, uint16 yVecLen, float32 yOffset, float32 yDistance, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float32 x, float32 y);
float64 ESDL_Linear_GroupTable2_getAt_r32r32r64 (const volatile float64 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, float32 deltaX, float32 distX, uint16 xVecLen, uint16 idx_Y, float32 deltaY, float32 distY, uint16 yVecLen);

/* signature combination: r32r64r32 */

float32 ESDL_Linear_CharTable2_getAt_r32r64r32(uint16 xVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE yDist, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float32 x, float64 y);
float32 ESDL_Linear_CharTableFixed2_getAt_r32r64r32(uint16 xVecLen, float32 xOffset, float32 xDistance, uint16 yVecLen, float64 yOffset, float64 yDistance, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float32 x, float64 y);
float32 ESDL_Linear_GroupTable2_getAt_r32r64r32 (const volatile float32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, float32 deltaX, float32 distX, uint16 xVecLen, uint16 idx_Y, float64 deltaY, float64 distY, uint16 yVecLen);

/* signature combination: r32r64r64 */

float64 ESDL_Linear_CharTable2_getAt_r32r64r64(uint16 xVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE yDist, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float32 x, float64 y);
float64 ESDL_Linear_CharTableFixed2_getAt_r32r64r64(uint16 xVecLen, float32 xOffset, float32 xDistance, uint16 yVecLen, float64 yOffset, float64 yDistance, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float32 x, float64 y);
float64 ESDL_Linear_GroupTable2_getAt_r32r64r64 (const volatile float64 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, float32 deltaX, float32 distX, uint16 xVecLen, uint16 idx_Y, float64 deltaY, float64 distY, uint16 yVecLen);

/* signature combination: r64r32r32 */

float32 ESDL_Linear_CharTable2_getAt_r64r32r32(uint16 xVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE yDist, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float64 x, float32 y);
float32 ESDL_Linear_CharTableFixed2_getAt_r64r32r32(uint16 xVecLen, float64 xOffset, float64 xDistance, uint16 yVecLen, float32 yOffset, float32 yDistance, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float64 x, float32 y);
float32 ESDL_Linear_GroupTable2_getAt_r64r32r32 (const volatile float32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, float64 deltaX, float64 distX, uint16 xVecLen, uint16 idx_Y, float32 deltaY, float32 distY, uint16 yVecLen);

/* signature combination: r64r32r64 */

float64 ESDL_Linear_CharTable2_getAt_r64r32r64(uint16 xVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile float32 ESDL_LINEAR_PTR_TYPE yDist, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float64 x, float32 y);
float64 ESDL_Linear_CharTableFixed2_getAt_r64r32r64(uint16 xVecLen, float64 xOffset, float64 xDistance, uint16 yVecLen, float32 yOffset, float32 yDistance, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float64 x, float32 y);
float64 ESDL_Linear_GroupTable2_getAt_r64r32r64 (const volatile float64 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, float64 deltaX, float64 distX, uint16 xVecLen, uint16 idx_Y, float32 deltaY, float32 distY, uint16 yVecLen);

/* signature combination: r64r64r32 */

float32 ESDL_Linear_CharTable2_getAt_r64r64r32(uint16 xVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE yDist, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float64 x, float64 y);
float32 ESDL_Linear_CharTableFixed2_getAt_r64r64r32(uint16 xVecLen, float64 xOffset, float64 xDistance, uint16 yVecLen, float64 yOffset, float64 yDistance, const volatile float32 ESDL_LINEAR_PTR_TYPE zVal, float64 x, float64 y);
float32 ESDL_Linear_GroupTable2_getAt_r64r64r32 (const volatile float32 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, float64 deltaX, float64 distX, uint16 xVecLen, uint16 idx_Y, float64 deltaY, float64 distY, uint16 yVecLen);

/* signature combination: r64r64r64 */

float64 ESDL_Linear_CharTable2_getAt_r64r64r64(uint16 xVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE xDist, uint16 yVecLen, const volatile float64 ESDL_LINEAR_PTR_TYPE yDist, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float64 x, float64 y);
float64 ESDL_Linear_CharTableFixed2_getAt_r64r64r64(uint16 xVecLen, float64 xOffset, float64 xDistance, uint16 yVecLen, float64 yOffset, float64 yDistance, const volatile float64 ESDL_LINEAR_PTR_TYPE zVal, float64 x, float64 y);
float64 ESDL_Linear_GroupTable2_getAt_r64r64r64 (const volatile float64 ESDL_LINEAR_PTR_TYPE vMat, uint16 idx_X, float64 deltaX, float64 distX, uint16 xVecLen, uint16 idx_Y, float64 deltaY, float64 distY, uint16 yVecLen);

/*
 * Definition of macros for not implemented type combinations force compilation abort
 * with a more coherent error message.
 * MISRA rules are not important here as the code should not compile if one of these macros
 * is present.
 */
#define ESDL_Linear_CharTable2_getAt_r32r32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r64s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r64s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r64s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r64s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r64s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r64s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r64s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r64s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r64s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r64u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r64u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r64u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r64u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r64u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r64u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32r64u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32r64u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32r64u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s16s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s16s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s16s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s16s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s16s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s16s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s16s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s16s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s16s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s16u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s16u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s16u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s16u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s16u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s16u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s16u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s16u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s16u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s8s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s8s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s8s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s8s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s8s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s8s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s8s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s8s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s8s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s8u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s8u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s8u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s8u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s8u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s8u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32s8u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32s8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32s8u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32s8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32s8u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32s8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u16s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u16s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u16s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u16s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u16s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u16s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u16s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u16s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u16s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u16u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u16u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u16u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u16u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u16u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u16u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u16u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u16u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u16u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u8s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u8s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u8s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u8s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u8s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u8s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u8s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u8s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u8s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u8u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u8u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u8u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u8u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u8u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u8u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r32u8u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r32u8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r32u8u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r32u8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r32u8u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r32u8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r64s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r64s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r64s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r64s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r64s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r64s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r64s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r64s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r64s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r64u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r64u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r64u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r64u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r64u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r64u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64r64u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64r64u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64r64u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s16s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s16s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s16s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s16s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s16s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s16s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s16s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s16s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s16s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s16u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s16u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s16u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s16u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s16u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s16u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s16u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s16u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s16u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s8s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s8s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s8s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s8s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s8s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s8s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s8s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s8s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s8s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s8u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s8u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s8u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s8u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s8u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s8u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64s8u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64s8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64s8u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64s8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64s8u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64s8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u16s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u16s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u16s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u16s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u16s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u16s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u16s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u16s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u16s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u16s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u16s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u16s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u16u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u16u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u16u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u16u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u16u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u16u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u16u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u16u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u16u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u16u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u16u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u16u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u8s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u8s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u8s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u8s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u8s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u8s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u8s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u8s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u8s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u8s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u8s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u8s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u8u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u8u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u8u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u8u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u8u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u8u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u8u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u8u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_r64u8u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_r64u8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_r64u8u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_r64u8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_r64u8u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_r64u8u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r64r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r64r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r64r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r64r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r64r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r64r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r64s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r64s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r64s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r64s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r64s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r64s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r64s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r64s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r64s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r64u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r64u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r64u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r64u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r64u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r64u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16r64u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16r64u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16r64u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16s16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16s16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16s16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16s16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16s16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16s16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16s32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16s32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16s32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16s32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16s32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16s32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16s8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16s8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16s8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16s8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16s8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16s8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16u16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16u16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16u16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16u16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16u16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16u16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16u32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16u32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16u32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16u32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16u32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16u32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16u8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16u8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16u8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s16u8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s16u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s16u8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s16u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s16u8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s16u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r64r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r64r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r64r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r64r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r64r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r64r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r64s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r64s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r64s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r64s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r64s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r64s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r64s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r64s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r64s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r64u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r64u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r64u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r64u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r64u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r64u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32r64u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32r64u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32r64u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32s16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32s16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32s16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32s16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32s16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32s16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32s32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32s32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32s32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32s32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32s32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32s32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32s8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32s8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32s8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32s8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32s8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32s8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32u16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32u16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32u16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32u16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32u16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32u16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32u32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32u32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32u32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32u32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32u32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32u32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32u8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32u8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32u8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s32u8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s32u8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s32u8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r64r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r64r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r64r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r64r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r64r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r64r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r64s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r64s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r64s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r64s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r64s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r64s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r64s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r64s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r64s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r64u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r64u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r64u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r64u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r64u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r64u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8r64u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8r64u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8r64u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8s16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8s16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8s16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8s16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8s16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8s16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8s32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8s32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8s32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8s32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8s32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8s32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8s8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8s8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8s8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8s8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8s8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8s8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8u16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8u16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8u16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8u16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8u16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8u16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8u32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8u32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8u32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8u32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8u32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8u32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8u8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8u8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8u8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_s8u8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_s8u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_s8u8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_s8u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_s8u8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_s8u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r64r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r64r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r64r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r64r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r64r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r64r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r64s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r64s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r64s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r64s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r64s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r64s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r64s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r64s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r64s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r64u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r64u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r64u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r64u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r64u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r64u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16r64u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16r64u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16r64u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16s16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16s16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16s16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16s16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16s16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16s16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16s32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16s32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16s32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16s32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16s32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16s32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16s8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16s8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16s8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16s8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16s8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16s8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16u16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16u16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16u16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16u16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16u16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16u16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16u32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16u32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16u32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16u32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16u32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16u32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16u8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16u8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16u8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u16u8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u16u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u16u8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u16u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u16u8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u16u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r64r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r64r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r64r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r64r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r64r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r64r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r64s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r64s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r64s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r64s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r64s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r64s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r64s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r64s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r64s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r64u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r64u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r64u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r64u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r64u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r64u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32r64u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32r64u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32r64u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32s16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32s16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32s16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32s16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32s16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32s16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32s32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32s32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32s32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32s32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32s32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32s32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32s8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32s8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32s8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32s8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32s8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32s8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32u16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32u16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32u16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32u16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32u16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32u16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32u32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32u32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32u32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32u32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32u32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32u32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32u8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32u8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32u8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u32u8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u32u8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u32u8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u32u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r32s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r32s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r32s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r32s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r32s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r32s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r32s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r32s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r32s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r32s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r32s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r32s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r32u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r32u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r32u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r32u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r32u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r32u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r32u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r32u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r32u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r32u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r32u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r32u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r64r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r64r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r64r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r64r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r64r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r64r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r64r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r64r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r64s16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r64s16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r64s16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r64s16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r64s32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r64s32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r64s32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r64s32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r64s8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r64s8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r64s8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r64s8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r64u16(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r64u16(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r64u16(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r64u16__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r64u32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r64u32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r64u32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r64u32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8r64u8(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8r64u8(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8r64u8(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8r64u8__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8s16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8s16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8s16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8s16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8s16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8s16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8s16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8s16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8s32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8s32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8s32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8s32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8s32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8s32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8s32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8s32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8s8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8s8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8s8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8s8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8s8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8s8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8s8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8s8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8u16r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8u16r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8u16r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8u16r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8u16r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8u16r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8u16r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8u16r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8u32r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8u32r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8u32r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8u32r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8u32r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8u32r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8u32r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8u32r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8u8r32(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8u8r32(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8u8r32(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8u8r32__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTable2_getAt_u8u8r64(CT,X,Y)       ESDL_Linear_CharTable2_getAt_u8u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_CharTableFixed2_getAt_u8u8r64(CT,X,Y)  ESDL_Linear_CharTableFixed2_getAt_u8u8r64__INVALID_TYPE_COMBINATION
#define ESDL_Linear_GroupTable2_getAt_u8u8r64(GT,idx_X,deltaX,distX,xVecLen,idx_Y,deltaY,distY,yVecLen) \
    ESDL_Linear_GroupTable2_getAt_u8u8r64__INVALID_TYPE_COMBINATION

#ifdef __cplusplus
}
#endif

#endif /* ESDL_LINEAR_INTERPOLATION_H */
