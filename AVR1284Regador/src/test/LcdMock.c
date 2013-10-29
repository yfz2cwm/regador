/*
 * lcdMock.c
 *
 *  Created on: Oct 28, 2013
 *      Author: juan
 */
#include <stdint.h>
#include <stdio.h>
char display [2][17];

void LCDInit(uint8_t style) {

}
void LCDByte(uint8_t a, uint8_t b) {

}

void showDisplay(){
	printf("------------------ \n");
	printf("|%s|\n",display[0]);
	printf("|%s|\n",display[1]);
	printf("------------------ \n");
}

void LCDWriteString(const char *msg) {
	printf("%s", msg);
	printf("\n");
}

void LCDWriteInt(int val, unsigned int field_length) {
	printf("%d", val);
	printf("\n");
}

void LCDGotoXY(uint8_t x, uint8_t y) {

}
