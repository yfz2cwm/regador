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

typedef struct {
	State super;
	char * label;
	Transition returnTransition;
	Transition editTransition;
	uint16_t * variable;
	bool shouldPrint;
} StateShowNumber;

typedef struct {
} StateShowNumberTransitionData;

void StateShowNumber_new(StateShowNumber * this, char* label, uint16_t * variable, Transition returnTransition, Transition editTransition);

Transition StateShowNumber_showNumber(void * instance, void * data);

#endif /* STATESHOWNUMBER_H_ */
