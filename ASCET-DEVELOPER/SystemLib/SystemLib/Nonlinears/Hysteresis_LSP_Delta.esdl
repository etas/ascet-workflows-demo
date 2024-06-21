package SystemLib.Nonlinears;

/** Hysteresis-LSP-Delta is a hysteresis with a left switching point and a delta offset */
class Hysteresis_LSP_Delta {
	boolean hysterese = false;

	/** TRUE is returned, if x > (lsp + delta). FALSE is returned, if x < lsp. The return value is unchanged, if x lies within the open interval [lsp, (lsp + delta)]. */
	@generated("blockdiagram", "6ce4abc3")
	public boolean value(real in x, real in lsp, real in deltav) {
		if (x > (deltav + lsp)) {
			hysterese = true; // Main/value 1/if-then 1
		} else {
			if (x < lsp) {
				hysterese = false; // Main/value 1/if-else 1/if-then 1
			} // Main/value 1/if-else 1
		} // Main/value 1
		return hysterese; // Main/value 2
	}
}