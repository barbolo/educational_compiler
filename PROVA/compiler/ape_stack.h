#ifndef APE_STACK_H
#define APE_STACK_H

/*
 *  ape_stack.h
 *  compiler
 *
 */

#include "stdlib.h"
#include "stdio.h"
#include "machine.h"

typedef struct ape_stack_type {
	int machine_state;
	Machine machine;
	struct APEStack *next;
} APEStack;

APEStack *apestack_head;


void push_apestack(Machine machine);


Machine pop_apestack();


int is_apestack_empty();

#endif