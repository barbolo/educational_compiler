/*
 *  ape.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos on 20/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ape.h"


//talvez seja melhor chamar get_transition_id ou algo assim. pq nem tudo é token né.
//vai usar essa fç pra poder consultar a matriz q representa o automato. pq nao se sabe diretamente o id do tipo do token.
int get_token_id(Token * token){
	
	int answer_id;
	int token_special_value;
	
	//se for palavra reservada, ver q palavara é e aí pega o ID dela
	if (token->type == TOKEN_TYPE_RESERVED_WORD) {
		
		
		
		
	}
	
	
	//se for caracter especial, ver qual é e aí pega o ID dele
	if (token->type == TOKEN_TYPE_SPECIAL) {
		
		token_special_value = ((int) token->value);
		
		switch ( token_special_value ) {
			case  ((int)'+'):
				answer_id = PLUS_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)'-'):
				answer_id = MINUS_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)'*'):
				answer_id = TIMES_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)'/'):
				answer_id = DIVIDED_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)','):
				answer_id = COMMA_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)':'):
				answer_id = COLON_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)';'):
				answer_id = SEMICOLON_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)'{'):
				answer_id = OPEN_BRACE_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)'}'):
				answer_id = CLOSE_BRACE_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)'['):
				answer_id = OPEN_BRACKET_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)']'):
				answer_id = CLOSE_BRACKET_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)'('):
				answer_id = OPEN_PARENTHESIS_SPECIAL_CHAR_TOKEN_ID;
				break;
			case  ((int)')'):
				answer_id = CLOSE_PARENTHESIS_SPECIAL_CHAR_TOKEN_ID;
				break;		
				
			//falta os == <= e etc....  putz acho q vai dar merda. ah!!!!	acho q vai ter q usar o comparador de sring... pra palavra reservada tb.
				
				
			default:
				answer_id = -1;
				break;
		}
		
		
	}
	
	
	if (token->type == TOKEN_TYPE_IDENTIFIER) {
		return IDENTIFIER_TOKEN_ID;
	}
	
	if (token->type == TOKEN_TYPE_STRING) {
		return STRING_TOKEN_ID;
	}
	
	if (token->type == TOKEN_TYPE_INT_NUMBER) {
		return INT_NUMBER_TOKEN_ID;
	}
	

	
/*
 
 ????
 
 e os: 
 
 como é q vai chegar um token delcaracoes??? isso nao é token.
 
 DECLARACOES_MIN_NON_TERMINAL_TOKEN_ID			16
 PARAMETROS_MIN_NON_TERMINAL_TOKEN_ID			17
 COMANDOS_MIN_NON_TERMINAL_TOKEN_ID				18
 EXPRESSAO_MIN_NON_TERMINAL_TOKEN_ID			19
 PROGRAMA_MIN_NON_TERMINAL_TOKEN_ID				20
 EXPRESSAOBOOLEANA_MIN_NON_TERMINAL_TOKEN_ID	21
 TEXTO_MIN_NON_TERMINAL_TOKEN_ID				22
	
*/	
	
	return answer_id;
	
}