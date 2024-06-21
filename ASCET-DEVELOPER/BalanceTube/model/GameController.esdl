package model;

import SystemLib.Miscellaneous.EdgeRising;
import SystemLib.CounterTimer.Timer;
import SystemLib.CounterTimer.StopWatch;

class GameController {

	Timer timer;
	StopWatch stopWatch;
	EdgeRising edgeDetect;
	characteristic real gameTime = 120.0;
	characteristic real scoringZone = 0.2;
	@set
	private real ballPosition = 0.0;
	@set
	private boolean startGame = false;
	@get
	private real score = 0.0;

	@no_side_effect
	boolean isInScoringZone() {
		return(abs(ballPosition - 0.5) <= (scoringZone / 2.0));
	}

	boolean isStartGameButtonPushed() {
		edgeDetect.compute(startGame);
		return edgeDetect.value();
	}

	@no_side_effect
	public GameControllerStatemachineStates gameState() {
		return EvaluatorStatemachine.getState();
	}

	@no_side_effect
	public real getTime() {
		return timer.getTime() / gameTime;
	}

	boolean isCanceled() {
		if ((gameTime - timer.getTime()) <= 2.0) {
			return false;
		}
		edgeDetect.compute(startGame);
		return edgeDetect.value();
	}

	@generated("statemachine", "000000")
	public void periodicTrigger() triggers EvaluatorStatemachine;

	@generated("statemachine", "bdee0ede")
	statemachine EvaluatorStatemachine default trigger periodicTrigger using GameControllerStatemachineStates {
		start Idle;

		state Idle {
			transition isStartGameButtonPushed() to GameRunning;
		}

		state GameRunning {
			entry {
				timer.begin(gameTime);
				stopWatch.reset();
				score = 0.0;
			}
			static {
				timer.compute();
			}
			transition timer.isElapsed() to Idle;
			transition isCanceled() to Idle;
			start NotInScoringZone;

			state IncreaseScore {
				static {
					stopWatch.compute();
					score = stopWatch.value();
				}
				transition !isInScoringZone() to NotInScoringZone;
			}

			state NotInScoringZone {
				transition isInScoringZone() to IncreaseScore;
			}
		}
	}
}

@generated("statemachine", "000000")
type GameControllerStatemachineStates is enum {
	Idle,
	GameRunning,
	NotInScoringZone,
	IncreaseScore
};