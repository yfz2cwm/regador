/*
 * state.h
 *
 *  Created on: Oct 12, 2013
 *      Author: juan
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct Transition Transition;
typedef struct State State;

typedef Transition (*State_stateLoop)(void * stateInstance, void* transitionData);

struct Transition {
	State * nextState;
	void * dataFornextState;

};

struct State {
	State_stateLoop stateLoop;
	void * concreteStateInstance;
};

void State_new(State * this, void * concreteStateInstance, State_stateLoop stateLoop);

Transition Transition_nullTransition();

bool Transition_isNullTransition(Transition * this);

Transition * Transition_new(Transition * this, State * state, void * transitionData);
#endif /* STATE_H_ */
