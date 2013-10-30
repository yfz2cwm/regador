/*
 * StateCfgNumber.c
 *
 *  Created on: Oct 26, 2013
 *      Author: juan
 */
#include <stdio.h>
#include "StateCfgNumber.h"
#include "../lcd/lcd.h"
#include "../buttons/buttons.h"

void StateCfgNumber_new(StateCfgNumber * this, char* label, uint16_t * variable, Transition returnTransition) {
	this->label = label;
	this->variable = variable;
	this->returnTransition = returnTransition;
	this->shouldPrint = true;
	this->lastSelectedValue = *variable;
	State_new(&(this->selfState), &StateCfgNumber_cfgNumber);
}

void StateCfgNumber_updateScreen(StateCfgNumber* instance) {
	if (instance->shouldPrint) {
		LCDWriteStringXY(0, 0, instance->label);
	}
	if (instance->lastSelectedValue != instance->lastPrintValue) {
		char buff[17];
		snprintf(buff, 17, "%16d", instance->lastSelectedValue);
		LCDWriteStringXY(0, 1, (const char * )buff);
		instance->lastPrintValue = instance->lastSelectedValue;
	}
}

Transition StateCfgNumber_cfgNumber(void * data) {
	Transition transition;
	ButtonsStatus buttonStatus;
	StateCfgNumberTransitionData * transitionData = (StateCfgNumberTransitionData *) data;
	StateCfgNumber * instance = transitionData->instance;

	if(instance->shouldPrint){
		instance->lastSelectedValue = *instance->variable;
		//Force print the last selected value.
		instance->lastPrintValue = instance->lastSelectedValue +1;
	}

	StateCfgNumber_updateScreen(instance);
	transition.nextState = &(instance->selfState);
	instance->shouldPrint = false;

	readButtons(&buttonStatus);
	if(buttonStatus.button.enter){
		*instance->variable = instance->lastSelectedValue;
		instance->shouldPrint = true;
		transition =  instance->returnTransition;
	}else if (buttonStatus.button.back) {
		instance->shouldPrint = true;
		transition =  instance->returnTransition;
	}else if (buttonStatus.button.down){
		instance->lastSelectedValue--;
	}else if (buttonStatus.button.up){
		instance->lastSelectedValue++;
	}
	return transition;
}
