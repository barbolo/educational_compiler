#ifndef TOKEN_H
#define TOKEN_H

/*
 *  token.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
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

// ---- Token Types - end -----



struct token_structure{
	int type;
	char value[100]; // hum ñ sei se isos vai ser int mesmo! talvez tenhamos q usar um void * e depois pelo tipo do token dar um cast pro tipo de dado certo.
	int index;
	int line;
	int column;
};

typedef struct token_structure token_type; 



/*****************************************************************************
 name: new_token
 purpose: Prepare the strucutre of a token. Cleans it and fills it with standard values.
 args: The token.
 returns: nothing.
 *****************************************************************************/
void new_token(token_type token);


/*****************************************************************************
 name: get_token_type_name
 purpose: Get the name of the token type.
 args: Token type ID.
 returns: The name of the token type.
 *****************************************************************************/
char * get_token_type_name(int token_type);


#endif