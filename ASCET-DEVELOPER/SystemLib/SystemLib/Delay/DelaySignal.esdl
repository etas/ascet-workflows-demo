package SystemLib.Delay;

/** DelaySignal delays its input signal by one evaluation step.
*/
class DelaySignal
using Impl {
	boolean memory1 = false;
	boolean memory2 = false;

	/** The input signal is buffered. */
	@generated("blockdiagram", "b2df40bc")
	public void compute(boolean in signal) {
		memory2 = memory1; // Main/compute 1
		memory1 = signal; // Main/compute 2
	}

	/** The buffered signal is returned, thus the input signal is delayed by one step. */

	@no_side_effect
	@generated("blockdiagram", "9fb7b8bd")
	public boolean value() {
		return memory2; // Main/value 1
	}
	representation Impl {
		represent memory1 using {
			datatype = sint8;
		};
		represent memory2 using {
			datatype = sint8;
		};
		represent value return using {
			datatype = sint8;
		};
		represent compute.signal using {
			datatype = sint8;
		};
	}
}