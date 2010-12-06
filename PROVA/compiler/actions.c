/*
 *  actions.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos on 26/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "actions.h"

int CONTATEMP = 0;
char * ultimo_identificador_lido = NULL;
char * nome_variavel_retornada_por_expressao = NULL;
char buffer[200];
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
		jj_erro("declaração de função incorreta");
	}
}

// É chamada quando ocorre a declaração de uma variável, por exemplo: int n
void declaring_variable() {
	if (nome_do_identificador_eh_unico) {
		current_symbol_table->lines[current_symbol_table->nsimbolos].rotulo_ou_variavel = TIPO_VARIAVEL;
		current_symbol_table->lines[current_symbol_table->nsimbolos].nome_identificador = token.value;
		current_symbol_table->nsimbolos++;
	} else {
		jj_erro("declaração de variável incorreta");
	}

}

// É chamada quando um identificar receberá atribuição
void comecando_atribuicao() {
	ultimo_identificador_lido = token.value;
}

void definir_nome_da_variavel_retornada_por_expressao(char * nome) {
	nome_variavel_retornada_por_expressao = nome;
}

// É chamada quando o comando de atribuição finaliza
void atribuicao_finalizada() {
	
	// LOAD
	write("\t\tLD\t");
	write(nome_variavel_retornada_por_expressao);
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
	push_stack(&pilha_operandos, token.value);
}

// empilha (pilha de operandos, número encontrado)
void jj_expressao_2() {
	char * constante;
	sprintf(buffer, "K_%d", find_by_key(&table_numbers, token.value));
	constante = strcpy(buffer);
	push_stack(&pilha_operandos, constante);
	definir_nome_da_variavel_retornada_por_expressao(constante);
}

// empilha (pilha de operadores, "(")
void jj_expressao_3() {
	push_stack(&pilha_operadores, "(");
}

// nada executa
void jj_expressao_4() {
}

// X5:	consulta (pilha de operadores, Y);
//		Se Y != "(": executa GERACÓDIGO, detalhada adiante;. GO TO X5.
//		Se Y =	"(":	desempilha (pilha de operadores, Y);
void jj_expressao_5() {
	if (strcmp(consulta_pilha(pilha_operadores), "(") != 0) {
		jj_gera_codigo();
		jj_expressao_5();
	} else {
		pop_stack(&pilha_operadores);
	}
}

// X6:	consulta (pilha de operadores, Y);
//		Se Y for "+", "-", "*" ou "/":
//			executa GERACÓDIGO, detalhada adiante; GO TO X6;
//		Caso contrário: empilha (pilha de operadores, "+");
void jj_expressao_6() {
	if (strcmp(consulta_pilha(pilha_operadores), "+") == 0 ||
		strcmp(consulta_pilha(pilha_operadores), "-") == 0 ||
		strcmp(consulta_pilha(pilha_operadores), "*") == 0 ||
		strcmp(consulta_pilha(pilha_operadores), "/") == 0) {
		jj_gera_codigo();
		jj_expressao_6();
	} else {
		push_stack(&pilha_operadores, "+");
	}
}

// X7:	consulta (pilha de operadores, Y);
//		Se Y for "+", "-", "*" ou "/":
//			executa GERACÓDIGO, detalhada adiante; GO TO X7;
//		Caso contrário: empilha (pilha de operadores, "-");
void jj_expressao_7() {
	if (strcmp(consulta_pilha(pilha_operadores), "+") == 0 ||
		strcmp(consulta_pilha(pilha_operadores), "-") == 0 ||
		strcmp(consulta_pilha(pilha_operadores), "*") == 0 ||
		strcmp(consulta_pilha(pilha_operadores), "/") == 0) {
		jj_gera_codigo();
		jj_expressao_7();
	} else {
		push_stack(&pilha_operadores, "-");
	}
}

// X8:	consulta (pilha de operadores, Y);
//		Se Y for "*" ou "/": executa GERACÓDIGO, detalhada adiante; GO TO X8;
//		Caso contrário: empilha (pilha de operadores, "*");
void jj_expressao_8() {
	if (strcmp(consulta_pilha(pilha_operadores), "*") == 0 ||
		strcmp(consulta_pilha(pilha_operadores), "/") == 0) {
		jj_gera_codigo();
		jj_expressao_8();
	} else {
		push_stack(&pilha_operadores, "*");
	}
}

// X9:	consulta (pilha de operadores, Y);
//		Se Y for "*" ou "/": executa GERACÓDIGO, detalhada adiante; GO TO X9;
//		Caso contrário: empilha (pilha de operadores, "/");
void jj_expressao_9() {
	if (strcmp(consulta_pilha(pilha_operadores), "*") == 0 ||
		strcmp(consulta_pilha(pilha_operadores), "/") == 0) {
		jj_gera_codigo();
		jj_expressao_9();
	} else {
		push_stack(&pilha_operadores, "/");
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

void jj_expressao_11() {
	jj_erro("esperava-se identificador, número ou '(' neste ponto");
}
void jj_expressao_12() {
	jj_erro("esperava-se uma expressão correta neste ponto");
}
void jj_expressao_13() {
	jj_erro("esperava-se ')' neste ponto");
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
	CONTATEMP++;

	char * Y = pop_stack(&pilha_operadores);
	char * B = pop_stack(&pilha_operandos);
	char * A = pop_stack(&pilha_operandos);
	
	sprintf(buffer, "AC = %s", A);
	jj_gera("LD", A, buffer);

	sprintf(buffer, "AC = AC%s%s", Y, B);
	jj_gera(Y, B, buffer);

	sprintf(buffer, "TEMP%d", CONTATEMP);

	jj_gera("MM", buffer, "TEMPX = AC");

	push_stack(&pilha_operandos, strcpy(buffer));
	definir_nome_da_variavel_retornada_por_expressao(strcpy(buffer));
}

// GERA(X,Y):	Esta rotina deve limitar-se a emitir, em um dispositivo de saída, a lista de variáveis fornecidas.
//				O primeiro parâmetro é o mnemônico da instrução gerada, e o segundo é o operando. Note-se que, em
//				alguns casos, o operando aparece na forma P.Q., designando a concatenação das cadeias de caracteres
//				P e Q, nesta ordem.
void jj_gera(char * x, char * y, char *c) {
	write("\t\t");
	write(x);
	write("\t\t");
	write(y);
	write("\t\t;\t");
	write(c);
	write("\n");
}

// Esta rotina deve imprimir a mensagem X passada como parâmetro, e contabilizar os erros ocorridos.
void jj_erro(char * erro) {
	printf("\nchamando função: jj_erro\n");
	sprintf(buffer, "ERRO SEMÂNTICO: %s", erro);
	fputs(buffer, stderr);
	semantic_error++;
}

void write_variables() {
	int i;
	SymbolLine line;
	
	write("\t\t#\tmain\n\t\tHM /0\n\n\n\t\t@\t/200\t; começo da área de dados\n");
	
	//TODO: navegar em todas as tabelas de símbolo do stack frame

	// Declaração de variáveis
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
	
	// Declaração de constantes inteiras
	
	linked_table * temp_line = &table_numbers;
	
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
	
	// Declaração de variáveis temporárias
	for (i=1; i <= CONTATEMP; i++) {
		write("TEMP");
		sprintf(buffer, "%d", i);
		write(buffer);
		write("\t\tK\t\t=0");
		write(" ; declaração da variável temporária TEMP");
		write(buffer);
		write("\n");
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
	
	/* Machine 0: bloco */
	
	/* token transitions */
	semantic_functions_tokens 		 [0][0][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_BREAK_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_FOR_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_FUNCTION_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_IF_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_LOCAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_REPEAT_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_RETURN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][0][APE_TOKEN_WHILE_ID]		=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_DOIS_PONTOS_ID]		=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][1][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][7][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][8][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][9][APE_TOKEN_FUNCTION_ID]		=		default_action;
	semantic_functions_tokens 		 [0][9][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][10][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][11][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][12][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][14][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][15][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][15][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][16][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][16][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][16][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_BREAK_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_DOIS_PONTOS_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_FOR_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_FUNCTION_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_IF_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_LOCAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_REPEAT_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_RETURN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][18][APE_TOKEN_WHILE_ID]		=		default_action;
	semantic_functions_tokens 		 [0][19][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][21][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][21][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][21][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][22][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][22][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_BREAK_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_FOR_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_FUNCTION_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_IF_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_LOCAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_REPEAT_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_RETURN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][23][APE_TOKEN_WHILE_ID]		=		default_action;
	semantic_functions_tokens 		 [0][25][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][25][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_BREAK_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_FOR_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_FUNCTION_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_IF_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_LOCAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_REPEAT_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_RETURN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][26][APE_TOKEN_WHILE_ID]		=		default_action;
	semantic_functions_tokens 		 [0][27][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][28][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][30][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][30][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][30][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][31][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][31][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][32][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][33][APE_TOKEN_END_ID]		=		default_action;
	semantic_functions_tokens 		 [0][34][APE_TOKEN_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][35][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][35][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][35][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_BREAK_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_FOR_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_FUNCTION_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_IF_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_LOCAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_REPEAT_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_RETURN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][37][APE_TOKEN_WHILE_ID]		=		default_action;
	semantic_functions_tokens 		 [0][38][APE_TOKEN_FECHA_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][39][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][39][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][41][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_BREAK_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_FOR_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_FUNCTION_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_IF_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_LOCAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_REPEAT_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_RETURN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][42][APE_TOKEN_WHILE_ID]		=		default_action;
	semantic_functions_tokens 		 [0][43][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][43][APE_TOKEN_DOIS_PONTOS_ID]		=		default_action;
	semantic_functions_tokens 		 [0][43][APE_TOKEN_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][44][APE_TOKEN_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][44][APE_TOKEN_IN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][44][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][45][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][48][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][48][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][49][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][51][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][51][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][52][APE_TOKEN_DO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][53][APE_TOKEN_IN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][53][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][54][APE_TOKEN_THEN_ID]		=		default_action;
	semantic_functions_tokens 		 [0][56][APE_TOKEN_ELSEIF_ID]		=		default_action;
	semantic_functions_tokens 		 [0][56][APE_TOKEN_ELSE_ID]		=		default_action;
	semantic_functions_tokens 		 [0][56][APE_TOKEN_END_ID]		=		default_action;
	semantic_functions_tokens 		 [0][57][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][57][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][57][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][57][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][57][APE_TOKEN_DOIS_PONTOS_ID]		=		default_action;
	semantic_functions_tokens 		 [0][57][APE_TOKEN_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][57][APE_TOKEN_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][57][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][59][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][60][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][60][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][60][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][60][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][60][APE_TOKEN_DOIS_PONTOS_ID]		=		default_action;
	semantic_functions_tokens 		 [0][60][APE_TOKEN_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][61][APE_TOKEN_UNTIL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][62][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][64][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][65][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][65][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][65][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][66][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [0][68][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][68][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][68][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][69][APE_TOKEN_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [0][70][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][70][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][70][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][72][APE_TOKEN_FECHA_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][74][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][75][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][75][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][75][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][75][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][75][APE_TOKEN_DOIS_PONTOS_ID]		=		default_action;
	semantic_functions_tokens 		 [0][75][APE_TOKEN_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [0][76][APE_TOKEN_FECHA_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][77][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [0][77][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [0][79][APE_TOKEN_FECHA_COLCHETES_ID]		=		default_action;
	
	/* machine transitions */
	semantic_functions_machines 		 [0][2][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][3][APE_MACHINE_BLOCO_ID]		=		default_action;
	semantic_functions_machines 		 [0][4][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][5][APE_MACHINE_BLOCO_ID]		=		default_action;
	semantic_functions_machines 		 [0][6][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][10][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][12][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][13][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][16][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][17][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][24][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][29][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][36][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][40][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][46][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][47][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][50][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][55][APE_MACHINE_BLOCO_ID]		=		default_action;
	semantic_functions_machines 		 [0][58][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][62][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][63][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][65][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][67][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][71][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][73][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [0][78][APE_MACHINE_EXP_ID]		=		default_action;
	
	/* ações semânticas de saída */
	semantic_funcions_saida 		 [0][0]		=		default_action;
	semantic_funcions_saida 		 [0][1]		=		default_action;
	semantic_funcions_saida 		 [0][2]		=		default_action;
	semantic_funcions_saida 		 [0][3]		=		default_action;
	semantic_funcions_saida 		 [0][4]		=		default_action;
	semantic_funcions_saida 		 [0][5]		=		default_action;
	semantic_funcions_saida 		 [0][6]		=		default_action;
	semantic_funcions_saida 		 [0][7]		=		default_action;
	semantic_funcions_saida 		 [0][8]		=		default_action;
	semantic_funcions_saida 		 [0][9]		=		default_action;
	semantic_funcions_saida 		 [0][10]		=		default_action;
	semantic_funcions_saida 		 [0][11]		=		default_action;
	semantic_funcions_saida 		 [0][12]		=		default_action;
	semantic_funcions_saida 		 [0][13]		=		default_action;
	semantic_funcions_saida 		 [0][14]		=		default_action;
	semantic_funcions_saida 		 [0][15]		=		default_action;
	semantic_funcions_saida 		 [0][16]		=		default_action;
	semantic_funcions_saida 		 [0][17]		=		default_action;
	semantic_funcions_saida 		 [0][18]		=		default_action;
	semantic_funcions_saida 		 [0][19]		=		default_action;
	semantic_funcions_saida 		 [0][20]		=		default_action;
	semantic_funcions_saida 		 [0][21]		=		default_action;
	semantic_funcions_saida 		 [0][22]		=		default_action;
	semantic_funcions_saida 		 [0][23]		=		default_action;
	semantic_funcions_saida 		 [0][24]		=		default_action;
	semantic_funcions_saida 		 [0][25]		=		default_action;
	semantic_funcions_saida 		 [0][26]		=		default_action;
	semantic_funcions_saida 		 [0][27]		=		default_action;
	semantic_funcions_saida 		 [0][28]		=		default_action;
	semantic_funcions_saida 		 [0][29]		=		default_action;
	semantic_funcions_saida 		 [0][30]		=		default_action;
	semantic_funcions_saida 		 [0][31]		=		default_action;
	semantic_funcions_saida 		 [0][32]		=		default_action;
	semantic_funcions_saida 		 [0][33]		=		default_action;
	semantic_funcions_saida 		 [0][34]		=		default_action;
	semantic_funcions_saida 		 [0][35]		=		default_action;
	semantic_funcions_saida 		 [0][36]		=		default_action;
	semantic_funcions_saida 		 [0][37]		=		default_action;
	semantic_funcions_saida 		 [0][38]		=		default_action;
	semantic_funcions_saida 		 [0][39]		=		default_action;
	semantic_funcions_saida 		 [0][40]		=		default_action;
	semantic_funcions_saida 		 [0][41]		=		default_action;
	semantic_funcions_saida 		 [0][42]		=		default_action;
	semantic_funcions_saida 		 [0][43]		=		default_action;
	semantic_funcions_saida 		 [0][44]		=		default_action;
	semantic_funcions_saida 		 [0][45]		=		default_action;
	semantic_funcions_saida 		 [0][46]		=		default_action;
	semantic_funcions_saida 		 [0][47]		=		default_action;
	semantic_funcions_saida 		 [0][48]		=		default_action;
	semantic_funcions_saida 		 [0][49]		=		default_action;
	semantic_funcions_saida 		 [0][50]		=		default_action;
	semantic_funcions_saida 		 [0][51]		=		default_action;
	semantic_funcions_saida 		 [0][52]		=		default_action;
	semantic_funcions_saida 		 [0][53]		=		default_action;
	semantic_funcions_saida 		 [0][54]		=		default_action;
	semantic_funcions_saida 		 [0][55]		=		default_action;
	semantic_funcions_saida 		 [0][56]		=		default_action;
	semantic_funcions_saida 		 [0][57]		=		default_action;
	semantic_funcions_saida 		 [0][58]		=		default_action;
	semantic_funcions_saida 		 [0][59]		=		default_action;
	semantic_funcions_saida 		 [0][60]		=		default_action;
	semantic_funcions_saida 		 [0][61]		=		default_action;
	semantic_funcions_saida 		 [0][62]		=		default_action;
	semantic_funcions_saida 		 [0][63]		=		default_action;
	semantic_funcions_saida 		 [0][64]		=		default_action;
	semantic_funcions_saida 		 [0][65]		=		default_action;
	semantic_funcions_saida 		 [0][66]		=		default_action;
	semantic_funcions_saida 		 [0][67]		=		default_action;
	semantic_funcions_saida 		 [0][68]		=		default_action;
	semantic_funcions_saida 		 [0][69]		=		default_action;
	semantic_funcions_saida 		 [0][70]		=		default_action;
	semantic_funcions_saida 		 [0][71]		=		default_action;
	semantic_funcions_saida 		 [0][72]		=		default_action;
	semantic_funcions_saida 		 [0][73]		=		default_action;
	semantic_funcions_saida 		 [0][74]		=		default_action;
	semantic_funcions_saida 		 [0][75]		=		default_action;
	semantic_funcions_saida 		 [0][76]		=		default_action;
	semantic_funcions_saida 		 [0][77]		=		default_action;
	semantic_funcions_saida 		 [0][78]		=		default_action;
	semantic_funcions_saida 		 [0][79]		=		default_action;
	
	/* Machine 1: exp */
	
	/* token transitions */
	semantic_functions_tokens 		 [1][0][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_FALSE_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_FUNCTION_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_JOGO_DA_VELHA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_NIL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_NOT_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_NUMERO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_SUBTRACAO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][0][APE_TOKEN_TRUE_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_ACENTO_CIRCUNFLEXO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_AND_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_DIVISAO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_IGUAL_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_MAIOR_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_MAIOR_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_MENOR_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_MENOR_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_MULTIPLICACAO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_OR_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_PONTO_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_PORCENTAGEM_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_SOMA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_SUBTRACAO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][1][APE_TOKEN_TIO_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][2][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_ACENTO_CIRCUNFLEXO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_AND_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_DIVISAO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_DOIS_PONTOS_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_IGUAL_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_MAIOR_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_MAIOR_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_MENOR_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_MENOR_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_MULTIPLICACAO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_OR_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_PONTO_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_PORCENTAGEM_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_SOMA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_SUBTRACAO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][4][APE_TOKEN_TIO_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][5][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][5][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][5][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [1][6][APE_TOKEN_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][7][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][7][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][7][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][9][APE_TOKEN_FECHA_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][11][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][13][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [1][14][APE_TOKEN_ABRE_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][14][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][14][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [1][15][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [1][16][APE_TOKEN_ABRE_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][16][APE_TOKEN_ABRE_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][16][APE_TOKEN_CADEIA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][17][APE_TOKEN_IGUAL_ID]		=		default_action;
	semantic_functions_tokens 		 [1][18][APE_TOKEN_FECHA_CHAVES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][18][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][18][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][20][APE_TOKEN_FECHA_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][22][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][22][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][24][APE_TOKEN_FECHA_COLCHETES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][25][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][26][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][26][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [1][26][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		default_action;
	semantic_functions_tokens 		 [1][27][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][28][APE_TOKEN_FECHA_PARENTESES_ID]		=		default_action;
	semantic_functions_tokens 		 [1][28][APE_TOKEN_VIRGULA_ID]		=		default_action;
	semantic_functions_tokens 		 [1][30][APE_TOKEN_END_ID]		=		default_action;
	semantic_functions_tokens 		 [1][31][APE_TOKEN_NOME_ID]		=		default_action;
	semantic_functions_tokens 		 [1][31][APE_TOKEN_PONTO_PONTO_PONTO_ID]		=		default_action;
	
	/* machine transitions */
	semantic_functions_machines 		 [1][3][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][5][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][8][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][10][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][11][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][12][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][14][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][19][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][21][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][23][APE_MACHINE_EXP_ID]		=		default_action;
	semantic_functions_machines 		 [1][29][APE_MACHINE_BLOCO_ID]		=		default_action;
	
	/* ações semânticas de saída */
	semantic_funcions_saida 		 [1][0]		=		default_action;
	semantic_funcions_saida 		 [1][1]		=		default_action;
	semantic_funcions_saida 		 [1][2]		=		default_action;
	semantic_funcions_saida 		 [1][3]		=		default_action;
	semantic_funcions_saida 		 [1][4]		=		default_action;
	semantic_funcions_saida 		 [1][5]		=		default_action;
	semantic_funcions_saida 		 [1][6]		=		default_action;
	semantic_funcions_saida 		 [1][7]		=		default_action;
	semantic_funcions_saida 		 [1][8]		=		default_action;
	semantic_funcions_saida 		 [1][9]		=		default_action;
	semantic_funcions_saida 		 [1][10]		=		default_action;
	semantic_funcions_saida 		 [1][11]		=		default_action;
	semantic_funcions_saida 		 [1][12]		=		default_action;
	semantic_funcions_saida 		 [1][13]		=		default_action;
	semantic_funcions_saida 		 [1][14]		=		default_action;
	semantic_funcions_saida 		 [1][15]		=		default_action;
	semantic_funcions_saida 		 [1][16]		=		default_action;
	semantic_funcions_saida 		 [1][17]		=		default_action;
	semantic_funcions_saida 		 [1][18]		=		default_action;
	semantic_funcions_saida 		 [1][19]		=		default_action;
	semantic_funcions_saida 		 [1][20]		=		default_action;
	semantic_funcions_saida 		 [1][21]		=		default_action;
	semantic_funcions_saida 		 [1][22]		=		default_action;
	semantic_funcions_saida 		 [1][23]		=		default_action;
	semantic_funcions_saida 		 [1][24]		=		default_action;
	semantic_funcions_saida 		 [1][25]		=		default_action;
	semantic_funcions_saida 		 [1][26]		=		default_action;
	semantic_funcions_saida 		 [1][27]		=		default_action;
	semantic_funcions_saida 		 [1][28]		=		default_action;
	semantic_funcions_saida 		 [1][29]		=		default_action;
	semantic_funcions_saida 		 [1][30]		=		default_action;
	semantic_funcions_saida 		 [1][31]		=		default_action;
}

//////////////////////////////////////////////////////////