/*
 *  token.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include "token.h"


char * token_type_name() {

	char * type_name;
	
	switch ( token.type ) {
		case  TOKEN_TYPE_INVALID:
			type_name = "invalid";
			break;
		case  TOKEN_TYPE_INCOMPLETE:
			type_name = "incomplete";
			break;
		case  TOKEN_TYPE_RESERVED_WORD:
			type_name = "reserved word";
			break;
		case  TOKEN_TYPE_IDENTIFIER:
			type_name = "identifier";
			break;
		case  TOKEN_TYPE_INT_NUMBER:
			type_name = "integer number";
			break;
		case  TOKEN_TYPE_SPECIAL:
			type_name = "special char";
			break;
		case  TOKEN_TYPE_IGNORED:
			type_name = "ignored char";
			break;
		case  TOKEN_TYPE_END_OF_FILE:
			type_name = "end of file";
			break;
		case  TOKEN_TYPE_STRING:
			type_name = "string";
			break;
		case  TOKEN_TYPE_FLOAT_NUMBER:
			type_name = "float number";
			break;
		case  TOKEN_TYPE_HEXA_NUMBER:
			type_name = "hexa number";
			break;
		case  TOKEN_TYPE_SCIENTIFC_NUMBER:
			type_name = "scientific number";
			break;
		default:
			type_name = "Wrong token type identifier.";
			break;
	}
	
	return type_name;
}
