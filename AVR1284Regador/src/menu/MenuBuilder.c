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
		uint16_t * variable,
		Transition returnTransition,
		uint16_t upperLimit,
		uint16_t lowerLimit,
		bool cycle) {

	Transition transitionToShow;


	//Transition edit
	StateCfgNumber_new(&numberConfigAndEdit->cfgNumberState, editLabel, (uint16_t * )variable, &numberConfigAndEdit->toShow);
	Transition_new(&numberConfigAndEdit->toEdit, &(numberConfigAndEdit->cfgNumberState.super), &(numberConfigAndEdit->cfgNumberTransitionData));
	StateCfgNumber_setLowerLimit(&numberConfigAndEdit->cfgNumberState,lowerLimit);
	StateCfgNumber_setUpperLimit(&numberConfigAndEdit->cfgNumberState,upperLimit);
	StateCfgNumber_setCycle(&numberConfigAndEdit->cfgNumberState,cycle);

	//Transition show
	StateShowNumber_new(&numberConfigAndEdit->showNumberState, menulabel, variable, returnTransition, numberConfigAndEdit->toEdit);
	Transition_new(&numberConfigAndEdit->toShow, StateShowNumber_getState(&numberConfigAndEdit->showNumberState), &numberConfigAndEdit->showNumberTransitionData);


	Transition_new(&transitionToShow,StateShowNumber_getState(&numberConfigAndEdit->showNumberState), &numberConfigAndEdit->showNumberTransitionData);

	return transitionToShow;
}
