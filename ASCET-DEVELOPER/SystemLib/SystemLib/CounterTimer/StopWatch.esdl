package SystemLib.CounterTimer;
import SystemLib.Miscellaneous.DeltaTimeService;

/**
 * StopWatch increments the time counter by one dT.
 */
class StopWatch  {
	real timeCounter = 0.0;
	/** The time counter is incremented by dT. */
	@generated("blockdiagram", "67eaa79a")
	public void compute() {
		timeCounter = (DeltaTimeService.deltaT + timeCounter); // Main/compute 1
	}

	/** The time counter value, i.e. the time elapsed since the last start, is returned. */

	@no_side_effect
	@generated("blockdiagram", "791bab3d")
	public real value() {
		return timeCounter; // Main/value 1
	}
	/** The time counter is set to zero. */
	@generated("blockdiagram", "fe5a0d66")
	public void reset() {
		timeCounter = 0.0; // Main/reset 1
	}
}