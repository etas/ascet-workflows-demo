package SystemLib.CounterTimer;
import SystemLib.Miscellaneous.DeltaTimeService;

/** TimerRetriggerEnabled decrements the time counter by dT and signals when the time counter has reached zero. It can be retriggered and must be enabled explicitly.
*/
class TimerRetriggerEnabled {
	boolean inOld = true;
	real timeCounter = 0.0;

	/** If enable is TRUE and val has a rising edge, the timer is started, i.e. its counter value is set to the start value. 
	* Otherwise, the time counter is decremented by dT (the time frame). 
	* If enable is FALSE, nothing happens. 
	* */
	@generated("blockdiagram", "c4a0c53a")
	public void compute(boolean in enable, boolean in val, real in startTime) {
		if (enable) {
			timeCounter = max((timeCounter - DeltaTimeService.deltaT), 0.0); // Main/compute 1/if-then 1
		} // Main/compute 1
		if (enable) {
			if (val && (!inOld)) {
				timeCounter = startTime; // Main/compute 2/if-then 1/if-then 1
			} // Main/compute 2/if-then 1
		} // Main/compute 2
		inOld = val; // Main/compute 3
	}

	/** TRUE is returned, if the time counter value is greater than zero. Otherwise, FALSE is returned. */
	@no_side_effect
	@generated("blockdiagram", "fa986249")
	public boolean value() {
		return(timeCounter > 0.0); // Main/value 1
	}
}