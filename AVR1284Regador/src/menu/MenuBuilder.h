/*
 * MenuBuilder.h
 *
 *  Created on: Nov 3, 2013
 *      Author: juan
 */

#ifndef MENUBUILDER_H_
#define MENUBUILDER_H_

#include "StateShowNumber.h"
#include "StateMenuEntry.h"

typedef struct {
	StateShowNumber showNumberState;
	StateShowNumberTransitionData showNumberTransitionData;

	StateCfgNumber cfgNumberState;
	StateCfgNumberTransitionData cfgNumberTransitionData;

	Transition toEdit,toShow;

} MenuNumberConfigAndEdit;

Transition MenuBuilder_buildMenuAndConfigurationNumber(
		MenuNumberConfigAndEdit * numberConfigAndEdit,
		char * menulabel,
		char * editLabel,
		uint16_t * variable,
		Transition returnTransition,
		uint16_t upperLimit,
		uint16_t lowerLimit,
		bool cycle);

#endif /* MENUBUILDER_H_ */
