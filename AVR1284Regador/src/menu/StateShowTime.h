/*
 * StateShowTime.h
 *
 *  Created on: Nov 13, 2013
 *      Author: juan
 */

#ifndef STATESHOWTIME_H_
#define STATESHOWTIME_H_

#include "../state/State.h"
#include "StateMenuEntry.h"
#include "../Timer.h"

typedef struct {
	StateMenuEntry super;
	Time * variable;
} StateShowTime;

typedef struct {
} StateShowTimeTransitionData;

void StateShowTime_new(StateShowTime * this,
		char* label,
		Time * variable,
		Transition returnTransition,
		Transition editTransition);

Transition StateShowTime_show(void * instance, void * data);

State * StateShowTime_getState(StateShowTime * this);

#endif /* STATESHOWTIME_H_ */
