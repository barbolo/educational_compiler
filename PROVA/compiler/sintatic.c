/*
 *  sintatic.c
 *  compiler
 *
 */

#include "sintatic.h"


void run_sintatic(){
	
	// get the first token
	get_next_token();
	
	printf("\nTestando sintático:\n");
	
	printf("token: %s - %d - %d - %d - %s\n", token.value, ape_parser.current_machine.current_state, ape_parser.current_machine.machine_id, ape_get_token_id(), token_type_name());	

	printf("\nReading tokens:\n\n|   Token   |  index  |   type_name   |  type_id  | line | column |\n");
	
	while (token.type != TOKEN_TYPE_END_OF_FILE) {
		

		// print info
		printf("%10s	(%d)	%10s	%d	%5i %5i\n", 
			   token.value, token.index, token_type_name(), token.type, token.line, token.column);
		
		// execute APE transition
		if (!ape_consume_token() || token.type == TOKEN_TYPE_INVALID) {
			printf("\nAi que burrico! Tem erro no seu código, Zé! Olha o último token! =P\n\n");
			exit(1);
		}
		
		// get the next token
		get_next_token();

	}
	
	if (was_correctly_parsed()) {
		printf("\nParabéns! Você conseguiu gerar um código compilável!\n\n");
	} else {
		printf("\nOops! Seu código não foi compilado até o fim!\n\n ");
	}

	
}


int was_correctly_parsed() {
	return is_ape_in_final_state() && is_apestack_empty();
}