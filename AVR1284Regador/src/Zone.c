/*
 * Zone.c
 *
 *  Created on: Oct 30, 2013
 *      Author: dev
 */
#include <stdio.h>
#include "Zone.h"
#include "menu/StateMenuEntry.h"

#define ZONE_COUNT 6
Zone zones[ZONE_COUNT];

StateMenuEntry zoneMenuEntries[ZONE_COUNT];
char zoneMenuEntriesLabels[ZONE_COUNT][16];
MenuEntryTransitionData zoneMenuEntriesTransitionData[ZONE_COUNT];

void Zone_initLabels() {
	uint16_t i;
	for (i = 0; i < ZONE_COUNT; i++) {
		sprintf(&zoneMenuEntriesLabels[i][0], "Zone %d", i);
	}
}

void Zone_initTransitionDatas() {
	uint16_t i;
	for (i = 0; i < ZONE_COUNT; i++) {
		zoneMenuEntriesTransitionData[i].instance = &zoneMenuEntries[i];
	}
}

Transition Zone_initMenu(Transition backTransition) {
	Transition up;
	Transition down;
	Transition transitionToReturn;

	uint16_t i;

	Zone_initLabels();
	Zone_initTransitionDatas();

	up.nextState = &zoneMenuEntries[ZONE_COUNT - 1].selfState;
	up.dataFornextState = &zoneMenuEntriesTransitionData[ZONE_COUNT - 1];
	down.nextState = &zoneMenuEntries[1].selfState;
	down.dataFornextState = &zoneMenuEntriesTransitionData[1];

	StateMenuEntry_new(&zoneMenuEntries[0], zoneMenuEntriesLabels[0], up, down, Transition_nullTransition(), backTransition);

	for (i = 1; i < ZONE_COUNT - 1; i++) {
		up.nextState = &zoneMenuEntries[i - 1].selfState;
		up.dataFornextState = &zoneMenuEntriesTransitionData[i - 1];
		down.nextState = &zoneMenuEntries[i + 1].selfState;
		down.dataFornextState = &zoneMenuEntriesTransitionData[i + 1];
		StateMenuEntry_new(&zoneMenuEntries[i], zoneMenuEntriesLabels[i], up, down, Transition_nullTransition(), backTransition);
	}

	up.nextState = &zoneMenuEntries[ZONE_COUNT - 2].selfState;
	up.dataFornextState = &zoneMenuEntriesTransitionData[ZONE_COUNT - 2];
	down.nextState = &zoneMenuEntries[0].selfState;
	down.dataFornextState = &zoneMenuEntriesTransitionData[0];
	StateMenuEntry_new(&zoneMenuEntries[ZONE_COUNT - 1], zoneMenuEntriesLabels[ZONE_COUNT - 1], up, down, Transition_nullTransition(), backTransition);
	transitionToReturn.nextState = &zoneMenuEntries[0].selfState;
	transitionToReturn.dataFornextState = &zoneMenuEntriesTransitionData[0];

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
