/*
 *  transducer.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "transducer.h"



void init_transducer(){

	int initial_state = 0;
	int current_state = initial_state;
	int total_states = 1;
	int available_states = 100;

	//transitions = {}
	
	
	//Initialize transitions  
	
	
	// Default transition goes to an invalid state and returns an invalid token type
	for (int i = 0; i < available_states; i++) {
		
		
		
		
		
	}
	
	/*
	@available_states.times do |state|
        @transitions[state] = {}
	(0..255).each do |input|
		@transitions[state][input] = [INVALID_STATE, Token::Type::INVALID]
        end
        @transitions[state][EMPTY_STRING] = [INVALID_STATE, Token::Type::INVALID]
		end
	
	*/
	
	
	


}