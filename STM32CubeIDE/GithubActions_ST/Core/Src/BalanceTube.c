#include "main.h"
#include "vl53l0x_def.h"
#include "vl53l0x_api.h"
#include "vl53l0x_tof.h"
#include "ht16k33.h"
#include "BalanceTube.h"
#include "model_Signals_stm32f334r8.h"

#define PROXIMITY_I2C_ADDRESS         ((uint16_t)0x0052)
#define VL53L0X_ID                    ((uint16_t)0xEEAA)

extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;

extern void Task_5ms();


static void initializeHandDistanceSensor();
static void initializeBallDistanceSensor();
static void initializeServoMotor();
static void initializeDisplay();
static void ReadButtons();
static void ReadBallPosition();
static void ReadHandPosition();
static void ControlServo();
static void ControlDisplay();
static void ControlLedRing();

static void VL53L0X_PROXIMITY_Init(void);
static uint16_t VL53L0X_PROXIMITY_GetDistance(void);

double map(double x, double in_min, double in_max, double out_min,
		double out_max);

volatile uint8_t balanceTube_doStep = 0;
VL53L0X_Dev_t Dev = { .I2cHandle = &hi2c1, .I2cDevAddr = PROXIMITY_I2C_ADDRESS };


void initializeBalanceTube() {
	HAL_TIM_Base_Start_IT(&htim6);

	initializeHandDistanceSensor();
	initializeBallDistanceSensor();
	initializeServoMotor();
	initializeDisplay();

}

void runBalanceTube() {
	if (balanceTube_doStep == 1) {

		ReadHandPosition();
		ReadBallPosition();
		ReadButtons();

		Task_5ms();

		ControlServo();
		ControlDisplay();
		ControlLedRing();

		balanceTube_doStep = 0;
	}
}

void ReadButtons() {
	model_Signals_autoModeButton = !HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin);
	model_Signals_startGameButton = !HAL_GPIO_ReadPin(BTN2_GPIO_Port, BTN2_Pin);
}

void ControlDisplay() {
	seg7_displayIntWithPoint((int) (model_Signals_score * 10.0), 2);
}

void initializeDisplay() {
	seg7_displayOn();
	seg7_displayIntWithPoint(0000, 2);
}

