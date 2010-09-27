/*
 *  analyser.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "analyser.h"


token_type get_next_token(){

	//char a_char;
	int i = 0;
	
	init_reader(read_head);
	
	new_token(token);
//	new_transducer(transducer); // Vai precisar disso mesmo???        !!!!!       liberar essa linha depois q o transducer tiver pronto   !!!!!!!!!!!!!!!
	
	
	
	read_head = get_next_char("../resources/test_lex.poli", read_head);
	token.column++;
	
	// If the file is empty, return a empty type token.
	if (read_head.current == EOF) {
		token.type = TOKEN_TYPE_END_OF_FILE;
		return token;
	}
	
	
	// Read ignored chars
	while (read_head.current != EOF && token.type == TOKEN_TYPE_IGNORED) {
		// do nothing, chars are being ignored
		
//		token.type = transducer.consume_input(read_head.current, read_head.next);        !!!!!       liberar essa linha depois q o transducer tiver pronto
		token.value[0] = read_head.current;
		
		read_head = get_next_char("../resources/test_lex.poli", read_head);
		token.column++;
		
		if (token.value[0] == '\n') {
			token.line++;
			token.column = 0;
		}
	}
	
	
	// Read token
	while (read_head.current != EOF && token.type == TOKEN_TYPE_INCOMPLETE) {
		
//		token.type = transducer.consume_input(read_head.current, read_head.next);         !!!!!      liberar essa linha depois q o transducer tiver pronto
		token.value[i] = read_head.current;
		
		read_head = get_next_char("../resources/test_lex.poli", read_head);
		token.column++;
		
		// ????????  if value[-1] == ?\n  ???????????? o que é esse [-1]?
		if (token.value[i] == '\n') {
			token.line++;
			token.column = 0;
		}		
		
		i++;
	}
	
	
	
	if (token.type == TOKEN_TYPE_IGNORED) {
		for (int i = 0 ; i < 100; i++) {
			token.value[i] = 0;
		}
	}
	
	if (token.type == TOKEN_TYPE_INCOMPLETE) {
		token.type = TOKEN_TYPE_INVALID; 
	}
	else {
//		if (token.type == TOKEN_TYPE_IDENTIFIER &&      !!!!!     Semantic::TableReservedWords.include?(value)      !!!!!!!       ) {
//			token.type = TOKEN_TYPE_RESERVED_WORD;
//		}
	}

	
	// !!!!!!!!!!!!!!!!!!!!!!
	//token.index = table_value(value, type)       !!!!!!        liberar essa linha e fazer a função table_value depois q as tabelas ficarem prontas
	// !!!!!!!!!!!!!!!!!!!!!!	

	return token;
}

///*

