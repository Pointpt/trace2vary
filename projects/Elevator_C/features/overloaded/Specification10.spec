#include "Elevator.h"
#include "Floor.h"
#include <stdio.h>

automaton Specification10 {
	// specification 10
	/* Original: The Doors of the lift cannot be closed when the lift is overloaded.
	 * MyVersion: The doors are never closed when the lift is overloaded.
	 */
// after timeshift
    after void timeShift() {
	if (weight > maximumWeight && ! areDoorsOpen()) {
		 fail;
	 }
    }
}
