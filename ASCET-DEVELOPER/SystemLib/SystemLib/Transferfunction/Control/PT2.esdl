package SystemLib.Transferfunction.Control;
import SystemLib.Miscellaneous.DeltaTimeService;

/** PT2 is a time discrete delay function with time constant T, gain constant K, and damping d */
class PT2 {
	real memoryInt1 = 0.0;
	real memoryInt2 = 0.0;
	characteristic real zwei = 2.0;

	/** The value of the PT2 function is computed via two I functions in row, which are backcoupled by a cascade of two P functions. */
	@generated("blockdiagram", "814c1f6d")
	public void compute(real in val, real in d, real in K, real in T) {
		memoryInt1 = (((DeltaTimeService.deltaT / T) * (val - (memoryInt2 / K))) + memoryInt1); // Main/compute 1
		memoryInt2 = (((DeltaTimeService.deltaT * (K / T)) * (memoryInt1 - (((zwei * d) / K) * memoryInt2))) + memoryInt2); // Main/compute 2
	}

	/** The value of the PT2 function is returned. */

	@no_side_effect
	@generated("blockdiagram", "f392d6e4")
	public real value() {
		return memoryInt2; // Main/value 1
	}

	/** The two integrator values are set to initValue. */
	@generated("blockdiagram", "8a94aee3")
	public void reset(real in initValue) {
		memoryInt2 = initValue; // Main/reset 1
		memoryInt1 = initValue; // Main/reset 2
	}
}