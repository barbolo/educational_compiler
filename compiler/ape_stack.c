/*
 *  ape_stack.c
 *  compiler
 *
 */

#include "ape_stack.h"

void push_apestack(Machine machine) {
	APEStack *node = malloc(sizeof(APEStack));
	
	if (node == NULL) {
		fputs("Error: no space available for APEStack node\n", stderr);
		abort();
	} else {
		node->machine_state = machine.current_state;
		node->machine = machine;
		node->next = apestack_head;
		apestack_head = node;
	}
	
}

Machine pop_apestack() {
	
	if (is_apestack_empty()) {
		fputs("Error: APEStack underflow\n", stderr);
		abort();
	} else {
		APEStack *top = apestack_head;
		Machine machine = top->machine;
		machine.current_state = top->machine_state;
		apestack_head = top->next;
		free(top);
		return machine;
	}
	
}

int is_apestack_empty() {
	return apestack_head == NULL;
}