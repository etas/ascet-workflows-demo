package SystemLib.CounterTimer;

/** 
 * CountDown decrements the counter and signals when the counter has reached zero.
*/
class CountDown
using Impl {
	CounterType counter = 0;

	/** The counter is decremented by one. */
	@generated("blockdiagram", "265260bc")
	public void compute() {
		if (!(counter == 0)) {
			counter = (counter - 1); // Main/compute 1/if-then 1
		} // Main/compute 1
	}

	/** TRUE is returned if the counter is greater than zero. Otherwise, FALSE is returned. */
	@no_side_effect
	@generated("blockdiagram", "a9986392")
	public boolean value() {
		return(counter > 0); // Main/value 1
	}

	/** The counter is set to the start value. */
	@generated("blockdiagram", "ffa47e9b")
	public void begin(CounterType in startValue) {
		counter = startValue; // Main/begin 1
	}
	representation Impl {
		represent counter using {
			datatype = uint32;
		};
		represent value return using {
			datatype = sint16;
		};
		represent begin.startValue using {
			datatype = uint32;
		};
	}
}