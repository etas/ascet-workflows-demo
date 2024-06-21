package SystemLib.CounterTimer;

/**
 * Counter increments the counter by one.
 */ 

type CounterType is integer 0 .. 0xFFFFFFFF;

class Counter
using Impl {
	CounterType counter = 0;

	/** The counter is incremented by one. */
	@generated("blockdiagram", "3e5ebcb5")
	public void compute() {
		counter = (1 + counter); // Main/compute 1
	}

	/** The counter value is returned. */
	@no_side_effect
	@generated("blockdiagram", "8b684a9c")
	public CounterType value() {
		return counter; // Main/value 1
	}

	/** The counter is set to zero. */
	@generated("blockdiagram", "948c0408")
	public void reset() {
		counter = 0; // Main/reset 1
	}
	representation Impl {
		represent counter using {
			datatype = uint32;
		};
		represent value return using {
			datatype = uint32;
		};
	}
}