package simulation;
import SystemLib.Transferfunction.Integrator.IntegratorK;
import SystemLib.Miscellaneous.DeltaTimeService;

import model.Signals;

singleton class Stimulator
reads Signals.servoPosition
writes Signals.ballPosition, Signals.handPosition, Signals.startGameButton, Signals.autoModeButton {

	characteristic real handPosition = 0.5;
	characteristic boolean startGameButton = false;
	characteristic boolean autoModeButton = false;

	real ballPosition = 0.0;
	characteristic real velocityCoefficient = 0.05;
	
	boolean rightEdge = false;
	boolean leftEdge = false;
	
	@thread
	public void stimulate() {
		Signals.ballPosition = calcBallPosition();
		Signals.handPosition = handPosition;
		Signals.startGameButton = startGameButton;
		Signals.autoModeButton = autoModeButton;
	}
	
	real calcBallPosition() {
		real x = velocityCoefficient * (Signals.servoPosition - 0.5);
		rightEdge = (ballPosition > 0.9999 && x > 0.0);
		leftEdge = (ballPosition < 0.0001 && x < 0.0);
		if (rightEdge || leftEdge) {
			x = 0.0;
		} else {
			ballPosition = ballPosition + x;
			ballPosition = min(1.0, ballPosition);
			ballPosition = max(0.0, ballPosition);
		}
		return ballPosition;
	}
}
