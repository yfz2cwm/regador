/*
 * State.c
 *
 *  Created on: Oct 12, 2013
 *      Author: juan
 */
#include "State.h"
#include <stddef.h>

void State_new(State * this, Transition (*stateLoop)(void*)) {
	this->stateLoop = stateLoop;
}

Transition Transition_nullTransition(){
	Transition toReturn;
	toReturn.dataFornextState = NULL;
	toReturn.nextState = NULL;
	return toReturn;
}

bool Transition_isNullTransition(Transition * this){
	return this->nextState == NULL;
}
