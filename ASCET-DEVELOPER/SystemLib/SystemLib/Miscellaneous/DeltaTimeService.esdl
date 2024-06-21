package SystemLib.Miscellaneous;

// time is using seconds as unit
type TimeType is real 0.0 .. 100.0;

/**
 * Provides the delta time variable
 */
singleton class DeltaTimeService {
	/**
	 * This value contains the delta time between two subsequent task activations in seconds.
	 * There are several representations possible.
	 */
	@dT
	public static TimeType deltaT = 0.0;

	representation FixpointMilliSecondResolution {
		represent deltaT using {
			datatype = uint32;
			delta = 1.0e-3; // millisecond resolution
		};
	}

	representation FixPointMicroSecondResolution {
		represent deltaT using {
			datatype = uint32;
			delta = 1.0e-6; // microsecond resolution
		};
	}
}
