package SystemLib.CounterTimer;

/** 
 * CountDownEnabled decrements the counter and signals when the counter has reached zero. 
 * This counter must be enabled explicitly.
*/
class CountDownEnabled
using Impl {
	CounterType counter = 0;

	/** If enable is TRUE, the counter is decremented by one. */
	@generated("blockdiagram", "ca78507d")
	public void compute(boolean in enable) {
		if (enable) {
			if (!(counter == 0)) {
				counter = (counter - 1); // Main/compute 1/if-then 1/if-then 1
			} // Main/compute 1/if-then 1
		} // Main/compute 1
	}

	/** TRUE is returned if the counter is greater than zero. Otherwise, FALSE is returned. */
	@no_side_effect
	@generated("blockdiagram", "3a6ecd88")
	public boolean value() {
		return(counter > 0); // Main/value 1
	}

	/** The counter is set to the start value. */
	@generated("blockdiagram", "31534405")
	public void begin(CounterType in startValue) {
		counter = startValue; // Main/begin 1
	}
	representation Impl {
		represent counter using {
			datatype = uint32;
		};
		represent compute.enable using {
			datatype = sint8;
		};
		represent value return using {
			datatype = sint8;
		};
		represent begin.startValue using {
			datatype = uint32;
		};
	}
}