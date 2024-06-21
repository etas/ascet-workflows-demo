package SystemLib.Miscellaneous;

/** DeltaOneStep returns the difference of the current input value and the last input value. */
class DeltaOneStep  {
	real buffer = 0.0;
	real oldValue = 0.0;

	/** The previous input value is subtracted from the input value. */
	@generated("blockdiagram", "335a9ed0")
	public void compute(real in val) {
		buffer = (val - oldValue); // Main/compute 1
		oldValue = val; // Main/compute 2
	}

	/** The difference is returned. */

	@no_side_effect
	@generated("blockdiagram", "c1805d56")
	public real value() {
		return buffer; // Main/value 1
	}
}