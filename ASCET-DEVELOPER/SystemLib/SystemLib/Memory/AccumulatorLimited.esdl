package SystemLib.Memory;

/** AccumulatorLimited adds up its input value. Its accumulated value can be limited. */
class AccumulatorLimited {
	real memory = 0.0;

	/** The accumulator is incremented by the input value, i.e. accumulator(new) = accumulator(old) + input value. Additionally, the accumulator value is limited by mn and mx. */
	@generated("blockdiagram", "4f3de171")
	public void compute(real in valCompute, real in mn, real in mx) {
		memory = max(min((valCompute + memory), mx), mn); // Main/compute 1
	}

	/** The accumulator value is returned. */

	@no_side_effect
	@generated("blockdiagram", "35c7bf5c")
	public real value() {
		return memory; // Main/value 1
	}

	/** The accumulator value is set to initValue. */
	@generated("blockdiagram", "9d428708")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}