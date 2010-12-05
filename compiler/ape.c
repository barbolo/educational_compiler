/*
 *  ape.c
 *  compiler
 *
 */

#include "ape.h"

int is_ape_in_final_state() {
	Machine m = ape_parser.current_machine;
	int i;
	for(i=0; i< 100; i++) {
		if (m.current_state == m.final_states[i])
			return 1;
		else if (m.final_states[i] == -1)
			break;
	}
	return 0;
}

void change_ape_machine(int machine_id, int state) {
	(*semantic_functions_machines[ape_parser.current_machine.machine_id][ape_parser.current_machine.current_state][machine_id])();
	
	ape_parser.current_machine = ape_parser.machines[machine_id];
	ape_parser.current_machine.current_state = state;
}

void change_ape_machine_pop(int machine_id, int state) {
	(*semantic_funcions_saida[ape_parser.current_machine.machine_id][ape_parser.current_machine.current_state])();
	
	ape_parser.current_machine = ape_parser.machines[machine_id];
	ape_parser.current_machine.current_state = state;
}

void go_to_state(int next_state) {
	(*semantic_functions_tokens[ape_parser.current_machine.machine_id][ape_parser.current_machine.current_state][ape_get_token_id()])();
	
	ape_parser.current_machine.current_state = next_state;
}

int ape_consume_token() {
	int machine_id;
	int token_id = ape_get_token_id();
	Machine current_machine = ape_parser.current_machine;
	
	int next_state = current_machine.token_transitions[current_machine.current_state][token_id];
	
	printf("%d: (%d,%d) -> %d\t\t(Token ID: %d)\n", current_machine.machine_id, current_machine.current_state, token_id, next_state, ape_get_token_id());
	
	if (next_state == APE_INVALID_STATE) {
		// could not read the token, let's check if we can change the machine
		
		machine_id = machine_id_consume_token(token_id);
		next_state = current_machine.machine_transitions[current_machine.current_state][machine_id];
		
		if (machine_id != APE_INVALID_STATE) {
			
			// change the current machine
			change_ape_machine(machine_id, ape_parser.machines[machine_id].initial_state);
			
			current_machine.current_state = next_state;
			
			// enqueue the current machine
			push_apestack(current_machine);
			
			return ape_consume_token();
			
		} else if (is_ape_in_final_state() && !is_apestack_empty()) { // check if there's a machine in the queue
				
			// retrieve the machine in its original state
			Machine m = pop_apestack();
			change_ape_machine_pop(m.machine_id, m.current_state);
			
			return ape_consume_token();
			
		} else {
			// could not consume the token in any machine
			return 0;
		}
		
	} else {
		go_to_state(next_state);
		return 1;
	}

	return 0;
}

int machine_id_consume_token(int token_id){

	int i;
	Machine m, current;
	current = ape_parser.current_machine;
	for (i=0; i < APE_TOTAL_MACHINES; i++) {
		m = ape_parser.machines[i];
		if (m.token_transitions[m.initial_state][token_id] != APE_INVALID_STATE || can_machine_consume_machine(m)) {
			
			if (current.machine_transitions[current.current_state][m.machine_id] != APE_INVALID_STATE) {
				//ape_parser.current_machine.current_state = current.machine_transitions[current.current_state][m.machine_id];
				return m.machine_id;
			}
			
		}
	}
	return APE_INVALID_STATE;
}

int can_machine_consume_machine(Machine m) {
	for (int i =0; i < APE_TOTAL_MACHINES; i++) {
		if (m.machine_transitions[m.initial_state][i] != APE_INVALID_STATE) {
			return 1;
		}
	}
	return 0;
}

