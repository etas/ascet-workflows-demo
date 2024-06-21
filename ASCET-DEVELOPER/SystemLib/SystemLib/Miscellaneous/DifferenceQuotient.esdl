package SystemLib.Miscellaneous;

/** DifferenceQuotient computes the difference quotient of the input value.
*/
class DifferenceQuotient {
	real buffer = 0.0;
	real oldValue = 0.0;

	/** The difference quotient (value - previous value)/dT is computed. */
	@generated("blockdiagram", "bc02053a")
	public void compute(real in valCompute) {
		buffer = ((valCompute - oldValue) / DeltaTimeService.deltaT); // Main/compute 1
		oldValue = valCompute; // Main/compute 2
	}

	/** The difference quotient is returned. */

	@no_side_effect
	@generated("blockdiagram", "6a0d899a")
	public real value() {
		return buffer; // Main/value 1
	}
}