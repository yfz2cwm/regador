/*
 * Zone.c
 *
 *  Created on: Oct 30, 2013
 *      Author: dev
 */
#include <stdio.h>
#include "Zone.h"
#include "menu/StateMenuEntry.h"
#include "menu/MenuBuilder.h"

#define ZONE_COUNT 6
Zone zones[ZONE_COUNT];

MenuZone zoneMenuEntries[ZONE_COUNT];

MenuEntryTransitionData zoneMenuEntriesTransitionData[ZONE_COUNT];

void Zone_initLabels() {
	uint16_t i, j;
	for (i = 0; i < ZONE_COUNT; i++) {
		sprintf(zoneMenuEntries[i].label, "Zone %d", i);
		for (j = 0; j < ACTIVATION_CYLCES_COUNT; j++) {
			sprintf(zoneMenuEntries[i].activationCycleMenues[j].label, "Act Cycle %d", j);
		}
	}
}

void Zone_initActivationCycleMenu(MenuZone * menuZone, Zone * zoneToEdit) {
	uint16_t i;
	Transition backToZoneMenu, backToRoot;
	Transition_new(&backToZoneMenu, StateMenuEntry_getState(&menuZone->zoneMenu), NULL );

	for (i = 0; i < ACTIVATION_CYLCES_COUNT; i++) {
		Transition_new(&backToRoot, StateMenuEntry_getState(&menuZone->activationCycleMenues[i].root), NULL );

		StateMenuEntry_new(&menuZone->activationCycleMenues[i].root,
				menuZone->activationCycleMenues[i].label,
				Transition_nullTransition(),
				Transition_nullTransition(),
				Transition_nullTransition(),
				backToZoneMenu);

		menuZone->activationCycleMenues[i].root.super.enter = MenuBuilder_buildMenuAndConfigurationOnOff(
				&menuZone->activationCycleMenues[i].enable,
				"Enable:",
				"Enable*:",
				&zoneToEdit->activatioinCycles[i].enable,
				backToRoot);
	}


	for (i = 0; i < ACTIVATION_CYLCES_COUNT - 1; i++) {
		MenuBuilder_concatenateStates(&menuZone->activationCycleMenues[i].root.super, &menuZone->activationCycleMenues[i + 1].root.super);
	}
	MenuBuilder_concatenateStates(&menuZone->activationCycleMenues[ACTIVATION_CYLCES_COUNT - 1].root.super, &menuZone->activationCycleMenues[0].root.super);

	Transition_new(&menuZone->zoneMenu.super.enter, StateMenuEntry_getState(&menuZone->activationCycleMenues[0].root), NULL );
}

Transition Zone_initMenu(Transition backTransition) {
	Transition transitionToReturn;

	uint16_t i;

	Zone_initLabels();

	//Initialize the menues
	for (i = 0; i < ZONE_COUNT; i++) {
		StateMenuEntry_new(&zoneMenuEntries[i].zoneMenu, zoneMenuEntries[i].label, Transition_nullTransition(), Transition_nullTransition(), Transition_nullTransition(), backTransition);
		Zone_initActivationCycleMenu(&zoneMenuEntries[i], &zones[i]);
	}

	//Connect the menues
	for (i = 0; i < ZONE_COUNT - 1; i++) {
		MenuBuilder_concatenateStates(&zoneMenuEntries[i].zoneMenu.super, &zoneMenuEntries[i + 1].zoneMenu.super);
	}

	MenuBuilder_concatenateStates(&zoneMenuEntries[ZONE_COUNT - 1].zoneMenu.super, &zoneMenuEntries[0].zoneMenu.super);

	Transition_new(&transitionToReturn, StateMenuEntry_getState(&zoneMenuEntries[0].zoneMenu), &zoneMenuEntriesTransitionData[0]);
	return transitionToReturn;
}

ZoneList Zone_initZones() {
	ZoneList list;
	uint16_t i = 0;
	list.count = ZONE_COUNT;
	list.zones = zones;
	for (i = 0; i < list.count; i++) {
		list.zones->enable = false;
	}

	return list;
}
