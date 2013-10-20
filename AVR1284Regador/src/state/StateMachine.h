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

typedef struct _StateMachine{
	State * currentState;
	bool stop;
} StateMachine;

void StateMachine_start(StateMachine * this, void * dataForInitialStep);


void StateMachine_new(StateMachine * this, State * initialState);


#endif /* STATEMACHINE_H_ */
