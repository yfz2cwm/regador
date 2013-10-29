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
#include "menu/StateMenuEntry.h"
#include "menu/StateShowNumber.h"

StateMenuEntry menuStateRegadorStatus;
StateMenuEntry menuStateZones;
StateMenuEntry menuStateTime;
MenuEntryTransitionData timeData, zonesData, regadorStatusData;

StateShowNumber showSeconds;
StateShowNumberTransitionData showSecondsData;

State clock;

void initShowSeconds() {
	Transition backTransition;
	backTransition.nextState = &(menuStateTime.selfState);
	backTransition.dataFornextState = &timeData;
	showSecondsData.instance = &showSeconds;

	StateShowNumber_new(&showSeconds, "Segundos:", (uint16_t *)&(Timer_getInstance()->time.seconds), backTransition, Transition_nullTransition());
}

void initMenuStateRegadorStatus() {
	Transition up;
	Transition down;
	regadorStatusData.instance = &menuStateRegadorStatus;

	up.dataFornextState = &timeData;
	up.nextState = &menuStateTime.selfState;
	down.dataFornextState = &zonesData;
	down.nextState = &menuStateZones.selfState;

	StateMenuEntry_new(&menuStateRegadorStatus, "Estado de regador", up, down, Transition_nullTransition(), Transition_nullTransition());
}

void initMenuStateZones() {
	Transition up;
	Transition down;

	zonesData.instance = &menuStateZones;
	up.dataFornextState = &regadorStatusData;
	up.nextState = &menuStateRegadorStatus.selfState;
	down.dataFornextState = &timeData;
	down.nextState = &menuStateTime.selfState;

	StateMenuEntry_new(&menuStateZones, "Zonas", up, down, Transition_nullTransition(), Transition_nullTransition());
}

void initMenuStateTime() {
	Transition up;
	Transition down;
	Transition enter;
	timeData.instance = &menuStateTime;
	up.dataFornextState = &zonesData;
	up.nextState = &menuStateZones.selfState;
	down.dataFornextState = &regadorStatusData;
	down.nextState = &menuStateRegadorStatus.selfState;
	enter.nextState = &(showSeconds.selfState);
	enter.dataFornextState = &showSecondsData;

	StateMenuEntry_new(&menuStateTime, "Time", up, down, enter, Transition_nullTransition());
}

void initMenu() {
	initShowSeconds();
	initMenuStateRegadorStatus();
	initMenuStateZones();
	initMenuStateTime();
}

//100 ms
uint8_t lastSecond = 99;

typedef struct {
	Timer * timer;
} ClockUpdateData;

Transition clockUpdate(void* data) {
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
	Transition transitionArray[2];
	transitionList.transition = transitionArray;
	transitionList.transitionCount = 2;
	ClockUpdateData clockUpdateData;

	MenuEntryTransitionData regadorStatus;

	Timer * timer;

//Initialize the buttons
	initButtons();
//Initialize LCD module
	LCDInit(LS_BLINK | LS_ULINE);

	LCDClear();
	timer = Timer_getInstance();
	Timer_init(timer);

	initMenu();

	State_new(&clock, &clockUpdate);

	clockUpdateData.timer = timer;

	regadorStatus.instance = &menuStateRegadorStatus;
	transitionList.transition[0].dataFornextState = &regadorStatus;
	transitionList.transition[0].nextState = &menuStateRegadorStatus.selfState;

	transitionList.transition[1].dataFornextState = &clockUpdateData;
	transitionList.transition[1].nextState = &clock;

	StateMachine_new(&stateMachine, &transitionList);

	StateMachine_start(&stateMachine);

}

