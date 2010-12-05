/*
 *  stack.c
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "stack.h"

void push_stack(Stack * s, char * c) {
	Stack * node = malloc(sizeof(Stack));
	
	if (node == NULL) {
		fputs("Error: no space available for Stack node\n", stderr);
	} else {
		node->content = c;
		node->next = s;
		s = node;
	}

}

char * pop_stack(Stack * s) {
	if (is_stack_empty(s)) {
		fputs("Error: Stack underflow\n", stderr);
		abort();
	} else {
		Stack * top = s;
		char * c = top->content;
		s = top->next;
		free(top);
		return c;
	}

}

int is_stack_empty(Stack * s) {
	return s == NULL;
}
