/*
 * Timer.c
 *
 *  Created on: Oct 24, 2013
 *      Author: juan
 */
#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>


Timer instance;

Timer * Timer_getInstance() {
	return &instance;
}

void Timer_init(Timer* this) {
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode

	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt

	OCR1A = 3124; // Set CTC compare value 100ms, with a prescaler of 256

	TCCR1B |= ((1 << CS12)); // Start timer at 8Mhz/256

	sei();
	//  Enable global interrupts
}

Time Timer_getTime(Timer* this) {
	return this->time;
}

ISR(TIMER1_COMPA_vect)
{
	instance.time.ms += 100;

	if (instance.time.ms == 1000) {
		instance.time.seconds++;
		instance.time.ms = 0;
	}

	if (instance.time.seconds == 60) {
		instance.time.seconds = 0;
		instance.time.minutes++;
	}

	if (instance.time.minutes == 60) {
		instance.time.minutes = 0;
		instance.time.hours++;
	}
}
