package SystemLib.Nonlinears;

/** Hysteresis-Delta-RSP is a hysteresis with a right switching point and a delta offset */
class Hysteresis_Delta_RSP {
	boolean hysterese = false;

	/** TRUE is returned, if x > rsp. FALSE is returned, if x < (rsp - delta). The return value is unchanged, if x lies within the open interval [(rsp - delta), rsp]. */
	@generated("blockdiagram", "4c4852a6")
	public boolean value(real in x, real in deltav, real in rsp) {
		if (x > rsp) {
			hysterese = true; // Main/value 1/if-then 1
		} else {
			if (x < (rsp - deltav)) {
				hysterese = false; // Main/value 1/if-else 1/if-then 1
			} // Main/value 1/if-else 1
		} // Main/value 1
		return hysterese; // Main/value 2
	}
}