int ape_get_token_id(){

	switch ((int)token.type) {
			
		case TOKEN_TYPE_RESERVED_WORD:
			if (strcmp(token.value, "functions") == 0) {
				return APE_TOKEN_FUNCTIONS_ID;
			}
			
			if (strcmp(token.value, "int") == 0) {
				return APE_TOKEN_INT_ID;
			}
			
			if (strcmp(token.value, "char") == 0) {
				return APE_TOKEN_CHAR_ID;
			}
			
			if (strcmp(token.value, "boolean") == 0) {
				return APE_TOKEN_BOOLEAN_ID;
			}
			
			if (strcmp(token.value, "void") == 0) {
				return APE_TOKEN_VOID_ID;
			}
			
			if (strcmp(token.value, "main") == 0) {
				return APE_TOKEN_MAIN_ID;
			}
			
			if (strcmp(token.value, "begin") == 0) {
				return APE_TOKEN_BEGIN_ID;
			}
			
			if (strcmp(token.value, "return") == 0) {
				return APE_TOKEN_RETURN_ID;
			}
			
			if (strcmp(token.value, "if") == 0) {
				return APE_TOKEN_IF_ID;
			}
			
			if (strcmp(token.value, "while") == 0) {
				return APE_TOKEN_WHILE_ID;
			}
			
			if (strcmp(token.value, "scan") == 0) {
				return APE_TOKEN_SCAN_ID;
			}
			
			if (strcmp(token.value, "print") == 0) {
				return APE_TOKEN_PRINT_ID;
			}
			
			if (strcmp(token.value, "else") == 0) {
				return APE_TOKEN_ELSE_ID;
			}
			
			if (strcmp(token.value, "NOT") == 0) {
				return APE_TOKEN_NOT_ID;
			}
			
			if (strcmp(token.value, "AND") == 0) {
				return APE_TOKEN_AND_ID;
			}
			
			if (strcmp(token.value, "OR") == 0) {
				return APE_TOKEN_OR_ID;
			}
			
			if (strcmp(token.value, "call") == 0) {
				return APE_TOKEN_CALL_ID;
			}
			
			break;
			
		case TOKEN_TYPE_IDENTIFIER:
			return APE_TOKEN_ID_ID;
			break;
			
		case TOKEN_TYPE_INT_NUMBER:
			return APE_TOKEN_INTEIRO_ID;
			break;
			
		case TOKEN_TYPE_SPECIAL:
			if (strcmp(token.value, "{") == 0) {
				return APE_TOKEN_ABRE_CHAVES_ID;
			}
			
			if (strcmp(token.value, "(") == 0) {
				return APE_TOKEN_ABRE_PARENTESES_ID;
			}
			
			if (strcmp(token.value, ";") == 0) {
				return APE_TOKEN_PONTO_E_VIRGULA_ID;
			}
			
			if (strcmp(token.value, ")") == 0) {
				return APE_TOKEN_FECHA_PARENTESES_ID;
			}
			
			if (strcmp(token.value, "}") == 0) {
				return APE_TOKEN_FECHA_CHAVES_ID;
			}
			
			if (strcmp(token.value, ",") == 0) {
				return APE_TOKEN_VIRGULA_ID;
			}
			
			if (strcmp(token.value, "=") == 0) {
				return APE_TOKEN_IGUAL_ID;
			}
			
			if (strcmp(token.value, "+") == 0) {
				return APE_TOKEN_SOMA_ID;
			}
			
			if (strcmp(token.value, "*") == 0) {
				return APE_TOKEN_MULTIPLICACAO_ID;
			}
			
			if (strcmp(token.value, "/") == 0) {
				return APE_TOKEN_DIVISAO_ID;
			}
			
			if (strcmp(token.value, "-") == 0) {
				return APE_TOKEN_SUBTRACAO_ID;
			}
			
			if (strcmp(token.value, "<") == 0) {
				return APE_TOKEN_MENOR_ID;
			}
			
			if (strcmp(token.value, "<=") == 0) {
				return APE_TOKEN_MENOR_IGUAL_ID;
			}
			
			if (strcmp(token.value, ">") == 0) {
				return APE_TOKEN_MAIOR_ID;
			}
			
			if (strcmp(token.value, ">=") == 0) {
				return APE_TOKEN_MAIOR_IGUAL_ID;
			}
			
			if (strcmp(token.value, "==") == 0) {
				return APE_TOKEN_IGUAL_IGUAL_ID;
			}
			
			if (strcmp(token.value, "!=") == 0) {
				return APE_TOKEN_DIFERENTE_ID;
			}
			
			break;
			
		case TOKEN_TYPE_STRING:
			return APE_TOKEN_STRING_ID;
			break;

		default:
			break;
	}
	
	return -1;
}


//////////////////////////////////////////////////////////
////////// GENERATED BY RADIANT FIRE LOADER //////////////
//////////////////////////////////////////////////////////

