package SystemLib.Transferfunction.Integrator;
import SystemLib.Miscellaneous.DeltaTimeService;

/** IntegratorKLimited is a time discrete integrator with gain constant K. Its integrator value can be limited. */
class IntegratorKLimited  {
	real memory = 0.0;

	/** The integrator value is computed via integrator (new) = integrator (old) + in * dT * K (limited by mn and mx). */
	@generated("blockdiagram", "78eb27a5")
	public void compute(real in val, real in K, real in mn, real in mx) {
		memory = max(min(((DeltaTimeService.deltaT * K * val) + memory), mx), mn); // Main/compute 1
	}

	/** The integrator value is returned. */

	@no_side_effect
	@generated("blockdiagram", "dac31d2c")
	public real value() {
		return memory; // Main/value 1
	}

	/** The integrator value is set to initValue. */
	@generated("blockdiagram", "58992e22")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}