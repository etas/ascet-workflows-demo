package SystemLib.Delay;
import SystemLib.Miscellaneous.DeltaTimeService;

/** TurnOnDelayVariable delays a rising edge of the input signal. The duration of the delay can be modified at runtime via the Time variable.
*/
class TurnOnDelayVariable  {
	boolean outbit = false;
	real time = 0.0;

	/** A rising edge of the input signal is delayed. 
	 * If the signal flips from FALSE to TRUE, a timer is started. 
	 * On being TRUE the timer is incremented by dT and is compared to delayTime. 
	 * If the input signal is FALSE, the timer is reset.
	 */
	@generated("blockdiagram", "cc7e5329")
	public void compute(boolean in signal, real in delayTime) {
		if (signal) {
			if (time < delayTime) {
				time = (time + DeltaTimeService.deltaT); // Main/compute 1/if-then 1/if-then 1
			} else {
				outbit = true; // Main/compute 1/if-then 1/if-else 1
			} // Main/compute 1/if-then 1
		} else {
			time = 0.0; // Main/compute 1/if-else 1
			outbit = false; // Main/compute 1/if-else 2
		} // Main/compute 1
	}

	/** FALSE is returned if the input signal is FALSE, or the timer has not exceeded delayTime. Otherwise, TRUE is returned. */

	@no_side_effect
	@generated("blockdiagram", "1439d6b4")
	public boolean value() {
		return outbit; // Main/value 1
	}
}