/*
 *  hashtable.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "symbol_table_hashtable.h"
#include "tables.h"


symbol_table_hash_table * init_symbol_table(){
	
	//Allocate memory to the new cell
	symbol_table_hash_table * new_hash_table = (symbol_table_hash_table *) malloc(sizeof(symbol_table_hash_table));
	
	new_hash_table->key = "no_key";
	new_hash_table->value = -1;
	new_hash_table->type = -1;
	new_hash_table->dataType = -1;
	new_hash_table->memory_address = -1;
	new_hash_table->line_number = -1;
	new_hash_table->next = NULL;
	
	return new_hash_table;
	
}

int add_in_symbol_table(symbol_table_hash_table * table, char * key, int line){
	
	int value;
	
	
	//Check if the there is an entry with the key given.
	value = find_by_key_in_symbol_table(table, key);
	
	if ( value != -1 ){
		//The key already exists.
		return value;
	}
	else {
		//Add a new cell
		
		//If the firs cell has its key == no_key. So, to add a cell we only overwite its values.
		if (table->key == "no_key") {
			table->key = key;
			table->value = 0;
			
			table->type = -1;
			table->dataType = -1;
			table->memory_address = -1;
			table->line_number = line;
			
			table->next = NULL;
		}
		else {
			
			//Allocate memory to the new cell
			symbol_table_hash_table * new_hash_cell = (symbol_table_hash_table *) malloc(sizeof(symbol_table_hash_table));
			
			//Find the last cell and store a pointer to it.
			symbol_table_hash_table * last_cell_pointer = find_last_cell_in_symbol_table(table);
			
			// 
			new_hash_cell->key = key;
			new_hash_cell->value = last_cell_pointer->value + 1;
			
			new_hash_cell->type = -1;
			new_hash_cell->dataType = -1;
			new_hash_cell->memory_address = -1;
			new_hash_cell->line_number = line;
			
			new_hash_cell->next = NULL;
			
			last_cell_pointer->next = new_hash_cell;
			
			return new_hash_cell->value;
		}
	}
	
	return table->value;
}

symbol_table_hash_table * find_last_cell_in_symbol_table(symbol_table_hash_table * table){
	
	symbol_table_hash_table * current_table_cell;
	
	current_table_cell = table;
	
	while (1) {
		
		if (current_table_cell->next == NULL) {
			return current_table_cell;
		} 
		
		current_table_cell = current_table_cell->next;
	}
	
}

int find_by_key_in_symbol_table(symbol_table_hash_table * table, char * key){
	
	symbol_table_hash_table * current_table_cell;
	
	current_table_cell = table;
	
	while (1) {
		
		if (strcmp(current_table_cell->key, key) == 0) {
			return current_table_cell->value;
		} 
		
		if (current_table_cell->next != NULL) {
			current_table_cell = current_table_cell->next;
		}
		else {
			return -1;
		}	
	}
	
	return -1;
}

void print_symbol_table(symbol_table_hash_table * table){
	
	symbol_table_hash_table * current_table_cell;
	
	current_table_cell = table;
	
	printf("Scope: %d \nSymbol Table: \n\n", current_scope->id_value);
	printf("Key(Token.value)	|	Value(ID na tabela)	|	Type(rótulo(0) ou variavel(1))	|	DataType (int:0 bool:1 char:2)	|	Memory Address	|	LineNumber  \n");
	
	while (1) {
		
		printf("%s							%d							%d											%d									%d						%d\n", current_table_cell->key, current_table_cell->value, current_table_cell->type, current_table_cell->dataType, current_table_cell->memory_address, current_table_cell->line_number);
		
		if (current_table_cell->next != NULL) {
			current_table_cell = current_table_cell->next;
		}
		else {
			break;
		}	
	}
	printf("\n\n");
}

symbol_table_hash_table * find_cell_by_key_in_symbol_table(symbol_table_hash_table * table, char * key){
	
	symbol_table_hash_table * current_table_cell;
	
	current_table_cell = table;
	
	while (1) {
		
		if (strcmp(current_table_cell->key, key) == 0) {
			return current_table_cell;
		} 
		
		if (current_table_cell->next != NULL) {
			current_table_cell = current_table_cell->next;
		}
		else {
			return NULL;
		}	
	}
	
	return NULL;
	
}
