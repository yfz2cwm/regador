/*
 * StateMachine.c
 *
 *  Created on: Oct 12, 2013
 *      Author: juan
 */

#include "StateMachine.h"

void StateMachine_start(StateMachine * this, void * dataForInitialStep) {
	Transition transition;
	void * dataForNextStep = dataForInitialStep;
	while (!this->stop) {
		transition = this->currentState->stateLoop(dataForNextStep);
		this->currentState = transition.nextState;
		dataForNextStep = transition.dataFornextState;
	}

}

void StateMachine_new(StateMachine * this, State * initialState) {
	this->currentState = initialState;
	this->stop = false;
}
