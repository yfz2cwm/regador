/*
 * State.c
 *
 *  Created on: Oct 12, 2013
 *      Author: juan
 */
#include "State.h"

void State_new(State * this, Transition (*stateLoop)(void*)) {
	this->stateLoop = stateLoop;
}

