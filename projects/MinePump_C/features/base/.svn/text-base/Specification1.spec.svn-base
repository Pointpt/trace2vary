#include "MinePump.h"
#include "Environment.h"
#include <stdio.h>

automaton Specification1 {
	// Specification 1: The pump is never on when there is methane.
//    introduction {
//    }

    // initalization
//    before void runTest() {
//    }
    
// after timeshift
// monitor which calls where served
    after void timeShift() {
    	if (isMethaneLevelCritical() && isPumpRunning()) {
    		fail;
    	}
    }

// after programTermination
// fail on remaining calls
//    after void runTest() {
//    }
}
