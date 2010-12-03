#ifndef ST_HASHTABLE_H
#define ST_HASHTABLE_H
/*
 *  hashtable.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include <stdio.h>

#define IDENTIFIER_TYPE_LABEL 0
#define IDENTIFIER_TYPE_VARIABLE 1

#define DATA_TYPE_INT 0
#define DATA_TYPE_BOOLEAN 1
#define DATA_TYPE_CHAR 2
#define DATA_TYPE_VOID 3


typedef struct _ST_No {
	
	char * key;
	
	//Value from the last No plus 1.
	int value;
	
	
	//Useful variables to the symbol table
	
	//Rótulo(label) ou variável (variable)
	int type;
	
	//int, float, boolean ...
	int dataType;
	
	//Memory address of the variable.
	int memory_address;
	
	//Line number when it has been declared.
	int line_number;
	
	
	struct _ST_No * next;
	
} symbol_table_hash_table;






/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
symbol_table_hash_table init_symbol_table(symbol_table_hash_table new_hash_table);


/*****************************************************************************
 name: add
 purpose: Add values to the table.
 args: The key and the table.
 returns: The hash_table value added.
 *****************************************************************************/
int add_in_symbol_table(symbol_table_hash_table * table, char * key, int line);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
symbol_table_hash_table * find_last_cell_in_symbol_table(symbol_table_hash_table * table);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
int find_by_key_in_symbol_table(symbol_table_hash_table * table, char * key);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
void print_symbol_table(symbol_table_hash_table * table);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
symbol_table_hash_table * find_cell_by_key_in_symbol_table(symbol_table_hash_table * table, char * key);


#endif