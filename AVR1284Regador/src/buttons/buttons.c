/*
 * buttons.c
 *
 *  Created on: Oct 5, 2013
 *      Author: juan
 */

#include "buttons.h"

#define BUTTON_ENTER_PORT 	PORT(BUTTON_CFG_ENTER_PORT)
#define BUTTON_BACK_PORT 	PORT(BUTTON_CFG_BACK_PORT)
#define BUTTON_UP_PORT 	 	PORT(BUTTON_CFG_UP_PORT)
#define BUTTON_DOWN_PORT 	PORT(BUTTON_CFG_DOWN_PORT)


#define BUTTON_ENTER_PIN_NUMBER 	PIN(BUTTON_CFG_ENTER_PIN)
#define BUTTON_BACK_PIN_NUMBER 		PIN(BUTTON_CFG_BACK_PIN)
#define BUTTON_UP_PIN_NUMBER 	 	PIN(BUTTON_CFG_UP_PIN)
#define BUTTON_DOWN_PIN_NUMBER 		PIN(BUTTON_CFG_DOWN_PIN)

#define BUTTON_ENTER_DDR 	DDR(BUTTON_CFG_ENTER_PORT)
#define BUTTON_BACK_DDR 	DDR(BUTTON_CFG_BACK_PORT)
#define BUTTON_UP_DDR 		DDR(BUTTON_CFG_UP_PORT)
#define BUTTON_DOWN_DDR 	DDR(BUTTON_CFG_DOWN_PORT)

#define SFR 	DDR(BUTTON_CFG_DOWN_PORT)

#ifdef BUTTON_CFG_ENTER_PRESSED_VALUE
#	define enterButtonPressed(sfr, bit) bit_is_set(sfr, bit)
#else
#	define enterButtonPressed(sfr, bit) bit_is_clear(sfr, bit)
#endif

#ifdef BUTTON_CFG_UP_PRESSED_VALUE
#	define upButtonPressed(sfr, bit) bit_is_set(sfr, bit)
#else
#	define upButtonPressed(sfr, bit) bit_is_clear(sfr, bit)
#endif

#ifdef BUTTON_CFG_DOWN_PRESSED_VALUE
#	define downButtonPressed(sfr, bit) bit_is_set(sfr, bit)
#else
#	define downButtonPressed(sfr, bit) bit_is_clear(sfr, bit)
#endif

#ifdef BUTTON_CFG_BACK_PRESSED_VALUE
#	define backButtonPressed(sfr, bit) bit_is_set(sfr, bit)
#else
#	define backButtonPressed(sfr, bit) bit_is_clear(sfr, bit)
#endif

void initButtons() {
	BUTTON_ENTER_DDR &= ~(_BV(BUTTON_ENTER_PIN_NUMBER));
	BUTTON_UP_DDR &= ~(_BV(BUTTON_UP_PIN_NUMBER));
	BUTTON_DOWN_DDR &= ~(_BV(BUTTON_DOWN_PIN_NUMBER));
	BUTTON_BACK_DDR &= ~(_BV(BUTTON_BACK_PIN_NUMBER));
	//Enable the pullUps
	BUTTON_ENTER_PORT |= _BV(BUTTON_ENTER_PIN_NUMBER);
	BUTTON_UP_PORT |= _BV(BUTTON_UP_PIN_NUMBER);
	BUTTON_DOWN_PORT |= _BV(BUTTON_DOWN_PIN_NUMBER);
	BUTTON_BACK_PORT |= _BV(BUTTON_BACK_PIN_NUMBER);
}

void readButtons(ButtonsStatus * buttonStatus) {

	buttonStatus->button.enter = enterButtonPressed(PIN(BUTTON_CFG_ENTER_PORT),BUTTON_ENTER_PIN_NUMBER) ? 1:0;
	buttonStatus->button.up = enterButtonPressed(PIN(BUTTON_CFG_UP_PORT),BUTTON_UP_PIN_NUMBER) ? 1:0;
	buttonStatus->button.down = enterButtonPressed(PIN(BUTTON_CFG_DOWN_PORT),BUTTON_DOWN_PIN_NUMBER) ? 1:0;
	buttonStatus->button.back = enterButtonPressed(PIN(BUTTON_CFG_DOWN_PORT),BUTTON_BACK_PIN_NUMBER) ? 1:0;
}
