package SystemLib.Memory;

/** RSFlipFlop is a flip flop with a reset and a set input, where the reset input dominates the set input. */
class RSFlipFlop
using Impl {
	boolean status = false;

	/** If r is TRUE, the state of the flip flop is set to FALSE. Otherwise, if s is TRUE, the state is set to TRUE. If both r and s are FALSE, the state is left unchanged. */
	@generated("blockdiagram", "abdd2018")
	public void compute(boolean in r, boolean in s) {
		if (r) {
			status = false; // Main/compute 1/if-then 1
		} else {
			if (s) {
				status = true; // Main/compute 1/if-else 1/if-then 1
			} // Main/compute 1/if-else 1
		} // Main/compute 1
	}

	/** The negated value of the state is returned. */

	@no_side_effect
	@generated("blockdiagram", "1499bfd8")
	public boolean nq() {
		return(!status); // Main/nq 1
	}

	/** The state of the flip flop is returned. */

	@no_side_effect
	@generated("blockdiagram", "c1cdf228")
	public boolean q() {
		return status; // Main/q 1
	}
	representation Impl {
		represent compute.r using {
			datatype = uint8;
		};
		represent nq return using {
			datatype = uint8;
		};
		represent q return using {
			datatype = uint8;
		};
		represent compute.s using {
			datatype = uint8;
		};
		represent status using {
			datatype = uint8;
		};
	}
}