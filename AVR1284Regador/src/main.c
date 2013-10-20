#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "lcd/lcd.h"
#include "buttons/buttons.h"
#include "state/StateMachine.h"
#include "state/State.h"
#include "avr/interrupt.h"
Transition state2Loop(void* data);
Transition state1Loop(void * data);
void printStatus(ButtonsStatus butStat);

Transition state1Loop(void* data) {
	State state2;
	Transition state2Transition;

	ButtonsStatus currentButtonStatus;
	ButtonsStatus previousButtonStatus;
	previousButtonStatus.buttons = 0;
	State_new(&state2, &state2Loop);
	state2Transition.dataFornextState = 0;
	state2Transition.nextState = &state2;

	LCDClear();
	LCDWriteString("State1 (EUDB):");

	while (1) {
		readButtons(&currentButtonStatus);
		_delay_ms(5);
		if (currentButtonStatus.buttons != previousButtonStatus.buttons) {
			printStatus(currentButtonStatus);
			previousButtonStatus.buttons = currentButtonStatus.buttons;
			if (currentButtonStatus.button.enter) {
				LCDWriteStringXY(7, 1, "1");
				return state2Transition;
			}
		}
	}

}

Transition state2Loop(void * data) {
	State state1;
	Transition state1Transition;

	ButtonsStatus currentButtonStatus;
	ButtonsStatus previousButtonStatus;
	previousButtonStatus.buttons = 0;
	State_new(&state1, &state1Loop);
	state1Transition.dataFornextState = 0;
	state1Transition.nextState = &state1;

	LCDClear();
	LCDWriteString("State2 (EUDB):");

	while (1) {
		readButtons(&currentButtonStatus);
		_delay_ms(5);
		if (currentButtonStatus.buttons != previousButtonStatus.buttons) {
			printStatus(currentButtonStatus);
			previousButtonStatus.buttons = currentButtonStatus.buttons;
			if (currentButtonStatus.button.back) {
				LCDWriteStringXY(8, 1, "1");
				return state1Transition;
			}
		}
	}
}

void printStatus(ButtonsStatus butStat) {
	if (butStat.buttons != 0) {
		if (butStat.button.enter) {
			LCDWriteStringXY(0, 1, "1");
		} else {
			LCDWriteStringXY(0, 1, "0");
		}
		if (butStat.button.up) {
			LCDWriteStringXY(1, 1, "1");
		} else {
			LCDWriteStringXY(1, 1, "0");
		}
		if (butStat.button.down) {
			LCDWriteStringXY(2, 1, "1");
		} else {
			LCDWriteStringXY(2, 1, "0");
		}
		if (butStat.button.back) {
			LCDWriteStringXY(3, 1, "1");
		} else {
			LCDWriteStringXY(3, 1, "0");
		}

	}
}

int main(void) {
	ButtonsStatus currentButtonStatus;
	ButtonsStatus previousButtonStatus;
	State state1;
	StateMachine stateMachine;

//Initialize the buttons
	initButtons();
//Initialize LCD module
	LCDInit(LS_BLINK | LS_ULINE);

	State_new(&state1, &state1Loop);

	previousButtonStatus.buttons = 0;

	StateMachine_new(&stateMachine, &state1);
	StateMachine_start(&stateMachine, 0);

//Clear the screen
	LCDClear();
	LCDWriteString("PRESSED (EUDB):");

	while (1) {
		readButtons(&currentButtonStatus);
		if (currentButtonStatus.buttons != previousButtonStatus.buttons) {
			printStatus(currentButtonStatus);
			previousButtonStatus.buttons = currentButtonStatus.buttons;
		}
	}

}

