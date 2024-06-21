//#ifdef PC

	time += DeltaTimeService.deltaT;
	if (time > period) {OnOff = !OnOff; time = 0.0;}
	outVal = offst + OnOff * amplitude;

//#endif /* PC */

