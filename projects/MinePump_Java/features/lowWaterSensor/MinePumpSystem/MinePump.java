package MinePumpSystem;

import MinePumpSystem.Environment;

public class MinePump {

	public void processEnvironment() {
		if (pumpRunning && isLowWaterLevel()) {
			deactivatePump();
		} else {
			original();
		}
	}
	
	boolean isLowWaterLevel() {
		return !env.isLowWaterSensorDry();
	}
}
