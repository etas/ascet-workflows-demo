package SystemLib.Transferfunction.Control;
import SystemLib.Miscellaneous.DeltaTimeService;

/** PT1 is a time discrete low pass with time constant T and gain constant K. */
class PT1 {
	real memory = 0.0;
	characteristic real one = 1.0;

	/** The value of the PT1 function is computed via an I function and a P function that is backcoupled. */
	@generated("blockdiagram", "234c3f94")
	public void compute(real in val, real in K, real in T) {
		memory = (((DeltaTimeService.deltaT * (K / T)) * (val - ((one / K) * memory))) + memory); // Main/compute 1
	}

	/** The value of the PT1 function is returned. */

	@no_side_effect
	@generated("blockdiagram", "74ebc99d")
	public real value() {
		return memory; // Main/value 1
	}

	/** The value of the integrator is set to initValue. */
	@generated("blockdiagram", "2711954b")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}