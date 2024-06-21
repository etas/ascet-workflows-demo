package SystemLib.Transferfunction.Control;
import SystemLib.Miscellaneous.DeltaTimeService;

/** PILimited is a time discrete proportional integrator with time constant T and gain constant K. The value of the integrator is limited */
class PILimited {
	real memory1 = 0.0;
	real memory2 = 0.0;

	/** The value of the PI function is computed as the sum of a P function and an I function, where the integrator value of the I function is limited by mn and mx. */
	@generated("blockdiagram", "6dfc139c")
	public void compute(real in val, real in K, real in T, real in mn, real in mx) {
		memory1 = max(min((((K / T) * val * DeltaTimeService.deltaT) + memory1), mx), mn); // Main/compute 1
		memory2 = (memory1 + (val * K)); // Main/compute 2
	}

	/** The value of the PI function is returned. */

	@no_side_effect
	@generated("blockdiagram", "cccdf82b")
	public real value() {
		return memory2; // Main/value 1
	}

	/** The integrator value is set to initValue. */
	@generated("blockdiagram", "da073a96")
	public void reset(real in initValue) {
		memory1 = initValue; // Main/reset 1
		memory2 = memory1; // Main/reset 2
	}
}