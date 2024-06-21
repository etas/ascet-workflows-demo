package SystemLib.Delay;

/** DelayValue delays its input value by one evaluation step.
*/
class DelayValue {
	real memory1 = 0.0;
	real memory2 = 0.0;

	/** The input value is buffered.
*/
	@generated("blockdiagram", "49cab2c6")
	public void compute(real in valCompute) {
		memory2 = memory1; // Main/compute 1
		memory1 = valCompute; // Main/compute 2
	}

	/** The buffered value is returned, thus the input value is delayed by one step.
*/

	@no_side_effect
	@generated("blockdiagram", "15222d2b")
	public real value() {
		return memory2; // Main/value 1
	}
}