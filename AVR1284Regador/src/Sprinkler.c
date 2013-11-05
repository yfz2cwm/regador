/*
 * Sprinkler.c
 *
 *  Created on: Nov 5, 2013
 *      Author: juan
 */
#include "Sprinkler.h"

void Sprinkler_new(Sprinkler * this) {
	State_new(&this->super, this, &Sprinkler_stateLoop);
	this->working = true;
}

Transition Sprinkler_stateLoop(void * instance, void * transitionData) {
	Sprinkler * this = (Sprinkler *) instance;
	//TODO implement
	Transition noTransition;
	Transition_new(&noTransition, &this->super, transitionData);

	return noTransition;
}
