/*
 * sevensegment.c
 *
 *  Created on: 20.05.2022
 *      Author: lenni
 */

#include "ht16k33.h"

// Commands
#define HT16K33_ON              0x21  // 0=off 1=on
#define HT16K33_STANDBY         0x20  // bit xxxxxxx0

// bit pattern 1000 0xxy
// y    =  display on / off
// xx   =  00=off     01=2Hz     10=1Hz     11=0.5Hz
#define HT16K33_DISPLAYON       0x81
#define HT16K33_DISPLAYOFF      0x80
#define HT16K33_BLINKON0_5HZ    0x87
#define HT16K33_BLINKON1HZ      0x85
#define HT16K33_BLINKON2HZ      0x83
#define HT16K33_BLINKOFF        0x81

// bit pattern 1110 xxxx
// xxxx    =  0000 .. 1111 (0 - F)
#define HT16K33_BRIGHTNESS      0xE0

//
//  HEX codes 7 segment
//
//      01
//  20      02
//      40
//  10      04
//      08
//
const uint8_t charmap[] = {
		0x3F,   // 0
		0x06,   // 1
		0x5B,   // 2
		0x4F,   // 3
		0x66,   // 4
		0x6D,   // 5
		0x7D,   // 6
		0x07,   // 7
		0x7F,   // 8
		0x6F,   // 9
		0x77,   // A
		0x7C,   // B
		0x39,   // C
		0x5E,   // D
		0x79,   // E
		0x71,   // F
		0x00,   // space
		0x40,   // minus
		0x30,   // I
		0x38,   // L
};

volatile uint8_t _displayCache[5];   	//cache for performance
volatile uint8_t _digits = 4;			//number of digits to display (0-4)
volatile uint8_t _bright = 15;			//current brightness (0-15)

//##### BEGIN: I2C-WRITE-FUNCTIONS (PRIVATE) #####
// sends complete cached data per i2c
void _refresh() {
	uint8_t pData[2];

	for (uint8_t pos = 0; pos < 4; pos++) {
		pData[0] = pos * 2;
		pData[1] = _displayCache[pos];

		HAL_I2C_Master_Transmit(&HT16K33_I2C_PORT, HT16K33_I2C_ADDR << 1, pData,2, HAL_MAX_DELAY);
	}
}

// sends given command per i2c
void _writeCmd(uint8_t cmd) {
	HAL_I2C_Master_Transmit(&HT16K33_I2C_PORT, HT16K33_I2C_ADDR << 1, &cmd, 1, HAL_MAX_DELAY);
}

// sends value (mask) for specific position per i2c, if different from cached value
void _writePos(uint8_t pos, uint8_t mask) {
	if (_displayCache[pos] == mask)
		return;

	uint8_t pData[2];
	pData[0] = pos * 2;
	pData[1] = mask;

	HAL_I2C_Master_Transmit(&HT16K33_I2C_PORT, HT16K33_I2C_ADDR << 1, pData, 2, HAL_MAX_DELAY);
	_displayCache[pos] = mask;	// update value in cache
}

// update mask to display point at given location, before sending it per i2c
void _writePosPoint(uint8_t pos, uint8_t mask, int point) {
	if (point)
		mask |= 0x80;
	else
		mask &= 0x7F;

	_writePos(pos, mask);
}

//##### END: I2C-WRITE-FUNCTIONS #####
//####################################
//##### BEGIN: CONTROL-FUNCTIONS #####

void seg7_init() {
	seg7_reset();
	seg7_displayOn();
}

void seg7_reset() {
	seg7_displayClear();
	seg7_clearCache();
	seg7_setBlinkRate(0);
	seg7_setDigits(4);
	seg7_setBrightness(15);
}

void seg7_clearCache() {
	for (uint8_t i = 0; i < 5; i++) {
		_displayCache[i] = SEG7_NONE;
	}
}

void seg7_refresh() {
	_refresh();
}

void seg7_displayOn() {
	_writeCmd(HT16K33_ON);
	_writeCmd(HT16K33_DISPLAYON);
	seg7_setBrightness(_bright);
}

void seg7_displayOff() {
	_writeCmd(HT16K33_DISPLAYOFF);
	_writeCmd(HT16K33_STANDBY);
}