void init_ape_machines() {
	/* load machines */
	Machine programa, comando, expressao, condicao;
	
	
	/* Machine 0: programa */
	programa.machine_id = APE_MACHINE_PROGRAMA_ID; // 0
	programa.initial_state = 0;
	programa.current_state = 0;
	initialize_machine_transitions(&programa);
	programa.final_states[0] = 8;
	programa.final_states[1] = -1;
	
	/* token transitions */
	programa.token_transitions		[0][APE_TOKEN_BOOLEAN_ID]		=		1;
	programa.token_transitions		[0][APE_TOKEN_CHAR_ID]		=		1;
	programa.token_transitions		[0][APE_TOKEN_INT_ID]		=		1;
	programa.token_transitions		[0][APE_TOKEN_MAIN_ID]		=		2;
	programa.token_transitions		[0][APE_TOKEN_VOID_ID]		=		1;
	programa.token_transitions		[1][APE_TOKEN_ID_ID]		=		3;
	programa.token_transitions		[2][APE_TOKEN_ABRE_CHAVES_ID]		=		4;
	programa.token_transitions		[3][APE_TOKEN_ABRE_PARENTESES_ID]		=		5;
	programa.token_transitions		[4][APE_TOKEN_BOOLEAN_ID]		=		6;
	programa.token_transitions		[4][APE_TOKEN_CHAR_ID]		=		6;
	programa.token_transitions		[4][APE_TOKEN_FECHA_CHAVES_ID]		=		8;
	programa.token_transitions		[4][APE_TOKEN_INT_ID]		=		6;
	programa.token_transitions		[4][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		7;
	programa.token_transitions		[5][APE_TOKEN_BOOLEAN_ID]		=		9;
	programa.token_transitions		[5][APE_TOKEN_CHAR_ID]		=		9;
	programa.token_transitions		[5][APE_TOKEN_FECHA_PARENTESES_ID]		=		10;
	programa.token_transitions		[5][APE_TOKEN_INT_ID]		=		9;
	programa.token_transitions		[6][APE_TOKEN_ID_ID]		=		15;
	programa.token_transitions		[7][APE_TOKEN_FECHA_CHAVES_ID]		=		8;
	programa.token_transitions		[9][APE_TOKEN_ID_ID]		=		21;
	programa.token_transitions		[10][APE_TOKEN_ABRE_CHAVES_ID]		=		11;
	programa.token_transitions		[11][APE_TOKEN_BOOLEAN_ID]		=		12;
	programa.token_transitions		[11][APE_TOKEN_CHAR_ID]		=		12;
	programa.token_transitions		[11][APE_TOKEN_FECHA_CHAVES_ID]		=		0;
	programa.token_transitions		[11][APE_TOKEN_INT_ID]		=		12;
	programa.token_transitions		[11][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		13;
	programa.token_transitions		[11][APE_TOKEN_RETURN_ID]		=		14;
	programa.token_transitions		[12][APE_TOKEN_ID_ID]		=		19;
	programa.token_transitions		[13][APE_TOKEN_FECHA_CHAVES_ID]		=		0;
	programa.token_transitions		[13][APE_TOKEN_RETURN_ID]		=		14;
	programa.token_transitions		[15][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		7;
	programa.token_transitions		[15][APE_TOKEN_VIRGULA_ID]		=		17;
	programa.token_transitions		[16][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		18;
	programa.token_transitions		[17][APE_TOKEN_BOOLEAN_ID]		=		6;
	programa.token_transitions		[17][APE_TOKEN_CHAR_ID]		=		6;
	programa.token_transitions		[17][APE_TOKEN_INT_ID]		=		6;
	programa.token_transitions		[18][APE_TOKEN_FECHA_CHAVES_ID]		=		0;
	programa.token_transitions		[19][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		13;
	programa.token_transitions		[19][APE_TOKEN_VIRGULA_ID]		=		20;
	programa.token_transitions		[20][APE_TOKEN_BOOLEAN_ID]		=		12;
	programa.token_transitions		[20][APE_TOKEN_CHAR_ID]		=		12;
	programa.token_transitions		[20][APE_TOKEN_INT_ID]		=		12;
	programa.token_transitions		[21][APE_TOKEN_FECHA_PARENTESES_ID]		=		10;
	programa.token_transitions		[21][APE_TOKEN_VIRGULA_ID]		=		22;
	programa.token_transitions		[22][APE_TOKEN_BOOLEAN_ID]		=		9;
	programa.token_transitions		[22][APE_TOKEN_CHAR_ID]		=		9;
	programa.token_transitions		[22][APE_TOKEN_INT_ID]		=		9;
	
	/* machine transitions */
	programa.machine_transitions		[4][APE_MACHINE_COMANDO_ID]		=		7;
	programa.machine_transitions		[7][APE_MACHINE_COMANDO_ID]		=		7;
	programa.machine_transitions		[11][APE_MACHINE_COMANDO_ID]		=		13;
	programa.machine_transitions		[13][APE_MACHINE_COMANDO_ID]		=		13;
	programa.machine_transitions		[14][APE_MACHINE_EXPRESSAO_ID]		=		16;
	
	/* Machine 1: comando */
	comando.machine_id = APE_MACHINE_COMANDO_ID; // 1
	comando.initial_state = 0;
	comando.current_state = 0;
	initialize_machine_transitions(&comando);
	comando.final_states[0] = 15;
	comando.final_states[1] = 26;
	comando.final_states[2] = -1;
	
	/* token transitions */
	comando.token_transitions		[0][APE_TOKEN_CALL_ID]		=		2;
	comando.token_transitions		[0][APE_TOKEN_ID_ID]		=		1;
	comando.token_transitions		[0][APE_TOKEN_IF_ID]		=		3;
	comando.token_transitions		[0][APE_TOKEN_PRINT_ID]		=		6;
	comando.token_transitions		[0][APE_TOKEN_SCAN_ID]		=		5;
	comando.token_transitions		[0][APE_TOKEN_WHILE_ID]		=		4;
	comando.token_transitions		[1][APE_TOKEN_IGUAL_ID]		=		7;
	comando.token_transitions		[2][APE_TOKEN_ID_ID]		=		16;
	comando.token_transitions		[3][APE_TOKEN_ABRE_PARENTESES_ID]		=		22;
	comando.token_transitions		[4][APE_TOKEN_ABRE_PARENTESES_ID]		=		27;
	comando.token_transitions		[5][APE_TOKEN_ABRE_PARENTESES_ID]		=		17;
	comando.token_transitions		[6][APE_TOKEN_ABRE_PARENTESES_ID]		=		8;
	comando.token_transitions		[7][APE_TOKEN_CALL_ID]		=		10;
	comando.token_transitions		[8][APE_TOKEN_STRING_ID]		=		11;
	comando.token_transitions		[9][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		15;
	comando.token_transitions		[10][APE_TOKEN_ID_ID]		=		12;
	comando.token_transitions		[11][APE_TOKEN_FECHA_PARENTESES_ID]		=		9;
	comando.token_transitions		[11][APE_TOKEN_SOMA_ID]		=		8;
	comando.token_transitions		[12][APE_TOKEN_ABRE_PARENTESES_ID]		=		13;
	comando.token_transitions		[13][APE_TOKEN_FECHA_PARENTESES_ID]		=		9;
	comando.token_transitions		[14][APE_TOKEN_FECHA_PARENTESES_ID]		=		9;
	comando.token_transitions		[16][APE_TOKEN_ABRE_PARENTESES_ID]		=		18;
	comando.token_transitions		[17][APE_TOKEN_BOOLEAN_ID]		=		19;
	comando.token_transitions		[17][APE_TOKEN_CHAR_ID]		=		19;
	comando.token_transitions		[17][APE_TOKEN_INT_ID]		=		19;
	comando.token_transitions		[19][APE_TOKEN_VIRGULA_ID]		=		21;
	comando.token_transitions		[20][APE_TOKEN_FECHA_PARENTESES_ID]		=		15;
	comando.token_transitions		[21][APE_TOKEN_ID_ID]		=		14;
	comando.token_transitions		[23][APE_TOKEN_FECHA_PARENTESES_ID]		=		24;
	comando.token_transitions		[24][APE_TOKEN_ABRE_CHAVES_ID]		=		25;
	comando.token_transitions		[25][APE_TOKEN_FECHA_CHAVES_ID]		=		26;
	comando.token_transitions		[26][APE_TOKEN_ELSE_ID]		=		28;
	comando.token_transitions		[28][APE_TOKEN_ABRE_CHAVES_ID]		=		30;
	comando.token_transitions		[29][APE_TOKEN_FECHA_PARENTESES_ID]		=		28;
	comando.token_transitions		[30][APE_TOKEN_FECHA_CHAVES_ID]		=		15;
	
	/* machine transitions */
	comando.machine_transitions		[7][APE_MACHINE_EXPRESSAO_ID]		=		9;
	comando.machine_transitions		[8][APE_MACHINE_CONDICAO_ID]		=		11;
	comando.machine_transitions		[13][APE_MACHINE_EXPRESSAO_ID]		=		14;
	comando.machine_transitions		[18][APE_MACHINE_EXPRESSAO_ID]		=		20;
	comando.machine_transitions		[22][APE_MACHINE_CONDICAO_ID]		=		23;
	comando.machine_transitions		[25][APE_MACHINE_COMANDO_ID]		=		25;
	comando.machine_transitions		[27][APE_MACHINE_CONDICAO_ID]		=		29;
	comando.machine_transitions		[30][APE_MACHINE_COMANDO_ID]		=		30;
	
	/* Machine 2: expressao */
	expressao.machine_id = APE_MACHINE_EXPRESSAO_ID; // 2
	expressao.initial_state = 0;
	expressao.current_state = 0;
	initialize_machine_transitions(&expressao);
	expressao.final_states[0] = 2;
	expressao.final_states[1] = -1;
	
	/* token transitions */
	expressao.token_transitions		[0][APE_TOKEN_ABRE_PARENTESES_ID]		=		1;
	expressao.token_transitions		[0][APE_TOKEN_ID_ID]		=		2;
	expressao.token_transitions		[0][APE_TOKEN_INTEIRO_ID]		=		2;
	expressao.token_transitions		[2][APE_TOKEN_DIVISAO_ID]		=		0;
	expressao.token_transitions		[2][APE_TOKEN_MULTIPLICACAO_ID]		=		0;
	expressao.token_transitions		[2][APE_TOKEN_SOMA_ID]		=		0;
	expressao.token_transitions		[2][APE_TOKEN_SUBTRACAO_ID]		=		0;
	expressao.token_transitions		[3][APE_TOKEN_FECHA_PARENTESES_ID]		=		2;
	
	/* machine transitions */
	expressao.machine_transitions		[1][APE_MACHINE_EXPRESSAO_ID]		=		3;
	
	/* Machine 3: condicao */
	condicao.machine_id = APE_MACHINE_CONDICAO_ID; // 3
	condicao.initial_state = 0;
	condicao.current_state = 0;
	initialize_machine_transitions(&condicao);
	condicao.final_states[0] = 1;
	condicao.final_states[1] = 2;
	condicao.final_states[2] = -1;
	
	/* token transitions */
	condicao.token_transitions		[0][APE_TOKEN_BOOLEANO_ID]		=		2;
	condicao.token_transitions		[1][APE_TOKEN_DIFERENTE_ID]		=		3;
	condicao.token_transitions		[1][APE_TOKEN_IGUAL_IGUAL_ID]		=		3;
	condicao.token_transitions		[1][APE_TOKEN_MAIOR_ID]		=		3;
	condicao.token_transitions		[1][APE_TOKEN_MAIOR_IGUAL_ID]		=		3;
	condicao.token_transitions		[1][APE_TOKEN_MENOR_ID]		=		3;
	condicao.token_transitions		[1][APE_TOKEN_MENOR_IGUAL_ID]		=		3;
	
	/* machine transitions */
	condicao.machine_transitions		[0][APE_MACHINE_EXPRESSAO_ID]		=		1;
	condicao.machine_transitions		[3][APE_MACHINE_EXPRESSAO_ID]		=		2;
	
	/* initialize ape machines */
	ape_parser.initial_machine = programa;
	ape_parser.current_machine = programa;
	ape_parser.machines[0] = programa;
	ape_parser.machines[1] = comando;
	ape_parser.machines[2] = expressao;
	ape_parser.machines[3] = condicao;
}

//////////////////////////////////////////////////////////