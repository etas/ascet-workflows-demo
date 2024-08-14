package hardware;

import model.Signals;

singleton class HandDistanceSensor
reads Signals.adcHandPosition
writes Signals.handPosition {

	MappingUtil m;
	characteristic real adcMin = 800.0;
	characteristic real adcMax = 2000.0;

	@thread
	@generated("blockdiagram", "54d31754")
	public void read() {
		Signals.handPosition = min(max(m.map(Signals.adcHandPosition, adcMin, adcMax, 0.0, 1.0), 0.0), 1.0); // Main/read 1
	}
}
