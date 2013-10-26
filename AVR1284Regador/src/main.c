#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "avr/interrupt.h"
#include "lcd/lcd.h"
#include "buttons/buttons.h"
#include "state/StateMachine.h"
#include "state/State.h"
#include "Timer.h"

Transition state2Loop(void* data);
Transition state1Loop(void * data);

State state1;
State state2;
State clock;

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

	if (lastSecond == clockUpdateData->timer->time.seconds) {
		//Do not update
		return toReturn;
	} else {
		lastSecond = clockUpdateData->timer->time.seconds;
	}

	char buff[12];
	snprintf(buff, 12, "%02d:%02d:%02d", clockUpdateData->timer->time.hours, clockUpdateData->timer->time.minutes, clockUpdateData->timer->time.seconds);
	LCDWriteStringXY(0, 1, (const char *)buff);

	return toReturn;
}

Transition state1Loop(void* data) {

	Transition state2Transition;
	Transition sateSameTransition;
	ButtonsStatus currentButtonStatus;


	state2Transition.dataFornextState = data;
	state2Transition.nextState = &state2;

	sateSameTransition.dataFornextState = data;
	sateSameTransition.nextState = &state1;

	if (*((uint8_t *) data) == 0) {
		LCDWriteStringXY(0, 0, "State1");
		*((uint8_t *) sateSameTransition.dataFornextState)  = 1;
	}

	readButtons(&currentButtonStatus);
	if (currentButtonStatus.button.enter) {
		*((uint8_t *) sateSameTransition.dataFornextState) = 0;
		return state2Transition;
	}

	return sateSameTransition;

}

Transition state2Loop(void * data) {
	Transition state1Transition;
	Transition sateSameTransition;

	ButtonsStatus currentButtonStatus;

	State_new(&state1, &state1Loop);
	state1Transition.dataFornextState = data;
	state1Transition.nextState = &state1;

	sateSameTransition.dataFornextState = data;
	sateSameTransition.nextState = &state2;

	if (*((uint8_t *) data) == 0) {
		LCDWriteStringXY(0, 0, "State2");
		*((uint8_t *) sateSameTransition.dataFornextState) = 1;
	}

	readButtons(&currentButtonStatus);

	if (currentButtonStatus.button.back) {
		*((uint8_t *) sateSameTransition.dataFornextState) = 0;
		return state1Transition;
	}

	return sateSameTransition;
}

int main(void) {
	StateMachine stateMachine;

	TransitionList transitionList;
	Transition transitionArray[2];
	transitionList.transition = transitionArray;
	transitionList.transitionCount = 2;
	ClockUpdateData clockUpdateData;

	uint8_t loopData = 0;

	Timer * timer;

//Initialize the buttons
	initButtons();
//Initialize LCD module
	LCDInit(LS_BLINK | LS_ULINE);

	LCDClear();
	timer = Timer_getInstance();
	Timer_init(timer);

	State_new(&state1, &state1Loop);
	State_new(&state2, &state2Loop);
	State_new(&clock, &clockUpdate);

	clockUpdateData.timer = timer;

	transitionList.transition[1].dataFornextState = &clockUpdateData;
	transitionList.transition[1].nextState = &clock;

	transitionList.transition[0].dataFornextState = &loopData;
	transitionList.transition[0].nextState = &state1;


	StateMachine_new(&stateMachine, &transitionList);

	StateMachine_start(&stateMachine);


	while (1) {

	}

}

