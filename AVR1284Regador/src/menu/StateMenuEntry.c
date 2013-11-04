/*
 * StateMenuEntry.c
 *
 *  Created on: Oct 27, 2013
 *      Author: juan
 */
#include <stddef.h>
#include "StateMenuEntry.h"
#include "../lcd/lcd.h"
#include "../buttons/buttons.h"

void StateMenuEntry_new(StateMenuEntry * this, char * label, Transition up, Transition down, Transition enter, Transition back) {
	StateBaseMenuEntry_new(&this->super, up, down, enter, back, &StateMenuEntry_showMenu);
	this->label = label;
}

void StateMenuEntry_updateScreen(StateMenuEntry * this) {
	if (this->super.shouldPaint) {
		LCDClear();
		LCDWriteStringXY(0, 0, this->label);
	}
}

Transition StateMenuEntry_showMenu(void* instance, void * data) {
	StateMenuEntry * this = (StateMenuEntry *) instance;

	StateMenuEntry_updateScreen(this);
	return StateBaseMenuEntry_doTransitionIfNeeded(&this->super);
}

State * StateMenuEntry_getState(StateMenuEntry * this){
	return StateBaseMenuEntry_getState(&this->super);
}
