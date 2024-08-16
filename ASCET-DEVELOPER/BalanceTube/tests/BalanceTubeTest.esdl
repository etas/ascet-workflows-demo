package tests;

import assert.Assert;
import model.Signals;
import hardware.HandDistanceSensor;

singleton class BalanceTubeTest
writes Signals.adcHandPosition
reads Signals.handPosition {
	
	HandDistanceSensor sensor;
	Assert assert;
	
	@Test
	public void handPositionNormalization() {
		Signals.adcHandPosition = sensor.adcMin;
		sensor.read();
		assert.assertDoubleEqual(Signals.handPosition, 1.0);
		
		Signals.adcHandPosition = (sensor.adcMax + sensor.adcMin) / 2;
		sensor.read();
		assert.assertDoubleEqual(Signals.handPosition, 0.5);
		
		Signals.adcHandPosition = sensor.adcMax;
		sensor.read();
		assert.assertDoubleEqual(Signals.handPosition, 0.0);
	}
}
