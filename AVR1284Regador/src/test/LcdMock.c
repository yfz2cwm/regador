/*
 * lcdMock.c
 *
 *  Created on: Oct 28, 2013
 *      Author: juan
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

char display[2][17];
uint8_t xCurrent, yCurrent = 0;

void LCDInit(uint8_t style) {
	display[0][16] = '\0';
	display[1][16] = '\0';
}
void LCDByte(uint8_t a, uint8_t b) {

}

void showDisplay() {
	printf("------------------ \n");
	printf("|%16s|\n", display[0]);
	printf("|%16s|\n", display[1]);
	printf("------------------ \n");
}

void LCDWriteString(const char *msg) {
//	printf("%s", msg);
	char * to = &display[yCurrent][xCurrent];
	strncpy(to,msg,16);
	showDisplay();
}

void LCDWriteInt(int val, unsigned int field_length) {
	printf("%d", val);
	printf("\n");
}

void LCDGotoXY(uint8_t x, uint8_t y) {
	xCurrent = x;
	yCurrent = y;
}
