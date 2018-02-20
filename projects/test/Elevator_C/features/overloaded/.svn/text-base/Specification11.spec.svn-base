#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification11 {
	 // specification 11
	 /* Elevator must not move while it is overloaded.
	  */


    introduction {
	 int stayAt = -1000;
	}

// before timeshift
    before void timeShift() {
        if (weight > maximumWeight)
		 stayAt = getCurrentFloorID();
	 else 
		 stayAt = -1000;
    }


// after timeshift
    after void timeShift() {
        if (stayAt != -1000 && stayAt != getCurrentFloorID()) {
		fail;
	 }
    }
}
