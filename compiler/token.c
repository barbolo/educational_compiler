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