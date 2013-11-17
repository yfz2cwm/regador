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
	uint16_t i;
	for (i = 0; i < ZONE_COUNT; i++) {
		sprintf(zoneMenuEntries[i].label, "Zone %d", i);
	}
}

Transition Zone_initMenu(Transition backTransition) {
	Transition transitionToReturn;

	uint16_t i;

	Zone_initLabels();

	for (i = 0; i < ZONE_COUNT; i++) {
		StateMenuEntry_new(&zoneMenuEntries[i].zoneMenu, zoneMenuEntries[i].label, Transition_nullTransition(), Transition_nullTransition(), Transition_nullTransition(), backTransition);
	}

	for (i = 0; i < ZONE_COUNT - 1; i++) {
		MenuBuilder_concatenateStates(&zoneMenuEntries[i].zoneMenu.super, &zoneMenuEntries[i + 1].zoneMenu.super);
	}

	MenuBuilder_concatenateStates(&zoneMenuEntries[ZONE_COUNT -1].zoneMenu.super, &zoneMenuEntries[0].zoneMenu.super);

	Transition_new(&transitionToReturn,StateMenuEntry_getState(&zoneMenuEntries[0].zoneMenu),&zoneMenuEntriesTransitionData[0]);
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
