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

#define ACTIVATION_CYLCES_COUNT 5

typedef struct {
	bool enable;
	Time startTime;
	uint16_t durationInMinutes;
} ActivationCycle;

typedef struct {
	uint16_t port;
	uint16_t pinNumber;
	ActivationCycle activatioinCycles[ACTIVATION_CYLCES_COUNT];
	bool enable;
} Zone;

typedef struct {
	Zone * zones;
	uint16_t count;
} ZoneList;


Transition Zone_initMenu(Transition backTransition);

ZoneList Zone_initZones();

#endif /* ZONE_H_ */
