#ifndef STACKFRAME_H
#define STACKFRAME_H
/*
 *  stack_frame.h
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 04/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "stdlib.h"
#include "stdio.h"

#include "symbol_table.h"

typedef struct sf_node {
	
	SymbolTable * symbol_table; // guarda tabela de símbolos do escopo	
	
	struct sf_node *next;
} StackFrame;

StackFrame * stack_frame_head;


void push_stack_frame(SymbolTable * symbol_table);


SymbolTable * pop_stack_frame();


int is_stack_frame_empty();

#endif