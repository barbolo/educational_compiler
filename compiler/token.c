/*
 *  token.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "token.h"


char * get_type_name(int token_type){

	char * type_name;
	
	switch ( token_type ) {
		case  -1:
			type_name = "invalid";
			break;
		case  0:
			type_name = "incomplete";
			break;
		case  1:
			type_name = "reserved word";
			break;
		case  2:
			type_name = "identifier";
			break;
		case  3:
			type_name = "integer number";
			break;
		case  4:
			type_name = "special char";
			break;
		case  5:
			type_name = "ignored char";
			break;
		case  6:
			type_name = "end of file";
			break;
		default:
			type_name = "Wrong token type identifier.";
			break;
	}
	
	return type_name;
}


void new_token(token_type token){
	
	token.column = 0;
	token.index = 0;
	token.line = 0;
	token.type = TOKEN_TYPE_IGNORED;
	for (int i = 0 ; i < 100; i++) {
		token.value[i] = 0;
	}
	
	
	
}