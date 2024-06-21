package model;

singleton class MainClass
writes Signals.score, Signals.servoPosition, Signals.ledRing
reads Signals.ballPosition, Signals.handPosition, Signals.startGameButton, Signals.autoModeButton {

	GameController gameController;
	LedController ledController;
	ServoController servoController;

	@thread
	@generated("blockdiagram", "32cff729")
	public void step() {
		gameController.ballPosition = Signals.ballPosition; // Main/step 1
		gameController.startGame = Signals.startGameButton; // Main/step 2
		gameController.periodicTrigger(); // Main/step 3
		Signals.score = gameController.score; // Main/step 4
		ledController.gameTime = gameController.getTime(); // Main/step 5
		ledController.gameState = gameController.gameState(); // Main/step 6
		ledController.periodicTrigger(); // Main/step 7
		Signals.ledRing = ledController.ledRing; // Main/step 8
		servoController.gameState = gameController.gameState(); // Main/step 9
		servoController.ballPosition = Signals.ballPosition; // Main/step 10
		servoController.handPosition = Signals.handPosition; // Main/step 11
		servoController.switchMode = Signals.autoModeButton; // Main/step 12
		servoController.periodicTrigger(); // Main/step 13
		Signals.servoPosition = servoController.servoPosition; // Main/step 14
	}
	representation stm32f334r8 {
		represent ledController using stm32f334r8;
	}
}