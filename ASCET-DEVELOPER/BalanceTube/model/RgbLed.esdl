package model;

type RgbLed is struct {
	real red;
	real green;
	real blue;
	
	representation stm32f334r8 {
		represent red, green, blue using {
			range = 0 .. 255;
			delta = 1.0 / 255.0;
			datatype = uint8;
		};
	}
};

type RgbLedRing is array [12] of RgbLed;