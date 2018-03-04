#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification9 {
	 // specification 9
	 /*
	  * The Lift will honour Requests from within the lift as long as it is not empty.
	  * (this is actually a copy of Spec2 with added property that the lift is not empty.
	  */
    introduction {
        int floorButtons_spc9_0;
        int floorButtons_spc9_1;
        int floorButtons_spc9_2;
        int floorButtons_spc9_3;
        int floorButtons_spc9_4;
    }
    // initalization
    before void runTest() {
	floorButtons_spc9_0 = 0;
	floorButtons_spc9_1 = 0;
	floorButtons_spc9_2 = 0;
	floorButtons_spc9_3 = 0;
	floorButtons_spc9_4 = 0;
    }

    before void pressInLiftFloorButton(floor:int) {
		if (floor == 0) floorButtons_spc9_0 = 1;
		else if (floor == 1) floorButtons_spc9_1 = 1;
		else if (floor == 2) floorButtons_spc9_2 = 1;
		else if (floor == 3) floorButtons_spc9_3 = 1;
		else if (floor == 4) floorButtons_spc9_4 = 1;
    }

// after timeshift
    after void timeShift() {
	int floor = getCurrentFloorID();
	if (isEmpty()) { // this is the difference to Spec2
		floorButtons_spc9_0 = 0;
		floorButtons_spc9_1 = 0;
		floorButtons_spc9_2 = 0;
		floorButtons_spc9_3 = 0;
		floorButtons_spc9_4 = 0;
	} else if (areDoorsOpen()) {
		if (floor == 0 && floorButtons_spc9_0) floorButtons_spc9_0 = 0;
		else if (floor == 1 && floorButtons_spc9_1) floorButtons_spc9_1 = 0;
		else if (floor == 2 && floorButtons_spc9_2) floorButtons_spc9_2 = 0;
		else if (floor == 3 && floorButtons_spc9_3) floorButtons_spc9_3 = 0;
		else if (floor == 4 && floorButtons_spc9_4) floorButtons_spc9_4 = 0;
	}
    } 
// after programTermination
    after void runTest() {
	if (floorButtons_spc9_0) fail;
	else if (floorButtons_spc9_1) fail;
	else if (floorButtons_spc9_2) fail;
	else if (floorButtons_spc9_3) fail;
	else if (floorButtons_spc9_4) fail;
    }
}
