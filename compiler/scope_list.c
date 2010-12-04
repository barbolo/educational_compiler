/*
 *  scope_hashtable.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos and Rafael Barbolo Lopes on 03/12/10.
 *  Copyright 2010 COOP10-POLI-USP. All rights reserved.
 *
 */

#include "scope_list.h"
#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "symbol_table_hashtable.h"




scope_list init_scope_list(scope_list new_list ){
	
	new_list.id_value = 0;
	new_list.next = NULL;
	new_list.last = NULL;
	
	new_list.symbol_table = init_symbol_table();
	
	
	return new_list;
	
}


scope_list * add_scope(scope_list * scopes){
	
	//Add a new cell
	
	//Go to the last scope of the list.
	while (scopes->next != NULL) {
		scopes = scopes->next;
	}
	
	//Store a pointer to it.
	scope_list * last_scope_pointer = scopes;
	
	//Allocate memory to the new cell
	scope_list * new_scope = (scope_list *) malloc(sizeof(scope_list));
	
	new_scope->id_value = last_scope_pointer->id_value + 1;
	new_scope->next = NULL;
	new_scope->last = last_scope_pointer;
	
	last_scope_pointer->next = new_scope;
	
	//Allocate memory to the new symbol table
	symbol_table_hash_table * new_symbol_table = (symbol_table_hash_table *) malloc(sizeof(symbol_table_hash_table));
	
	new_scope->symbol_table = init_symbol_table(*new_symbol_table);
	
	return new_scope;
}


scope_list delete_last_scope(scope_list * scopes){
	
	printf("Delete scope not implemented!!");
	
	return *scopes;
}










