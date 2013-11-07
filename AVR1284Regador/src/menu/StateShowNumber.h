/*
 * StateShowNumber.h
 *
 *  Created on: Oct 27, 2013
 *      Author: juan
 */

#ifndef STATESHOWNUMBER_H_
#define STATESHOWNUMBER_H_
#include <stdbool.h>
#include <stdint.h>
#include "../state/State.h"
#include "StateCfgNumber.h"
#include "StateMenuEntry.h"

typedef struct {
	StateMenuEntry super;
	int16_t * variable;
} StateShowNumber;

typedef struct {
} StateShowNumberTransitionData;

void StateShowNumber_new(StateShowNumber * this, char* label, int16_t * variable, Transition returnTransition, Transition editTransition);

Transition StateShowNumber_showNumber(void * instance, void * data);

State * StateShowNumber_getState(StateShowNumber * this);

bool StateShowNumber_shouldPaint(StateShowNumber * this);
#endif /* STATESHOWNUMBER_H_ */
