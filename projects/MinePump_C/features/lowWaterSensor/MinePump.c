	int isLowWaterLevel() {
		return ! isLowWaterSensorDry();
	}
	void processEnvironment() {
		if (pumpRunning && isLowWaterLevel()) {
			deactivatePump();
		} else {
			original();
		}
	}
