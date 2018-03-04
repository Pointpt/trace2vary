	int isExecutiveFloorCalling() {
		return isFloorCalling(executiveFloor);
	}

	int stopRequestedInDirection (int dir, int respectFloorCalls, int respectInLiftCalls) {
		if (isExecutiveFloorCalling()) {
			return ((getCurrentFloorID() < executiveFloor) == (dir == 1));
		} else {
			return original(dir, respectFloorCalls, respectInLiftCalls);
		}
	}
	
	int stopRequestedAtCurrentFloor() {
		if (isExecutiveFloorCalling() && ! (executiveFloor == getCurrentFloorID())) {
			return 0;
		} else return original();
	}
	int isExecutiveFloor(int floorID) {
		return (executiveFloor == floorID);
	}
