#include <stdio.h>
#include <stdlib.h>

#include "Floor.h"

int calls_0;
int calls_1;
int calls_2;
int calls_3;
int calls_4;

int personOnFloor_0_0;
int personOnFloor_0_1;
int personOnFloor_0_2;
int personOnFloor_0_3;
int personOnFloor_0_4;
int personOnFloor_1_0;
int personOnFloor_1_1;
int personOnFloor_1_2;
int personOnFloor_1_3;
int personOnFloor_1_4;
int personOnFloor_2_0;
int personOnFloor_2_1;
int personOnFloor_2_2;
int personOnFloor_2_3;
int personOnFloor_2_4;
int personOnFloor_3_0;
int personOnFloor_3_1;
int personOnFloor_3_2;
int personOnFloor_3_3;
int personOnFloor_3_4;
int personOnFloor_4_0;
int personOnFloor_4_1;
int personOnFloor_4_2;
int personOnFloor_4_3;
int personOnFloor_4_4;
int personOnFloor_5_0;
int personOnFloor_5_1;
int personOnFloor_5_2;
int personOnFloor_5_3;
int personOnFloor_5_4;

void initFloors() {
	calls_0 = 0;
	calls_1 = 0;
	calls_2 = 0;
	calls_3 = 0;
	calls_4 = 0;
	personOnFloor_0_0 = 0;
	personOnFloor_0_1 = 0;
	personOnFloor_0_2 = 0;
	personOnFloor_0_3 = 0;
	personOnFloor_0_4 = 0;
	personOnFloor_1_0 = 0;
	personOnFloor_1_1 = 0;
	personOnFloor_1_2 = 0;
	personOnFloor_1_3 = 0;
	personOnFloor_1_4 = 0;
	personOnFloor_2_0 = 0;
	personOnFloor_2_1 = 0;
	personOnFloor_2_2 = 0;
	personOnFloor_2_3 = 0;
	personOnFloor_2_4 = 0;
	personOnFloor_3_0 = 0;
	personOnFloor_3_1 = 0;
	personOnFloor_3_2 = 0;
	personOnFloor_3_3 = 0;
	personOnFloor_3_4 = 0;
	personOnFloor_4_0 = 0;
	personOnFloor_4_1 = 0;
	personOnFloor_4_2 = 0;
	personOnFloor_4_3 = 0;
	personOnFloor_4_4 = 0;
	personOnFloor_5_0 = 0;
	personOnFloor_5_1 = 0;
	personOnFloor_5_2 = 0;
	personOnFloor_5_3 = 0;
	personOnFloor_5_4 = 0;
}

int isFloorCalling(int floorID) {
	if (floorID == 0) return calls_0;
	else if (floorID == 1) return calls_1;
	else if (floorID == 2) return calls_2;
	else if (floorID == 3) return calls_3;
	else if (floorID == 4) return calls_4;
	return 0;
}

void resetCallOnFloor(int floorID) {
	if (floorID == 0) calls_0 = 0;
	else if (floorID == 1) calls_1 = 0;
	else if (floorID == 2) calls_2 = 0;
	else if (floorID == 3) calls_3 = 0;
	else if (floorID == 4) calls_4 = 0;
}

void callOnFloor(int floorID) {
	if (floorID == 0) calls_0 = 1;
	else if (floorID == 1) calls_1 = 1;
	else if (floorID == 2) calls_2 = 1;
	else if (floorID == 3) calls_3 = 1;
	else if (floorID == 4) calls_4 = 1;
}

