package SystemLib.Transferfunction.Integrator;
import SystemLib.Miscellaneous.DeltaTimeService;

/** IntegratorTEnabled is a time discrete integrator with time constant T. It must be enabled explicitly and its integrator value can be limited. */
class IntegratorTEnabled  {
	real memory = 0.0;

	/** If enable is TRUE, the integrator value is computed via integrator(new) = integrator(old) + in * dT / T (limited by mn and mx). */
	@generated("blockdiagram", "289f041e")
	public void compute(real in val, real in T, real in mn, real in mx, boolean in enable) {
		if (enable) {
			memory = max(min((((DeltaTimeService.deltaT / T) * val) + memory), mx), mn); // Main/compute 1/if-then 1
		} // Main/compute 1
	}

	/** The integrator value is returned. */

	@no_side_effect
	@generated("blockdiagram", "87b478d5")
	public real value() {
		return memory; // Main/value 1
	}

	/** If initEnable is TRUE, the integrator value is set to initValue. */
	@generated("blockdiagram", "1adb1823")
	public void reset(real in initValue, boolean in initEnable) {
		if (initEnable) {
			memory = initValue; // Main/reset 1/if-then 1
		} // Main/reset 1
	}
}