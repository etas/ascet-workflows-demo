package SystemLib.CounterTimer;

import SystemLib.Miscellaneous.DeltaTimeService;

/** Timer decrements the time counter by dT and signals when the time counter has reached zero. It is not retriggerable. */
class Timer {

	real timeCounter = 0.0;

	/** The time counter is decremented by dT. */
	@generated("blockdiagram", "29e4f88e")
	public void compute() {
		timeCounter = max((timeCounter - DeltaTimeService.deltaT), 0.0); // Main/compute 1
	}

	/** TRUE is returned if the time counter value is greater than zero. Otherwise, FALSE is returned. */
	@no_side_effect
	@generated("blockdiagram", "8983dd8d")
	public boolean isElapsed() {
		return(timeCounter <= 0.0); // Main/isElapsed 1
	}

	/** The time counter is set to startTime if the time counter value was previously less than or equal to zero. */
	@generated("blockdiagram", "76573912")
	public void begin(real in startTime) {
		timeCounter = startTime; // Main/begin 1
	}

	@no_side_effect
	@generated("blockdiagram", "7437b77b")
	public real getTime() {
		return timeCounter; // Main/getTime 1
	}
}