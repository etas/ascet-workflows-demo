package SystemLib.Transferfunction.Integrator;
import SystemLib.Miscellaneous.DeltaTimeService;

/** IntegratorK is a time discrete integrator with gain constant K. */
class IntegratorK {
	real memory = 0.0;

	/** The integrator value is computed via integrator (new) = integrator (old) + in * dT* K. */
	@generated("blockdiagram", "441750a6")
	public void compute(real in val, real in K) {
		memory = ((val * DeltaTimeService.deltaT * K) + memory); // Main/compute 1
	}

	/** The integrator value is returned. */

	@no_side_effect
	@generated("blockdiagram", "ee5a4e7e")
	public real value() {
		return memory; // Main/value 1
	}

	/** The integrator value is set to initValue. */
	@generated("blockdiagram", "3f25f89e")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}