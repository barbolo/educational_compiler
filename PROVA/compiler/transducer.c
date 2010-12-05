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
	transducer_state s;
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
	
	
	/* transitions with comments */
	s = transducer_new_state();
	transducer_transitions[0][(int)'%'].next_state = s;
	transducer_transitions[0][(int)'%'].type = TOKEN_TYPE_IGNORED;
	for (aux = 0; aux < 256; aux++) {
		transducer_transitions[s][aux].next_state = s;
		transducer_transitions[s][aux].type = TOKEN_TYPE_IGNORED;
	}
	transducer_transitions[s][(int)'\n'].next_state = 0;
	transducer_transitions[s][(int)'\n'].type = TOKEN_TYPE_IGNORED;
	
	
	/* transitions with identifiers */
	s = transducer_new_state();
	for (aux = (int)'a'; aux <= (int)'z'; aux++) {
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
	
	
	/* transitions with integer numbers */
	s = transducer_new_state();
	for (aux = (int)'0'; aux <= (int)'9'; aux++) {
		transducer_transitions[0][aux].next_state = s;
		transducer_transitions[0][aux].type = TOKEN_TYPE_INCOMPLETE;
		
		transducer_transitions[s][aux].next_state = s;
		transducer_transitions[s][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	transducer_transitions[s][EMPTY_STRING].next_state = 0;
	transducer_transitions[s][EMPTY_STRING].type = TOKEN_TYPE_INT_NUMBER;
	
	
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
	
	
	
	// !=
	s = transducer_new_state();
	
	transducer_transitions[0][(int)'!'].next_state = s;
	transducer_transitions[0][(int)'!'].type = TOKEN_TYPE_INCOMPLETE;
	
	transducer_transitions[s][(int)'='].next_state = 0;
	transducer_transitions[s][(int)'='].type = TOKEN_TYPE_SPECIAL;
	
	
	// transitions with strings
	
	s = transducer_new_state();
	
	transducer_transitions[0][(int)'"'].next_state = s;
	transducer_transitions[0][(int)'"'].type = TOKEN_TYPE_INCOMPLETE;	
	
	for (aux = (int)'a'; aux <= (int)'z'; aux++) {
		transducer_transitions[s][aux].next_state = s;
		transducer_transitions[s][aux].type = TOKEN_TYPE_INCOMPLETE;
	}
	for (aux = (int)'0'; aux <= (int)'9'; aux++) {
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