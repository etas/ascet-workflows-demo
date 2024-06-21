package SystemLib.Nonlinears;

/** Hysteresis-LSP-RSP is a hysteresis with both a left and a right switching point */
class Hysteresis_LSP_RSP  {
	boolean hysterese = false;

	/** TRUE is returned, if x > rsp. FALSE is returned, if x < lsp. The return value is unchanged, if x lies within the open interval [lsp, rsp]. */
	@generated("blockdiagram", "28b252de")
	public boolean value(real in x, real in lsp, real in rsp) {
		if (x > rsp) {
			hysterese = true; // Main/value 1/if-then 1
		} else {
			if (x < lsp) {
				hysterese = false; // Main/value 1/if-else 1/if-then 1
			} // Main/value 1/if-else 1
		} // Main/value 1
		return hysterese; // Main/value 2
	}
}