package SystemLib.Transferfunction.Control;
import SystemLib.Miscellaneous.DeltaTimeService;

/** PI is a time discrete proportional integrator with time constant T and gain constant K. */
class PI {
	real memory1 = 0.0;
	real memory2 = 0.0;

	/** The value of the PI function is computed as the sum of a P function and an I function. */
	@generated("blockdiagram", "3f378ff4")
	public void compute(real in val, real in K, real in T) {
		memory1 = (((K / T) * val * DeltaTimeService.deltaT) + memory1); // Main/compute 1
		memory2 = (memory1 + (val * K)); // Main/compute 2
	}

	/** The value of the PI function is returned. */

	@no_side_effect
	@generated("blockdiagram", "fe6b1259")
	public real value() {
		return memory2; // Main/value 1
	}

	/** The integrator value is set to initValue. */
	@generated("blockdiagram", "9da9d6a0")
	public void reset(real in initValue) {
		memory1 = initValue; // Main/reset 1
		memory2 = memory1; // Main/reset 2
	}
}