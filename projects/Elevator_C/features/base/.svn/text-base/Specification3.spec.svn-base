#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification3 {
	 // specification 3
	 /*Specification 3:
	  * The Lift will not change direction while there are calls in the direction it is traveling.
	  */
	
    introduction {
	int expectedDirection = 0;// 0=unknown, 1=up, -1=down
    }

    // initalization
/*    before void runTest() {
    }
*/
   before void timeShift() {
      expectedDirection = 0;
      int currentFloorID = getCurrentFloorID();
      if (getCurrentHeading() == 1) {
		if (currentFloorID < 0 && buttonForFloorIsPressed(0)) expectedDirection = 1;
		else if (currentFloorID < 1 && buttonForFloorIsPressed(1)) expectedDirection = 1;
		else if (currentFloorID < 2 && buttonForFloorIsPressed(2)) expectedDirection = 1;
		else if (currentFloorID < 3 && buttonForFloorIsPressed(3)) expectedDirection = 1;
		else if (currentFloorID < 4 && buttonForFloorIsPressed(4)) expectedDirection = 1;
     } else {
		if (currentFloorID > 0 && buttonForFloorIsPressed(0)) expectedDirection = -1;
		else if (currentFloorID > 1 && buttonForFloorIsPressed(1)) expectedDirection = -1;
		else if (currentFloorID > 2 && buttonForFloorIsPressed(2)) expectedDirection = -1;
		else if (currentFloorID > 3 && buttonForFloorIsPressed(3)) expectedDirection = -1;
		else if (currentFloorID > 4 && buttonForFloorIsPressed(4)) expectedDirection = -1;
     }
  }

// after timeshift
    after void timeShift() {
	if (expectedDirection==-1 && getCurrentHeading() == 1) fail;
	else 
     	if (expectedDirection==1 && getCurrentHeading() == 0) fail;
 
    }
}
