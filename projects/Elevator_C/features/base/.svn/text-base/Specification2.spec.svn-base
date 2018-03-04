#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification2 {
	 // specification 2
	 /*
	 * Pressing a button inside the lift guarantees that the lift will arrive at that landing and open the doors.
	  */
    introduction {
	int floorButtons_spc2_0;
	int floorButtons_spc2_1;
	int floorButtons_spc2_2;
	int floorButtons_spc2_3;
	int floorButtons_spc2_4;
    }

    // initalization
    before void runTest() {
	floorButtons_spc2_0 = 0;
	floorButtons_spc2_1 = 0;
	floorButtons_spc2_2 = 0;
	floorButtons_spc2_3 = 0;
	floorButtons_spc2_4 = 0;
    }

    before void pressInLiftFloorButton(floor:int) {
	    if (floor == 0) floorButtons_spc2_0 = 1;
	    else if (floor == 1) floorButtons_spc2_1 = 1;
	    else if (floor == 2) floorButtons_spc2_2 = 1;
	    else if (floor == 3) floorButtons_spc2_3 = 1;
	    else if (floor == 4) floorButtons_spc2_4 = 1;
    }

// after timeshift
    after void timeShift() {
		int floor = getCurrentFloorID();
		if (floor == 0 && floorButtons_spc2_0 && areDoorsOpen()) {	
			floorButtons_spc2_0 = 0;
		} else if (floor == 1 && floorButtons_spc2_1 && areDoorsOpen()) {	
			floorButtons_spc2_1 = 0;
		} else if (floor == 2 && floorButtons_spc2_2 && areDoorsOpen()) {	
			floorButtons_spc2_2 = 0;
		} else if (floor == 3 && floorButtons_spc2_3 && areDoorsOpen()) {	
			floorButtons_spc2_3 = 0;
		} else if (floor == 4 && floorButtons_spc2_4 && areDoorsOpen()) {	
			floorButtons_spc2_4 = 0;
		} 
    } 
// after programTermination
    after void runTest() {
	if (floorButtons_spc2_0) fail;
	else if (floorButtons_spc2_1) fail;
	else if (floorButtons_spc2_2) fail;
	else if (floorButtons_spc2_3) fail;
	else if (floorButtons_spc2_4) fail;
    }
}
