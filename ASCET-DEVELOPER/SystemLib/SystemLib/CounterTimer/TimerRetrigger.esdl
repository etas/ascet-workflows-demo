package SystemLib.CounterTimer;
import SystemLib.Miscellaneous.DeltaTimeService;

/** TimerRetrigger decrements the time counter by dT and signals when the time counter has reached zero. It can be retriggered
*/
class TimerRetrigger {
	real timeCounter = 0.0;

	/** The time counter is decremented by dT. */
	@generated("blockdiagram", "763f1a5b")
	public void compute() {
		timeCounter = max((timeCounter - DeltaTimeService.deltaT), 0.0); // Main/compute 1
	}

	/** TRUE is returned, if the time counter value is greater than zero. Otherwise, FALSE is returned. */
	@no_side_effect
	@generated("blockdiagram", "40ac7a31")
	public boolean value() {
		return(timeCounter > 0.0); // Main/value 1
	}

	/** The time counter is set to the start value. */
	@generated("blockdiagram", "43fbd193")
	public void begin(real in startTime) {
		timeCounter = startTime; // Main/begin 1
	}
}