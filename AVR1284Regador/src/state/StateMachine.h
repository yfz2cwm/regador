/*
 * StateMachine.h
 *
 *  Created on: Oct 12, 2013
 *      Author: juan
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include <stdbool.h>
#include "State.h"

typedef struct {
	Transition * transition;
	uint16_t transitionCount;
} TransitionList;

typedef struct _StateMachine{
	TransitionList * currentTransitions;
	bool stop;
} StateMachine;

void StateMachine_start(StateMachine * this);


void StateMachine_new(StateMachine * this, TransitionList * initialTransition);


#endif /* STATEMACHINE_H_ */
