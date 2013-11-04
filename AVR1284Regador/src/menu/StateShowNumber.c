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
	State_new(&(this->super),this, &StateShowNumber_showNumber);
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
		char buff[17];
		snprintf(buff, 17, "%16d", *instance->variable);
		LCDWriteStringXY(0, 1, (const char * )buff);
	}
}

Transition StateShowNumber_showNumber(void * instance, void * data) {
	StateShowNumber * this =  (StateShowNumber * ) instance;
	Transition noTransition;
	ButtonsStatus buttonStatus;
	StateShowNumber_updateScreen(this);
	readButtons(&buttonStatus);
	this->shouldPrint = false;

	if (buttonStatus.button.back) {
		this->shouldPrint = true;
		return this->returnTransition;
	} else if (buttonStatus.button.enter) {
		if (!Transition_isNullTransition(&(this->editTransition))) {
			this->shouldPrint = true;
			return this->editTransition;
		}
	}

	noTransition.nextState = &(this->super);
	return noTransition;
}