void seg7_setBlinkRate(uint8_t value) {
	if (value > 0x03) {
		value = 0x00;
	}

	_writeCmd(HT16K33_BLINKOFF | (value << 1));
}

void seg7_setBrightness(uint8_t value) {
	if (value == _bright)
		return;

	_bright = value;

	if (_bright > 0x0F)
		_bright = 0x0F;

	_writeCmd(HT16K33_BRIGHTNESS | _bright);
}

void seg7_setDigits(uint8_t value) {
	_digits = (value > 4) ? 4 : value;
}

//#####  END: CONTROL-FUNCTIONS  #####
//####################################
//##### BEGIN: DISPLAY-FUNCTIONS #####

void seg7_displayClear() {
	uint8_t arr[4] = { SEG7_SPACE, SEG7_SPACE, SEG7_SPACE, SEG7_SPACE };
	seg7_display(arr);
	seg7_displayColon(0);
}

int seg7_displayInt(int n) {
	int inRange = ((-1000 < n) && (n < 10000));
	int neg = (n < 0);

	uint8_t arr[4], h, l;

	if (neg)
		n = -n;

	h = n / 100;
	l = n - h * 100;
	arr[0] = h / 10;
	arr[1] = h - arr[0] * 10;
	arr[2] = l / 10;
	arr[3] = l - arr[2] * 10;

	if (neg) {
		if (_digits >= 3) {
			arr[0] = SEG7_MINUS;
		} else {
			int i = 0;
			for (i = 0; i < (4 - _digits); i++) {
				if (arr[i] != 0) {
					break;
				}
				arr[i] = SEG7_SPACE;
			}
			arr[i - 1] = SEG7_MINUS;
		}
	}

	seg7_display(arr);

	return inRange;
}

int seg7_displayIntWithPoint(int n, uint8_t point) {
	int inRange = ((-1000 < n) && (n < 10000));
	int neg = (n < 0);

	uint8_t arr[4], h, l;

	if (neg)
		n = -n;

	h = n / 100;
	l = n - h * 100;
	arr[0] = h / 10;
	arr[1] = h - arr[0] * 10;
	arr[2] = l / 10;
	arr[3] = l - arr[2] * 10;

	if (neg) {
		if (_digits >= 3) {
			arr[0] = SEG7_MINUS;
		} else {
			int i = 0;
			for (i = 0; i < (4 - _digits); i++) {
				if (arr[i] != 0) {
					break;
				}
				arr[i] = SEG7_SPACE;
			}
			arr[i - 1] = SEG7_MINUS;
		}
	}

	seg7_displayPoint(arr, point);

	return inRange;
}

int seg7_displayTime(uint8_t left, uint8_t right, int colon) {
	int inRange = ((left < 100) && (right < 100));
	uint8_t arr[4];

	arr[0] = left / 10;
	arr[1] = left - arr[0] * 10;

	arr[2] = right / 10;
	arr[3] = right - arr[2] * 10;

	seg7_display(arr);
	seg7_displayColon(colon);

	return inRange;
}

void seg7_display(uint8_t *array) {
	for (uint8_t i = 0; i < (4 - _digits); i++) {
		if (array[i] != 0) {
			break;
		}
		array[i] = SEG7_SPACE;
	}

	_writePos(0, charmap[array[0]]);
	_writePos(1, charmap[array[1]]);
	_writePos(3, charmap[array[2]]);
	_writePos(4, charmap[array[3]]);
}

void seg7_displayPoint(uint8_t *array, uint8_t point) {
	_writePosPoint(0, charmap[array[0]], point == 0);
	_writePosPoint(1, charmap[array[1]], point == 1);
	_writePosPoint(3, charmap[array[2]], point == 2);
	_writePosPoint(4, charmap[array[3]], point == 3);
}

void seg7_displayColon(uint8_t on) {
	_writePos(2, on ? 2 : 0);
}

void seg7_displayRaw(uint8_t *array, int colon) {
	_writePos(0, array[0]);
	_writePos(1, array[1]);
	_writePos(3, array[2]);
	_writePos(4, array[3]);
	_writePos(2, colon ? 255 : 0);
}

//##### END: DISPLAY-FUNCTIONS #####
