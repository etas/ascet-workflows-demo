//#ifdef PC
	step = DeltaTimeService.deltaT*amplitude/period;
	val += step;
	if ((step > 0.0 && val > offst+amplitude)||(step < 0.0 && val < offst+amplitude)) val = offst;
	outVal = val;

//#endif /* PC */

