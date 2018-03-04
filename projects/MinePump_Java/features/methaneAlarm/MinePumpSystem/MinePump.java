package MinePumpSystem;

import MinePumpSystem.Environment;

public class MinePump {
	public void processEnvironment() {
		if (pumpRunning && isMethaneAlarm()) {
			deactivatePump();
		} else {
			original();
		}
	}
}
