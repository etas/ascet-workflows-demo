package SystemLib.Delay;

/** DelaySignalEnabled delays its input signal by one evaluation step. It must be enabled explicitly.
*/
class DelaySignalEnabled
using Impl {
	boolean memory1 = false;
	boolean memory2 = false;

	/** If enable is TRUE, the input signal is buffered. */
	@generated("blockdiagram", "766b38ef")
	public void compute(boolean in signal, boolean in enable) {
		if (enable) {
			memory2 = memory1; // Main/compute 1/if-then 1
			memory1 = signal; // Main/compute 1/if-then 2
		} // Main/compute 1
	}

	/** The buffered signal is returned, thus the input signal is delayed by one step. */

	@no_side_effect
	@generated("blockdiagram", "902eaa7a")
	public boolean value() {
		return memory2; // Main/value 1
	}

	/** If initEnable is TRUE, initValue is buffered. */
	@generated("blockdiagram", "7f264157")
	public void reset(boolean in initValue, boolean in initEnable) {
		if (initEnable) {
			memory1 = initValue; // Main/reset 1/if-then 1
			memory2 = memory1; // Main/reset 1/if-then 2
		} // Main/reset 1
	}
	representation Impl {
		represent compute.enable using {
			datatype = sint8;
		};
		represent reset.initEnable using {
			datatype = sint8;
		};
		represent reset.initValue using {
			datatype = sint8;
		};
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