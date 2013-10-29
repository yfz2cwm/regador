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

struct Transition{
    State * nextState;
    void * dataFornextState;

};

struct State {
	Transition (*stateLoop)(void*);
};

void State_new (State * this, Transition (*stateLoop)(void*));

Transition Transition_nullTransition();

bool Transition_isNullTransition(Transition * this);

#endif /* STATE_H_ */
