package SystemLib.Memory;

/** Accumulator adds up its input value.
*/
class Accumulator {
	real memory = 0.0;

	/** The accumulator is incremented by the input value, i.e.accumulator (new) = accumulator (old) + input value. */
	@generated("blockdiagram", "d14f45d5")
	public void compute(real in valCompute) {
		memory = (valCompute + memory); // Main/compute 1
	}

	/** The accumulator value is returned. */

	@no_side_effect
	@generated("blockdiagram", "a4e9c2d6")
	public real value() {
		return memory; // Main/value 1
	}

	/** The accumulator value is set to initValue. */
	@generated("blockdiagram", "785cf2de")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}