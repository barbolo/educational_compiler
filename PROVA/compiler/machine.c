/*
 *  machine.c
 *  compiler
 *
 */

#include "machine.h"

void initialize_machine_transitions(Machine * m) {
	int i, j;
	for(i=0; i < 100; i++) {
		for(j=0; j < 200; j++)
			m->token_transitions[i][j] = APE_INVALID_STATE;
		for(j=0; j < 50; j++)
			m->machine_transitions[i][j] = APE_INVALID_STATE;
	}
}



