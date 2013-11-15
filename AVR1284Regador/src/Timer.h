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
	int16_t seconds;
	int16_t minutes;
	int16_t hours;
} Time;

typedef struct {
	volatile Time time;
} Timer;

Timer * Timer_getInstance();

void Timer_init(Timer* this);

Time Timer_getTime(Timer* this);

#endif /* TIMER_H_ */
