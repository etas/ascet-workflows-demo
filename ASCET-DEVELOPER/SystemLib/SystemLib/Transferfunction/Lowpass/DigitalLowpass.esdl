package SystemLib.Transferfunction.Lowpass;

/** DigitalLowpass recursively computes the mean value of the input value. */
class DigitalLowpass {
	real memory = 0.0;

	/** The mean value is computed via mean value (new) = mean value (old) + m *(in -mean value (old) ). */
	@generated("blockdiagram", "6ac8dcac")
	public void compute(real in val, real in m) {
		memory = ((m * (val - memory)) + memory); // Main/compute 1
	}

	/** The mean value is returned. */

	@no_side_effect
	@generated("blockdiagram", "962192c0")
	public real value() {
		return memory; // Main/value 1
	}

	/** The mean value is set to initValue. */
	@generated("blockdiagram", "c501c3f1")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}