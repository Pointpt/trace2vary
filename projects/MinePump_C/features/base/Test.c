#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int cleanupTimeShifts = 4;

int get_nondet() {
    int nd;
    return nd;
}

void cleanup() {
	// minimum 1 timeShift(), maximum cleanupTimeShifts.
	// (1 is needed for certain scenarios)
	timeShift();
	int i;
	for (i = 0; i < cleanupTimeShifts - 1; i++) {
		timeShift();
	}
}
/*
	void randomSequenceOfActions() {
		int maxLength = 4;
		int counter = 0;
		while (counter < maxLength) {
			counter++;
			int action = get_nondetMinMax(0, 7);
			if (get_nondet()) {
				waterRise();
				//actionName += "rise ";
			}
			if (get_nondet()) {
				changeMethaneLevel();
				//actionName += "methChange ";
			}
			if (get_nondet()) {
				startSystem();
				//actionName += "start ";
			} else if (get_nondet()) {
				stopSystem();
				//actionName += "stop ";
			}
			timeShift();
			//actionHistory.add(actionName);
			// System.out.println(listToString(actionHistory));
			//System.out.println(a.getSystemState());
		}
		cleanup();
	}*/
	void Specification2() {
		timeShift();printPump();
		timeShift();printPump();
		timeShift();printPump();
		waterRise();printPump();
		timeShift();printPump();
		changeMethaneLevel();printPump();
		timeShift();printPump();
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
