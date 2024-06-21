package model;

import SystemLib.CounterTimer.StopWatch;

class LedController
using stm32f334r8 {

	@set
	GameControllerStatemachineStates gameState = GameControllerStatemachineStates.Idle;
	@set
	private real gameTime = 0.0;
	@get
	private RgbLedRing ledRing = {
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
	private real fadeValue = 0.0;
	StopWatch sw;

	void fadeViolet() {
		sw.compute();
		if (sw.value() <= 2.0) {
			fadeValue = (sw.value() + 0.2) / 2.2;
		} else if (sw.value() <= 4.0) {
			fadeValue = (4.2 - sw.value()) / 2.2;
		} else {
			sw.reset();
		}
		for (i in ledRing.indexRange()) {
			ledRing[i] = {fadeValue, 0.0, fadeValue};
		}
	}

	void indicateGameTime() {
		real mappedTime;
		RgbLed color = {0.0, 0.0, 1.0}; // blue

		if (gameTime <= 0.2) {
			color = {1.0, 0.0, 0.0}; // red
		}

		// e.g., for 12 LEDs: 0.0 .. 12.0
		mappedTime = gameTime * real(ledRing.length());

		for (i in ledRing.indexRange()) {
			real brightness;
			brightness = mappedTime - real(i);
			brightness = min(brightness, 1.0);
			brightness = max(brightness, 0.0);

			ledRing[i].red = color.red * brightness;
			ledRing[i].green = color.green * brightness;
			ledRing[i].blue = color.blue * brightness;
		}
	}

	@no_side_effect
	boolean isGameIdle() {
		return gameState == GameControllerStatemachineStates.Idle;
	}

	@no_side_effect
	boolean isGameRunning() {
		return !isGameIdle();
	}

	@generated("statemachine", "000000")
	public void periodicTrigger() triggers LedControllerStatemachine;

	@generated("statemachine", "3b49ad61")
	statemachine LedControllerStatemachine using LedControllerStatemachineStates {
		start IdleFading;

		state IdleFading {
			static {
				fadeViolet();
			}
			transition isGameRunning() to IndicateGameTime;
		}

		state IndicateGameTime {
			static {
				indicateGameTime();
			}
			transition isGameIdle() to IdleFading;
		}
	}
	representation stm32f334r8 {
		represent ledRing using stm32f334r8;
		represent indicateGameTime.color using stm32f334r8;
	}
}

@generated("statemachine", "000000")
type LedControllerStatemachineStates is enum {
	IdleFading,
	IndicateGameTime
};