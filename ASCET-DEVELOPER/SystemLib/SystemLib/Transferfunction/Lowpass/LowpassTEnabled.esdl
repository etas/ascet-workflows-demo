package SystemLib.Transferfunction.Lowpass;
import SystemLib.Miscellaneous.DeltaTimeService;

/** LowpassTEnabled is a simplified PT1-function with time constant T (low pass filter). It must be enabled explicitly. */
class LowpassTEnabled {
	real memory = 0.0;

	/** If enable is TRUE, the lowpass is computed via lowpass (new) = lowpass (old)+ (in - lowpass (old) ) * dT / T. */
	@generated("blockdiagram", "89b111f2")
	public void compute(real in val, real in T, boolean in enabled) {
		if (enabled) {
			memory = (((DeltaTimeService.deltaT / T) * (val - memory)) + memory); // Main/compute 1/if-then 1
		} // Main/compute 1
	}

	/** The lowpass value is returned. */

	@no_side_effect
	@generated("blockdiagram", "3a403945")
	public real value() {
		return memory; // Main/value 1
	}

	/** If initEnable is TRUE, the lowpass value is set to initValue. */
	@generated("blockdiagram", "d1dcee66")
	public void reset(real in initValue, boolean in initEnabled) {
		if (initEnabled) {
			memory = initValue; // Main/reset 1/if-then 1
		} // Main/reset 1
	}
}