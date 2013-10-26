/*
 * StateMachine.c
 *
 *  Created on: Oct 12, 2013
 *      Author: juan
 */

#include "StateMachine.h"

void StateMachine_start(StateMachine * this) {
	uint16_t i = 0;
	while (!this->stop) {
		for (i = 0; i < this->currentTransitions->transitionCount; i++) {
			void * dataForNextStep = this->currentTransitions->transition[i].dataFornextState;
			Transition transition = this->currentTransitions->transition[i].nextState->stateLoop(dataForNextStep);
			this->currentTransitions->transition[i] = transition;
		}
	}

}

void StateMachine_new(StateMachine * this, TransitionList * initialTransition) {
	this->currentTransitions = initialTransition;
	this->stop = false;
}
