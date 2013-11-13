/*
 * StateShowTime.c
 *
 *  Created on: Nov 13, 2013
 *      Author: juan
 */

#include "StateShowTime.h"
#include <stdio.h>
#include "../lcd/lcd.h"

void StateShowTime_new(StateShowTime * this,
		char* label,
		Time * variable,
		Transition returnTransition,
		Transition editTransition) {
	StateMenuEntry_new(&this->super, label, Transition_nullTransition(), Transition_nullTransition(), editTransition, returnTransition);
	StateMenuEntry_setStateLoop(&this->super, &StateShowTime_show);
	this->variable = variable;
}

void StateShowTime_updateScreen(StateShowTime * this) {
	StateMenuEntry_updateScreen(&this->super);
	if (StateMenuEntry_shouldPaint(&this->super)) {
		Time * time = this->variable;
		char buff[17];
		char buffTimeString[9];
		snprintf(buffTimeString,9, "%02d:%02d:%02d", time->hours, time->minutes, time->seconds);
		snprintf(buff, 17, "%16s", buffTimeString);
		LCDWriteStringXY(0, 1, (const char *) buff);
	}
}

Transition StateShowTime_show(void * instance, void * data) {
	StateShowTime * this = (StateShowTime *) instance;
	StateShowTime_updateScreen(this);
	return StateBaseMenuEntry_doTransitionIfNeeded(&this->super.super);
}

State * StateShowTime_getState(StateShowTime * this) {
	return StateMenuEntry_getState(&this->super);
}
