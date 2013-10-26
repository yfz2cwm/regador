/*
 * Timer.h
 *
 *  Created on: Oct 24, 2013
 *      Author: juan
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>

typedef struct {
	uint16_t ms;
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
} Time;

typedef struct {
	volatile Time time;
} Timer;

Timer * Timer_getInstance();

void Timer_init(Timer* this);

Time Timer_getTime(Timer* this);

#endif /* TIMER_H_ */
