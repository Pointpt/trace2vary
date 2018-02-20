#include "MinePump.h"
#include "Environment.h"
#include <stdio.h>

automaton Specification5 {
// Specification 5: The Pump is never switched on when the water is below the highWater sensor.
    introduction {
		int switchedOnBeforeTS;
    }

    // initalization
    before void runTest() {
    	switchedOnBeforeTS = 0;
    }

    before void timeShift() {
		switchedOnBeforeTS = isPumpRunning();    	
    }

// after timeshift
// monitor which calls where served
    after void timeShift() {
    	if (getWaterLevel() != 2 
    		&& isPumpRunning()
    		&& ! switchedOnBeforeTS) {
    		fail;
    	}
    }

// after programTermination
// fail on remaining calls
//    after void runTest() {
//    }
}
