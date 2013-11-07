/*
 * MenuBuilder.c
 *
 *  Created on: Nov 3, 2013
 *      Author: juan
 */

#include "MenuBuilder.h"
Transition MenuBuilder_buildMenuAndConfigurationNumber(
		MenuNumberConfigAndEdit * numberConfigAndEdit,
		char * menulabel,
		char * editLabel,
		int16_t * variable,
		Transition returnTransition,
		int16_t upperLimit,
		int16_t lowerLimit,
		bool cycle) {

	Transition transitionToShow;

	//Transition edit
	StateCfgNumber_new(&numberConfigAndEdit->cfgNumberState, editLabel, variable, &numberConfigAndEdit->toShow);
	Transition_new(&numberConfigAndEdit->toEdit, &(numberConfigAndEdit->cfgNumberState.super), &(numberConfigAndEdit->cfgNumberTransitionData));
	StateCfgNumber_setLowerLimit(&numberConfigAndEdit->cfgNumberState, lowerLimit);
	StateCfgNumber_setUpperLimit(&numberConfigAndEdit->cfgNumberState, upperLimit);
	StateCfgNumber_setCycle(&numberConfigAndEdit->cfgNumberState, cycle);

	//Transition show
	StateShowNumber_new(&numberConfigAndEdit->showNumberState, menulabel, variable, returnTransition, numberConfigAndEdit->toEdit);
	Transition_new(&numberConfigAndEdit->toShow, StateShowNumber_getState(&numberConfigAndEdit->showNumberState), &numberConfigAndEdit->showNumberTransitionData);

	Transition_new(&transitionToShow, StateShowNumber_getState(&numberConfigAndEdit->showNumberState), &numberConfigAndEdit->showNumberTransitionData);

	return transitionToShow;
}

Transition MenuBuilder_buildMenuAndConfigurationOnOff(
		MenuOnOffConfigAndEdit * configAndEdit,
		char * menulabel,
		char * editLabel,
		bool * variable,
		Transition returnTransition) {
	Transition transitionToShow;

	//Transition edit
	StateCfgOnOff_new(&configAndEdit->cfgState, editLabel, variable, &configAndEdit->toShow);
	Transition_new(&configAndEdit->toEdit, &(configAndEdit->cfgState.super), &(configAndEdit->cfgTransitionData));

	//Transition show
	StateShowOnOff_new(&configAndEdit->showState, menulabel, variable, returnTransition, configAndEdit->toEdit);
	Transition_new(&configAndEdit->toShow, StateShowOnOff_getState(&configAndEdit->showState), &configAndEdit->showTransitionData);

	Transition_new(&transitionToShow, StateShowOnOff_getState(&configAndEdit->showState), &configAndEdit->showTransitionData);

	return transitionToShow;

}
