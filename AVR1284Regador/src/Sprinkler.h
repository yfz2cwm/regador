/*
 * Sprinkler.h
 *
 *  Created on: Nov 5, 2013
 *      Author: juan
 */

#ifndef SPRINKLER_H_
#define SPRINKLER_H_
#include <stdbool.h>
#include "state/State.h"

typedef struct {
	State super;
	bool working;
} Sprinkler;

void Sprinkler_new(Sprinkler * this);

Transition Sprinkler_stateLoop(void * instance, void * transitionData);

#endif /* SPRINKLER_H_ */
