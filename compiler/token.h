#ifndef TOKEN_H
#define TOKEN_H

/*
 *  token.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

// ---- Token Types - start -----

#define TOKEN_TYPE_INVALID		   -1
#define TOKEN_TYPE_INCOMPLETE		0
#define TOKEN_TYPE_RESERVED_WORD	1
#define TOKEN_TYPE_IDENTIFIER		2
#define TOKEN_TYPE_INT_NUMBER		3
#define TOKEN_TYPE_SPECIAL			4
#define TOKEN_TYPE_IGNORED			5	// blank char, \n, \t, comments
#define TOKEN_TYPE_END_OF_FILE		6	// this is a special token type, that belongs to the tokens returned when the file content has been all read
#define TOKEN_TYPE_STRING			7


typedef int type_of_token;

// ---- Token Types - end -----



typedef struct token_type {
	type_of_token type;
	char *value;
	int index;
	int line;
	int column;
} Token;

/* global variable token */
Token token;


/*****************************************************************************
 name: token_type_name
 purpose: Get the name of the token type.
 args: 
 returns: The name of the token type.
 *****************************************************************************/
char * token_type_name();


#endif