#include "MinePump.h"
#include "Environment.h"
#include <stdio.h>

automaton Specification3 {
	// Specification 3: When the water is high and there is no methane, then the pump is on.
//    introduction {
//    }

    // initalization
//    before void runTest() {
//    }

// after timeshift
// monitor which calls where served
    after void timeShift() {
    	if (! isMethaneLevelCritical() 
    		&& getWaterLevel() == 2
    		&& ! isPumpRunning()) {
    		fail;
    	}
    }

// after programTermination
// fail on remaining calls
//    after void runTest() {
//    }
}
