package SystemLib.CounterTimer;
import SystemLib.Miscellaneous.DeltaTimeService;

/**
 * StopWatchEnabled increments the time counter by one dT. This timer must be enabled explicitly.
 */

class StopWatchEnabled  {
	real timeCounter = 0.0;
	/** If enable is TRUE, the time counter is incremented by dT. */
	@generated("blockdiagram", "4dc078bb")
	public void compute(boolean in enable) {
		if (enable) {
			timeCounter = (DeltaTimeService.deltaT + timeCounter); // Main/compute 1/if-then 1
		} // Main/compute 1
	}

	/** The time counter value, i.e. the time elapsed since the last start and while enabled was TRUE is returned. */
	@no_side_effect
	@generated("blockdiagram", "8e04be7f")
	public real value() {
		return timeCounter; // Main/value 1
	}
	/** If initEnable is TRUE, the time internal counter is set to zero. */
	@generated("blockdiagram", "48bb086d")
	public void reset(boolean in initEnable) {
		if (initEnable) {
			timeCounter = 0.0; // Main/reset 1/if-then 1
		} // Main/reset 1
	}
}