package SystemLib.Stimulation.Sinus;
import SystemLib.Miscellaneous.DeltaTimeService;
import SystemLib.Math.MathLib;

/**
 * SinusGenerator creates a phase-shifted sine wave with adjustable amplitude, frequency and delay.
 */

@c_code
class SinusGenerator
{
	
	characteristic real amplitude = 1.5;
	real angle = 0.0;
	characteristic real period = 2.0;
	characteristic real phase = 90.0;
	characteristic real offst = 0.5;
	const real Pi = 3.141592653589793;
	characteristic real raster = 0.01;
	real step = 0.0;
	real outVal = 0.0;
	MathLib MathLib_instance;
	
	public void calc();
	public void init();
	public real value();

	public initializer set2() {
	amplitude = 2.2;
	phase = 0.0;
	period = 0.5;
	offst = 0.0;
}
}

