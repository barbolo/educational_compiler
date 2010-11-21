#ifndef APE_H
#define APE_H

/*
 *  ape.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos on 20/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "token.h"


/*
 
 APE: 
 
 matrix representation:
 
        token type id 
     __0______1______2____
    |go to|      |       |
   0|state|  2   |   1   |  ...
 s  |__5__|______|_______|
 t  |  .      .      .
 a  |  .      .      .      
 t  |  .      .      .
 e  |
    |
 
 Numer of states:
 declaracoes:		15
 parametros:		14
 comandos:			30
 expressao:			13
 programa:			19
 expressaoBooleana:	12
 texto:				22
 
 Number of token ids:
 reserved words + minimal non terminal (delcaracoes,parametros,comandos,expressao,programa,expressaoBooleana,texto) + special chars + identifier + int number + string
       16       +           7                                                                                       +      20       +     1      +      1     +    1
 = 46
 
 */


#define NUMBER_OF_TOKEN_TYPE_IDS 46

#define NUMBER_OF_STATES_IN_DECLARACOES_APE			15
#define NUMBER_OF_STATES_IN_PARAMETROS_APE			14
#define NUMBER_OF_STATES_IN_COMANDOS_APE			30
#define NUMBER_OF_STATES_IN_EXPRESSAO_APE			13
#define NUMBER_OF_STATES_IN_PROGRAMA_APE			19
#define NUMBER_OF_STATES_IN_EXPRESSAOBOOLEANA_APE	12
#define NUMBER_OF_STATES_IN_TEXTO_APE				22


//IDs

#define IF_RESERVED_WORD_TOKEN_ID			0
#define VOID_RESERVED_WORD_TOKEN_ID			1
#define INT_RESERVED_WORD_TOKEN_ID			2
#define FLOAT_RESERVED_WORD_TOKEN_ID		3
#define CHAR_RESERVED_WORD_TOKEN_ID			4
#define BOOLEAN_RESERVED_WORD_TOKEN_ID		5
#define STRUCT_RESERVED_WORD_TOKEN_ID		6
#define TYPEDEF_RESERVED_WORD_TOKEN_ID		7
#define RETURN_RESERVED_WORD_TOKEN_ID		8
#define MAIN_RESERVED_WORD_TOKEN_ID			9
#define CONST_RESERVED_WORD_TOKEN_ID		10
#define WHILE_RESERVED_WORD_TOKEN_ID		11
#define READ_RESERVED_WORD_TOKEN_ID			12
#define WRITE_RESERVED_WORD_TOKEN_ID		13
#define TRUE_RESERVED_WORD_TOKEN_ID			14
#define FALSE_RESERVED_WORD_TOKEN_ID		15

#define DECLARACOES_MIN_NON_TERMINAL_ID				16
#define PARAMETROS_MIN_NON_TERMINAL_ID				17
#define COMANDOS_MIN_NON_TERMINAL_ID				18
#define EXPRESSAO_MIN_NON_TERMINAL_ID				19
#define PROGRAMA_MIN_NON_TERMINAL_ID				20
#define EXPRESSAOBOOLEANA_MIN_NON_TERMINAL_ID		21
#define TEXTO_MIN_NON_TERMINAL_ID					22

#define MINUS_SPECIAL_CHAR_TOKEN_ID					23
#define PLUS_SPECIAL_CHAR_TOKEN_ID					24
#define TIMES_SPECIAL_CHAR_TOKEN_ID					25
#define DIVIDED_SPECIAL_CHAR_TOKEN_ID				26
#define COMMA_SPECIAL_CHAR_TOKEN_ID					27
#define COLON_SPECIAL_CHAR_TOKEN_ID					28 // colon --> :
#define SEMICOLON_SPECIAL_CHAR_TOKEN_ID				29 // semicolon --> ;
#define OPEN_BRACE_SPECIAL_CHAR_TOKEN_ID			30 // brace--> {}
#define CLOSE_BRACE_SPECIAL_CHAR_TOKEN_ID			31 
#define OPEN_BRACKET_SPECIAL_CHAR_TOKEN_ID			32 // BRACKET--> []
#define CLOSE_BRACKET_SPECIAL_CHAR_TOKEN_ID			33
#define OPEN_PARENTHESIS_SPECIAL_CHAR_TOKEN_ID		34
#define CLOSE_PARENTHESIS_SPECIAL_CHAR_TOKEN_ID		35
#define EQUAL_SPECIAL_CHAR_TOKEN_ID					36
#define EQUAL_EQUAL_SPECIAL_CHAR_TOKEN_ID			37
#define BIGGER_SPECIAL_CHAR_TOKEN_ID				38
#define BIGGER_OR_EQUAL_SPECIAL_CHAR_TOKEN_ID		39
#define SMALLER_SPECIAL_CHAR_TOKEN_ID				40
#define SMALLER_OR_EQUAL_SPECIAL_CHAR_TOKEN_ID		41
#define DIFFERENT_SPECIAL_CHAR_TOKEN_ID				42

#define IDENTIFIER_TOKEN_ID				43

#define INT_NUMBER_TOKEN_ID				44

#define STRING_TOKEN_ID					45


typedef struct ape_type {
	int finalState;
	int currentState;
	int initialState;
} APE;


/* global APEs variables */
APE declaracoes_ape;
APE parametros_ape;
APE comandos_ape;
APE expressao_ape;
APE programa_ape;
APE expressaoBooleana_ape;
APE texto_ape;


// matrix representation
int declaracoes_ape_transitions			[NUMBER_OF_STATES_IN_DECLARACOES_APE]		[NUMBER_OF_TOKEN_TYPE_IDS];
int parametros_ape_transitions			[NUMBER_OF_STATES_IN_PARAMETROS_APE]		[NUMBER_OF_TOKEN_TYPE_IDS];
int comandos_ape_transitions			[NUMBER_OF_STATES_IN_COMANDOS_APE]			[NUMBER_OF_TOKEN_TYPE_IDS];
int expressao_ape_transitions			[NUMBER_OF_STATES_IN_EXPRESSAO_APE]			[NUMBER_OF_TOKEN_TYPE_IDS];
int programa_ape_transitions			[NUMBER_OF_STATES_IN_PROGRAMA_APE]			[NUMBER_OF_TOKEN_TYPE_IDS];
int expressaoBooleana_ape_transitions	[NUMBER_OF_STATES_IN_EXPRESSAOBOOLEANA_APE]	[NUMBER_OF_TOKEN_TYPE_IDS];
int texto_ape_transitions				[NUMBER_OF_STATES_IN_TEXTO_APE]				[NUMBER_OF_TOKEN_TYPE_IDS];




int get_token_id(Token * token);



void init_apes_transitions();


#endif