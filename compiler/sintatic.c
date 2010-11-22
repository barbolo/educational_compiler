/*
 *  sintatic.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos on 20/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "sintatic.h"

#define INITIAL_MACHINE_ID 0

void start_sintatic(){	
	
	//faz de conta... algum lugar vai ter q iniciar os APE depois
	mini_programa_ape.initial_state = 0;
	mini_programa_ape.final_state = 3;
	
	sintatic.current_state =  mini_programa_ape.initial_state;
	
	sintatic.id_machine = INITIAL_MACHINE_ID;
	
	
	while (token.type != TOKEN_TYPE_END_OF_FILE) {
		
		//ve se consome ou nao (qdo for um estado q chama uma outra máquina ele nao vai consumir o token!) ( antes implementar uma apilha :( )
		
		//get token
		get_next_token();
		
		//Print Token info.
		if (token.type != TOKEN_TYPE_END_OF_FILE) {
			printf("Token:	%s	(%d)	::	%s	(%d)	::	line	%i, column	%i\n", 
				   token.value, token.index, token_type_name(), token.type, token.line, token.column);
		}
		
		//transita no APE
		//Get next state
		if (mini_programa_ape_transitions[sintatic.current_state][get_token_id_simplificada(&token)] != APE_ERROR) {
				sintatic.next_state = mini_programa_ape_transitions[sintatic.current_state][get_token_id_simplificada(&token)];
		}
		else {
			printf("\nAi q burrico! Tem erro no seu código, Zé! :P \n\n"); 
			break;
		}
		
		//chama ações semanticas (sei q vao gerar os códigos... deve ter mais coisa tb)
		call_semantic_actions(mini_programa_ape.id_sementic_actions);
		
		if (sintatic.next_state == mini_programa_ape.final_state) {
			break;
		}
		else {
			sintatic.current_state = sintatic.next_state;
		}
		
	}
	
	printf("End of APE\n");
}

void call_semantic_actions(int id){

	//sei la como vai ser isso das ações semanticas... mas talvez pudesse exisir um id pra cada bloquinho de ações semânticas q cada transiçnao invoca.

}