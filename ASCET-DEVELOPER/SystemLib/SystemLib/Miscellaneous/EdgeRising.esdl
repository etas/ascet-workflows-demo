package SystemLib.Miscellaneous;

/** EdgeRising detects a rising edge of the logical input signal. */
class EdgeRising
using Impl {
	boolean buffer = false;
	boolean oldSignal = true;

	/** The input signal is compared to the previous input signal. */
	@generated("blockdiagram", "27567845")
	public void compute(boolean in signal) {
		buffer = (signal && (!oldSignal)); // Main/compute 1
		oldSignal = signal; // Main/compute 2
	}

	/** TRUE is returned, if the input signal is high and the previous input signal was low. Otherwise, FALSE is returned. */

	@no_side_effect
	@generated("blockdiagram", "d46e731f")
	public boolean value() {
		return buffer; // Main/value 1
	}
	representation Impl {
		represent buffer using {
			datatype = uint8;
		};
		represent oldSignal using {
			datatype = uint8;
		};
		represent value return using {
			datatype = uint8;
		};
		represent compute.signal using {
			datatype = uint8;
		};
	}
}