/*
 * State.c
 *
 *  Created on: Oct 12, 2013
 *      Author: juan
 */
#include "State.h"
#include <stddef.h>

void State_new(State * this, void * concreteStateInstance, State_stateLoop stateLoop){
	this->stateLoop = stateLoop;
	this->concreteStateInstance = concreteStateInstance;
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

Transition * Transition_new(Transition * this, State * state, void * transitionData){
	this->nextState = state;
	this->dataFornextState = transitionData;
	return this;
}
