#include "MinePump.h"
#include "Environment.h"
#include <stdio.h>

automaton Specification4 {
	// Specification 4: the pump is never on when the water level is low
//    introduction {
//    }

    // initalization
//    before void runTest() {
//    }

// after timeshift
// monitor which calls where served
    after void timeShift() {
    	if (getWaterLevel() == 0 && isPumpRunning()) {
    		fail;
    	}
    }

// after programTermination
// fail on remaining calls
//    after void runTest() {
//    }
}
