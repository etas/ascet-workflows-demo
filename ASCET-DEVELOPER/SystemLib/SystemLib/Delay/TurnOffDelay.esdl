package SystemLib.Delay;
import SystemLib.Miscellaneous.DeltaTimeService;

/** TurnOffDelay delays a falling edge of the input signal.
*/
class TurnOffDelay {
	boolean buffer = false;
	real time = 0.0;

	/** A falling edge of the input signal is delayed. If the signal flips from TRUE to FALSE, a timer is started. 
	 * On being FALSE the timer is incremented by dT and is compared to delayTime.
	 * If the input signal is TRUE, the timer is reset. */
	@generated("blockdiagram", "a0be5c2c")
	public void compute(boolean in signal, real in delayTime) {
		real memloc = 0.0;
		memloc = time; // Main/compute 1
		if (signal) {
			time = delayTime; // Main/compute 2/if-then 1
		} else {
			if (memloc > 0.0) {
				time = (time - DeltaTimeService.deltaT); // Main/compute 2/if-else 1/if-then 1
			} // Main/compute 2/if-else 1
		} // Main/compute 2
		buffer = (signal || (memloc > 0.0)); // Main/compute 3
	}

	/** TRUE is returned if the input signal is TRUE or the timer has not exceeded delayTime. Otherwise, FALSE is returned. */

	@no_side_effect
	@generated("blockdiagram", "841dfd85")
	public boolean value() {
		return buffer; // Main/value 1
	}
}