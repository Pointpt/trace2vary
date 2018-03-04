#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification1 {

// normal (with arrays)
    introduction {
	int landingButtons_spc1_0;
	int landingButtons_spc1_1;
	int landingButtons_spc1_2;
	int landingButtons_spc1_3;
	int landingButtons_spc1_4;
    }

    // initalization
    before void runTest() {
		landingButtons_spc1_0 = 0;
		landingButtons_spc1_1 = 0;
		landingButtons_spc1_2 = 0;
		landingButtons_spc1_3 = 0;
		landingButtons_spc1_4 = 0;
    }

// before Floor.callElevator
// remember calls
    before void callOnFloor(floor:int) {
    	if (floor == 0) landingButtons_spc1_0 = 1;
        else if (floor == 1) landingButtons_spc1_1 = 1;
        else if (floor == 2) landingButtons_spc1_2 = 1;
        else if (floor == 3) landingButtons_spc1_3 = 1;
        else if (floor == 4) landingButtons_spc1_4 = 1;
    }

// after timeshift
// monitor which calls where served
    after void timeShift() {
        int floor = getCurrentFloorID();
		if (floor == 0 && landingButtons_spc1_0 && areDoorsOpen()) {
			landingButtons_spc1_0 = 0;
		} else 	if (floor == 1 && landingButtons_spc1_1 && areDoorsOpen()) {
			landingButtons_spc1_1 = 0;
		} else 	if (floor == 2 && landingButtons_spc1_2 && areDoorsOpen()) {
			landingButtons_spc1_2 = 0;
		} else 	if (floor == 3 && landingButtons_spc1_3 && areDoorsOpen()) {
			landingButtons_spc1_3 = 0;
		} else 	if (floor == 4 && landingButtons_spc1_4 && areDoorsOpen()) {
			landingButtons_spc1_4 = 0;
		}
    }

// after programTermination
// fail on remaining calls
    after void runTest() {
	if (landingButtons_spc1_0) { fail; }
	else if (landingButtons_spc1_1) { fail; }
	else if (landingButtons_spc1_2) { fail; }
	else if (landingButtons_spc1_3) { fail; }
	else if (landingButtons_spc1_4) { fail; }
    }
}
