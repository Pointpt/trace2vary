	void activatePump() {
		if (!isMethaneAlarm()) {
			original();
		} else {
			//System.out.println("Pump not activated due to methane alarm");
		}
	}
