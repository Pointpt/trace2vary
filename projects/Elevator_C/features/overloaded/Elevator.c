	int isBlocked() {
		return blocked;
	}

// pre: elevator arrived at the current floor, next actions to be done
	void timeShift() {
		if (areDoorsOpen() && weight > maximumWeight) {
			blocked = 1;
		} else {
			blocked = 0;
			original();
		}
	}
	void printState() {
		if (isBlocked()) printf("Blocked ");
		original();
	}


