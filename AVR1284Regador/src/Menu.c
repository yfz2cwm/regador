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
#include "menu/StateShowOnOf.h"
#include "Timer.h"
#include "Zone.h"
#include "menu/MenuBuilder.h"
#include <stddef.h>

StateMenuEntry menuStateRegadorStatus;

StateMenuEntry menuStateZones;
StateMenuEntry menuStateTime;
MenuEntryTransitionData timeData, zonesData, regadorStatusData;



MenuOnOffConfigAndEdit sprinklerStatus;

MenuNumberConfigAndEdit menuSeconds;
int16_t number;

Transition initCfgSeconds(Transition backTransition) {

	Transition showAndEditTransition;
	showAndEditTransition = MenuBuilder_buildMenuAndConfigurationNumber(&menuSeconds, "Seconds:", "Seconds*:", &number, backTransition,59,0,true);
	return showAndEditTransition;
}
Transition initCfgRegadorOnOff(Transition backTransition,Sprinkler *  sprinkler) {

	Transition showAndEditTransition;
	showAndEditTransition = MenuBuilder_buildMenuAndConfigurationOnOff(&sprinklerStatus,"Sprinkler","Sprinkler*",&sprinkler->working,backTransition);
	return showAndEditTransition;
}

void initMenuStateRegadorStatus(Sprinkler * sprinkler) {

	Transition regadorStatusUpTransition;
	Transition regadorStatusDownTransition;
	Transition regadorStatusEnterTransition;
	Transition regadorStatusBackTransition;
	Transition backToRegador;

	Transition_new(&backToRegador,StateMenuEntry_getState(&menuStateRegadorStatus),&regadorStatusData);

	regadorStatusEnterTransition = initCfgRegadorOnOff(backToRegador,sprinkler);

	regadorStatusBackTransition = Transition_nullTransition();
	regadorStatusUpTransition.dataFornextState = &timeData;
	regadorStatusUpTransition.nextState = StateMenuEntry_getState(&menuStateTime);
	regadorStatusDownTransition.dataFornextState = &zonesData;
	regadorStatusDownTransition.nextState = StateMenuEntry_getState(&menuStateZones);

	StateMenuEntry_new(&menuStateRegadorStatus, "Regando", regadorStatusUpTransition, regadorStatusDownTransition, regadorStatusEnterTransition, regadorStatusBackTransition);
}

void initMenuStateZones() {
	Transition menuZoneUpTransition;
	Transition menuZoneDown;
	Transition menuZoneBackToZonesFromZoneEditTransition;
	Transition goToZonesDetail;
	Transition back;
	back = Transition_nullTransition();

	menuZoneUpTransition.dataFornextState = &regadorStatusData;
	menuZoneUpTransition.nextState = StateMenuEntry_getState(&menuStateRegadorStatus);
	menuZoneDown.dataFornextState = &timeData;
	menuZoneDown.nextState = StateMenuEntry_getState(&menuStateTime);
	menuZoneBackToZonesFromZoneEditTransition.nextState = StateMenuEntry_getState(&menuStateZones);
	menuZoneBackToZonesFromZoneEditTransition.dataFornextState = &zonesData;

	goToZonesDetail = Zone_initMenu(menuZoneBackToZonesFromZoneEditTransition);
	StateMenuEntry_new(&menuStateZones, "Zonas", menuZoneUpTransition, menuZoneDown, goToZonesDetail, back);

}

void initMenuStateTime() {
	Transition up;
	Transition down;
	Transition enter;
	Transition toReturnHere;

	up.dataFornextState = &zonesData;
	up.nextState = StateMenuEntry_getState(&menuStateZones);
	down.dataFornextState = &regadorStatusData;
	down.nextState = StateMenuEntry_getState(&menuStateRegadorStatus);

	Transition_new(&toReturnHere, StateMenuEntry_getState(&menuStateTime), &timeData);
	enter = initCfgSeconds(toReturnHere);
	StateMenuEntry_new(&menuStateTime, "Time", up, down, enter, Transition_nullTransition());
}

Transition Menu_init(Sprinkler * sprinkler) {
	Transition initialTransition;
	initMenuStateTime();
	initMenuStateRegadorStatus(sprinkler);
	initMenuStateZones();
	initialTransition.nextState = StateMenuEntry_getState(&menuStateRegadorStatus);
	initialTransition.dataFornextState = &regadorStatusData;
	return initialTransition;
}
