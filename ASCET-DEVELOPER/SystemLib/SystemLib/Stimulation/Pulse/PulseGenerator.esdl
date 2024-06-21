package SystemLib.Stimulation.Pulse;
import SystemLib.Miscellaneous.DeltaTimeService;

/**
 * PulseGenerator creates a pulse signal with adjustable period, amplitude, duty cycle and delay.
 */

@c_code
class PulseGenerator {
	characteristic real amplitude = 1.5;
	characteristic real offst = 0.5;
	real time = 0.0;
	characteristic real period = 2.0;
	boolean OnOff = false;
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