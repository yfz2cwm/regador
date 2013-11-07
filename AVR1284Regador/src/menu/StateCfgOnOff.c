/*
 * StateCfgOnOff.c
 *
 *  Created on: Nov 5, 2013
 *      Author: juan
 */

#include "StateCfgOnOff.h"
#include "../lcd/lcd.h"
#include <stddef.h>
#include <stdio.h>
#include "../buttons/buttons.h"

Transition StateCfgOnOff_cfgOnOff(void * instance, void * data) {
	Transition transition;
	ButtonsStatus buttonStatus;
	StateCfgOnOff* this = instance;

	if (this->shouldPrint) {
		this->lastSelectedValue = *this->variable;
		//Force print the last selected value.
		this->lastPrintValue = !this->lastSelectedValue;
	}

	StateCfgOnOff_updateScreen(this);
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
	} else if (buttonStatus.button.down || buttonStatus.button.up) {
		StateCfgOnOff_swapValue(this);
	}

	return transition;
}

void StateCfgOnOff_swapValue(StateCfgOnOff * this) {
	this->lastSelectedValue = !this->lastSelectedValue;
}

void StateCfgOnOff_new(StateCfgOnOff * this, char* label, bool * variable, Transition * returnTransition) {
	this->label = label;
	this->variable = variable;
	this->returnTransition = returnTransition;
	this->shouldPrint = true;
	this->lastSelectedValue = *variable;
	State_new(&(this->super), this, &StateCfgOnOff_cfgOnOff);
}

void StateCfgOnOff_updateScreen(StateCfgOnOff* this) {
	if (this->shouldPrint) {
		LCDClear();
		LCDWriteStringXY(0, 0, this->label);
	}

	if (this->lastSelectedValue != this->lastPrintValue) {
		char buff[17];
		snprintf(buff, 17, "%16s", *this->variable ? "On" : "Off");
		LCDWriteStringXY(0, 1, (const char *) buff);
		this->lastPrintValue = this->lastSelectedValue;
	}
}
