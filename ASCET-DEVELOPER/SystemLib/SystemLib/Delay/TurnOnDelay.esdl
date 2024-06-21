package SystemLib.Delay;
import SystemLib.Miscellaneous.DeltaTimeService;

/** TurnOnDelay delays a rising edge of the input signal. */
class TurnOnDelay {
	boolean buffer = false;
	real time = 0.0;

	/** A rising edge of the input signal is delayed. 
	 * If the signal flips from FALSE to TRUE, a timer is started. 
	 * On being TRUE the timer is incremented by dT and is compared to delayTime. 
	 * If the input signal is FALSE, the timer is reset.
	 */
	@generated("blockdiagram", "7b0d6d9a")
	public void compute(boolean in signal, real in delayTime) {
		real memloc = 0.0;
		memloc = time; // Main/compute 1
		if (signal) {
			if (memloc > 0.0) {
				time = (time - DeltaTimeService.deltaT); // Main/compute 2/if-then 1/if-then 1
			} // Main/compute 2/if-then 1
		} else {
			time = delayTime; // Main/compute 2/if-else 1
		} // Main/compute 2
		buffer = (signal && (memloc <= 0.0)); // Main/compute 3
	}

	/** FALSE is returned if the input signal is FALSE, or the timer has not exceeded delayTime. Otherwise, TRUE is returned. */

	@no_side_effect
	@generated("blockdiagram", "5c7ec4d6")
	public boolean value() {
		return buffer; // Main/value 1
	}
}