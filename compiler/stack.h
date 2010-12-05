#ifndef STACK_H
#define STACK_H

/*
 *  stack.h
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include "stdlib.h"
#include "stdio.h"


typedef struct stack_node {
	
	char * content;	
	
	struct stack_node *next;
} Stack;

void push_stack(Stack * s, char * c);


char * pop_stack(Stack * s);


int is_stack_empty(Stack * s);

#endif