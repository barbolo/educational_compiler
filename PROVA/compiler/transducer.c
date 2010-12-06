/*
 *  transducer.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include <stdio.h>
#include "transducer.h"
#include "token.h"

void initialize_transitions() {
	transducer_state s, s2, s3, s4, s5, s6, s7, s8;
	int aux, aux2;
	
	/* default transition goes to an invalid state and returns an invalid token type */
	for (aux = 0; aux < 100; aux++) {
		for(aux2 = 0; aux2 < 256; aux2++) {
			transducer_transitions[aux][aux2].next_state = INVALID_STATE;
			transducer_transitions[aux][aux2].type = TOKEN_TYPE_INVALID;
		}
		transducer_transitions[aux][EMPTY_STRING].next_state = INVALID_STATE;
		transducer_transitions[aux][EMPTY_STRING].type = TOKEN_TYPE_INVALID;
	}
	
	
	/* transitions with spaces */
	transducer_transitions[0][(int)' '].next_state = 0;
	transducer_transitions[0][(int)' '].type = TOKEN_TYPE_IGNORED;
	
	transducer_transitions[0][(int)'\n'].next_state = 0;
	transducer_transitions[0][(int)'\n'].type = TOKEN_TYPE_IGNORED;
	
	transducer_transitions[0][(int)'\t'].next_state = 0;
	transducer_transitions[0][(int)'\t'].type = TOKEN_TYPE_IGNORED;
	
	transducer_transitions[0][(int)'\r'].next_state = 0;
	transducer_transitions[0][(int)'\r'].type = TOKEN_TYPE_IGNORED;
	
	transducer_transitions[0][(int)'\a'].next_state = 0;
	transducer_transitions[0][(int)'\a'].type = TOKEN_TYPE_IGNORED;
	
	transducer_transitions[0][(int)'\b'].next_state = 0;
	transducer_transitions[0][(int)'\b'].type = TOKEN_TYPE_IGNORED;
	
	transducer_transitions[0][(int)'\f'].next_state = 0;
	transducer_transitions[0][(int)'\f'].type = TOKEN_TYPE_IGNORED;
	
	
	/* transitions with comments*/
	 
	s = transducer_new_state();
	transducer_transitions[0][(int)'-'].next_state = s;
	transducer_transitions[0][(int)'-'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s][EMPTY_STRING].next_state = INVALID_STATE;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_INVALID;
	
	s2 = transducer_new_state();
	transducer_transitions[s][(int)'-'].next_state = s2;
	transducer_transitions[s][(int)'-'].type = TOKEN_TYPE_IGNORED;
	
	for (aux = 0; aux < 256; aux++) {
		transducer_transitions[s2][aux].next_state = s2;
		transducer_transitions[s2][aux].type = TOKEN_TYPE_IGNORED;
	}
	transducer_transitions[s2][(int)'\n'].next_state = 0;
	transducer_transitions[s2][(int)'\n'].type = TOKEN_TYPE_IGNORED;
	 
	
	/* transitions with identifiers */
	s = transducer_new_state();
	for (aux = (int)'a'; aux <= (int)'z'; aux++) {
		transducer_transitions[0][aux].next_state = s;
		transducer_transitions[0][aux].type = TOKEN_TYPE_INCOMPLETE;
		
		transducer_transitions[s][aux].next_state = s;
		transducer_transitions[s][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	for (aux = (int)'A'; aux <= (int)'Z'; aux++) {
		transducer_transitions[0][aux].next_state = s;
		transducer_transitions[0][aux].type = TOKEN_TYPE_INCOMPLETE;
		
		transducer_transitions[s][aux].next_state = s;
		transducer_transitions[s][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	for (aux = (int)'0'; aux <= (int)'9'; aux++) {
		transducer_transitions[s][aux].next_state = s;
		transducer_transitions[s][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	transducer_transitions[s][EMPTY_STRING].next_state = 0;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_IDENTIFIER;
	
	
	/* transitions with scientifc, hexa, integer or float numbers */
	
	// integer
	s = transducer_new_state();
	for (aux = (int)'0'; aux <= (int)'9'; aux++) {
		transducer_transitions[0][aux].next_state = s;
		transducer_transitions[0][aux].type = TOKEN_TYPE_INCOMPLETE;
		
		transducer_transitions[s][aux].next_state = s;
		transducer_transitions[s][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	transducer_transitions[s][EMPTY_STRING].next_state = 0;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_INT_NUMBER;
	
	// float
	s2 = transducer_new_state();
	transducer_transitions[s][(int)'.'].next_state = s2;
	transducer_transitions[s][(int)'.'].type = TOKEN_TYPE_INCOMPLETE;
	
	for (aux = (int)'0'; aux <= (int)'9'; aux++) {
		transducer_transitions[s2][aux].next_state = s2;
		transducer_transitions[s2][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	
	transducer_transitions[s2][EMPTY_STRING].next_state = 0;
	transducer_transitions[s2][EMPTY_STRING].type = TOKEN_TYPE_FLOAT_NUMBER;
	
	// scientific
	s6 = transducer_new_state();
	transducer_transitions[s2][(int)'E'].next_state = s6;
	transducer_transitions[s2][(int)'E'].type = TOKEN_TYPE_INCOMPLETE;
	
	s7 = transducer_new_state();
	transducer_transitions[s2][(int)'e'].next_state = s7;
	transducer_transitions[s2][(int)'e'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s7][EMPTY_STRING].next_state = INVALID_STATE;
	transducer_transitions[s7][EMPTY_STRING].type = TOKEN_TYPE_INVALID;
	
	transducer_transitions[s7][(int)'-'].next_state = s6;
	transducer_transitions[s7][(int)'-'].type = TOKEN_TYPE_INCOMPLETE;
	
	for (aux = (int)'0'; aux <= (int)'9'; aux++) {
		transducer_transitions[s6][aux].next_state = s6;
		transducer_transitions[s6][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	
	transducer_transitions[s6][EMPTY_STRING].next_state = 0;
	transducer_transitions[s6][EMPTY_STRING].type = TOKEN_TYPE_SCIENTIFC_NUMBER;
	
	// hexa
	s3 = transducer_new_state();
	transducer_transitions[0][(int)'0'].next_state = s3;
	transducer_transitions[0][(int)'0'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s3][EMPTY_STRING].next_state = 0; // 0 is integer
	transducer_transitions[s3][EMPTY_STRING].type = TOKEN_TYPE_INT_NUMBER;
	
	for (aux = (int)'0'; aux <= (int)'9'; aux++) { // may be an integer
		transducer_transitions[s3][aux].next_state = s;
		transducer_transitions[s3][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	
	transducer_transitions[s3][(int)'.'].next_state = s2; // may be a float
	transducer_transitions[s3][(int)'.'].type = TOKEN_TYPE_INCOMPLETE;
	
	s4 = transducer_new_state();
	s5 = transducer_new_state();
	transducer_transitions[s3][(int)'x'].next_state = s4; // may be an hexa
	transducer_transitions[s3][(int)'x'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s4][EMPTY_STRING].next_state = INVALID_STATE;
	transducer_transitions[s4][EMPTY_STRING].type = TOKEN_TYPE_INVALID;
	
	for (aux = (int)'0'; aux <= (int)'9'; aux++) {
		transducer_transitions[s4][aux].next_state = s5;
		transducer_transitions[s4][aux].type = TOKEN_TYPE_INCOMPLETE;
		
		transducer_transitions[s5][aux].next_state = s5;
		transducer_transitions[s5][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	
	for (aux = (int)'A'; aux <= (int)'F'; aux++) {
		transducer_transitions[s4][aux].next_state = s4;
		transducer_transitions[s4][aux].type = TOKEN_TYPE_INCOMPLETE;
		
		transducer_transitions[s5][aux].next_state = s5;
		transducer_transitions[s5][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	
	transducer_transitions[s5][EMPTY_STRING].next_state = 0;
	transducer_transitions[s5][EMPTY_STRING].type = TOKEN_TYPE_HEXA_NUMBER;
		
	
	/* transitions with special chars */
	transducer_transitions[0][(int)':'].next_state = 0;
	transducer_transitions[0][(int)':'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)';'].next_state = 0;
	transducer_transitions[0][(int)';'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'+'].next_state = 0;
	transducer_transitions[0][(int)'+'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'-'].next_state = 0;
	transducer_transitions[0][(int)'-'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'*'].next_state = 0;
	transducer_transitions[0][(int)'*'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'/'].next_state = 0;
	transducer_transitions[0][(int)'/'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'%'].next_state = 0;
	transducer_transitions[0][(int)'%'].type = TOKEN_TYPE_SPECIAL;

	transducer_transitions[0][(int)'^'].next_state = 0;
	transducer_transitions[0][(int)'^'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'#'].next_state = 0;
	transducer_transitions[0][(int)'#'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'('].next_state = 0;
	transducer_transitions[0][(int)'('].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)')'].next_state = 0;
	transducer_transitions[0][(int)')'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)','].next_state = 0;
	transducer_transitions[0][(int)','].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'}'].next_state = 0;
	transducer_transitions[0][(int)'}'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'{'].next_state = 0;
	transducer_transitions[0][(int)'{'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)'['].next_state = 0;
	transducer_transitions[0][(int)'['].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[0][(int)']'].next_state = 0;
	transducer_transitions[0][(int)']'].type = TOKEN_TYPE_SPECIAL;
	
	
	/* nondeterministic special chars with dept <= 2 */
	
	// . .. ...
	s = transducer_new_state();
	s2 = transducer_new_state();
	transducer_transitions[0][(int)'.'].next_state = s;
	transducer_transitions[0][(int)'.'].type = TOKEN_TYPE_INCOMPLETE;	
	
	transducer_transitions[s][(int)'.'].next_state = s2;
	transducer_transitions[s][(int)'.'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s][EMPTY_STRING].next_state = 0;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[s2][(int)'.'].next_state = 0;
	transducer_transitions[s2][(int)'.'].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[s2][EMPTY_STRING].next_state = 0;
	transducer_transitions[s2][EMPTY_STRING].type = TOKEN_TYPE_SPECIAL;
	
	// = ==
	s = transducer_new_state();
	transducer_transitions[0][(int)'='].next_state = s;
	transducer_transitions[0][(int)'='].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s][(int)'='].next_state = 0;
	transducer_transitions[s][(int)'='].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[s][EMPTY_STRING].next_state = 0;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_SPECIAL;
	
	// > >=
	s = transducer_new_state();
	transducer_transitions[0][(int)'>'].next_state = s;
	transducer_transitions[0][(int)'>'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s][(int)'='].next_state = 0;
	transducer_transitions[s][(int)'='].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[s][EMPTY_STRING].next_state = 0;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_SPECIAL;
	
	// < <=
	s = transducer_new_state();
	transducer_transitions[0][(int)'<'].next_state = s;
	transducer_transitions[0][(int)'<'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s][(int)'='].next_state = 0;
	transducer_transitions[s][(int)'='].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[s][EMPTY_STRING].next_state = 0;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_SPECIAL;
	
	// ~=
	s = transducer_new_state();
	
	transducer_transitions[0][(int)'~'].next_state = s;
	transducer_transitions[0][(int)'~'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s][(int)'='].next_state = 0;
	transducer_transitions[s][(int)'='].type = TOKEN_TYPE_SPECIAL;
	
	transducer_transitions[s][EMPTY_STRING].next_state = INVALID_STATE;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_INVALID;
	
	// transitions with strings
	
	s = transducer_new_state();
	
	transducer_transitions[0][(int)'"'].next_state = s;
	transducer_transitions[0][(int)'"'].type = TOKEN_TYPE_INCOMPLETE;
	
	for (aux = 0; aux <= 255; aux++) {
		transducer_transitions[s][aux].next_state = s;
		transducer_transitions[s][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	transducer_transitions[s][(int)'"'].next_state = 0;
	transducer_transitions[s][(int)'"'].type = TOKEN_TYPE_STRING;

}



transducer_state transducer_new_state() {
	transducer_created_states += 1;
	return transducer_created_states - 1;
}



type_of_token transducer_consume_input(char current, char lookahead) {
	
	if (lookahead == EOF) {
		lookahead = ' ';
	}
	
	transducer_state next_state = transducer_transitions[transducer_current_state][(int) current].next_state;
	type_of_token type = transducer_transitions[transducer_current_state][(int) current].type;
	
	if (next_state == INVALID_STATE) {
		type = TOKEN_TYPE_INVALID;
		next_state = 0;
	} else if (type == TOKEN_TYPE_INCOMPLETE && transducer_transitions[next_state][(int) lookahead].next_state == INVALID_STATE) {
		type = transducer_transitions[next_state][EMPTY_STRING].type;
		next_state = 0;
	}
	
	transducer_current_state = next_state;
	
	return type;
}