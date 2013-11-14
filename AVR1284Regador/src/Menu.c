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
#include "menu/StateShowTime.h"
#include "Timer.h"
#include "Zone.h"
#include "menu/MenuBuilder.h"
#include <stddef.h>

StateMenuEntry menuStateRegadorStatus;

StateMenuEntry menuStateZones;
StateMenuEntry menuStateTime;
StateShowTime menuStateShowTime;
MenuEntryTransitionData  zonesData, regadorStatusData;

MenuOnOffConfigAndEdit sprinklerStatus;

MenuNumberConfigAndEdit menuSeconds;

MenuTimeShowAndEdit globalTimeMenu;
int16_t number;

Transition initCfgSeconds(Transition backTransition) {

	Transition showAndEditTransition;
	showAndEditTransition = MenuBuilder_buildMenuAndConfigurationNumber(&menuSeconds, "Seconds:", "Seconds*:", &number, backTransition, 59, 0, true);
	return showAndEditTransition;
}
Transition initCfgRegadorOnOff(Transition backTransition, Sprinkler * sprinkler) {

	Transition showAndEditTransition;
	showAndEditTransition = MenuBuilder_buildMenuAndConfigurationOnOff(&sprinklerStatus, "Sprinkler", "Sprinkler*", &sprinkler->working, backTransition);
	return showAndEditTransition;
}

void initMenuStateRegadorStatus(Sprinkler * sprinkler) {

	Transition regadorStatusEnterTransition;
	Transition regadorStatusBackTransition;
	Transition backToRegador;

	Transition_new(&backToRegador, StateMenuEntry_getState(&menuStateRegadorStatus), &regadorStatusData);

	regadorStatusEnterTransition = initCfgRegadorOnOff(backToRegador, sprinkler);

	regadorStatusBackTransition = Transition_nullTransition();


	StateMenuEntry_new(&menuStateRegadorStatus, "Regando", Transition_nullTransition(), Transition_nullTransition(), regadorStatusEnterTransition, regadorStatusBackTransition);
}

void initMenuStateZones() {
	Transition menuZoneBackToZonesFromZoneEditTransition;
	Transition goToZonesDetail;
	Transition back;
	back = Transition_nullTransition();

	menuZoneBackToZonesFromZoneEditTransition.nextState = StateMenuEntry_getState(&menuStateZones);
	menuZoneBackToZonesFromZoneEditTransition.dataFornextState = &zonesData;

	goToZonesDetail = Zone_initMenu(menuZoneBackToZonesFromZoneEditTransition);
	StateMenuEntry_new(&menuStateZones, "Zonas", Transition_nullTransition(), Transition_nullTransition(), goToZonesDetail, back);

}

void initMenuStateTime() {


	MenuBuilder_buildMenuAndConfigurationTime(&globalTimeMenu, "Global Time", (Time *) &Timer_getInstance()->time, Transition_nullTransition());


}

Transition Menu_init(Sprinkler * sprinkler) {
	Transition initialTransition;
	initMenuStateTime();
	initMenuStateRegadorStatus(sprinkler);
	initMenuStateZones();
	initialTransition.nextState = StateMenuEntry_getState(&menuStateRegadorStatus);
	initialTransition.dataFornextState = &regadorStatusData;

	MenuBuilder_concatenateStates(&menuStateRegadorStatus.super,&globalTimeMenu.showState.super.super);
	MenuBuilder_concatenateStates(&globalTimeMenu.showState.super.super, &menuStateZones.super);
	MenuBuilder_concatenateStates(&menuStateZones.super, &menuStateRegadorStatus.super);

	return initialTransition;
}
