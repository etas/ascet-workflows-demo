package SystemLib.Miscellaneous;

/** EdgeFalling detects a falling edge of the logical input signal. */
class EdgeFalling
using Impl {
	boolean buffer = false;
	boolean oldSignal = false;

	/** The input signal is compared to the previous input signal. */
	@generated("blockdiagram", "4bcb6614")
	public void compute(boolean in signal) {
		buffer = ((!signal) && oldSignal); // Main/compute 1
		oldSignal = signal; // Main/compute 2
	}

	/** TRUE is returned, if the input signal is low and the previous input signal was high. Otherwise, FALSE is returned. */

	@no_side_effect
	@generated("blockdiagram", "743a2058")
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