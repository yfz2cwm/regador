/*
 * StateCfgNumber.c
 *
 *  Created on: Oct 26, 2013
 *      Author: juan
 */
#include "StateCfgNumber.h"
#include "../lcd/lcd.h"
#include "../buttons/buttons.h"

void StateCfgNumber_new(StateCfgNumber * this, char* label, uint16_t * variable, State * returnState) {
	this->label = label;
	this->variable = variable;
	this->returnState = returnState;
	this->firstTime = true;
	this->lastSelectedValue = *variable;
	State_new(&(this->selfState), &StateCfgNumber_cfgNumber);

}

void StateCfgNumber_updateScreen(StateCfgNumber* instance) {
	if (instance->firstTime) {
		LCDWriteStringXY(0, 0, instance->label);
	}
	if (instance->lastSelectedValue != instance->lastPrintValue) {
		LCDWriteStringXY(1, 1, instance->label);
	}
}

Transition StateCfgNumber_cfgNumber(void * data) {
	Transition transition;
	ButtonsStatus buttonStatus;
	StateCfgNumberTransitionData * transitionData = (StateCfgNumberTransitionData *) data;
	StateCfgNumber * instance = transitionData->instance;

	StateCfgNumber_updateScreen(instance);
	transition.nextState = &(instance->selfState);
	instance->firstTime = false;

	readButtons(&buttonStatus);
	if(buttonStatus.button.enter){
		*instance->variable = instance->lastSelectedValue;
		instance->firstTime = true;
		transition.nextState = instance->returnState;
	}else if (buttonStatus.button.back) {
		instance->firstTime = true;
		transition.nextState = instance->returnState;
	}else if (buttonStatus.button.down){
		instance->lastSelectedValue--;
	}else if (buttonStatus.button.up){
		instance->lastSelectedValue++;
	}
	return transition;
}
