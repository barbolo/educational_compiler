/*
 *  stack.c
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 05/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "stack.h"

void push_stack(Stack ** head, char * c) {
	Stack * node = malloc(sizeof(Stack));
	
	if (node == NULL) {
		fputs("Error: no space available for Stack node\n", stderr);
	} else {
		node->content = c;
		node->next = *head;
		*head = node;
	}

}

char * pop_stack(Stack ** head) {
	if (is_stack_empty(*head)) {
		fputs("Error: Stack underflow\n", stderr);
		abort();
	} else {
		Stack * top = *head;
		char * c = top->content;
		*head = top->next;
		free(top);
		return c;
	}

}

char * consulta_pilha(Stack * head) {
	if (is_stack_empty(head)) {
		return NULL;
	} else {
		return head->content;
	}

}

int is_stack_empty(Stack * head) {
	return head == NULL;
}
