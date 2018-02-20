#include <stdio.h>
#include <stdlib.h>

#include "Elevator.h"

/*
 * Replacement of [4] with _4
 * with regex:
 * Search String: (?:\[)(\d)(?:\])
 * replacement String: _$1
 *
 */


int currentHeading = 1; // 1 = up, 0 = down
int currentFloorID = 0;
int persons_0;
int persons_1;
int persons_2;
int persons_3;
int persons_4;
int persons_5;

int doorState = 1; // 1 = open, 0 = closed
int floorButtons_0;
int floorButtons_1;
int floorButtons_2;
int floorButtons_3;
int floorButtons_4; // 5 floors

/*int main(void) {
	puts("!!!Hello World!!!");  prints !!!Hello World!!!
	return EXIT_SUCCESS;
}*/

void initTopDown() {
	currentFloorID = 4;
	currentHeading = 0;
	floorButtons_0 = 0;
	floorButtons_1 = 0;
	floorButtons_2 = 0;
	floorButtons_3 = 0;
	floorButtons_4 = 0;
	persons_0 = 0;
	persons_1 = 0;
	persons_2 = 0;
	persons_3 = 0;
	persons_4 = 0;
	persons_5 = 0;
	initFloors();
}
void initBottomUp() {
	currentFloorID = 0;
	currentHeading = 1;
	floorButtons_0 = 0;
	floorButtons_1 = 0;
	floorButtons_2 = 0;
	floorButtons_3 = 0;
	floorButtons_4 = 0;
	persons_0 = 0;
	persons_1 = 0;
	persons_2 = 0;
	persons_3 = 0;
	persons_4 = 0;
	persons_5 = 0;
	initFloors();
}

int isBlocked() {
	return 0;
}

void enterElevator(int p) {
	if (p == 0) persons_0 = 1;
	else if (p == 1) persons_1 = 1;
	else if (p == 2) persons_2 = 1;
	else if (p == 3) persons_3 = 1;
	else if (p == 4) persons_4 = 1;
	else if (p == 5) persons_5 = 1;

	//puts(" entered the Elevator at Landing " + this.getCurrentFloorID() + ", going to " + p.getDestination());
}
void leaveElevator(int p) {
	if (p == 0) persons_0 = 0;
	else if (p == 1) persons_1 = 0;
	else if (p == 2) persons_2 = 0;
	else if (p == 3) persons_3 = 0;
	else if (p == 4) persons_4 = 0;
	else if (p == 5) persons_5 = 0;
	// "p left the elevator"
}
void pressInLiftFloorButton(int floorID) {
	if (floorID == 0) floorButtons_0 = 1;
	else if (floorID == 1) floorButtons_1 = 1;
	else if (floorID == 2) floorButtons_2 = 1;
	else if (floorID == 3) floorButtons_3 = 1;
	else if (floorID == 4) floorButtons_4 = 1;
}
void resetFloorButton(int floorID) {
	if (floorID == 0) floorButtons_0 = 0;
	else if (floorID == 1) floorButtons_1 = 0;
	else if (floorID == 2) floorButtons_2 = 0;
	else if (floorID == 3) floorButtons_3 = 0;
	else if (floorID == 4) floorButtons_4 = 0;
}
int getCurrentFloorID() {
	return currentFloorID;
}
int areDoorsOpen() {
	return doorState;
}
int buttonForFloorIsPressed(int floorID) {
	if (floorID == 0) return floorButtons_0;
	else if (floorID == 1) return floorButtons_1;
	else if (floorID == 2) return floorButtons_2;
	else if (floorID == 3) return floorButtons_3;
	else if (floorID == 4) return floorButtons_4;
	else return 0;
}
int getCurrentHeading() {
	return currentHeading;
}
int isEmpty() {
	if (persons_0 == 1) return 0;
	else if (persons_1 == 1) return 0;
	else if (persons_2 == 1) return 0;
	else if (persons_3 == 1) return 0;
	else if (persons_4 == 1) return 0;
	else if (persons_5 == 1) return 0;
	return 1;
}

