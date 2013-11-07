/*
 * StateCfgOnOff.h
 *
 *  Created on: Nov 5, 2013
 *      Author: juan
 */

#ifndef STATECFGONOFF_H_
#define STATECFGONOFF_H_
#include <stdbool.h>
#include "../state/State.h"

typedef struct {
	State super;
	char * label;
	bool * variable;
	Transition * returnTransition;
	bool shouldPrint;
	bool lastSelectedValue;
	bool lastPrintValue;
} StateCfgOnOff;

typedef struct {
} StateCfgOnOffTransitionData;

Transition StateCfgOnOff_cfgOnOff(void * instance, void * data);

void StateCfgOnOff_new(StateCfgOnOff * this, char* label, bool * variable, Transition * returnTransition);

void StateCfgOnOff_updateScreen(StateCfgOnOff* instance);

void StateCfgOnOff_swapValue(StateCfgOnOff * this);
#endif /* STATECFGONOFF_H_ */
