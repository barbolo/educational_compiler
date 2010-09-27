/*
 *  hashtable.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include <stdio.h>



typedef struct _No {

	char * key;
	
	//Value from the last No plus 1.
	int value;

	struct _No * next;
	
} hash_table;






/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
hash_table init_table(hash_table new_hash_table);


/*****************************************************************************
 name: add
 purpose: Add values to the table.
 args: The key and the table.
 returns: The hash_table value added.
 *****************************************************************************/
int add(hash_table * table, char * key);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
hash_table * find_last_cell(hash_table * table);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
int find_by_key(hash_table * table, char * key);


