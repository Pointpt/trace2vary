
	int stopRequestedInDirection (int dir, int respectFloorCalls, int respectInLiftCalls) {
		int overload =weight > maximumWeight*2/3;
		int buttonPressed =isAnyLiftButtonPressed();
		if (overload && buttonPressed) {
			return original(dir, 0, respectInLiftCalls);
		} else return original(dir, respectFloorCalls, respectInLiftCalls);
	}
	int stopRequestedAtCurrentFloor() {
		if (weight > maximumWeight*2/3) {
			return buttonForFloorIsPressed(getCurrentFloorID()) == 1;
		} else return original();
	}
