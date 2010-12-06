/*
 *  sintatic.c
 *  compiler
 *
 */

#include "syntatic.h"


void run_sintatic(){
	
	int is_declaration = 0;
	semantic_error = 0;
	
	// get the first token
	get_next_token(1);
	
	printf("\nTestando sintático:\n");
	printf("token: %s - %d - %d - %d - %s\n", token.value, ape_parser.current_machine.current_state, ape_parser.current_machine.machine_id, ape_get_token_id(), token_type_name());	
	printf("\nReading tokens:\n\n|   Token	|	index	|	type_name	|	type_id	|	line	|	column	|\n");
	
	while (token.type != TOKEN_TYPE_END_OF_FILE) {

		// print info
		printf("%10s		(%d)		%10s				%d		%5i		%5i\n", 
			   token.value, token.index, token_type_name(), token.type, token.line, token.column);
		
		// descomente as duas linhas abaixo para testar o léxico:
		//get_next_token(1);
		//continue;
		
		// execute APE transition
		if (!ape_consume_token() || token.type == TOKEN_TYPE_INVALID) {
			printf("\nAi que burrico! Tem erro SINTÁTICO no seu código, Zé! Olha o último token! =P\n\n");
			exit(-1);
		}
		
		//if the semantic actions detect an error, it will set semantic_error to 1.
		if (semantic_error == 1) {
			printf("\nAi que burrico! Tem erro SEMÂNTICO no seu código, Zé!\n\n");
			exit(-1);
		}
		
		//Decide if it is a declaration of an identifier.
		//code to do that.
		is_declaration = 1;
		
		// get the next token
		get_next_token(is_declaration);
	}
	
	if (was_correctly_parsed()) {
		write_variables();
		printf("\nParabéns! Você conseguiu gerar um código compilável!\n\n");
	} else {
		printf("Oops! Seu código não foi compilado até o fim!\n\n ");
	}

}


int was_correctly_parsed() {
	return is_ape_in_final_state() && is_apestack_empty();
}