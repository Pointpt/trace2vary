package MinePumpSystem;

import MinePumpSystem.Environment;

public class MinePump {


	public void processEnvironment() {
		if (!pumpRunning && isHighWaterLevel()) {
			activatePump();
			original();
		} else {
			original();
		}
	}
	
	boolean isHighWaterLevel() {
		return !env.isHighWaterSensorDry();
	}
}
