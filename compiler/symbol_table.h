#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

/*
 *  symbol_table.h
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 04/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "strings.h"
#include "stdlib.h"

#define TIPO_IDENTIFICADOR_INT 1
#define TIPO_IDENTIFICADOR_BOOLEAN 2
#define TIPO_IDENTIFICADOR_CHAR 3
#define TIPO_IDENTIFICADOR_VOID 3
#define TIPO_ROTULO 0
#define TIPO_VARIAVEL 1

typedef struct sl_node {
	char * nome_identificador; // nome da variável ou do rótulo
	int tipo_identificador; // tipo do identificador (int, char, boolean ou void)
	int rotulo_ou_variavel; // 0 => rótulo; 1 => variável
	
	int valor_inteiro; // guarda valor da variável quando é inteiro ou booleano
	char * valor_string; // guarda valor da variável quando é char ou string
} SymbolLine;

typedef struct st_node {
	struct st_node * child;
	struct st_node * parent;
	
	int nsimbolos;
	SymbolLine lines[100];
	
} SymbolTable;


SymbolTable * current_symbol_table;


SymbolTable * nova_tabela_de_simbolos();

int pesquisa_posicao_na_tabela_de_simbolos(SymbolTable * tabela, char * nome);

int get_tipo_identificador(char * type);


#endif