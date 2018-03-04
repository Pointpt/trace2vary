	#include "Environment.h"
	#include "MinePump.h"


int pumpRunning = 0;
int systemActive = 1;

	void timeShift() {
		if (pumpRunning)
			lowerWaterLevel();
		if (systemActive)
			processEnvironment();
	}
	void processEnvironment() {
		
	}

	void activatePump() {
		pumpRunning = 1;
	}

	void deactivatePump() {
		pumpRunning = 0;
	}
	
	int isMethaneAlarm() {
		return isMethaneLevelCritical();
	}

	int isPumpRunning() {
		return pumpRunning;
	}

	void printPump() {
		printf("Pump(System:");
		if (systemActive)
			printf("On");
		else
			printf("Off");
		printf(",Pump:");
		if (pumpRunning)
			printf("On");
		else
			printf("Off");
		printf(") ");
		printEnvironment();
		printf("\n");
	}
