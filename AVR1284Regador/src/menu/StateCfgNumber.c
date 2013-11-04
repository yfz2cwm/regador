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

void StateCfgNumber_new(StateCfgNumber * this, char* label, uint16_t * variable, Transition * returnTransition) {
	this->label = label;
	this->variable = variable;
	this->returnTransition = returnTransition;
	this->shouldPrint = true;
	this->lastSelectedValue = *variable;
	State_new(&(this->super),this, &StateCfgNumber_cfgNumber);
}

void StateCfgNumber_updateScreen(StateCfgNumber* instance) {
	if (instance->shouldPrint) {
		LCDClear();
		LCDWriteStringXY(0, 0, instance->label);
	}
	if (instance->lastSelectedValue != instance->lastPrintValue) {
		char buff[17];
		snprintf(buff, 17, "%16d", instance->lastSelectedValue);
		LCDWriteStringXY(0, 1, (const char * )buff);
		instance->lastPrintValue = instance->lastSelectedValue;
	}
}

Transition StateCfgNumber_cfgNumber(void * instance, void * data) {
	Transition transition;
	ButtonsStatus buttonStatus;
	StateCfgNumber * this = instance;

	if (this->shouldPrint) {
		this->lastSelectedValue = *this->variable;
		//Force print the last selected value.
		this->lastPrintValue = this->lastSelectedValue + 1;
	}

	StateCfgNumber_updateScreen(this);
	transition.nextState = &(this->super);
	transition.dataFornextState = NULL;

	this->shouldPrint = false;

	readButtons(&buttonStatus);
	if (buttonStatus.button.enter) {
		*this->variable = this->lastSelectedValue;
		this->shouldPrint = true;
		transition = *this->returnTransition;
	} else if (buttonStatus.button.back) {
		this->shouldPrint = true;
		transition = *this->returnTransition;
	} else if (buttonStatus.button.down) {
		this->lastSelectedValue--;
	} else if (buttonStatus.button.up) {
		this->lastSelectedValue++;
	}
	return transition;
}