void initializeBallDistanceSensor() {
	VL53L0X_PROXIMITY_Init();
	VL53L0X_SetDeviceMode(&Dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
	VL53L0X_StartMeasurement(&Dev);
}

void initializeHandDistanceSensor() {
	/* USER CODE BEGIN 2 */
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start(&hadc1);
}

void initializeServoMotor() {
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

double map(double x, double in_min, double in_max, double out_min,
		double out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/////////////////////////////////////////////////////////////////////////////////
void ControlServo() {
	const double min_us = 1600.0;
	const double max_us = 1900.0;

	static double time_us = 1750.0;
	time_us = map(model_Signals_servoPosition, 0.0, 1.0, min_us, max_us);
	if (time_us >= max_us) {
		time_us = max_us;
	}
	if (time_us <= min_us) {
		time_us = min_us;
	}

	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, (uint16_t ) (time_us * 3.2));
}
/////////////////////////////////////////////////////////////////////////////////

typedef union {
	struct {
		uint8_t b;
		uint8_t r;
		uint8_t g;
	} color;
	uint32_t data;
} PixelRGB_t;

// ARR = 76
#define NEOPIXEL_ZERO	25 // (76 + 1) * 0.32
#define NEOPIXEL_ONE	49 // (76 + 1) * 0.64
#define NUM_PIXELS		12
#define DMA_BUFF_SIZE (NUM_PIXELS * 24) + 1

PixelRGB_t pixel[NUM_PIXELS] = {0};
uint32_t dmaBuffer[DMA_BUFF_SIZE] = {0};
uint32_t *pBuff;
int j;
int k = 0;

void ControlLedRing() {
	for (int i = 0; i < NUM_PIXELS; i++) {
		pixel[i].color.r = model_Signals_ledRing[i].red;
		pixel[i].color.g = model_Signals_ledRing[i].green;
		pixel[i].color.b = model_Signals_ledRing[i].blue;
	}

	pBuff = dmaBuffer;
	for (int i = 0; i < NUM_PIXELS; i++) {
		for (j = 23; j >= 0; j--) {
			if ((pixel[i].data >> j) & 0x01) {
				*pBuff = NEOPIXEL_ONE;
			} else {
				*pBuff = NEOPIXEL_ZERO;
			}
			pBuff++;
		}
	}
	dmaBuffer[DMA_BUFF_SIZE - 1] = 0; // last element must be 0!
	HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, dmaBuffer, DMA_BUFF_SIZE);
}

/////////////////////////////////////////////////////////////////////////////////

static void VL53L0X_PROXIMITY_Init(void) {
	uint16_t vl53l0x_id = 0;
	VL53L0X_DeviceInfo_t VL53L0X_DeviceInfo;

	/* Initialize IO interface */
	memset(&VL53L0X_DeviceInfo, 0, sizeof(VL53L0X_DeviceInfo_t));

	if (VL53L0X_ERROR_NONE
			== VL53L0X_GetDeviceInfo(&Dev, &VL53L0X_DeviceInfo)) {
		if (VL53L0X_ERROR_NONE
				== VL53L0X_RdWord(&Dev, VL53L0X_REG_IDENTIFICATION_MODEL_ID,
						(uint16_t*) &vl53l0x_id)) {
			if (vl53l0x_id == VL53L0X_ID) {
				if (VL53L0X_ERROR_NONE == VL53L0X_DataInit(&Dev)) {
					Dev.Present = 1;
					SetupSingleShot(&Dev);
				} else {
					printf("VL53L0X Time of Flight Failed to send its ID!\n");
				}
			}
		} else {
			printf("VL53L0X Time of Flight Failed to Initialize!\n");
		}
	} else {
		printf("VL53L0X Time of Flight Failed to get infos!\n");
	}
}

static uint16_t VL53L0X_PROXIMITY_GetDistance(void) {
	VL53L0X_RangingMeasurementData_t RangingMeasurementData;
	VL53L0X_GetRangingMeasurementData(&Dev, &RangingMeasurementData);
	return RangingMeasurementData.RangeMilliMeter;
}

#define BUF_SIZE 32
#define PARAMS 0 // TODO
void ReadBallPosition() {
#if PARAMS == 0
	const double ball_pos_end = 60.0;
	const double ball_pos_mid = 300.0;
	const double ball_pos_start = 470.0;
#elif PARAMS == 1
	const double ball_pos_end = 42.0;
	const double ball_pos_mid = 282.0;
	const double ball_pos_start = 471.0;
#endif

	static double buf[BUF_SIZE] = { 0.0 };
	static uint8_t i = 0;

	uint16_t distance_ball = VL53L0X_PROXIMITY_GetDistance();
	buf[i] = (double) distance_ball;
	i++;
	if (i >= BUF_SIZE) {
		i = 0;
	}
	double sum = 0.0;
	for (uint8_t j = 0; j < BUF_SIZE; j++) {
		sum += buf[j];
	}
	double dist = (sum / ((double) BUF_SIZE));
	if (dist >= ball_pos_mid) {
		model_Signals_ballPosition = map(dist, ball_pos_start, ball_pos_mid,
				0.0, 0.5);
	} else {
		model_Signals_ballPosition = map(dist, ball_pos_mid, ball_pos_end, 0.5,
				1.0);
	}
	if (model_Signals_ballPosition >= 1.0) {
		model_Signals_ballPosition = 1.0;
	}
	if (model_Signals_ballPosition <= 0.0) {
		model_Signals_ballPosition = 0.0;
	}
}



void ReadHandPosition() {
	HAL_ADC_PollForConversion(&hadc1, 10);
	model_Signals_adcHandPosition = (double) HAL_ADC_GetValue(&hadc1);
}

/////////////////////////////////////////////////////////////////////////////////

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim) {
	HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
}

/////////////////////////////////////////////////////////////////////////////////
