package SystemLib.Transferfunction.Lowpass;
import SystemLib.Miscellaneous.DeltaTimeService;

/** LowpassK is a simplified PT1 function with gain constant K (low pass filter). */
class LowpassK  {
	real memory = 0.0;

	/** The lowpass is computed via lowpass (new) = lowpass (old)+ (in - lowpass (old) ) * dT* K. */
	@generated("blockdiagram", "50565ce3")
	public void compute(real in val, real in K) {
		memory = (((DeltaTimeService.deltaT * K) * (val - memory)) + memory); // Main/compute 1
	}

	/** The lowpass value is returned. */

	@no_side_effect
	@generated("blockdiagram", "b9d7401c")
	public real value() {
		return memory; // Main/value 1
	}

	/** The lowpass value is set to initValue. */
	@generated("blockdiagram", "7a9ce2b1")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}