package SystemLib.Nonlinears;

/** Hysteresis-MSP-DeltaHalf is a hysteresis with a middle switching point and a delta/2 offset. */
class Hysteresis_MSP_DeltaHalf {
	boolean hysterese = false;

	/** TRUE is returned, if x > (msp + deltahalf). FALSE is returned, if x < (msp - deltahalf). The return value is unchanged, if input x is in the open interval [(msp - deltahalf), (msp + deltahalf)]. */
	@generated("blockdiagram", "ca154971")
	public boolean value(real in x, real in msp, real in deltaHalf) {
		if (x > (msp + deltaHalf)) {
			hysterese = true; // Main/value 1/if-then 1
		} else {
			if (x < (msp - deltaHalf)) {
				hysterese = false; // Main/value 1/if-else 1/if-then 1
			} // Main/value 1/if-else 1
		} // Main/value 1
		return hysterese; // Main/value 2
	}
}