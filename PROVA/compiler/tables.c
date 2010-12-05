/*
 *  tablesymbols.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include "tables.h"

void initialize_semantic_tables() {
	
	table_numbers = init_table(table_numbers);
	table_reserved_words = init_table(table_reserved_words);
	table_specials = init_table(table_specials);
	table_symbols = init_table(table_symbols);
	
	/* add reserved words */
	add(&table_reserved_words, "and");
	add(&table_reserved_words, "break");
	add(&table_reserved_words, "do");
	add(&table_reserved_words, "else");
	add(&table_reserved_words, "elseif");
	add(&table_reserved_words, "end");
	add(&table_reserved_words, "false");
	add(&table_reserved_words, "for");
	add(&table_reserved_words, "if");
	add(&table_reserved_words, "function");
	add(&table_reserved_words, "in");
	add(&table_reserved_words, "local");
	add(&table_reserved_words, "nil");
	add(&table_reserved_words, "not");
	add(&table_reserved_words, "repeat");
	add(&table_reserved_words, "or");
	add(&table_reserved_words, "return");
	add(&table_reserved_words, "then");
	add(&table_reserved_words, "true");
	add(&table_reserved_words, "until");
	add(&table_reserved_words, "while");
	
}


int update_semantic_tables() {
	
	int index = -1;

	if (token.type == TOKEN_TYPE_INT_NUMBER)
		index = add(&table_numbers, token.value);
	else if (token.type == TOKEN_TYPE_RESERVED_WORD)
		index = add(&table_reserved_words, token.value);
	else if (token.type == TOKEN_TYPE_IDENTIFIER)
		index = add(&table_symbols, token.value);
	else if (token.type == TOKEN_TYPE_SPECIAL)
		index = add(&table_specials, token.value);
	
	//TALVEZ PRECISE CRIAR UMA TABELA PRA STRING. MAS NAO SE SE PRECISA NAO. ver melhor depois.
	
	return index;
	
}