package SystemLib.Transferfunction.Control;
import SystemLib.Miscellaneous.DeltaTimeService;

/** PID is a time discrete proportional integrator with differential part with time constants TV and TN and gain constant K. */
class PID {
	real inOLD = 0.0;
	real memory1 = 0.0;
	real memory2 = 0.0;

	/** The value of the PID function is computed as a sum of a P function, a D function and an I function. */
	@generated("blockdiagram", "6188a24a")
	public void compute(real in val, real in K, real in TV, real in TN) {
		memory1 = ((DeltaTimeService.deltaT * val * (K / TN)) + memory1); // Main/compute 1
		memory2 = ((((K * TV) / DeltaTimeService.deltaT) * (val - inOLD)) + memory1 + (val * K)); // Main/compute 2
		inOLD = val; // Main/compute 3
	}

	/** The value of the PID function is returned. */

	@no_side_effect
	@generated("blockdiagram", "3e97f60d")
	public real value() {
		return memory2; // Main/value 1
	}

	/** The integrator value is set to initValue. */
	@generated("blockdiagram", "d2bb10d9")
	public void reset(real in initValue) {
		memory1 = initValue; // Main/reset 1
	}
}