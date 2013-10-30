/*
 * StateCfgNumber.h
 *
 *  Created on: Oct 26, 2013
 *      Author: juan
 */

#ifndef STATECFGNUMBER_H_
#define STATECFGNUMBER_H_
#include <stdint.h>
#include <stdbool.h>
#include "../state/State.h"

typedef struct {
	State selfState;
	char * label;
	uint16_t * variable;
	Transition returnTransition;
	bool shouldPrint;
	uint16_t lastSelectedValue;
	uint16_t lastPrintValue;
} StateCfgNumber;

typedef struct {
	StateCfgNumber * instance;
} StateCfgNumberTransitionData;

Transition StateCfgNumber_cfgNumber(void * data);

void StateCfgNumber_new(StateCfgNumber * this, char* label, uint16_t * variable, Transition returnTransition);

void StateCfgNumber_updateScreen(StateCfgNumber* instance);

#endif /* STATECFGNUMBER_H_ */
