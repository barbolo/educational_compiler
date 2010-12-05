#ifndef LINKEDTABLE_H
#define LINKEDTABLE_H
/*
 *  linkedtable.h
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
	
} linked_table;






/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
linked_table init_table(linked_table new_linked_table);


/*****************************************************************************
 name: add
 purpose: Add values to the table.
 args: The key and the table.
 returns: The linked_table value added.
 *****************************************************************************/
int add(linked_table * table, char * key);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
linked_table * find_last_cell(linked_table * table);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
int find_by_key(linked_table * table, char * key);


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
void print_table(linked_table * table);

#endif