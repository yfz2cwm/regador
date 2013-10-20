/*
 * buttons.h
 *
 *  Created on: Oct 5, 2013
 *      Author: juan
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include <avr/io.h>

#define _CONCAT(a,b) a##b
#define PORT(x) _CONCAT(PORT,x)
#define PIN(x) _CONCAT(PIN,x)
#define DDR(x) _CONCAT(DDR,x)

/************** Configuration **************
 * Available configuration is: Ports pin number and pressed value.
 * Default value for press button is 0. Uncomment to use 1 as pressed.
*/
#define BUTTON_CFG_ENTER_PORT A
#define BUTTON_CFG_ENTER_PIN 0
//#define BUTTON_CFG_ENTER_PRESSED_VALUE 1

#define BUTTON_CFG_BACK_PORT A
#define BUTTON_CFG_BACK_PIN 1
//#define BUTTON_CFG_BACK_PRESSED_VALUE 1

#define BUTTON_CFG_UP_PORT A
#define BUTTON_CFG_UP_PIN 2
//#define BUTTON_CFG_UP_PRESSED_VALUE 1

#define BUTTON_CFG_DOWN_PORT A
#define BUTTON_CFG_DOWN_PIN 3
//#define BUTTON_CFG_DOWN_PRESSED_VALUE 1

/********************************************/

typedef union {
	struct {
		uint8_t enter :1;
		uint8_t back :1;
		uint8_t up :1;
		uint8_t down :1;
	} button;
	uint8_t buttons;
} ButtonsStatus;

/**
 * Configure buttons ports and pins with adequate directions
 */
void initButtons();


/**
 *
 * @param [out] status of all the buttons
 */
void readButtons(ButtonsStatus * status);

#endif /* BUTTONS_H_ */
