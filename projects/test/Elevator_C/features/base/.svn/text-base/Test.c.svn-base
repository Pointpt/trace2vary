#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include "Elevator.h"
//#include "Person.h"
//#include "Floor.h"



int cleanupTimeShifts = 12;


int get_nondet() {
    int nd;
    return nd;
}

int get_nondetMinMax07() {
    int nd;
    
    if (nd==0) {
	return 0;
    } else if (nd==1) {
	return 1;
    } else if (nd==2) {
	return 2;
    } else if (nd==3) {
	return 3;
    } else if (nd==4) {
	return 4;
    } else if (nd==5) {
	return 5;
    } else if (nd==6) {
	return 6;
    } else if (nd==7) {
	return 7;
    } else {
    	exit(0);
    }
}

void bobCall()      { initPersonOnFloor(0, getOrigin(0)); }
void aliceCall()    { initPersonOnFloor(1, getOrigin(1)); }
void angelinaCall() { initPersonOnFloor(2, getOrigin(2)); }
void chuckCall()    { initPersonOnFloor(3, getOrigin(3)); }
void monicaCall()   { initPersonOnFloor(4, getOrigin(4)); }
void bigMacCall()   { initPersonOnFloor(5, getOrigin(5)); }
void threeTS()      { timeShift(); timeShift(); timeShift(); }
void cleanup() {
	// minimum 1 timeShift(), maximum cleanupTimeShifts.
	// (1 is needed for certain scnearios)
	timeShift();
	int i;
	for (i = 0; i < cleanupTimeShifts-1 && isBlocked()!=1; i++) {
		if (isIdle())
			return;
		else
			timeShift();
		//printState();
	}
}

void randomSequenceOfActions() {
		int maxLength = 4;
		if (get_nondet()) {
			// elevator from 4 going down
			initTopDown();
			//e = new Elevator(env, verbose, 4, false);
			//actionHistory.add("StartFromTop");
		} else {
			initBottomUp();
			// elevator from 0 going up
			//e = new Elevator(env, verbose);
			//actionHistory.add("StartFromBottom");
		}
		int counter = 0;
		while (counter < maxLength) {
			counter++;
			int action = get_nondetMinMax07();

			//if (action == 3 || action == 4) exit(0); // dont use chuck and monica
			// java used chuck and monica, too

			//String actionName = "";
			if (action < 6) {
				int origin = getOrigin(action);
				initPersonOnFloor(action, origin);
			} else if (action == 6) {
				timeShift(); // execute one timestep
			} else if (action == 7) {
				// execute three timesteps
				timeShift();
				timeShift();
				timeShift();
				// nobody calls
			}
			//actionHistory.add(actionName);
			//System.out.println(listToString(actionHistory));
			if (isBlocked()) {
				return;
			}
		}
		cleanup();
	}


void runTest_Simple() {
	bigMacCall();
	angelinaCall();
	cleanup();
}


	void Specification1() {
		bigMacCall();
		angelinaCall();
		cleanup();
	}

	void Specification2() {
		bigMacCall();
		cleanup();
	}
	void Specification3() {
		bobCall();
		timeShift();
		timeShift();
		timeShift();
		timeShift();

		timeShift();
		// executive suite calls again
		// (lift should reverse directions although in-lift button for bob's
		// destination is still pressed)
		// direction, is active)
		bobCall();
		cleanup();
	}


void setup() {
}
// this function is the hook for the specifications
// the generated scenarios do not work if the generated test()-function is called outside of this method!
void runTest() {
	//runTest_Simple();
	//randomSequenceOfActions();
	test();
}
int
main (void)
{ 
  select_helpers();
  select_features();
  if (valid_product()) { 
      setup();
      runTest();
  }
  return 0;

}
