package SystemLib.Miscellaneous;

/** EdgeBi detects a bidirectional edge of the logical input signal.
*/
class EdgeBi
using Impl {
	boolean buffer = false;
	boolean oldSignal = false;

	/** The input signal is compared to the previous input signal. */
	@generated("blockdiagram", "bceb06cb")
	public void compute(boolean in signal) {
		buffer = (signal != oldSignal); // Main/compute 1
		oldSignal = signal; // Main/compute 2
	}

	/** TRUE is returned, if the input signal and the previous input signal differ. Otherwise, FALSE is returned. */

	@no_side_effect
	@generated("blockdiagram", "ce096eb4")
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