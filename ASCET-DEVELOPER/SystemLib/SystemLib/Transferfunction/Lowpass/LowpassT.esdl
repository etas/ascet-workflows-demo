package SystemLib.Transferfunction.Lowpass;
import SystemLib.Miscellaneous.DeltaTimeService;

/** LowpassT is a simplified PT1-function with time constant T (low pass filter) */
class LowpassT {
	real memory = 0.0;

	/** The lowpass is computed via lowpass (new) = lowpass (old)+ (in - lowpass (old) ) * dT/ T. */
	@generated("blockdiagram", "0194056e")
	public void compute(real in val, real in T) {
		memory = (((DeltaTimeService.deltaT / T) * (val - memory)) + memory); // Main/compute 1
	}

	/** The lowpass value is returned. */

	@no_side_effect
	@generated("blockdiagram", "92a4c464")
	public real value() {
		return memory; // Main/value 1
	}

	/** The lowpass value is set to initValue. */
	@generated("blockdiagram", "11ad7f49")
	public void reset(real in initValue) {
		memory = initValue; // Main/reset 1
	}
}