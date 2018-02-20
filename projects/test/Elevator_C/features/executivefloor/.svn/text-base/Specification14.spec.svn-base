#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification14 {
	/* Original: The Lift will answer requests from the executive Floor.
	 * 
	 * My Version: While there is a request from the executive Floor the lift will not open its doors somewhere else.
	 * 
	 */
	introduction {
	}
// after timeshift
// monitor which calls where served
    after void timeShift() {
        if (isExecutiveFloorCalling()) {
		if (!isExecutiveFloor(getCurrentFloorID()) && areDoorsOpen()) {
			fail;
		}
	 }
    }
}
