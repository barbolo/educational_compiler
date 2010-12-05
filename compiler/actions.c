/*
 *  actions.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos on 26/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "actions.h"

char * ultimo_identificador_lido = NULL;
char buffer[100];
Stack * pilha_operandos = NULL;
Stack * pilha_operadores = NULL;

void default_action() {
	// do nothing
}

void save_stack_frame() {
	
}

// Cria novo escopo (guardando tabela de símbolos com valores da variáveis)
void create_new_scope(){
	
	// cria nova tabela de símbolos dentro da atual
	SymbolTable * tabela = nova_tabela_de_simbolos();
	
	// cria links entre tabelas
	tabela->parent = current_symbol_table;
	current_symbol_table->child = tabela;
	
	// define a tabela criada como a atual
	current_symbol_table = tabela;
	
}

// É chamada quando encontra um tipo (por exemplo, int ... ou void ...)
void declaring_type() {
	current_symbol_table->lines[current_symbol_table->nsimbolos].tipo_identificador = get_tipo_identificador(token.value);
}

// É chamada quando a declaração de uma função está sendo contruída (por exemplo, int nome...)
void declaring_function() {
	if (nome_do_identificador_eh_unico) {
		current_symbol_table->lines[current_symbol_table->nsimbolos].rotulo_ou_variavel = TIPO_ROTULO;
		current_symbol_table->lines[current_symbol_table->nsimbolos].nome_identificador = token.value;
		current_symbol_table->nsimbolos++;
	} else {
		semantic_error = 1;
	}
}

// É chamada quando ocorre a declaração de uma variável, por exemplo: int n
void declaring_variable() {
	if (nome_do_identificador_eh_unico) {
		current_symbol_table->lines[current_symbol_table->nsimbolos].rotulo_ou_variavel = TIPO_VARIAVEL;
		current_symbol_table->lines[current_symbol_table->nsimbolos].nome_identificador = token.value;
		current_symbol_table->nsimbolos++;
	} else {
		semantic_error = 1;
	}

}

// É chamada quando um identificar receberá atribuição
void comecando_atribuicao() {
	ultimo_identificador_lido = token.value;
}

// É chamada quando o comando de atribuição finaliza
void atribuicao_finalizada() {
	
	// LOAD
	write("\t\tLD\tK_");
	sprintf(buffer, "%d", find_by_key(&table_numbers,token.value));
	write(buffer);
	write("\t; carrega constante ");
	write(token.value);
	write(" no acumulador\n");
	
	// MOVE
	write("\t\tMM\t");
	write(ultimo_identificador_lido);
	write("\t; armazena conteúdo do acumulador na variável ");
	write(ultimo_identificador_lido);
	write("\n");
}

// empilha (pilha de operandos, identificador encontrado)
void jj_expressao_1() {
	push_stack(pilha_operandos, token.value);
}

// empilha (pilha de operandos, número encontrado)
void jj_expressao_2() {
	push_stack(pilha_operandos, token.value);
}

// empilha (pilha de operadores, "(")
void jj_expressao_3() {
	push_stack(pilha_operadores, "(");
}

// nada executa
void jj_expressao_4() {
}

// X5:	consulta (pilha de operadores, Y);
//		Se Y != "(": executa GERACÓDIGO, detalhada adiante;. GO TO X5.
//		Se Y =	"(":	desempilha (pilha de operadores, Y);
void jj_expressao_5() {
	if (strcmp(pilha_operadores->content, "(") != 0) {
		jj_gera_codigo();
		jj_expressao_5();
	} else {
		pop_stack(pilha_operadores);
	}
}

// X6:	consulta (pilha de operadores, Y);
//		Se Y for "+", "-", "*" ou "/":
//			executa GERACÓDIGO, detalhada adiante; GO TO X6;
//		Caso contrário: empilha (pilha de operadores, "+");
void jj_expressao_6() {
	if (strcmp(pilha_operadores->content, "+") == 0 ||
		strcmp(pilha_operadores->content, "-") == 0 ||
		strcmp(pilha_operadores->content, "*") == 0 ||
		strcmp(pilha_operadores->content, "/") == 0) {
		jj_gera_codigo();
		jj_expressao_6();
	} else {
		push_stack(pilha_operadores, "+");
	}
}

// X7:	consulta (pilha de operadores, Y);
//		Se Y for "+", "-", "*" ou "/":
//			executa GERACÓDIGO, detalhada adiante; GO TO X7;
//		Caso contrário: empilha (pilha de operadores, "-");
void jj_expressao_7() {
	if (strcmp(pilha_operadores->content, "+") == 0 ||
		strcmp(pilha_operadores->content, "-") == 0 ||
		strcmp(pilha_operadores->content, "*") == 0 ||
		strcmp(pilha_operadores->content, "/") == 0) {
		jj_gera_codigo();
		jj_expressao_7();
	} else {
		push_stack(pilha_operadores, "-");
	}
}

// X8:	consulta (pilha de operadores, Y);
//		Se Y for "*" ou "/": executa GERACÓDIGO, detalhada adiante; GO TO X8;
//		Caso contrário: empilha (pilha de operadores, "*");
void jj_expressao_8() {
	if (strcmp(pilha_operadores->content, "*") == 0 ||
		strcmp(pilha_operadores->content, "/") == 0) {
		jj_gera_codigo();
		jj_expressao_8();
	} else {
		push_stack(pilha_operadores, "*");
	}
}

// X9:	consulta (pilha de operadores, Y);
//		Se Y for "*" ou "/": executa GERACÓDIGO, detalhada adiante; GO TO X9;
//		Caso contrário: empilha (pilha de operadores, "/");
void jj_expressao_9() {
	if (strcmp(pilha_operadores->content, "*") == 0 ||
		strcmp(pilha_operadores->content, "/") == 0) {
		jj_gera_codigo();
		jj_expressao_9();
	} else {
		push_stack(pilha_operadores, "/");
	}
}

// (* Esta rotina é associada ao final do reconhecimento da expressão *)
// X10:	consulta (pilha de operadores, Y);
//		Se Y não for "vazio" : executa GERACÓDIGO, detalhada adiante, GO TO X10;
void jj_expressao_10() {
	if (pilha_operadores != NULL) {
		jj_gera_codigo();
		jj_expressao_10();
	}
}

// GERACÓDIGO:	Desempilha (pilha de operadores, Y);
//				Desempilha (pilha de operandos, B);
//				Desempilha (pilha de operandos, A);
//				Gera ("LDA", A);
//				Se Y = "+": gera("ADA", B);
//				Se Y = "-": gera("SUB", B);
//				Se Y = "*": gera("MUL", B);
//				Se Y = "/": gera("DIV", B);
//				Incrementacontador(CONTATEMP);
//				Gera("STA", "#TEMP".CONTATEMP);
//				empilha(pilha de operandos, "#TEMP".CONTATEMP);
void jj_gera_codigo() {
}

void write_variables() {
	int i;
	SymbolLine line;
	
	write("\t\t#\tmain\n\t\tHM /0\n\n\n\t\t@\t/200\t; começo da área de dados\n");
	
	//TODO: navegar em todas as tabelas de símbolo do stack frame

	while (current_symbol_table->parent != NULL) {
		current_symbol_table = current_symbol_table->parent;
	}
	
	while (current_symbol_table != NULL) {
		
		for (i=0; i < current_symbol_table->nsimbolos; i++) {
			
			if (current_symbol_table->lines[i].rotulo_ou_variavel == 1) {
				
				line = current_symbol_table->lines[i];
				
				sprintf(buffer, "%d", line.valor_inteiro);
				
				write(line.nome_identificador);
				write("\t\tK\t\t=");
				write(buffer);
				write("\t; declaração da variável ");
				write(line.nome_identificador);
				write("\n");	
			}
			
		}

		current_symbol_table = current_symbol_table->child;
		
	}
	
	hash_table * temp_line = &table_numbers;
	
	while (temp_line != NULL) {
		write("K_");
		sprintf(buffer, "%d", temp_line->value);
		write(buffer);
		write("\t\tK\t\t=");
		write(temp_line->key);
		write(" ; declaração da constante K_");
		write(buffer);
		write("\n");
		temp_line = temp_line->next;
	}
	
}

// Verifica se o identificador ainda não está presente na tabela de símbolos
int nome_do_identificador_eh_unico() {
	return pesquisa_posicao_na_tabela_de_simbolos(current_symbol_table, token.value) == 0;
}


//////////////////////////////////////////////////////////
////////// GENERATED BY RADIANT FIRE LOADER //////////////
//////////////////////////////////////////////////////////

void init_semantic_actions() {
	
	/* Machine 0: programa */
	
	/* token transitions */
	semantic_functions_tokens 		 [0][0][APE_TOKEN_FUNCTIONS_ID]			=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_BOOLEAN_ID]			=		declaring_type;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_CHAR_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_INT_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_MAIN_ID]				=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_VOID_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][2][APE_TOKEN_ID_ID]				=		declaring_function;
	semantic_functions_tokens 		 [0][3][APE_TOKEN_ABRE_CHAVES_ID]		=		create_new_scope;
	semantic_functions_tokens 		 [0][4][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [0][5][APE_TOKEN_BEGIN_ID]				=		default_action;
	semantic_functions_tokens 		 [0][5][APE_TOKEN_BOOLEAN_ID]			=		declaring_type;
	semantic_functions_tokens 		 [0][5][APE_TOKEN_CHAR_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][5][APE_TOKEN_INT_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][5][APE_TOKEN_PONTO_E_VIRGULA_ID]	=		default_action;
	semantic_functions_tokens 		 [0][6][APE_TOKEN_BOOLEAN_ID]			=		declaring_type;
	semantic_functions_tokens 		 [0][6][APE_TOKEN_CHAR_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][6][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [0][6][APE_TOKEN_INT_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][7][APE_TOKEN_ID_ID]				=		declaring_variable;
	semantic_functions_tokens 		 [0][8][APE_TOKEN_BEGIN_ID]				=		default_action;
	semantic_functions_tokens 		 [0][9][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][10][APE_TOKEN_ID_ID]				=		declaring_variable;
	semantic_functions_tokens 		 [0][11][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][13][APE_TOKEN_BEGIN_ID]			=		default_action;
	semantic_functions_tokens 		 [0][13][APE_TOKEN_BOOLEAN_ID]			=		declaring_type;
	semantic_functions_tokens 		 [0][13][APE_TOKEN_CHAR_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][13][APE_TOKEN_INT_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][13][APE_TOKEN_PONTO_E_VIRGULA_ID]	=		default_action;
	semantic_functions_tokens 		 [0][14][APE_TOKEN_ID_ID]				=		declaring_variable;
	semantic_functions_tokens 		 [0][15][APE_TOKEN_BEGIN_ID]			=		default_action;
	semantic_functions_tokens 		 [0][16][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][16][APE_TOKEN_RETURN_ID]			=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_PONTO_E_VIRGULA_ID]	=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_VIRGULA_ID]			=		default_action;
	semantic_functions_tokens 		 [0][19][APE_TOKEN_PONTO_E_VIRGULA_ID]	=		default_action;
	semantic_functions_tokens 		 [0][20][APE_TOKEN_BOOLEAN_ID]			=		declaring_type;
	semantic_functions_tokens 		 [0][20][APE_TOKEN_CHAR_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][20][APE_TOKEN_INT_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][21][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][22][APE_TOKEN_PONTO_E_VIRGULA_ID]	=		default_action;
	semantic_functions_tokens 		 [0][22][APE_TOKEN_VIRGULA_ID]			=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_BOOLEAN_ID]			=		declaring_type;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_CHAR_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_INT_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][24][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [0][24][APE_TOKEN_VIRGULA_ID]			=		default_action;
	semantic_functions_tokens 		 [0][25][APE_TOKEN_BOOLEAN_ID]			=		declaring_type;
	semantic_functions_tokens 		 [0][25][APE_TOKEN_CHAR_ID]				=		declaring_type;
	semantic_functions_tokens 		 [0][25][APE_TOKEN_INT_ID]				=		declaring_type;
	
	/* machine transitions */
	semantic_functions_machines 		 [0][9][APE_MACHINE_COMANDO_ID]		=		default_action;
	semantic_functions_machines 		 [0][16][APE_MACHINE_COMANDO_ID]	=		default_action;
	semantic_functions_machines 		 [0][17][APE_MACHINE_EXPRESSAO_ID]	=		default_action;
	
	/* Machine 1: comando */
	
	/* token transitions */
	semantic_functions_tokens 		 [1][0][APE_TOKEN_ID_ID]				=		comecando_atribuicao;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_IF_ID]				=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_PRINT_ID]				=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_SCAN_ID]				=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_WHILE_ID]				=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_IGUAL_ID]				=		default_action;
	semantic_functions_tokens 		 [1][2][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][3][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][5][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][7][APE_TOKEN_ID_ID]				=		default_action;
	semantic_functions_tokens 		 [1][8][APE_TOKEN_STRING_ID]			=		default_action;
	semantic_functions_tokens 		 [1][9][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][10][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][10][APE_TOKEN_SOMA_ID]				=		default_action;
	semantic_functions_tokens 		 [1][12][APE_TOKEN_PONTO_E_VIRGULA_ID]	=		default_action;
	semantic_functions_tokens 		 [1][14][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][15][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][16][APE_TOKEN_BOOLEAN_ID]			=		declaring_type;
	semantic_functions_tokens 		 [1][16][APE_TOKEN_CHAR_ID]				=		declaring_type;
	semantic_functions_tokens 		 [1][16][APE_TOKEN_INT_ID]				=		declaring_type;
	semantic_functions_tokens 		 [1][17][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][18][APE_TOKEN_VIRGULA_ID]			=		default_action;
	semantic_functions_tokens 		 [1][19][APE_TOKEN_ELSE_ID]				=		default_action;
	semantic_functions_tokens 		 [1][20][APE_TOKEN_ID_ID]				=		declaring_variable;
	semantic_functions_tokens 		 [1][21][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][22][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [1][23][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][25][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	
	/* machine transitions */
	semantic_functions_machines 		 [1][6][APE_MACHINE_EXPRESSAO_ID]	=		default_action;
	semantic_functions_machines 		 [1][7][APE_MACHINE_CONDICAO_ID]	=		default_action;
	semantic_functions_machines 		 [1][7][APE_MACHINE_EXPRESSAO_ID]	=		default_action;
	semantic_functions_machines 		 [1][8][APE_MACHINE_CONDICAO_ID]	=		default_action;
	semantic_functions_machines 		 [1][8][APE_MACHINE_EXPRESSAO_ID]	=		default_action;
	semantic_functions_machines 		 [1][13][APE_MACHINE_CONDICAO_ID]	=		default_action;
	semantic_functions_machines 		 [1][17][APE_MACHINE_COMANDO_ID]	=		default_action;
	semantic_functions_machines 		 [1][23][APE_MACHINE_COMANDO_ID]	=		default_action;
	semantic_functions_machines 		 [1][24][APE_MACHINE_CONDICAO_ID]	=		default_action;
	
	/* Machine 2: expressao */
	
	/* token transitions */
	semantic_functions_tokens 		 [2][0][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [2][0][APE_TOKEN_ID_ID]				=		default_action;
	semantic_functions_tokens 		 [2][0][APE_TOKEN_INTEIRO_ID]			=		atribuicao_finalizada;
	semantic_functions_tokens 		 [2][2][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [2][2][APE_TOKEN_DIVISAO_ID]			=		default_action;
	semantic_functions_tokens 		 [2][2][APE_TOKEN_MULTIPLICACAO_ID]		=		default_action;
	semantic_functions_tokens 		 [2][2][APE_TOKEN_SOMA_ID]				=		default_action;
	semantic_functions_tokens 		 [2][2][APE_TOKEN_SUBTRACAO_ID]			=		default_action;
	semantic_functions_tokens 		 [2][3][APE_TOKEN_DIVISAO_ID]			=		default_action;
	semantic_functions_tokens 		 [2][3][APE_TOKEN_MULTIPLICACAO_ID]		=		default_action;
	semantic_functions_tokens 		 [2][3][APE_TOKEN_SOMA_ID]				=		default_action;
	semantic_functions_tokens 		 [2][3][APE_TOKEN_SUBTRACAO_ID]			=		default_action;
	semantic_functions_tokens 		 [2][4][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [2][5][APE_TOKEN_ID_ID]				=		default_action;
	
	/* machine transitions */
	semantic_functions_machines 		 [2][1][APE_MACHINE_EXPRESSAO_ID]	=		default_action;
	semantic_functions_machines 		 [2][5][APE_MACHINE_CONDICAO_ID]	=		default_action;
	semantic_functions_machines 		 [2][5][APE_MACHINE_EXPRESSAO_ID]	=		default_action;
	
	/* Machine 3: condicao */
	
	/* token transitions */
	semantic_functions_tokens 		 [3][0][APE_TOKEN_BOOLEANO_ID]			=		default_action;
	semantic_functions_tokens 		 [3][0][APE_TOKEN_NOT_ID]				=		default_action;
	semantic_functions_tokens 		 [3][1][APE_TOKEN_DIFERENTE_ID]			=		default_action;
	semantic_functions_tokens 		 [3][1][APE_TOKEN_IGUAL_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [3][1][APE_TOKEN_MAIOR_ID]				=		default_action;
	semantic_functions_tokens 		 [3][1][APE_TOKEN_MAIOR_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [3][1][APE_TOKEN_MENOR_ID]				=		default_action;
	semantic_functions_tokens 		 [3][1][APE_TOKEN_MENOR_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [3][2][APE_TOKEN_AND_ID]				=		default_action;
	semantic_functions_tokens 		 [3][2][APE_TOKEN_OR_ID]				=		default_action;
	semantic_functions_tokens 		 [3][3][APE_TOKEN_ABRE_PARENTESES_ID]	=		default_action;
	semantic_functions_tokens 		 [3][7][APE_TOKEN_FECHA_PARENTESES_ID]	=		default_action;
	
	/* machine transitions */
	semantic_functions_machines 		 [3][0][APE_MACHINE_CONDICAO_ID]	=		default_action;
	semantic_functions_machines 		 [3][0][APE_MACHINE_EXPRESSAO_ID]	=		default_action;
	semantic_functions_machines 		 [3][5][APE_MACHINE_EXPRESSAO_ID]	=		default_action;
	semantic_functions_machines 		 [3][6][APE_MACHINE_CONDICAO_ID]	=		default_action;
	semantic_functions_machines 		 [3][8][APE_MACHINE_CONDICAO_ID]	=		default_action;
}

//////////////////////////////////////////////////////////