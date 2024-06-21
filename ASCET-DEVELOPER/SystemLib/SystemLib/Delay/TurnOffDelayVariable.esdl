package SystemLib.Delay;
import SystemLib.Miscellaneous.DeltaTimeService;

	/** 
	 * TurnOffDelay delays a falling edge of the input signal. 
	 * The duration of the delay can be modified at runtime via the Time variable.
	 */
class TurnOffDelayVariable  {
	boolean outbit = false;
	real time = 0.0;

	/** A falling edge of the input signal is delayed. 
	 * If the signal flips from TRUE to FALSE, a timer is started. 
	 * On being FALSE the timer is incremented by dT and is compared to delayTime. 
	 * If the input signal is TRUE, the timer is reset.
	 */
	@generated("blockdiagram", "f80be585")
	public void compute(boolean in signal, real in delayTime) {
		if (signal) {
			time = 0.0; // Main/compute 1/if-then 1
			outbit = true; // Main/compute 1/if-then 2
		} else {
			if (time < delayTime) {
				time = (time + DeltaTimeService.deltaT); // Main/compute 1/if-else 1/if-then 1
			} else {
				outbit = false; // Main/compute 1/if-else 1/if-else 1
			} // Main/compute 1/if-else 1
		} // Main/compute 1
	}

	/** TRUE is returned if the input signal is TRUE or the timer has not exceeded delayTime. Otherwise, FALSE is returned. */

	@no_side_effect
	@generated("blockdiagram", "c2a98edf")
	public boolean value() {
		return outbit; // Main/value 1
	}
}