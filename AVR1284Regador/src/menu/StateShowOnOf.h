/*
 * StateShowOnOf.h
 *
 *  Created on: Nov 5, 2013
 *      Author: juan
 */

#ifndef STATESHOWONOF_H_
#define STATESHOWONOF_H_

#include <stdbool.h>
#include "../state/State.h"
#include "StateCfgNumber.h"
#include "StateMenuEntry.h"

typedef struct {
	StateMenuEntry super;
	bool * variable;
} StateShowOnOff;

typedef struct {
} StateShowOnOffTransitionData;

void StateShowOnOff_new(StateShowOnOff * this,
		char* label,
		bool * variable,
		Transition returnTransition,
		Transition editTransition);

Transition StateShowOnOff_showOnOff(void * instance, void * data);

State * StateShowOnOff_getState(StateShowOnOff * this);

#endif /* STATESHOWONOF_H_ */
