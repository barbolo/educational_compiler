/*
 *  linked_table.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "linkedtable.h"



linked_table init_table(linked_table new_linked_table){
	
	new_linked_table.key = "no_key";
	new_linked_table.value = -1;
	new_linked_table.next = NULL;
	
	return new_linked_table;
		
}


int add(linked_table * table, char * key){

	int value;
	
	
	//Check if the there is an entry with the key given.
	value = find_by_key(table, key);
	
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
			table->next = NULL;
		}
		else {
			
			//Allocate memory to the new cell
			linked_table * new_hash_cell = (linked_table *) malloc(sizeof(linked_table));

			//Find the last cell and store a pointer to it.
			linked_table * last_cell_pointer = find_last_cell(table);
			
			// 
			new_hash_cell->key = key;
			new_hash_cell->value = last_cell_pointer->value + 1;
			new_hash_cell->next = NULL;
			
			last_cell_pointer->next = new_hash_cell;
			
			return new_hash_cell->value;
		}
	}
	
	return table->value;
}


linked_table * find_last_cell(linked_table * table){
	
	linked_table * current_table_cell;
	
	current_table_cell = table;
	
	while (1) {
		
		if (current_table_cell->next == NULL) {
			return current_table_cell;
		} 
		
		current_table_cell = current_table_cell->next;
	}
	
}


int find_by_key(linked_table * table, char * key){
	
	linked_table * current_table_cell;
	
	current_table_cell = table;
	
	while (current_table_cell != NULL) {
		
		if (strcmp(current_table_cell->key, key) == 0) {
			return current_table_cell->value;
		}
		
		current_table_cell = current_table_cell->next;
	}
	
	return -1;
}



void print_table(linked_table * table){
	
	linked_table * current_table_cell;
	
	current_table_cell = table;
	
	printf("Table: \n\n");
	
	while (1) {
		
		printf("Key(Token.value): %s  \nValue(ID na tabela): %d   \n  \n", current_table_cell->key, current_table_cell->value);
		
		if (current_table_cell->next != NULL) {
			current_table_cell = current_table_cell->next;
		}
		else {
			break;
		}	
	}
}