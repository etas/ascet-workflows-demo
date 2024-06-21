package SystemLib.Transferfunction.Integrator;
import SystemLib.Miscellaneous.DeltaTimeService;

/** IntegratorT is a time discrete integrator with time constant T. */
class IntegratorT {
	real memory = 0.0;

	/** The integrator value is computed via integrator(new) = integrator(old) + in * dT / T. */
	@generated("blockdiagram", "9033f48b")
	public void compute(real in val, real in T) {
		memory = (((DeltaTimeService.deltaT / T) * val) + memory); // Main/compute 1
	}

	/** The integrator value is returned. */

	@no_side_effect
	@generated("blockdiagram", "ee08727d")
	public real value() {
		return memory; // Main/value 1
	}

	/** The integrator value is set to initValue. */
	@generated("blockdiagram", "a63e2b3b")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}