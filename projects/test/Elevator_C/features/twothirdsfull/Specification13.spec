#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification13 {
	 // specification 13
	 /* Car calls have precedence when the Lift is two thirds full.
	  */


    introduction {
	 int prevDir = 0;
	}

// before timeshift
    before void timeShift() {
        prevDir = getCurrentHeading();
    }


// after timeshift
    after void timeShift() {
	 if (weight > maximumWeight*2/3) {
		 if (prevDir == 1) {
			 if (existInLiftCallsInDirection(0) &&  !existInLiftCallsInDirection(1))
				 if (getCurrentHeading() == 1)
					fail;
		 } else if (prevDir == 0) {
			 if (existInLiftCallsInDirection(1) && !existInLiftCallsInDirection(0))
				 if (getCurrentHeading() == 0)
					fail;
		 }
	 }
    }
}
