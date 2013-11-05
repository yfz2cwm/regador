/*
 * StateShowOnOf.c
 *
 *  Created on: Nov 5, 2013
 *      Author: juan
 */
#include "StateShowOnOf.h"
#include <stdio.h>
#include "../lcd/lcd.h"

void StateShowOnOff_new(StateShowOnOff * this,
		char* label,
		bool * variable,
		Transition returnTransition,
		Transition editTransition) {
	StateMenuEntry_new(&this->super, label, Transition_nullTransition(), Transition_nullTransition(), editTransition, returnTransition);
	StateMenuEntry_setStateLoop(&this->super, &StateShowOnOff_showOnOff);
	this->variable = variable;
}

void StateShowOnOff_updateScreen(StateShowOnOff * this) {
	StateMenuEntry_updateScreen(&this->super);
	if (StateMenuEntry_shouldPaint(&this->super)) {
		char buff[17];
		snprintf(buff, 17, "%16s", *this->variable ? "On" : "Off");
		LCDWriteStringXY(0, 1, (const char *) buff);
	}
}

Transition StateShowOnOff_showOnOff(void * instance, void * data) {
	StateShowOnOff * this = (StateShowOnOff *) instance;
	StateShowOnOff_updateScreen(this);
	return StateBaseMenuEntry_doTransitionIfNeeded(&this->super.super);
}

State * StateShowOnOff_getState(StateShowOnOff * this) {
	return StateMenuEntry_getState(&this->super);
}

