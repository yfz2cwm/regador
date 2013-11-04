/*
 * StateBaseMenuEntry.h
 *
 *  Created on: Nov 4, 2013
 *      Author: dev
 */

#ifndef STATEBASEMENUENTRY_H_
#define STATEBASEMENUENTRY_H_
#include <stdbool.h>
#include "../state/State.h"

typedef struct {
	State super;
	Transition up;
	Transition down;
	Transition enter;
	Transition back;
	bool shouldPaint;
} StateBaseMenuEntry;

void StateBaseMenuEntry_new(StateBaseMenuEntry * this, Transition up, Transition down, Transition enter, Transition back, State_stateLoop stateLoop);

Transition StateBaseMenuEntry_doTransitionIfNeeded(StateBaseMenuEntry * this);

State * StateBaseMenuEntry_getState(StateBaseMenuEntry * this);

#endif /* STATEBASEMENUENTRY_H_ */
