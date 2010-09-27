#ifndef TRANSDUCER_H
#define TRANSDUCER_H


/*
 *  transducer.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 *
 *	The transducer is an implementation of a finite automata.
 *	It offers a function that receives the actual STATE of the automata and
 *	the INPUT char, and it returns the NEXT_STATE and the OUTPUT.
 *
 *	The OUTPUT may be a token type or an empty string.
 *
 */

#include "token.h"


#define INVALID_STATE		-1
#define EMPTY_STRING		256

#define INITIAL_STATE		0
#define AVAILABLE_STATES	100

typedef int transducer_state;

typedef struct {
	transducer_state next_state;
	type_of_token type;
	
} automata_output;

transducer_state transducer_current_state = INITIAL_STATE;
int transducer_created_states = 1; // the initial state is always created

/* automata transitions */
automata_output transducer_transitions[AVAILABLE_STATES][257];



/*****************************************************************************
 name: initialize_transitions
 purpose: initialize table of automata transitions;
 args: 
 returns: 
 *****************************************************************************/

void initialize_transitions();


/*****************************************************************************
 name: transducer_new_state
 purpose: creates a new state for the automata and return it;
 args: 
 returns: transducer_state (int).
 *****************************************************************************/

transducer_state transducer_new_state();


/*****************************************************************************
 name: transducer_consume_input
 purpose: execute a transition in transducer automata.
 args: current and nex chars.
 returns: token type (int).
 *****************************************************************************/

type_of_token transducer_consume_input(char current, char lookahead);


#endif