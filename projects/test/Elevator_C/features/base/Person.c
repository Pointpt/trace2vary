#include <stdio.h>
#include <stdlib.h>

#include "Person.h"

/* Persons:
 * bob : 0
 * alice : 1
 * angelina : 2
 * chuck : 3
 * monica : 4
 * bigMac : 5
 *
 */


int getWeight(int person) {
	if (person == 0) {
		return 40;
	} else if (person == 1) {
		return 40;
	} else if (person == 2) {
		return 40;
	} else if (person == 3) {
		return 40;
	} else if (person == 4) {
		return 30;
	} else if (person == 5) {
		return 150;
	} else {
		return 0;
	}
}

int getOrigin(int person) {
	if (person == 0) {
		return 4;
	} else if (person == 1) {
		return 3;
	} else if (person == 2) {
		return 2;
	} else if (person == 3) {
		return 1;
	} else if (person == 4) {
		return 0;
	} else if (person == 5) {
		return 1;
	} else {
		return 0;
	}
}
int getDestination(int person) {
	if (person == 0) {
		return 0;
	} else if (person == 1) {
		return 0;
	} else if (person == 2) {
		return 1;
	} else if (person == 3) {
		return 3;
	} else if (person == 4) {
		return 1;
	} else if (person == 5) {
		return 3;
	} else {
		return 0;
	}
}
