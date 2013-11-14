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
#include "StateShowOnOf.h"
#include "StateCfgOnOff.h"
#include "StateShowTime.h"

typedef struct {
	StateShowNumber showNumberState;
	StateShowNumberTransitionData showNumberTransitionData;

	StateCfgNumber cfgNumberState;
	StateCfgNumberTransitionData cfgNumberTransitionData;

	Transition toEdit, toShow;

} MenuNumberConfigAndEdit;

typedef struct {
	StateShowOnOff showState;
	StateShowOnOffTransitionData showTransitionData;

	StateCfgOnOff cfgState;
	StateCfgOnOffTransitionData cfgTransitionData;

	Transition toEdit, toShow;

} MenuOnOffConfigAndEdit;

typedef struct {
	StateShowTime showState;
	StateShowTimeTransitionData showTransitionData;

	MenuNumberConfigAndEdit cfgHourState, cfgMinuteState, cfgSecondState;

	Transition toEdit, toShow;

} MenuTimeShowAndEdit;

Transition MenuBuilder_buildMenuAndConfigurationOnOff(MenuOnOffConfigAndEdit * configAndEdit, char * menulabel, char * editLabel,
bool * variable, Transition returnTransition);

Transition MenuBuilder_buildMenuAndConfigurationTime(MenuTimeShowAndEdit* showAndEdit, char * menulabel, Time * variable, Transition returnTransition);

Transition MenuBuilder_buildMenuAndConfigurationNumber(MenuNumberConfigAndEdit * numberConfigAndEdit, char * menulabel, char * editLabel, int16_t * variable, Transition returnTransition, int16_t upperLimit, int16_t lowerLimit,
bool cycle);

void MenuBuilder_concatenateStates(StateBaseMenuEntry * first, StateBaseMenuEntry *second);

#endif /* MENUBUILDER_H_ */
