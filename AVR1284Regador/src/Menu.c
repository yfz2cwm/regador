/*
 * Menu.c
 *
 *  Created on: Oct 30, 2013
 *      Author: dev
 */

#include "Menu.h"
#include "menu/StateMenuEntry.h"
#include "menu/StateShowNumber.h"
#include "menu/StateCfgNumber.h"
#include "Timer.h"


StateMenuEntry menuStateRegadorStatus;
StateMenuEntry menuStateZones;
StateMenuEntry menuStateTime;
MenuEntryTransitionData timeData, zonesData, regadorStatusData;

StateShowNumber showSeconds;
StateShowNumberTransitionData showSecondsData;

StateCfgNumber secondsStateCfg;
StateCfgNumberTransitionData secondsStateCfgData;

void initCfgSeconds() {

	Transition backTransition;
	backTransition.nextState = &(showSeconds.selfState);
	backTransition.dataFornextState = &showSecondsData;
	secondsStateCfgData.instance = &secondsStateCfg;
	StateCfgNumber_new(&secondsStateCfg,"Segundos*:",(uint16_t *)&(Timer_getInstance()->time.seconds),backTransition);
}

void initShowSeconds() {
	Transition backTransition;
	Transition editTransition;
	backTransition.nextState = &(menuStateTime.selfState);
	backTransition.dataFornextState = &timeData;
	editTransition.nextState = &(secondsStateCfg.selfState);
	editTransition.dataFornextState = &secondsStateCfgData;


	showSecondsData.instance = &showSeconds;

	StateShowNumber_new(&showSeconds, "Segundos:", (uint16_t *)&(Timer_getInstance()->time.seconds), backTransition, editTransition);
}

void initMenuStateRegadorStatus() {
	Transition up;
	Transition down;
	regadorStatusData.instance = &menuStateRegadorStatus;

	up.dataFornextState = &timeData;
	up.nextState = &menuStateTime.selfState;
	down.dataFornextState = &zonesData;
	down.nextState = &menuStateZones.selfState;

	StateMenuEntry_new(&menuStateRegadorStatus, "Regando", up, down, Transition_nullTransition(), Transition_nullTransition());
}

void initMenuStateZones() {
	Transition up;
	Transition down;

	zonesData.instance = &menuStateZones;

	up.dataFornextState = &regadorStatusData;
	up.nextState = &menuStateRegadorStatus.selfState;
	down.dataFornextState = &timeData;
	down.nextState = &menuStateTime.selfState;

	StateMenuEntry_new(&menuStateZones, "Zonas", up, down, Transition_nullTransition(), Transition_nullTransition());
}

void initMenuStateTime() {
	Transition up;
	Transition down;
	Transition enter;
	timeData.instance = &menuStateTime;
	up.dataFornextState = &zonesData;
	up.nextState = &menuStateZones.selfState;
	down.dataFornextState = &regadorStatusData;
	down.nextState = &menuStateRegadorStatus.selfState;
	enter.nextState = &(showSeconds.selfState);
	enter.dataFornextState = &showSecondsData;

	StateMenuEntry_new(&menuStateTime, "Time", up, down, enter, Transition_nullTransition());
}

Transition Menu_init() {
	Transition initialTransition;
	initCfgSeconds();
	initShowSeconds();
	initMenuStateRegadorStatus();
	initMenuStateZones();
	initMenuStateTime();
	initialTransition.nextState = &menuStateRegadorStatus.selfState;
	initialTransition.dataFornextState = &regadorStatusData;
	return initialTransition;
}
