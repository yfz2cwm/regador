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

void StateCfgNumber_new(StateCfgNumber * this, char* label, int16_t * variable, Transition * returnTransition) {
	this->label = label;
	this->variable = variable;
	this->returnTransition = returnTransition;
	this->shouldPrint = true;
	this->lastSelectedValue = *variable;
	State_new(&(this->super), this, &StateCfgNumber_cfgNumber);
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
		StateCfgNumber_decrease(this);
	} else if (buttonStatus.button.up) {
		StateCfgNumber_increase(this);
	}
	return transition;
}

bool StateCfgNumber_isLimited(StateCfgNumber* this){
	return this->upperLimit != this->lowerLimit;
}

void StateCfgNumber_setUpperLimit(StateCfgNumber* this, int16_t limit) {
	this->upperLimit = limit;
}

void StateCfgNumber_setLowerLimit(StateCfgNumber* this, int16_t limit) {
	this->lowerLimit = limit;
}

void StateCfgNumber_setCycle(StateCfgNumber* this, bool cycle) {
	this->cycle = cycle;
}

void StateCfgNumber_increase(StateCfgNumber* this) {
	this->lastSelectedValue++;
	if (StateCfgNumber_isLimited(this)) {
		if (this->lastSelectedValue > this->upperLimit) {
			if (this->cycle) {
				this->lastSelectedValue = this->lowerLimit;
			} else {
				this->lastSelectedValue--;
			}
		}
	}
}

void StateCfgNumber_decrease(StateCfgNumber* this) {
	this->lastSelectedValue--;
	if (StateCfgNumber_isLimited(this)) {
		if (this->lastSelectedValue < this->lowerLimit) {
			if (this->cycle) {
				this->lastSelectedValue = this->upperLimit;
			} else {
				this->lastSelectedValue++;
			}
		}
	}
}
