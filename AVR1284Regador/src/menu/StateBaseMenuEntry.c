/*
 * StateBaseMenuEntry.c
 *
 *  Created on: Nov 4, 2013
 *      Author: dev
 */
#include <stddef.h>
#include "StateBaseMenuEntry.h"
#include "../buttons/buttons.h"

void StateBaseMenuEntry_new(StateBaseMenuEntry * this, Transition up, Transition down, Transition enter, Transition back, State_stateLoop stateLoop){
		this->up = up;
		this->down = down;
		this->back = back;
		this->enter = enter;
		this->shouldPaint= true;
		State_new(&(this->super),this, stateLoop);
}


Transition StateBaseMenuEntry_doTransitionIfNeeded(StateBaseMenuEntry * this) {
	ButtonsStatus buttonStatus;
	Transition noTransition;

	this->shouldPaint = false;
	readButtons(&buttonStatus);

	noTransition.dataFornextState = NULL;
	noTransition.nextState = &(this->super);

	//If transition should paint is true.
	if (buttonStatus.buttons != 0) {
		this->shouldPaint = true;
	}

	if (buttonStatus.button.enter) {
		if (!Transition_isNullTransition(&this->enter)) {
			return this->enter;
		}
	} else if (buttonStatus.button.back) {
		if (!Transition_isNullTransition(&this->back)) {
			return this->back;
		}
	} else if (buttonStatus.button.down) {
		if (!Transition_isNullTransition(&this->down)) {
			return this->down;
		}
	} else if (buttonStatus.button.up) {
		if (!Transition_isNullTransition(&this->up)) {
			return this->up;
		}
	}
	return noTransition;
}

State * StateBaseMenuEntry_getState(StateBaseMenuEntry * this){
	return &this->super;
}
void StateBaseMenuEntry_setStateLoop(StateBaseMenuEntry * this,State_stateLoop newStateLoop){
	this->super.stateLoop = newStateLoop;
}
