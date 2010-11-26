#ifndef APE_H
#define APE_H
/*
 *  ape.h
 *  compiler
 *
 */

#include "strings.h"
#include "token.h"
#include "machine.h"
#include "ape_stack.h"

/* ape struct type */
typedef struct ape_type {
	Machine machines[APE_TOTAL_MACHINES];
	Machine initial_machine;
	Machine current_machine;
} APE;

/* the syntatic analyser parser */
APE ape_parser;

/* check if the current state of the ape is a final state */
int is_ape_in_final_state();

/* change the current ape machine after enqueueing */
void change_ape_machine(int machine_id, int state);

/* consume a token with the APE */
int ape_consume_token();

/* check if any machine can consume the token */
int machine_id_consume_token(int token_id);

int can_machine_consume_machine(Machine m);

/* get the token id readable by the APE */
int ape_get_token_id();

/* initialize ape machines */
void init_ape_machines();
#endif