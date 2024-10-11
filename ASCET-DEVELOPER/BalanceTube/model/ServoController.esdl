package model;

import SystemLib.Miscellaneous.EdgeRising;
import SystemLib.Miscellaneous.DeltaTimeService;

// Servo icon created by Freepik - Flaticon ( "https://www.flaticon.com/free-icons/servo" )

class ServoController {

	@set
	GameControllerStatemachineStates gameState = GameControllerStatemachineStates.Idle;
	EdgeRising edgeDetect;
	@set
	boolean switchMode = false;
	@set
	private real ballPosition = 0.0;
	@set
	private real handPosition = 0.0;
	@get
	private real servoPosition = 0.0;
	characteristic real kp = 0.22;
	characteristic real ki = 0.22;
	boolean doIntegrate = true;
	real error = 0.0;
	real integral = 0.0;
	real lastValue = 0.0;
	characteristic real kd = 0.44;

	@no_side_effect
	boolean isGameIdle() {
		return gameState == GameControllerStatemachineStates.Idle;
	}

	@no_side_effect
	boolean isGameRunning() {
		return !isGameIdle();
	}

	boolean switchModeButtonPushed() {
		edgeDetect.compute(switchMode);
		return edgeDetect.value();
	}

	@generated("statemachine", "000000")
	public void periodicTrigger() triggers ServoControllerStatemachine;

	@generated("blockdiagram", "9d4a483c")
	public void autoMode() {
		error = (0.5 - ballPosition); // Main/autoMode 1
		if (doIntegrate) {
			integral = ((ki * error * DeltaTimeService.deltaT) + integral); // Main/autoMode 2/if-then 1
		} // Main/autoMode 2
		doIntegrate = ((servoPosition < 0.9) && (servoPosition > 0.1)); // Main/autoMode 3
		servoPosition = min(1.0, max((0.5 + ((kp * error) + integral + (((error - lastValue) * kd) / DeltaTimeService.deltaT))), 0.0)); // Main/autoMode 4
		lastValue = error; // Main/autoMode 5
	}

	@generated("statemachine", "f58535b1")
	statemachine ServoControllerStatemachine using ServoControllerStatemachineStates {
		start IdlePosition;

		state IdlePosition {
			static {
				servoPosition = 0.5;
			}
			transition isGameRunning() to ControlPosition;
		}

		state ControlPosition {
			transition isGameIdle() to IdlePosition;
			start ManualMode;

			state AutoMode {
				static {
					autoMode();
				}
				exit {
					integral = 0.0;
				}
				transition switchModeButtonPushed() to ManualMode;
			}

			state ManualMode {
				static {
					servoPosition = handPosition;
				}
				transition switchModeButtonPushed() to AutoMode;
			}
		}
	}
}

@generated("statemachine", "000000")
type ServoControllerStatemachineStates is enum {
	ManualMode,
	AutoMode,
	ControlPosition,
	IdlePosition
};