int anyStopRequested () {
	if (isFloorCalling(0)) return 1;
	else if (floorButtons_0) return 1;
	else if (isFloorCalling(1)) return 1;
	else if (floorButtons_1) return 1;
	else if (isFloorCalling(2)) return 1;
	else if (floorButtons_2) return 1;
	else if (isFloorCalling(3)) return 1;
	else if (floorButtons_3) return 1;
	else if (isFloorCalling(4)) return 1;
	else if (floorButtons_4) return 1;
	return 0;
}
int isIdle() {
	return (anyStopRequested() == 0);
}
	int stopRequestedInDirection (int dir, int respectFloorCalls, int respectInLiftCalls) {
		if (dir == 1) {
			if (isTopFloor(currentFloorID)) return 0;
			/*// Good Implementation:
			int i = 0;
			for (i = currentFloorID+1; i < buildingSize; i++) {
				if (respectFloorCalls && isFloorCalling(i)) return 1;
				if (respectInLiftCalls && floorButtons[i]) return 1;
			}
			*/
			// Bad implementation (needed to avoid loop unrolling in CBMC)
			if (currentFloorID < 0 && respectFloorCalls && isFloorCalling(0)) return 1;
			else if (currentFloorID < 0 && respectInLiftCalls && floorButtons_0) return 1;

			else if (currentFloorID < 1 && respectFloorCalls && isFloorCalling(1)) return 1;
			else if (currentFloorID < 1 && respectInLiftCalls && floorButtons_1) return 1;

			else if (currentFloorID < 2 && respectFloorCalls && isFloorCalling(2)) return 1;
			else if (currentFloorID < 2 && respectInLiftCalls && floorButtons_2) return 1;

			else if (currentFloorID < 3 && respectFloorCalls && isFloorCalling(3)) return 1;
			else if (currentFloorID < 3 && respectInLiftCalls && floorButtons_3) return 1;

			else if (currentFloorID < 4 && respectFloorCalls && isFloorCalling(4)) return 1;
			else if (currentFloorID < 4 && respectInLiftCalls && floorButtons_4) return 1;
			else return 0;
		} else {
			if (currentFloorID == 0) return 0;
			/*// Good Implementation:
			int i = 0;
			for (i = currentFloorID-1; i >= 0; i--) {
				if (respectFloorCalls && isFloorCalling(i)) return 1;
				if (respectInLiftCalls && floorButtons[i]) return 1;
			}
			*/
			// Bad implementation (needed for loop unrolling in CBMC)
			if (currentFloorID > 0 && respectFloorCalls && isFloorCalling(0)) return 1;
			else if (currentFloorID > 0 && respectInLiftCalls && floorButtons_0) return 1;

			else if (currentFloorID > 1 && respectFloorCalls && isFloorCalling(1)) return 1;
			else if (currentFloorID > 1 && respectInLiftCalls && floorButtons_1) return 1;

			else if (currentFloorID > 2 && respectFloorCalls && isFloorCalling(2)) return 1;
			else if (currentFloorID > 2 && respectInLiftCalls && floorButtons_2) return 1;

			else if (currentFloorID > 3 && respectFloorCalls && isFloorCalling(3)) return 1;
			else if (currentFloorID > 3  &&respectInLiftCalls && floorButtons_3) return 1;

			else if (currentFloorID > 4 && respectFloorCalls && isFloorCalling(4)) return 1;
			else if (currentFloorID > 4 && respectInLiftCalls && floorButtons_4) return 1;
			else return 0;
		}
	}
	int isAnyLiftButtonPressed() {
		if (floorButtons_0) return 1;
		else if (floorButtons_1) return 1;
		else if (floorButtons_2) return 1;
		else if (floorButtons_3) return 1;
		else if (floorButtons_4) return 1;
		else return 0;
	}
	void continueInDirection(int dir) {
		currentHeading = dir;
		if (currentHeading == 1) {
			if (isTopFloor(currentFloorID)) {
				//System.out.println("Reversing at Top Floor");
				currentHeading = 0;
			}
		} else {
			if (currentFloorID == 0) {
				//System.out.println("Reversing at Basement Floor");
				currentHeading = 1;
			}
		}
		if (currentHeading == 1) {
			currentFloorID = currentFloorID + 1;
		} else {
			currentFloorID = currentFloorID - 1;
		}
	}
	int stopRequestedAtCurrentFloor() {
		if (isFloorCalling(currentFloorID)) {
			return 1;
		} else if (buttonForFloorIsPressed(currentFloorID)) {
			return 1;
		} else {
			return 0;
		}
	}
	int getReverseHeading(int ofHeading) {
		if (ofHeading==0) {
			return 1;
		} else return 0;
	}

