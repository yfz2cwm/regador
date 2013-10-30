/*
 * StateShowNumber.c
 *
 *  Created on: Oct 27, 2013
 *      Author: juan
 */

#include <stdio.h>
#include "StateShowNumber.h"
#include "../lcd/lcd.h"
#include "../buttons/buttons.h"

void StateShowNumber_new(StateShowNumber * this, char * label, uint16_t * variable, Transition returnTransition, Transition editTransition) {
	State_new(&(this->selfState), &StateShowNumber_showNumber);
	this->label = label;
	this->variable = variable;
	this->returnTransition = returnTransition;
	this->editTransition = editTransition;
	this->shouldPrint = true;
}

void StateShowNumber_updateScreen(StateShowNumber * instance) {
	if (instance->shouldPrint) {
		LCDClear();
		LCDWriteStringXY(0, 0, instance->label);
		char buff[12];
		snprintf(buff, 12, "%d", *instance->variable);
		LCDWriteStringXY(0, 1, (const char * )buff);
	}
}

Transition StateShowNumber_showNumber(void * data) {
	Transition noTransition;
	ButtonsStatus buttonStatus;
	StateShowNumberTransitionData * transitionData = (StateShowNumberTransitionData *) data;
	StateShowNumber_updateScreen(transitionData->instance);
	readButtons(&buttonStatus);
	transitionData->instance->shouldPrint = false;

	if (buttonStatus.button.back) {
		transitionData->instance->shouldPrint = true;
		return transitionData->instance->returnTransition;
	} else if (buttonStatus.button.enter) {
		if (!Transition_isNullTransition(&(transitionData->instance->editTransition))) {
			transitionData->instance->shouldPrint = true;
			return transitionData->instance->editTransition;
		}
	}

	noTransition.nextState = &(transitionData->instance->selfState);
	noTransition.dataFornextState = transitionData;
	return noTransition;
}
