/*
 * TimerMock.c
 *
 *  Created on: Oct 28, 2013
 *      Author: juan
 */

#include "../Timer.h"

Timer instance;

void Timer_init(Timer* this){

}


Time Timer_getTime(Timer* this){
	this->time.seconds++;
	return this->time;
}

Timer * Timer_getInstance(){
	return & instance;
}
