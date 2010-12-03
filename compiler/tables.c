/*
 *  tablesymbols.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include "tables.h"
#include "token.h"


void initialize_semantic_tables() {
	table_symbols = init_symbol_table(table_symbols);
	table_numbers = init_table(table_numbers);
	table_reserved_words = init_table(table_reserved_words);
	table_specials = init_table(table_specials);
	
	/* add reserved words */
	add(&table_reserved_words, "functions");
	add(&table_reserved_words, "int");
	add(&table_reserved_words, "char");
	add(&table_reserved_words, "boolean");
	add(&table_reserved_words, "void");
	add(&table_reserved_words, "main");
	add(&table_reserved_words, "begin");
	add(&table_reserved_words, "return");
	add(&table_reserved_words, "if");
	add(&table_reserved_words, "while");
	add(&table_reserved_words, "scan");
	add(&table_reserved_words, "print");
	add(&table_reserved_words, "else");
	add(&table_reserved_words, "not");
	add(&table_reserved_words, "and");
	add(&table_reserved_words, "or");
	
}


int update_semantic_tables() {
	
	int index = -1;

	if (token.type == TOKEN_TYPE_INT_NUMBER)
		index = add(&table_numbers, token.value);
	else if (token.type == TOKEN_TYPE_RESERVED_WORD)
		index = add(&table_reserved_words, token.value);
	else if (token.type == TOKEN_TYPE_IDENTIFIER)
		index = add_in_symbol_table(&table_symbols, token.value, token.line);
	else if (token.type == TOKEN_TYPE_SPECIAL)
		index = add(&table_specials, token.value);
	
	//TALVEZ PRECISE CRIAR UMA TABELA PRA STRING. MAS NAO SE SE PRECISA NAO. ver melhor depois.
	
	return index;
	
}