void processWaitingOnFloor(int floorID) {
		if (isPersonOnFloor(0,floorID)) {
			removePersonFromFloor(0, floorID);
			pressInLiftFloorButton(getDestination(0));
			enterElevator(0);
		}
		if (isPersonOnFloor(1,floorID)) {
			removePersonFromFloor(1, floorID);
			pressInLiftFloorButton(getDestination(1));
			enterElevator(1);
		}
		if (isPersonOnFloor(2,floorID)) {
			removePersonFromFloor(2, floorID);
			pressInLiftFloorButton(getDestination(2));
			enterElevator(2);
		}
		if (isPersonOnFloor(3,floorID)) {
			removePersonFromFloor(3, floorID);
			pressInLiftFloorButton(getDestination(3));
			enterElevator(3);
		}
		if (isPersonOnFloor(4,floorID)) {
			removePersonFromFloor(4, floorID);
			pressInLiftFloorButton(getDestination(4));
			enterElevator(4);
		}
		if (isPersonOnFloor(5,floorID)) {
			removePersonFromFloor(5, floorID);
			pressInLiftFloorButton(getDestination(5));
			enterElevator(5);
		}
		resetCallOnFloor(floorID);
	}
// pre: elevator arrived at the current floor, next actions to be done
	void timeShift() {
		//System.out.println("--");

		if (stopRequestedAtCurrentFloor()) {
			//System.out.println("Arriving at " +  currentFloorID + ", Doors opening");
			doorState = 1;
			// iterate over a copy of the original list, avoids concurrent modification exception
			if (persons_0 && getDestination(0) == currentFloorID) leaveElevator(0);
			if (persons_1 && getDestination(1) == currentFloorID) leaveElevator(1);
			if (persons_2 && getDestination(2) == currentFloorID) leaveElevator(2);
			if (persons_3 && getDestination(3) == currentFloorID) leaveElevator(3);
			if (persons_4 && getDestination(4) == currentFloorID) leaveElevator(4);
			if (persons_5 && getDestination(5) == currentFloorID) leaveElevator(5);
			processWaitingOnFloor(currentFloorID);
			resetFloorButton(currentFloorID);
		} else {
			if (doorState == 1)  {
				doorState = 0;
				//System.out.println("Doors Closing");
			}
			if (stopRequestedInDirection(currentHeading, 1, 1)) {
				//System.out.println("Arriving at " + currentFloorID + ", continuing");
				// continue
				continueInDirection(currentHeading);
			} else if (stopRequestedInDirection(getReverseHeading(currentHeading), 1, 1)) {
				//System.out.println("Arriving at " + currentFloorID + ", reversing direction because of call in other direction");
				// revert direction
				continueInDirection(getReverseHeading(currentHeading));
			} else {
				//idle
				//System.out.println("Arriving at " + currentFloorID + ", idle->continuing");
				continueInDirection(currentHeading);
			}
		}
	}
	void printState() {
		printf("Elevator ");
		if (doorState) printf("[_]");
		else printf("[] ");
		printf(" at ");
		printf("%i",currentFloorID);
		printf(" heading ");
		if (currentHeading)	printf("up");
		else printf("down");
		printf(" IL_p:");
		if (floorButtons_0) printf(" %i",0);
		if (floorButtons_1) printf(" %i",1);
		if (floorButtons_2) printf(" %i",2);
		if (floorButtons_3) printf(" %i",3);
		if (floorButtons_4) printf(" %i",4);
		printf(" F_p:");
		if (isFloorCalling(0)) printf(" %i",0);
		if (isFloorCalling(1)) printf(" %i",1);
		if (isFloorCalling(2)) printf(" %i",2);
		if (isFloorCalling(3)) printf(" %i",3);
		if (isFloorCalling(4)) printf(" %i",4);
		printf("\n");
	}

	int existInLiftCallsInDirection(int d) {
		 if (d == 1) {
		 	 int i = 0;
			 for (i =  currentFloorID + 1; i < 5; i++) {
			 	 if (i==0 && floorButtons_0) return 1;
			 	 else if (i==1 && floorButtons_1) return 1;
			 	 else if (i==2 && floorButtons_2) return 1;
			 	 else if (i==3 && floorButtons_3) return 1;
			 	 else if (i==4 && floorButtons_4) return 1;
			 }
		 } else if (d == 0) {
		 	 int i = 0;
			 for (i =  currentFloorID - 1; i >= 0; i--)
			 for (i =  currentFloorID + 1; i < 5; i++) {
			 	 if (i==0 && floorButtons_0) return 1;
			 	 else if (i==1 && floorButtons_1) return 1;
			 	 else if (i==2 && floorButtons_2) return 1;
			 	 else if (i==3 && floorButtons_3) return 1;
			 	 else if (i==4 && floorButtons_4) return 1;
			 }
		 }
		 return 0;		 
	}


