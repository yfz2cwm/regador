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
#include "Zone.h"
#include "menu/MenuBuilder.h"
#include <stddef.h>
StateMenuEntry menuStateRegadorStatus;
StateMenuEntry menuStateZones;
StateMenuEntry menuStateTime;
MenuEntryTransitionData timeData, zonesData, regadorStatusData;

MenuNumberConfigAndEdit menuSeconds;
uint16_t number;

Transition initCfgSeconds(Transition backTransition) {

	Transition showAndEditTransition;
	showAndEditTransition = MenuBuilder_buildMenuAndConfigurationNumber(&menuSeconds, "Seconds:", "Seconds*:",&number, backTransition);
	return showAndEditTransition;
}

void initMenuStateRegadorStatus() {
	Transition up;
	Transition down;

	up.dataFornextState = &timeData;
	up.nextState = &menuStateTime.super;
	down.dataFornextState = &zonesData;
	down.nextState = &menuStateZones.super;

	StateMenuEntry_new(&menuStateRegadorStatus, "Regando", up, down, Transition_nullTransition(), Transition_nullTransition());
}

void initMenuStateZones() {
	Transition up;
	Transition down;
	Transition backToZonesTransition;
	Transition goToZonesDetail;

	up.dataFornextState = &regadorStatusData;
	up.nextState = &menuStateRegadorStatus.super;
	down.dataFornextState = &timeData;
	down.nextState = &menuStateTime.super;
	backToZonesTransition.nextState = &menuStateZones.super;
	backToZonesTransition.dataFornextState = &zonesData;

	goToZonesDetail = Zone_initMenu(backToZonesTransition);
	StateMenuEntry_new(&menuStateZones, "Zonas", up, down, goToZonesDetail, Transition_nullTransition());

}

void initMenuStateTime() {
	Transition up;
	Transition down;
	Transition enter;
	Transition toReturnHere;

	up.dataFornextState = &zonesData;
	up.nextState = &menuStateZones.super;
	down.dataFornextState = &regadorStatusData;
	down.nextState = &menuStateRegadorStatus.super;

	Transition_new(&toReturnHere, &menuStateTime.super, &timeData);
	enter = initCfgSeconds(toReturnHere);
	StateMenuEntry_new(&menuStateTime, "Time", up, down, enter, Transition_nullTransition());
}

Transition Menu_init() {
	Transition initialTransition;
	initMenuStateTime();
	initMenuStateRegadorStatus();
	initMenuStateZones();
	initialTransition.nextState = &menuStateRegadorStatus.super;
	initialTransition.dataFornextState = &regadorStatusData;
	return initialTransition;
}
