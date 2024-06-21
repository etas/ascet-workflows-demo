package SystemLib.Stimulation.Ramp;
import SystemLib.Miscellaneous.DeltaTimeService;

/**
 * The Ramp  generates a constantly increasing or decreasing signal that starts at a specified time. The rate of change (Slope) can be varied.
 */

@c_code
class RampGenerator {
	characteristic real amplitude = 1.5;
	characteristic real offst = 0.5;
	real val = 0.0;
	characteristic real period = 2.0;
	real step = 0.0;
	real outVal = 0.0;

	public void calc();

	public void init();

	public real value();

	public initializer set2() {
		amplitude = 2.2;
		period = 0.5;
		offst = 0.0;
	}
}