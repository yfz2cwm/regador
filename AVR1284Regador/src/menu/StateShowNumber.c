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
	StateMenuEntry_new(&this->super, label, Transition_nullTransition(), Transition_nullTransition(), editTransition, returnTransition);
	StateMenuEntry_setStateLoop(&this->super, &StateShowNumber_showNumber);
	this->variable = variable;
}

void StateShowNumber_updateScreen(StateShowNumber * this) {
	StateMenuEntry_updateScreen(&this->super);
	if (this->super.super.shouldPaint) {
		char buff[17];
		snprintf(buff, 17, "%16d", *this->variable);
		LCDWriteStringXY(0, 1, (const char * )buff);
	}
}

Transition StateShowNumber_showNumber(void * instance, void * data) {
	StateShowNumber * this = (StateShowNumber *) instance;
	StateShowNumber_updateScreen(this);
	return StateBaseMenuEntry_doTransitionIfNeeded(&this->super.super);
}

State * StateShowNumber_getState(StateShowNumber * this){
	return StateMenuEntry_getState(&this->super);
}
