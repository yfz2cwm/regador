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
		Transition returnTransition) {

	Transition transitionToShow;


	//Transition edit
	numberConfigAndEdit->cfgNumberTransitionData.instance = &(numberConfigAndEdit->cfgNumberState);
	StateCfgNumber_new(&numberConfigAndEdit->cfgNumberState, editLabel, (uint16_t * )variable, &numberConfigAndEdit->toShow);
	Transition_new(&numberConfigAndEdit->toEdit, &(numberConfigAndEdit->cfgNumberState.selfState), &(numberConfigAndEdit->cfgNumberTransitionData));

	//Transition show
	numberConfigAndEdit->showNumberTransitionData.instance = &numberConfigAndEdit->showNumberState;
	StateShowNumber_new(&numberConfigAndEdit->showNumberState, menulabel, variable, returnTransition, numberConfigAndEdit->toEdit);
	Transition_new(&numberConfigAndEdit->toShow, &numberConfigAndEdit->showNumberState.selfState, &numberConfigAndEdit->showNumberTransitionData);


	Transition_new(&transitionToShow, &numberConfigAndEdit->showNumberState.selfState, &numberConfigAndEdit->showNumberTransitionData);

	return transitionToShow;
}
