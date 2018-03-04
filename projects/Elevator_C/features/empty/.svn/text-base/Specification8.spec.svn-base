#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification8 {
	// specification 8
	/* Original: The Lift will not arrive empty at a floor unless the button on that landing was pressed.
	 * MyVersion: The Lift will not arrive empty at a floor and open its doors unless the button on that landing was pressed.
	 */
    introduction {
        int floorButtons_spc8_0;
	int floorButtons_spc8_1;
	int floorButtons_spc8_2;
	int floorButtons_spc8_3;
	int floorButtons_spc8_4;

        int wasEmptyBeforeTimeStep;
    }
    //initialization
    before void runTest() {
	floorButtons_spc8_0 = 0;
	floorButtons_spc8_1 = 0;
	floorButtons_spc8_2 = 0;
	floorButtons_spc8_3 = 0;
	floorButtons_spc8_4 = 0;
	wasEmptyBeforeTimeStep = 0;
    }
    before void timeShift() {
	floorButtons_spc8_0 = isFloorCalling(0);
	floorButtons_spc8_1 = isFloorCalling(1);
	floorButtons_spc8_2 = isFloorCalling(2);
	floorButtons_spc8_3 = isFloorCalling(3);
	floorButtons_spc8_4 = isFloorCalling(4);
        
	wasEmptyBeforeTimeStep = isEmpty();
    }

// after timeshift
    after void timeShift() {
		if (areDoorsOpen() && wasEmptyBeforeTimeStep) {
			int floor = getCurrentFloorID();
			if (floor == 0 && !floorButtons_spc8_0) fail;
			else if (floor == 1 && !floorButtons_spc8_1) fail;
			else if (floor == 2 && !floorButtons_spc8_2) fail;
			else if (floor == 3 && !floorButtons_spc8_3) fail;
			else if (floor == 4 && !floorButtons_spc8_4) fail;
		}
    } 
}
