#include <stdio.h>
#include <stdlib.h>

#include "Elevator.h"
#include "Person.h"
#include "Floor.h"

int cleanupTimeShifts = 12;
/* persons:
 * 0 bob
 * 1 alice
 * 2 angelina
 * 3 chuck
 * 4 monica
 * 5 bigMac
 */

void spec1() {
	initBottomUp();
	initPersonOnFloor(5,getOrigin(5));
	printState();
	//a.bigMacCall(); return new Person("BigMac", 150, 1, 3, env);

	initPersonOnFloor(2,getOrigin(2));
	printState();
	//a.angelinaCall(); return new Person("angelina", 40, 2, 1, env);

	int i;
	for (i = 0; i < cleanupTimeShifts && isBlocked()!=1; i++) {
		timeShift();
		printState();
	}
}

void spec14() {
	initTopDown();
	initPersonOnFloor(5,getOrigin(5));
	printState();
	//a.bigMacCall(); return new Person("BigMac", 150, 1, 3, env);
	timeShift();
	timeShift();
	timeShift();
	timeShift();

	initPersonOnFloor(0,getOrigin(0));
	printState();
	//a.angelinaCall(); return new Person("angelina", 40, 2, 1, env);

	int i;
	for (i = 0; i < cleanupTimeShifts && isBlocked()!=1; i++) {
		timeShift();
		printState();
	}
}


