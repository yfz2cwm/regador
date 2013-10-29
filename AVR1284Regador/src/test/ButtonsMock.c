/*
 * ButtonsMock.c
 *
 *  Created on: Oct 28, 2013
 *      Author: juan
 */

#include <stdio.h>
#include "../buttons/buttons.h"

void readButtons(ButtonsStatus * status) {
	status->buttons = 0;

	char a = getchar();
	switch (a) {
	case 'w':
		status->button.up = 1;
		break;
	case 's':
		status->button.down = 1;
		break;
	case 'a':
		status->button.back = 1;
		break;
	case 'd':
		status->button.enter = 1;
		break;
	default:
		status->buttons = 0;
		break;
	}

}

void initButtons() {

}
