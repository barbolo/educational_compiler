#ifndef TABLES_H
#define TABLES_H
/*
 *  tables.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include "hashtable.h"
#include "symbol_table_hashtable.h"

symbol_table_hash_table table_symbols;
hash_table table_numbers;
hash_table table_reserved_words;
hash_table table_specials;



/*****************************************************************************
 name: initialize_semantic_tables
 purpose: initialize the tables user by the semantic analyzer
 args: 
 returns: 
 *****************************************************************************/

void initialize_semantic_tables();



/*****************************************************************************
 name: update_semantic_tables
 purpose: insert/update token into a table related to its type.
 args: 
 returns: index in table.
 *****************************************************************************/

int update_semantic_tables();


#endif