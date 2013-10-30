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

typedef struct {
	bool enable;
	Time startTime;
	uint16_t durationInMinutes;
} ActivationCycle;

typedef struct {
	uint16_t port;
	uint16_t pinNumber;
	ActivationCycle activatioinCycles[5];
} Zone;


#endif /* ZONE_H_ */
