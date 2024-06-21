//#ifdef PC
	step = 2*Pi*DeltaTimeService.deltaT/period;
	angle += step;
	if (angle > 2*Pi) angle -= 2*Pi;
	outVal = amplitude * MathLib_instance.sin (angle)+offst;

//#endif /* PC */

