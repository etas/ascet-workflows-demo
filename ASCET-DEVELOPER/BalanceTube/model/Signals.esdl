package model;

data interface Signals using stm32f334r8 {
	
	real score = 0.0;
	real ballPosition = 0.0;
	real handPosition = 0.0;
	real servoPosition = 0.5;
	
	boolean startGameButton = false;
	boolean autoModeButton = false;
	
	RgbLedRing ledRing = {
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 },
		{ 0.0, 0.0, 0.0 }
	};
	
	representation stm32f334r8 {
		represent ledRing using stm32f334r8;
	}
}