int isPersonOnFloor(int person, int floor) {
	if (floor == 0) {
		if (person == 0) return personOnFloor_0_0;
		else if (person == 1) return personOnFloor_1_0;
		else if (person == 2) return personOnFloor_2_0;
		else if (person == 3) return personOnFloor_3_0;
		else if (person == 4) return personOnFloor_4_0;
		else if (person == 5) return personOnFloor_5_0;
	} else if (floor == 1) {
		if (person == 0) return personOnFloor_0_1;
		else if (person == 1) return personOnFloor_1_1;
		else if (person == 2) return personOnFloor_2_1;
		else if (person == 3) return personOnFloor_3_1;
		else if (person == 4) return personOnFloor_4_1;
		else if (person == 5) return personOnFloor_5_1;
	} else if (floor == 2) {
		if (person == 0) return personOnFloor_0_2;
		else if (person == 1) return personOnFloor_1_2;
		else if (person == 2) return personOnFloor_2_2;
		else if (person == 3) return personOnFloor_3_2;
		else if (person == 4) return personOnFloor_4_2;
		else if (person == 5) return personOnFloor_5_2;
	} else if (floor == 3) {
		if (person == 0) return personOnFloor_0_3;
		else if (person == 1) return personOnFloor_1_3;
		else if (person == 2) return personOnFloor_2_3;
		else if (person == 3) return personOnFloor_3_3;
		else if (person == 4) return personOnFloor_4_3;
		else if (person == 5) return personOnFloor_5_3;
	} else if (floor == 4) {
		if (person == 0) return personOnFloor_0_4;
		else if (person == 1) return personOnFloor_1_4;
		else if (person == 2) return personOnFloor_2_4;
		else if (person == 3) return personOnFloor_3_4;
		else if (person == 4) return personOnFloor_4_4;
		else if (person == 5) return personOnFloor_5_4;
	}
	return 0;
}
void initPersonOnFloor(int person, int floor) {
	if (floor == 0) {
		if (person == 0)  personOnFloor_0_0 = 1;
		else if (person == 1)  personOnFloor_1_0 = 1;
		else if (person == 2)  personOnFloor_2_0 = 1;
		else if (person == 3)  personOnFloor_3_0 = 1;
		else if (person == 4)  personOnFloor_4_0 = 1;
		else if (person == 5)  personOnFloor_5_0 = 1;
	} else if (floor == 1) {
		if (person == 0)  personOnFloor_0_1 = 1;
		else if (person == 1)  personOnFloor_1_1 = 1;
		else if (person == 2)  personOnFloor_2_1 = 1;
		else if (person == 3)  personOnFloor_3_1 = 1;
		else if (person == 4)  personOnFloor_4_1 = 1;
		else if (person == 5)  personOnFloor_5_1 = 1;
	} else if (floor == 2) {
		if (person == 0)  personOnFloor_0_2 = 1;
		else if (person == 1)  personOnFloor_1_2 = 1;
		else if (person == 2)  personOnFloor_2_2 = 1;
		else if (person == 3)  personOnFloor_3_2 = 1;
		else if (person == 4)  personOnFloor_4_2 = 1;
		else if (person == 5)  personOnFloor_5_2 = 1;
	} else if (floor == 3) {
		if (person == 0)  personOnFloor_0_3 = 1;
		else if (person == 1)  personOnFloor_1_3 = 1;
		else if (person == 2)  personOnFloor_2_3 = 1;
		else if (person == 3)  personOnFloor_3_3 = 1;
		else if (person == 4)  personOnFloor_4_3 = 1;
		else if (person == 5)  personOnFloor_5_3 = 1;
	} else if (floor == 4) {
		if (person == 0)  personOnFloor_0_4 = 1;
		else if (person == 1)  personOnFloor_1_4 = 1;
		else if (person == 2)  personOnFloor_2_4 = 1;
		else if (person == 3)  personOnFloor_3_4 = 1;
		else if (person == 4)  personOnFloor_4_4 = 1;
		else if (person == 5)  personOnFloor_5_4 = 1;
	}
	callOnFloor(floor);
}
void removePersonFromFloor(int person, int floor) {
	if (floor == 0) {
		if (person == 0)  personOnFloor_0_0= 0;
		else if (person == 1)  personOnFloor_1_0= 0;
		else if (person == 2)  personOnFloor_2_0= 0;
		else if (person == 3)  personOnFloor_3_0= 0;
		else if (person == 4)  personOnFloor_4_0= 0;
		else if (person == 5)  personOnFloor_5_0= 0;
	} else if (floor == 1) {
		if (person == 0)  personOnFloor_0_1= 0;
		else if (person == 1)  personOnFloor_1_1= 0;
		else if (person == 2)  personOnFloor_2_1= 0;
		else if (person == 3)  personOnFloor_3_1= 0;
		else if (person == 4)  personOnFloor_4_1= 0;
		else if (person == 5)  personOnFloor_5_1= 0;
	} else if (floor == 2) {
		if (person == 0)  personOnFloor_0_2= 0;
		else if (person == 1)  personOnFloor_1_2= 0;
		else if (person == 2)  personOnFloor_2_2= 0;
		else if (person == 3)  personOnFloor_3_2= 0;
		else if (person == 4)  personOnFloor_4_2= 0;
		else if (person == 5)  personOnFloor_5_2= 0;
	} else if (floor == 3) {
		if (person == 0)  personOnFloor_0_3= 0;
		else if (person == 1)  personOnFloor_1_3= 0;
		else if (person == 2)  personOnFloor_2_3= 0;
		else if (person == 3)  personOnFloor_3_3= 0;
		else if (person == 4)  personOnFloor_4_3= 0;
		else if (person == 5)  personOnFloor_5_3= 0;
	} else if (floor == 4) {
		if (person == 0)  personOnFloor_0_4= 0;
		else if (person == 1)  personOnFloor_1_4= 0;
		else if (person == 2)  personOnFloor_2_4= 0;
		else if (person == 3)  personOnFloor_3_4= 0;
		else if (person == 4)  personOnFloor_4_4= 0;
		else if (person == 5)  personOnFloor_5_4= 0;
	}
	resetCallOnFloor(floor);
}
int isTopFloor(int floorID) {
	return floorID == buildingSize-1;
}
