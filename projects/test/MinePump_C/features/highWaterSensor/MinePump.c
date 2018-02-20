	int isHighWaterLevel() {
		return ! isHighWaterSensorDry();
	}
	void processEnvironment() {
		if (!pumpRunning && isHighWaterLevel()) {
			activatePump();
		} else {
			original();
		}
	}
