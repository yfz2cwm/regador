#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdio.h>
#include "avr/interrupt.h"
#include "lcd/lcd.h"
#include "buttons/buttons.h"
#include "state/StateMachine.h"
#include "state/State.h"
Transition state2Loop(void* data);
Transition state1Loop(void * data);
void printStatus(ButtonsStatus butStat);

//100 ms
uint8_t cms = 0;
uint8_t seconds = 0;
uint8_t minutes = 0;
uint8_t hours = 0;
uint8_t days = 0;

void initTimer() {
	TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode

	TIMSK1 |= (1 << OCIE1A); // Enable CTC interrupt

	OCR1A = 3124; // Set CTC compare value 100ms, with a prescaler of 256

	TCCR1B |= ((1 << CS12)); // Start timer at 8Mhz/256

	sei();
	//  Enable global interrupts
}

ISR(TIMER1_COMPA_vect)
{
	cms++;
	if (cms == 10) {
		seconds++;
		cms = 0;
	}

	if (seconds == 60) {
		seconds = 0;
		minutes++;
	}
	if (minutes == 60) {
		minutes = 0;
		hours++;
	}
	if (hours == 24) {
		hours = 0;
		days++;
	}
	char buff[12];
	snprintf(buff, 12, "%02d:%02d:%02d:%02d", days, hours, minutes, seconds);
	LCDWriteStringXY(0, 1, (const char *)buff);
}

Transition state1Loop(void* data) {
	State state2;
	Transition state2Transition;

	ButtonsStatus currentButtonStatus;
	ButtonsStatus previousButtonStatus;
	previousButtonStatus.buttons = 0;
	State_new(&state2, &state2Loop);
	state2Transition.dataFornextState = 0;
	state2Transition.nextState = &state2;
	_delay_ms(5);
	LCDWriteStringXY(0,0,"State1");

	while (1) {
		readButtons(&currentButtonStatus);
		if (currentButtonStatus.buttons != previousButtonStatus.buttons) {
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
	_delay_ms(5);
	LCDWriteStringXY(0,0,"State2");

	while (1) {
		readButtons(&currentButtonStatus);

		if (currentButtonStatus.buttons != previousButtonStatus.buttons) {
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

	initTimer();
	State_new(&state1, &state1Loop);

	previousButtonStatus.buttons = 0;

	StateMachine_new(&stateMachine, &state1);
	StateMachine_start(&stateMachine, 0);

//Clear the screen


	while (1) {

//		readButtons(&currentButtonStatus);
//		if (currentButtonStatus.buttons != previousButtonStatus.buttons) {
//			printStatus(currentButtonStatus);
//			previousButtonStatus.buttons = currentButtonStatus.buttons;
//		}
	}

}

