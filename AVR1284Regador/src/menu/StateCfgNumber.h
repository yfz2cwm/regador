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
	State super;
	char * label;
	int16_t * variable;
	Transition * returnTransition;
	bool shouldPrint;
	int16_t lastSelectedValue;
	int16_t lastPrintValue;
	int16_t upperLimit;
	int16_t lowerLimit;
	bool cycle;
} StateCfgNumber;

typedef struct {
} StateCfgNumberTransitionData;

Transition StateCfgNumber_cfgNumber(void * instance, void * data);

void StateCfgNumber_new(StateCfgNumber * this, char* label, int16_t * variable, Transition * returnTransition);

void StateCfgNumber_updateScreen(StateCfgNumber* instance);

void StateCfgNumber_setUpperLimit(StateCfgNumber* this, uint16_t limit);

void StateCfgNumber_setLowerLimit(StateCfgNumber* this, uint16_t limit);

void StateCfgNumber_setCycle(StateCfgNumber* this, bool cycle);

void StateCfgNumber_increase(StateCfgNumber* this);

void StateCfgNumber_decrease(StateCfgNumber* this);

bool StateCfgNumber_isLimited(StateCfgNumber* this);

#endif /* STATECFGNUMBER_H_ */
