/*
 * StateMenuEntry.c
 *
 *  Created on: Oct 27, 2013
 *      Author: juan
 */
#include "StateMenuEntry.h"
#include "../lcd/lcd.h"
#include "../buttons/buttons.h"
#include <stddef.h>

void StateMenuEntry_new(StateMenuEntry * this, char * label, Transition up, Transition down, Transition enter, Transition back) {
	this->label = label;
	this->up = up;
	this->down = down;
	this->back = back;
	this->enter = enter;
	this->firstTime = true;
	State_new(&(this->selfState), &StateMenuEntry_showMenu);
}

void StateMenuEntry_updateScreen(StateMenuEntry * this) {
	if (this->firstTime) {
		LCDWriteStringXY(0, 0, this->label);
	}
}

Transition StateMenuEntry_showMenu(void * data) {
	ButtonsStatus buttonStatus;
	Transition noTransition;

	MenuEntryTransitionData * transitionData = (MenuEntryTransitionData*) data;
	StateMenuEntry_updateScreen(transitionData->instance);
	transitionData->instance->firstTime = false;
	readButtons(&buttonStatus);

	noTransition.dataFornextState = data;
	noTransition.nextState = &(transitionData->instance->selfState);

	if (buttonStatus.buttons != 0) {
		transitionData->instance->firstTime = true;
	}

	if (buttonStatus.button.enter) {
		if (!Transition_isNullTransition(&(transitionData->instance->enter))) {
			return transitionData->instance->enter;
		}
	} else if (buttonStatus.button.back) {
		if (!Transition_isNullTransition(&(transitionData->instance->back))) {
			return transitionData->instance->back;
		}
	} else if (buttonStatus.button.down) {
		if (!Transition_isNullTransition(&(transitionData->instance->down))) {
			return transitionData->instance->down;
		}
	} else if (buttonStatus.button.up) {
		if (!Transition_isNullTransition(&(transitionData->instance->up))) {
			return transitionData->instance->up;
		}
	}
	return noTransition;
}

