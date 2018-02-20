#include "MinePump.h"
#include "Environment.h"
#include <stdio.h>

automaton Specification2 {
	// Original : When the pump is running, and there is methane, then it is eventually switched off.
	// my Version:
	// Specification 2: When the pump is running, and there is methane, then it is in switched on at most 1 timesteps.
    introduction {
    	int methAndRunningLastTime;
    }

    // initalization
    before void runTest() {
    	methAndRunningLastTime = 0;
    }

// after timeshift
// monitor which calls where served
    after void timeShift() {
    	if (isMethaneLevelCritical() && isPumpRunning()) {
    	    if (methAndRunningLastTime) {
    			fail;
    		} else {
    			methAndRunningLastTime = 1;
    		}
    	} else {
    		methAndRunningLastTime = 0;
    	}
    }

// after programTermination
// fail on remaining calls
//    after void runTest() {
//    }
}
