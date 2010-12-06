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

int is_initial_state_final(Machine m) {
	int i;
	for(i=0; i< 100; i++) {
		if (m.initial_state == m.final_states[i])
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
	//if (is_initial_state_final(m)) {
	//	return 1;
	//}
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
			
			if (strcmp(token.value, "do") == 0) {
				return APE_TOKEN_DO_ID;
			}
			
			if (strcmp(token.value, "while") == 0) {
				return APE_TOKEN_WHILE_ID;
			}
			
			if (strcmp(token.value, "repeat") == 0) {
				return APE_TOKEN_REPEAT_ID;
			}
			
			if (strcmp(token.value, "if") == 0) {
				return APE_TOKEN_IF_ID;
			}
			
			if (strcmp(token.value, "for") == 0) {
				return APE_TOKEN_FOR_ID;
			}
			
			if (strcmp(token.value, "function") == 0) {
				return APE_TOKEN_FUNCTION_ID;
			}
			
			if (strcmp(token.value, "local") == 0) {
				return APE_TOKEN_LOCAL_ID;
			}
			
			if (strcmp(token.value, "return") == 0) {
				return APE_TOKEN_RETURN_ID;
			}
			
			if (strcmp(token.value, "break") == 0) {
				return APE_TOKEN_BREAK_ID;
			}
			
			if (strcmp(token.value, "end") == 0) {
				return APE_TOKEN_END_ID;
			}
			
			if (strcmp(token.value, "in") == 0) {
				return APE_TOKEN_IN_ID;
			}
			
			if (strcmp(token.value, "then") == 0) {
				return APE_TOKEN_THEN_ID;
			}
			
			if (strcmp(token.value, "elseif") == 0) {
				return APE_TOKEN_ELSEIF_ID;
			}
			
			if (strcmp(token.value, "else") == 0) {
				return APE_TOKEN_ELSE_ID;
			}
			
			if (strcmp(token.value, "until") == 0) {
				return APE_TOKEN_UNTIL_ID;
			}
			
			if (strcmp(token.value, "nil") == 0) {
				return APE_TOKEN_NIL_ID;
			}
			
			if (strcmp(token.value, "not") == 0) {
				return APE_TOKEN_NOT_ID;
			}
			
			if (strcmp(token.value, "or") == 0) {
				return APE_TOKEN_OR_ID;
			}
			
			if (strcmp(token.value, "and") == 0) {
				return APE_TOKEN_AND_ID;
			}
			
			if (strcmp(token.value, "false") == 0) {
				return APE_TOKEN_FALSE_ID;
			}
			
			if (strcmp(token.value, "true") == 0) {
				return APE_TOKEN_TRUE_ID;
			}
			
			break;
			
		case TOKEN_TYPE_IDENTIFIER:
			return APE_TOKEN_NOME_ID;
			break;
			
		case TOKEN_TYPE_INT_NUMBER:
			return APE_TOKEN_NUMERO_ID;
			break;
			
		case TOKEN_TYPE_FLOAT_NUMBER:
			return APE_TOKEN_NUMERO_ID;
			break;
			
		case TOKEN_TYPE_SCIENTIFC_NUMBER:
			return APE_TOKEN_NUMERO_ID;
			break;
			
		case TOKEN_TYPE_HEXA_NUMBER:
			return APE_TOKEN_NUMERO_ID;
			break;
			
		case TOKEN_TYPE_SPECIAL:
			
			if (strcmp(token.value, "(") == 0) {
				return APE_TOKEN_ABRE_PARENTESES_ID;
			}
			
			if (strcmp(token.value, ",") == 0) {
				return APE_TOKEN_VIRGULA_ID;
			}
			
			if (strcmp(token.value, "=") == 0) {
				return APE_TOKEN_IGUAL_ID;
			}
			
			if (strcmp(token.value, ";") == 0) {
				return APE_TOKEN_PONTO_E_VIRGULA_ID;
			}
			
			if (strcmp(token.value, "[") == 0) {
				return APE_TOKEN_ABRE_COLCHETES_ID;
			}
			
			if (strcmp(token.value, ".") == 0) {
				return APE_TOKEN_PONTO_ID;
			}
			
			if (strcmp(token.value, "{") == 0) {
				return APE_TOKEN_ABRE_CHAVES_ID;
			}
			
			if (strcmp(token.value, ":") == 0) {
				return APE_TOKEN_DOIS_PONTOS_ID;
			}
			
			if (strcmp(token.value, ")") == 0) {
				return APE_TOKEN_FECHA_PARENTESES_ID;
			}
			
			if (strcmp(token.value, "...") == 0) {
				return APE_TOKEN_PONTO_PONTO_PONTO_ID;
			}
			
			if (strcmp(token.value, "]") == 0) {
				return APE_TOKEN_FECHA_COLCHETES_ID;
			}
			
			if (strcmp(token.value, "}") == 0) {
				return APE_TOKEN_FECHA_CHAVES_ID;
			}
			
			
			if (strcmp(token.value, "-") == 0) {
				return APE_TOKEN_SUBTRACAO_ID;
			}
			
			if (strcmp(token.value, "#") == 0) {
				return APE_TOKEN_JOGO_DA_VELHA_ID;
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
			
			if (strcmp(token.value, "^") == 0) {
				return APE_TOKEN_ACENTO_CIRCUNFLEXO_ID;
			}
			
			if (strcmp(token.value, "%") == 0) {
				return APE_TOKEN_PORCENTAGEM_ID;
			}
			
			if (strcmp(token.value, "..") == 0) {
				return APE_TOKEN_PONTO_PONTO_ID;
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
			
			if (strcmp(token.value, "~=") == 0) {
				return APE_TOKEN_TIO_IGUAL_ID;
			}
			
			break;
			
		case TOKEN_TYPE_STRING:
			return APE_TOKEN_CADEIA_ID;
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
	Machine bloco, exp;
	
	
	/* Machine 0: bloco */
	bloco.machine_id = APE_MACHINE_BLOCO_ID; // 0
	bloco.initial_state = 0;
	bloco.current_state = 0;
	initialize_machine_transitions(&bloco);
	bloco.final_states[0] = 10;
	bloco.final_states[1] = 11;
	bloco.final_states[2] = 18;
	bloco.final_states[3] = 20;
	bloco.final_states[4] = 22;
	bloco.final_states[5] = 23;
	bloco.final_states[6] = 26;
	bloco.final_states[7] = 37;
	bloco.final_states[8] = 42;
	bloco.final_states[9] = -1;
	
	/* token transitions */
	bloco.token_transitions		[0][APE_TOKEN_ABRE_PARENTESES_ID]		=		2;
	bloco.token_transitions		[0][APE_TOKEN_BREAK_ID]		=		11;
	bloco.token_transitions		[0][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[0][APE_TOKEN_FOR_ID]		=		7;
	bloco.token_transitions		[0][APE_TOKEN_FUNCTION_ID]		=		8;
	bloco.token_transitions		[0][APE_TOKEN_IF_ID]		=		6;
	bloco.token_transitions		[0][APE_TOKEN_LOCAL_ID]		=		9;
	bloco.token_transitions		[0][APE_TOKEN_NOME_ID]		=		1;
	bloco.token_transitions		[0][APE_TOKEN_REPEAT_ID]		=		5;
	bloco.token_transitions		[0][APE_TOKEN_RETURN_ID]		=		10;
	bloco.token_transitions		[0][APE_TOKEN_WHILE_ID]		=		4;
	bloco.token_transitions		[1][APE_TOKEN_ABRE_CHAVES_ID]		=		16;
	bloco.token_transitions		[1][APE_TOKEN_ABRE_COLCHETES_ID]		=		13;
	bloco.token_transitions		[1][APE_TOKEN_ABRE_PARENTESES_ID]		=		12;
	bloco.token_transitions		[1][APE_TOKEN_CADEIA_ID]		=		18;
	bloco.token_transitions		[1][APE_TOKEN_DOIS_PONTOS_ID]		=		19;
	bloco.token_transitions		[1][APE_TOKEN_IGUAL_ID]		=		17;
	bloco.token_transitions		[1][APE_TOKEN_PONTO_ID]		=		14;
	bloco.token_transitions		[1][APE_TOKEN_VIRGULA_ID]		=		15;
	bloco.token_transitions		[7][APE_TOKEN_NOME_ID]		=		44;
	bloco.token_transitions		[8][APE_TOKEN_NOME_ID]		=		43;
	bloco.token_transitions		[9][APE_TOKEN_FUNCTION_ID]		=		27;
	bloco.token_transitions		[9][APE_TOKEN_NOME_ID]		=		26;
	bloco.token_transitions		[10][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		20;
	bloco.token_transitions		[11][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		20;
	bloco.token_transitions		[12][APE_TOKEN_FECHA_PARENTESES_ID]		=		18;
	bloco.token_transitions		[14][APE_TOKEN_NOME_ID]		=		1;
	bloco.token_transitions		[15][APE_TOKEN_ABRE_PARENTESES_ID]		=		58;
	bloco.token_transitions		[15][APE_TOKEN_NOME_ID]		=		57;
	bloco.token_transitions		[16][APE_TOKEN_ABRE_COLCHETES_ID]		=		36;
	bloco.token_transitions		[16][APE_TOKEN_FECHA_CHAVES_ID]		=		18;
	bloco.token_transitions		[16][APE_TOKEN_NOME_ID]		=		34;
	bloco.token_transitions		[18][APE_TOKEN_ABRE_CHAVES_ID]		=		16;
	bloco.token_transitions		[18][APE_TOKEN_ABRE_COLCHETES_ID]		=		13;
	bloco.token_transitions		[18][APE_TOKEN_ABRE_PARENTESES_ID]		=		12;
	bloco.token_transitions		[18][APE_TOKEN_BREAK_ID]		=		11;
	bloco.token_transitions		[18][APE_TOKEN_CADEIA_ID]		=		18;
	bloco.token_transitions		[18][APE_TOKEN_DOIS_PONTOS_ID]		=		19;
	bloco.token_transitions		[18][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[18][APE_TOKEN_FOR_ID]		=		7;
	bloco.token_transitions		[18][APE_TOKEN_FUNCTION_ID]		=		8;
	bloco.token_transitions		[18][APE_TOKEN_IF_ID]		=		6;
	bloco.token_transitions		[18][APE_TOKEN_LOCAL_ID]		=		9;
	bloco.token_transitions		[18][APE_TOKEN_NOME_ID]		=		1;
	bloco.token_transitions		[18][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		23;
	bloco.token_transitions		[18][APE_TOKEN_PONTO_ID]		=		14;
	bloco.token_transitions		[18][APE_TOKEN_REPEAT_ID]		=		5;
	bloco.token_transitions		[18][APE_TOKEN_RETURN_ID]		=		10;
	bloco.token_transitions		[18][APE_TOKEN_WHILE_ID]		=		4;
	bloco.token_transitions		[19][APE_TOKEN_NOME_ID]		=		21;
	bloco.token_transitions		[21][APE_TOKEN_ABRE_CHAVES_ID]		=		16;
	bloco.token_transitions		[21][APE_TOKEN_ABRE_PARENTESES_ID]		=		12;
	bloco.token_transitions		[21][APE_TOKEN_CADEIA_ID]		=		18;
	bloco.token_transitions		[22][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		20;
	bloco.token_transitions		[22][APE_TOKEN_VIRGULA_ID]		=		24;
	bloco.token_transitions		[23][APE_TOKEN_ABRE_PARENTESES_ID]		=		2;
	bloco.token_transitions		[23][APE_TOKEN_BREAK_ID]		=		11;
	bloco.token_transitions		[23][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[23][APE_TOKEN_FOR_ID]		=		7;
	bloco.token_transitions		[23][APE_TOKEN_FUNCTION_ID]		=		8;
	bloco.token_transitions		[23][APE_TOKEN_IF_ID]		=		6;
	bloco.token_transitions		[23][APE_TOKEN_LOCAL_ID]		=		9;
	bloco.token_transitions		[23][APE_TOKEN_NOME_ID]		=		1;
	bloco.token_transitions		[23][APE_TOKEN_REPEAT_ID]		=		5;
	bloco.token_transitions		[23][APE_TOKEN_RETURN_ID]		=		10;
	bloco.token_transitions		[23][APE_TOKEN_WHILE_ID]		=		4;
	bloco.token_transitions		[25][APE_TOKEN_FECHA_PARENTESES_ID]		=		18;
	bloco.token_transitions		[25][APE_TOKEN_VIRGULA_ID]		=		29;
	bloco.token_transitions		[26][APE_TOKEN_ABRE_PARENTESES_ID]		=		2;
	bloco.token_transitions		[26][APE_TOKEN_BREAK_ID]		=		11;
	bloco.token_transitions		[26][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[26][APE_TOKEN_FOR_ID]		=		7;
	bloco.token_transitions		[26][APE_TOKEN_FUNCTION_ID]		=		8;
	bloco.token_transitions		[26][APE_TOKEN_IF_ID]		=		6;
	bloco.token_transitions		[26][APE_TOKEN_IGUAL_ID]		=		17;
	bloco.token_transitions		[26][APE_TOKEN_LOCAL_ID]		=		9;
	bloco.token_transitions		[26][APE_TOKEN_NOME_ID]		=		1;
	bloco.token_transitions		[26][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		23;
	bloco.token_transitions		[26][APE_TOKEN_REPEAT_ID]		=		5;
	bloco.token_transitions		[26][APE_TOKEN_RETURN_ID]		=		10;
	bloco.token_transitions		[26][APE_TOKEN_VIRGULA_ID]		=		41;
	bloco.token_transitions		[26][APE_TOKEN_WHILE_ID]		=		4;
	bloco.token_transitions		[27][APE_TOKEN_NOME_ID]		=		28;
	bloco.token_transitions		[28][APE_TOKEN_ABRE_PARENTESES_ID]		=		30;
	bloco.token_transitions		[30][APE_TOKEN_FECHA_PARENTESES_ID]		=		3;
	bloco.token_transitions		[30][APE_TOKEN_NOME_ID]		=		31;
	bloco.token_transitions		[30][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		32;
	bloco.token_transitions		[31][APE_TOKEN_FECHA_PARENTESES_ID]		=		3;
	bloco.token_transitions		[31][APE_TOKEN_VIRGULA_ID]		=		39;
	bloco.token_transitions		[32][APE_TOKEN_FECHA_PARENTESES_ID]		=		3;
	bloco.token_transitions		[33][APE_TOKEN_END_ID]		=		37;
	bloco.token_transitions		[34][APE_TOKEN_IGUAL_ID]		=		40;
	bloco.token_transitions		[35][APE_TOKEN_FECHA_CHAVES_ID]		=		18;
	bloco.token_transitions		[35][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		16;
	bloco.token_transitions		[35][APE_TOKEN_VIRGULA_ID]		=		16;
	bloco.token_transitions		[37][APE_TOKEN_ABRE_PARENTESES_ID]		=		2;
	bloco.token_transitions		[37][APE_TOKEN_BREAK_ID]		=		11;
	bloco.token_transitions		[37][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[37][APE_TOKEN_FOR_ID]		=		7;
	bloco.token_transitions		[37][APE_TOKEN_FUNCTION_ID]		=		8;
	bloco.token_transitions		[37][APE_TOKEN_IF_ID]		=		6;
	bloco.token_transitions		[37][APE_TOKEN_LOCAL_ID]		=		9;
	bloco.token_transitions		[37][APE_TOKEN_NOME_ID]		=		1;
	bloco.token_transitions		[37][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		23;
	bloco.token_transitions		[37][APE_TOKEN_REPEAT_ID]		=		5;
	bloco.token_transitions		[37][APE_TOKEN_RETURN_ID]		=		10;
	bloco.token_transitions		[37][APE_TOKEN_WHILE_ID]		=		4;
	bloco.token_transitions		[38][APE_TOKEN_FECHA_COLCHETES_ID]		=		34;
	bloco.token_transitions		[39][APE_TOKEN_NOME_ID]		=		31;
	bloco.token_transitions		[39][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		32;
	bloco.token_transitions		[41][APE_TOKEN_NOME_ID]		=		26;
	bloco.token_transitions		[42][APE_TOKEN_ABRE_PARENTESES_ID]		=		2;
	bloco.token_transitions		[42][APE_TOKEN_BREAK_ID]		=		11;
	bloco.token_transitions		[42][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[42][APE_TOKEN_FOR_ID]		=		7;
	bloco.token_transitions		[42][APE_TOKEN_FUNCTION_ID]		=		8;
	bloco.token_transitions		[42][APE_TOKEN_IF_ID]		=		6;
	bloco.token_transitions		[42][APE_TOKEN_LOCAL_ID]		=		9;
	bloco.token_transitions		[42][APE_TOKEN_NOME_ID]		=		1;
	bloco.token_transitions		[42][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		23;
	bloco.token_transitions		[42][APE_TOKEN_REPEAT_ID]		=		5;
	bloco.token_transitions		[42][APE_TOKEN_RETURN_ID]		=		10;
	bloco.token_transitions		[42][APE_TOKEN_VIRGULA_ID]		=		17;
	bloco.token_transitions		[42][APE_TOKEN_WHILE_ID]		=		4;
	bloco.token_transitions		[43][APE_TOKEN_ABRE_PARENTESES_ID]		=		30;
	bloco.token_transitions		[43][APE_TOKEN_DOIS_PONTOS_ID]		=		27;
	bloco.token_transitions		[43][APE_TOKEN_PONTO_ID]		=		8;
	bloco.token_transitions		[44][APE_TOKEN_IGUAL_ID]		=		46;
	bloco.token_transitions		[44][APE_TOKEN_IN_ID]		=		47;
	bloco.token_transitions		[44][APE_TOKEN_VIRGULA_ID]		=		45;
	bloco.token_transitions		[45][APE_TOKEN_NOME_ID]		=		53;
	bloco.token_transitions		[48][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[48][APE_TOKEN_VIRGULA_ID]		=		47;
	bloco.token_transitions		[49][APE_TOKEN_VIRGULA_ID]		=		50;
	bloco.token_transitions		[51][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[51][APE_TOKEN_VIRGULA_ID]		=		4;
	bloco.token_transitions		[52][APE_TOKEN_DO_ID]		=		3;
	bloco.token_transitions		[53][APE_TOKEN_IN_ID]		=		47;
	bloco.token_transitions		[53][APE_TOKEN_VIRGULA_ID]		=		45;
	bloco.token_transitions		[54][APE_TOKEN_THEN_ID]		=		55;
	bloco.token_transitions		[56][APE_TOKEN_ELSEIF_ID]		=		6;
	bloco.token_transitions		[56][APE_TOKEN_ELSE_ID]		=		3;
	bloco.token_transitions		[56][APE_TOKEN_END_ID]		=		37;
	bloco.token_transitions		[57][APE_TOKEN_ABRE_CHAVES_ID]		=		65;
	bloco.token_transitions		[57][APE_TOKEN_ABRE_COLCHETES_ID]		=		63;
	bloco.token_transitions		[57][APE_TOKEN_ABRE_PARENTESES_ID]		=		62;
	bloco.token_transitions		[57][APE_TOKEN_CADEIA_ID]		=		60;
	bloco.token_transitions		[57][APE_TOKEN_DOIS_PONTOS_ID]		=		66;
	bloco.token_transitions		[57][APE_TOKEN_IGUAL_ID]		=		17;
	bloco.token_transitions		[57][APE_TOKEN_PONTO_ID]		=		64;
	bloco.token_transitions		[57][APE_TOKEN_VIRGULA_ID]		=		15;
	bloco.token_transitions		[59][APE_TOKEN_FECHA_PARENTESES_ID]		=		60;
	bloco.token_transitions		[60][APE_TOKEN_ABRE_CHAVES_ID]		=		65;
	bloco.token_transitions		[60][APE_TOKEN_ABRE_COLCHETES_ID]		=		63;
	bloco.token_transitions		[60][APE_TOKEN_ABRE_PARENTESES_ID]		=		62;
	bloco.token_transitions		[60][APE_TOKEN_CADEIA_ID]		=		60;
	bloco.token_transitions		[60][APE_TOKEN_DOIS_PONTOS_ID]		=		66;
	bloco.token_transitions		[60][APE_TOKEN_PONTO_ID]		=		64;
	bloco.token_transitions		[61][APE_TOKEN_UNTIL_ID]		=		67;
	bloco.token_transitions		[62][APE_TOKEN_FECHA_PARENTESES_ID]		=		60;
	bloco.token_transitions		[64][APE_TOKEN_NOME_ID]		=		57;
	bloco.token_transitions		[65][APE_TOKEN_ABRE_COLCHETES_ID]		=		71;
	bloco.token_transitions		[65][APE_TOKEN_FECHA_CHAVES_ID]		=		60;
	bloco.token_transitions		[65][APE_TOKEN_NOME_ID]		=		69;
	bloco.token_transitions		[66][APE_TOKEN_NOME_ID]		=		68;
	bloco.token_transitions		[68][APE_TOKEN_ABRE_CHAVES_ID]		=		65;
	bloco.token_transitions		[68][APE_TOKEN_ABRE_PARENTESES_ID]		=		62;
	bloco.token_transitions		[68][APE_TOKEN_CADEIA_ID]		=		60;
	bloco.token_transitions		[69][APE_TOKEN_IGUAL_ID]		=		73;
	bloco.token_transitions		[70][APE_TOKEN_FECHA_CHAVES_ID]		=		60;
	bloco.token_transitions		[70][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		65;
	bloco.token_transitions		[70][APE_TOKEN_VIRGULA_ID]		=		65;
	bloco.token_transitions		[72][APE_TOKEN_FECHA_COLCHETES_ID]		=		69;
	bloco.token_transitions		[74][APE_TOKEN_FECHA_PARENTESES_ID]		=		75;
	bloco.token_transitions		[75][APE_TOKEN_ABRE_CHAVES_ID]		=		16;
	bloco.token_transitions		[75][APE_TOKEN_ABRE_COLCHETES_ID]		=		13;
	bloco.token_transitions		[75][APE_TOKEN_ABRE_PARENTESES_ID]		=		12;
	bloco.token_transitions		[75][APE_TOKEN_CADEIA_ID]		=		18;
	bloco.token_transitions		[75][APE_TOKEN_DOIS_PONTOS_ID]		=		19;
	bloco.token_transitions		[75][APE_TOKEN_PONTO_ID]		=		14;
	bloco.token_transitions		[76][APE_TOKEN_FECHA_COLCHETES_ID]		=		1;
	bloco.token_transitions		[77][APE_TOKEN_FECHA_PARENTESES_ID]		=		60;
	bloco.token_transitions		[77][APE_TOKEN_VIRGULA_ID]		=		78;
	bloco.token_transitions		[79][APE_TOKEN_FECHA_COLCHETES_ID]		=		57;
	
	/* machine transitions */
	bloco.machine_transitions		[2][APE_MACHINE_EXP_ID]		=		74;
	bloco.machine_transitions		[3][APE_MACHINE_BLOCO_ID]		=		33;
	bloco.machine_transitions		[4][APE_MACHINE_EXP_ID]		=		52;
	bloco.machine_transitions		[5][APE_MACHINE_BLOCO_ID]		=		61;
	bloco.machine_transitions		[6][APE_MACHINE_EXP_ID]		=		54;
	bloco.machine_transitions		[10][APE_MACHINE_EXP_ID]		=		22;
	bloco.machine_transitions		[12][APE_MACHINE_EXP_ID]		=		25;
	bloco.machine_transitions		[13][APE_MACHINE_EXP_ID]		=		76;
	bloco.machine_transitions		[16][APE_MACHINE_EXP_ID]		=		35;
	bloco.machine_transitions		[17][APE_MACHINE_EXP_ID]		=		42;
	bloco.machine_transitions		[24][APE_MACHINE_EXP_ID]		=		22;
	bloco.machine_transitions		[29][APE_MACHINE_EXP_ID]		=		25;
	bloco.machine_transitions		[36][APE_MACHINE_EXP_ID]		=		38;
	bloco.machine_transitions		[40][APE_MACHINE_EXP_ID]		=		35;
	bloco.machine_transitions		[46][APE_MACHINE_EXP_ID]		=		49;
	bloco.machine_transitions		[47][APE_MACHINE_EXP_ID]		=		48;
	bloco.machine_transitions		[50][APE_MACHINE_EXP_ID]		=		51;
	bloco.machine_transitions		[55][APE_MACHINE_BLOCO_ID]		=		56;
	bloco.machine_transitions		[58][APE_MACHINE_EXP_ID]		=		59;
	bloco.machine_transitions		[62][APE_MACHINE_EXP_ID]		=		77;
	bloco.machine_transitions		[63][APE_MACHINE_EXP_ID]		=		79;
	bloco.machine_transitions		[65][APE_MACHINE_EXP_ID]		=		70;
	bloco.machine_transitions		[67][APE_MACHINE_EXP_ID]		=		37;
	bloco.machine_transitions		[71][APE_MACHINE_EXP_ID]		=		72;
	bloco.machine_transitions		[73][APE_MACHINE_EXP_ID]		=		70;
	bloco.machine_transitions		[78][APE_MACHINE_EXP_ID]		=		77;
	
	/* Machine 1: exp */
	exp.machine_id = APE_MACHINE_EXP_ID; // 1
	exp.initial_state = 0;
	exp.current_state = 0;
	initialize_machine_transitions(&exp);
	exp.final_states[0] = 1;
	exp.final_states[1] = 4;
	exp.final_states[2] = -1;
	
	/* token transitions */
	exp.token_transitions		[0][APE_TOKEN_ABRE_CHAVES_ID]		=		5;
	exp.token_transitions		[0][APE_TOKEN_ABRE_PARENTESES_ID]		=		3;
	exp.token_transitions		[0][APE_TOKEN_CADEIA_ID]		=		1;
	exp.token_transitions		[0][APE_TOKEN_FALSE_ID]		=		1;
	exp.token_transitions		[0][APE_TOKEN_FUNCTION_ID]		=		2;
	exp.token_transitions		[0][APE_TOKEN_JOGO_DA_VELHA_ID]		=		0;
	exp.token_transitions		[0][APE_TOKEN_NIL_ID]		=		1;
	exp.token_transitions		[0][APE_TOKEN_NOME_ID]		=		4;
	exp.token_transitions		[0][APE_TOKEN_NOT_ID]		=		0;
	exp.token_transitions		[0][APE_TOKEN_NUMERO_ID]		=		1;
	exp.token_transitions		[0][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		1;
	exp.token_transitions		[0][APE_TOKEN_SUBTRACAO_ID]		=		0;
	exp.token_transitions		[0][APE_TOKEN_TRUE_ID]		=		1;
	exp.token_transitions		[1][APE_TOKEN_ACENTO_CIRCUNFLEXO_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_AND_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_DIVISAO_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_IGUAL_IGUAL_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_MAIOR_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_MAIOR_IGUAL_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_MENOR_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_MENOR_IGUAL_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_MULTIPLICACAO_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_OR_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_PONTO_PONTO_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_PORCENTAGEM_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_SOMA_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_SUBTRACAO_ID]		=		0;
	exp.token_transitions		[1][APE_TOKEN_TIO_IGUAL_ID]		=		0;
	exp.token_transitions		[2][APE_TOKEN_ABRE_PARENTESES_ID]		=		26;
	exp.token_transitions		[4][APE_TOKEN_ABRE_CHAVES_ID]		=		14;
	exp.token_transitions		[4][APE_TOKEN_ABRE_COLCHETES_ID]		=		12;
	exp.token_transitions		[4][APE_TOKEN_ABRE_PARENTESES_ID]		=		11;
	exp.token_transitions		[4][APE_TOKEN_ACENTO_CIRCUNFLEXO_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_AND_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_CADEIA_ID]		=		4;
	exp.token_transitions		[4][APE_TOKEN_DIVISAO_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_DOIS_PONTOS_ID]		=		15;
	exp.token_transitions		[4][APE_TOKEN_IGUAL_IGUAL_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_MAIOR_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_MAIOR_IGUAL_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_MENOR_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_MENOR_IGUAL_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_MULTIPLICACAO_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_OR_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_PONTO_ID]		=		13;
	exp.token_transitions		[4][APE_TOKEN_PONTO_PONTO_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_PORCENTAGEM_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_SOMA_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_SUBTRACAO_ID]		=		0;
	exp.token_transitions		[4][APE_TOKEN_TIO_IGUAL_ID]		=		0;
	exp.token_transitions		[5][APE_TOKEN_ABRE_COLCHETES_ID]		=		8;
	exp.token_transitions		[5][APE_TOKEN_FECHA_CHAVES_ID]		=		1;
	exp.token_transitions		[5][APE_TOKEN_NOME_ID]		=		6;
	exp.token_transitions		[6][APE_TOKEN_IGUAL_ID]		=		10;
	exp.token_transitions		[7][APE_TOKEN_FECHA_CHAVES_ID]		=		1;
	exp.token_transitions		[7][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		5;
	exp.token_transitions		[7][APE_TOKEN_VIRGULA_ID]		=		5;
	exp.token_transitions		[9][APE_TOKEN_FECHA_COLCHETES_ID]		=		6;
	exp.token_transitions		[11][APE_TOKEN_FECHA_PARENTESES_ID]		=		4;
	exp.token_transitions		[13][APE_TOKEN_NOME_ID]		=		4;
	exp.token_transitions		[14][APE_TOKEN_ABRE_COLCHETES_ID]		=		19;
	exp.token_transitions		[14][APE_TOKEN_FECHA_CHAVES_ID]		=		4;
	exp.token_transitions		[14][APE_TOKEN_NOME_ID]		=		17;
	exp.token_transitions		[15][APE_TOKEN_NOME_ID]		=		16;
	exp.token_transitions		[16][APE_TOKEN_ABRE_CHAVES_ID]		=		14;
	exp.token_transitions		[16][APE_TOKEN_ABRE_PARENTESES_ID]		=		11;
	exp.token_transitions		[16][APE_TOKEN_CADEIA_ID]		=		4;
	exp.token_transitions		[17][APE_TOKEN_IGUAL_ID]		=		21;
	exp.token_transitions		[18][APE_TOKEN_FECHA_CHAVES_ID]		=		4;
	exp.token_transitions		[18][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		14;
	exp.token_transitions		[18][APE_TOKEN_VIRGULA_ID]		=		14;
	exp.token_transitions		[20][APE_TOKEN_FECHA_COLCHETES_ID]		=		17;
	exp.token_transitions		[22][APE_TOKEN_FECHA_PARENTESES_ID]		=		4;
	exp.token_transitions		[22][APE_TOKEN_VIRGULA_ID]		=		23;
	exp.token_transitions		[24][APE_TOKEN_FECHA_COLCHETES_ID]		=		4;
	exp.token_transitions		[25][APE_TOKEN_FECHA_PARENTESES_ID]		=		4;
	exp.token_transitions		[26][APE_TOKEN_FECHA_PARENTESES_ID]		=		29;
	exp.token_transitions		[26][APE_TOKEN_NOME_ID]		=		28;
	exp.token_transitions		[26][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		27;
	exp.token_transitions		[27][APE_TOKEN_FECHA_PARENTESES_ID]		=		29;
	exp.token_transitions		[28][APE_TOKEN_FECHA_PARENTESES_ID]		=		29;
	exp.token_transitions		[28][APE_TOKEN_VIRGULA_ID]		=		31;
	exp.token_transitions		[30][APE_TOKEN_END_ID]		=		1;
	exp.token_transitions		[31][APE_TOKEN_NOME_ID]		=		28;
	exp.token_transitions		[31][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		27;
	
	/* machine transitions */
	exp.machine_transitions		[3][APE_MACHINE_EXP_ID]		=		25;
	exp.machine_transitions		[5][APE_MACHINE_EXP_ID]		=		7;
	exp.machine_transitions		[8][APE_MACHINE_EXP_ID]		=		9;
	exp.machine_transitions		[10][APE_MACHINE_EXP_ID]		=		7;
	exp.machine_transitions		[11][APE_MACHINE_EXP_ID]		=		22;
	exp.machine_transitions		[12][APE_MACHINE_EXP_ID]		=		24;
	exp.machine_transitions		[14][APE_MACHINE_EXP_ID]		=		18;
	exp.machine_transitions		[19][APE_MACHINE_EXP_ID]		=		20;
	exp.machine_transitions		[21][APE_MACHINE_EXP_ID]		=		18;
	exp.machine_transitions		[23][APE_MACHINE_EXP_ID]		=		22;
	exp.machine_transitions		[29][APE_MACHINE_BLOCO_ID]		=		30;
	
	/* initialize ape machines */
	ape_parser.initial_machine = bloco;
	ape_parser.current_machine = bloco;
	ape_parser.machines[0] = bloco;
	ape_parser.machines[1] = exp;
}

//////////////////////////////////////////////////////////