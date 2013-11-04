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
	this->label = label;
	this->up = up;
	this->down = down;
	this->back = back;
	this->enter = enter;
	this->firstTime = true;
	State_new(&(this->super),this, &StateMenuEntry_showMenu);
}

void StateMenuEntry_updateScreen(StateMenuEntry * this) {
	if (this->firstTime) {
		LCDClear();
		LCDWriteStringXY(0, 0, this->label);
	}
}

Transition StateMenuEntry_showMenu(void* instance, void * data) {
	ButtonsStatus buttonStatus;
	Transition noTransition;
	StateMenuEntry * this = (StateMenuEntry *) instance;

	StateMenuEntry_updateScreen(this);
	this->firstTime = false;
	readButtons(&buttonStatus);

	noTransition.dataFornextState = data;
	noTransition.nextState = &(this->super);

	if (buttonStatus.buttons != 0) {
		this->firstTime = true;
	}

	if (buttonStatus.button.enter) {
		if (!Transition_isNullTransition(&(this->enter))) {
			return this->enter;
		}
	} else if (buttonStatus.button.back) {
		if (!Transition_isNullTransition(&(this->back))) {
			return this->back;
		}
	} else if (buttonStatus.button.down) {
		if (!Transition_isNullTransition(&(this->down))) {
			return this->down;
		}
	} else if (buttonStatus.button.up) {
		if (!Transition_isNullTransition(&(this->up))) {
			return this->up;
		}
	}
	return noTransition;
}

