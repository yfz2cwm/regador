/*
 * Zone.h
 *
 *  Created on: Oct 24, 2013
 *      Author: juan
 */
#ifndef ZONE_H_
#define ZONE_H_

#include "Timer.h"
#include <stdbool.h>
#include <stdint.h>
#include "state/State.h"
#include "menu/MenuBuilder.h"

#define ACTIVATION_CYLCES_COUNT 5

typedef struct {
	bool enable;
	Time startTime;
	int16_t durationInMinutes;
} ActivationCycle;

typedef struct {
	int16_t port;
	int16_t pinNumber;
	ActivationCycle activatioinCycles[ACTIVATION_CYLCES_COUNT];
	bool enable;
	bool test;
} Zone;

typedef struct {
	Zone * zones;
	uint16_t count;
} ZoneList;

typedef struct {
	MenuTimeShowAndEdit activationTime;
	MenuOnOffConfigAndEdit enable;
	MenuOnOffConfigAndEdit test;
	MenuNumberConfigAndEdit durationTime;
	char label[16];
	StateMenuEntry root;
} MenuZoneActivationCycle;

typedef struct {
	MenuZoneActivationCycle activationCycleMenues[ACTIVATION_CYLCES_COUNT];
	StateMenuEntry zoneMenu;
	char label[16];
} MenuZone;

Transition Zone_initMenu(Transition backTransition);

ZoneList Zone_initZones();

#endif /* ZONE_H_ */
