/*
 * StateMenuEntry.h
 *
 *  Created on: Oct 27, 2013
 *      Author: juan
 */

#ifndef STATEMENUENTRY_H_
#define STATEMENUENTRY_H_
#include <stdbool.h>
#include "../state/State.h"

typedef struct {
	State super;
	char * label;
	Transition up;
	Transition down;
	Transition enter;
	Transition back;
	bool firstTime;
} StateMenuEntry;

typedef struct {
} MenuEntryTransitionData;

void StateMenuEntry_new(StateMenuEntry * this,char * label, Transition up, Transition down, Transition enter, Transition back);

Transition StateMenuEntry_showMenu(void * instance, void * data);

#endif /* STATEMENUENTRY_H_ */
