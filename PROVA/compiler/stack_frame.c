/*
 *  stack_frame.c
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 04/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "stack_frame.h"

void push_stack_frame(SymbolTable * symbol_table) {
	StackFrame * node = malloc(sizeof(StackFrame));
	
	if (node == NULL) {
		fputs("Error: no space available for StackFrame node\n", stderr);
		abort();
	} else {
		node->symbol_table = symbol_table;
		node->next = stack_frame_head;
		stack_frame_head = node;
	}

}


SymbolTable * pop_stack_frame() {
	if (is_stack_frame_empty()) {
		fputs("Error: StackFrame underflow\n", stderr);
		abort();
	} else {
		StackFrame *top = stack_frame_head;
		SymbolTable * tabela = top->symbol_table;
		stack_frame_head = top->next;
		free(top);
		return tabela;
	}

}


int is_stack_frame_empty() {
	return stack_frame_head == NULL;
}