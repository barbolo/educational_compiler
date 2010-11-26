#include "stdlib.h"
#include "stdio.h"
#include "stack.h"

void initialize_apestack() {
	apestack_head = malloc(sizeof(APEStack));
	apestack_head->machine_state = 0;
}

void push_apestack(int machine_state) {
	APEStack *node = malloc(sizeof(APEStack));
	
	if (node == NULL) {
		fputs("Error: no space available for APEStack node\n", stderr);
		abort();
	} else {
		node->machine_state = machine_state;
		node->next = apestack_head;
		apestack_head = node;
	}
	
}

int pop_apestack() {
	
	if (apestack_head == NULL) {
		fputs("Error: APEStack underflow\n", stderr);
		abort();
	} else {
		APEStack *top = apestack_head;
		int value = top->machine_state;
		apestack_head = top->next;
		free(top);
		return value;
	}
	
}

int main() {
	
	//initialize_apestack();
	push_apestack(1);
	push_apestack(2);
	push_apestack(3);
	push_apestack(4);
	push_apestack(5);
	
	printf("Machine state: %d\n", pop_apestack());
	printf("Machine state: %d\n", pop_apestack());
	printf("Machine state: %d\n", pop_apestack());
	
	return 0;
}