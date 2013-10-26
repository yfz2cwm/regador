#include <stdio.h>
#include "../state/StateMachine.h"
State state1;
State state2;
Transition task1(void *data) {
	Transition toReturn;

	toReturn.nextState = &state1;
	toReturn.dataFornextState = NULL;
	printf("Task 1\n");
	return toReturn;

}

Transition task2(void *data) {
	Transition toReturn;

	toReturn.nextState = &state2;
	toReturn.dataFornextState = NULL;
	printf("Task 2\n");
	return toReturn;
}

int main(int argc, char **argv) {

	StateMachine stateMachine;

	TransitionList transitionList;
	Transition transitionArray[2];
	transitionList.transition = transitionArray;
	transitionList.transitionCount = 2;

	State_new(&state1, &task1);
	State_new(&state2, &task2);

	transitionList.transition[0].nextState = &state1;
	transitionList.transition[1].nextState = &state2;

	StateMachine_new(&stateMachine, &transitionList);
	StateMachine_start(&stateMachine);
	printf("Hola mundo");
	return 0;
}
