/*
 *  hashtable.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"



hash_table init_table(hash_table new_hash_table){
	
	new_hash_table.key = "no_key";
	new_hash_table.value = -1;
	new_hash_table.next = NULL;
	
	return new_hash_table;
		
}


int add(hash_table * table, char * key){

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
			hash_table * new_hash_cell = (hash_table *) malloc(sizeof(hash_table));

			//Find the last cell and store a pointer to it.
			hash_table * last_cell_pointer = find_last_cell(table);
			
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

hash_table * find_last_cell(hash_table * table){
	
	hash_table * current_table_cell;
	
	current_table_cell = table;
	
	while (1) {
		
		if (current_table_cell->next == NULL) {
			return current_table_cell;
		} 
		
		current_table_cell = current_table_cell->next;
	}
	
}


int find_by_key(hash_table * table, char * key){
	
	hash_table * current_table_cell;
	
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