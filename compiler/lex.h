#ifndef LEX_H
#define LEX_H


/*
 *  lex.h
 *  compilador
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

/*
lex.c -> representa analisador léxico. Tem uma função chamada "get_next_token" que deve retornar o próximo token. 
Caso não haja mais tokens, ele retorna um token especial que indica que os tokens acabaram.
Ele usa o reader.c para ler os caracteres e enviar para o transducer processar até retornar o tipo do token lido.
*/


struct token_structure{
	int class;
	char repr;
};

typedef struct token_structure token_type; 

token_type token;

char * text_buffer[200];

/*****************************************************************************
 name: get_next_token
 purpose: get the next token from the source code.
 args: 
 returns: next token.
 *****************************************************************************/

token_type get_next_token();




#endif