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
	table_symbols = init_table(table_symbols);
	table_numbers = init_table(table_numbers);
	table_reserved_words = init_table(table_reserved_words);
	table_specials = init_table(table_specials);
	
	/* add reserved words */
	add(&table_reserved_words, "if");
	add(&table_reserved_words, "void");
	add(&table_reserved_words, "int");
	add(&table_reserved_words, "float");
	add(&table_reserved_words, "char");
	add(&table_reserved_words, "boolean");
	add(&table_reserved_words, "struct");
	add(&table_reserved_words, "typedef");
	add(&table_reserved_words, "return");
	add(&table_reserved_words, "main");
	add(&table_reserved_words, "const");
	add(&table_reserved_words, "while");
	add(&table_reserved_words, "read");
	add(&table_reserved_words, "write");
	add(&table_reserved_words, "true");
	add(&table_reserved_words, "false");
	//add(&table_reserved_words, "for");
	//add(&table_reserved_words, "else");
	
	
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