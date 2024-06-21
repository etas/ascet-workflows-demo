package SystemLib.Transferfunction.Integrator;
import SystemLib.Miscellaneous.DeltaTimeService;

/** IntegratorTLimited is a time discrete integrator with time constant T. Its integrator value can be limited. */
class IntegratorTLimited {
	real memory = 0.0;

	/** The integrator value is computed via integrator(new) = integrator(old) + in * dT / T (limited by mn and mx). */
	@generated("blockdiagram", "2c4640e7")
	public void compute(real in val, real in T, real in mn, real in mx) {
		memory = max(min((((DeltaTimeService.deltaT / T) * val) + memory), mx), mn); // Main/compute 1
	}

	/** The integrator value is returned. */

	@no_side_effect
	@generated("blockdiagram", "2bc23eaa")
	public real value() {
		return memory; // Main/value 1
	}

	/** The integrator value is set to initValue. */
	@generated("blockdiagram", "10571732")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}