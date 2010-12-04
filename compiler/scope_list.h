#ifndef SCOPE_LIST_H
#define SCOPE_LIST_H

/*
 *  scope_hashtable.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos on 03/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include <stdio.h>
#include "symbol_table_hashtable.h"


typedef struct _scope_No {
	
	symbol_table_hash_table * symbol_table;
	
	//Value from the last No plus 1.
	int id_value;
	
	struct _scope_No * next;
	struct _scope_No * last;
	
} scope_list;


/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
scope_list init_scope_list(scope_list new_hash_table);

/*****************************************************************************
 name: add
 purpose: 
 args: 
 returns: the address to the current added scope..
 *****************************************************************************/
scope_list * add_scope(scope_list * scopes);

/*****************************************************************************
 name: delete_last_scope
 purpose: 
 args: 
 returns: the address to the current added scope.
 *****************************************************************************/
scope_list delete_last_scope(scope_list * scopes);

#endif