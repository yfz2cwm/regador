/*
 * Regador.c
 *
 *  Created on: Oct 28, 2013
 *      Author: juan
 */

#include "Regador.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd/lcd.h"
#include "buttons/buttons.h"
#include "state/StateMachine.h"
#include "state/State.h"
#include "Timer.h"
#include "Menu.h"

State clock;

//100 ms
uint8_t lastSecond = 99;

typedef struct {
	Timer * timer;
} ClockUpdateData;

Transition clockUpdate(void* stateInstance, void* data) {
	Transition toReturn;

	toReturn.dataFornextState = data;
	toReturn.nextState = &clock;

	ClockUpdateData * clockUpdateData = (ClockUpdateData *) data;

	Time currentTime = Timer_getTime(clockUpdateData->timer);
	if (lastSecond == currentTime.seconds) {
		//Do not update
		return toReturn;
	} else {
		lastSecond = currentTime.seconds;
	}

	char buff[12];
	snprintf(buff, 12, "%02d:%02d:%02d", clockUpdateData->timer->time.hours, clockUpdateData->timer->time.minutes, clockUpdateData->timer->time.seconds);
	LCDWriteStringXY(0, 1, (const char * )buff);

	return toReturn;
}

void doStuff(void) {
	StateMachine stateMachine;

	TransitionList transitionList;
	Transition transitionArray[1];
	transitionList.transition = transitionArray;
	transitionList.transitionCount = 1;

	ClockUpdateData clockUpdateData;

	Transition menuInitialTransition;

	Timer * timer;

//Initialize the buttons
	initButtons();
//Initialize LCD module
	LCDInit(LS_BLINK | LS_ULINE);

	LCDClear();
	timer = Timer_getInstance();
	Timer_init(timer);

	menuInitialTransition = Menu_init();

	State_new(&clock, NULL, &clockUpdate);

	clockUpdateData.timer = timer;

	transitionList.transition[0] = menuInitialTransition;

	StateMachine_new(&stateMachine, &transitionList);

	StateMachine_start(&stateMachine);

}

