/*
 *  symbol_table.c
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 04/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "symbol_table.h"

SymbolTable * nova_tabela_de_simbolos() {
	SymbolTable * tabela = malloc(sizeof(SymbolTable));
	tabela->parent = NULL;
	tabela->child = NULL;
	tabela->nsimbolos = 0;
	return tabela;
}


int pesquisa_posicao_na_tabela_de_simbolos(SymbolTable * tabela, char * nome) {
	int i;
	for (i=0; i < tabela->nsimbolos; i++) {
		if (strcmp(tabela->lines[i].nome_identificador, nome)) {
			return i;
		}
	}
	return -1;
}


int get_tipo_identificador(char * type) {
	if (strcmp(type, "void") == 0) {
		return TIPO_IDENTIFICADOR_VOID;
	}
	
	if (strcmp(type, "int") == 0) {
		return TIPO_IDENTIFICADOR_INT;
	}
	
	if (strcmp(type, "char") == 0) {
		return TIPO_IDENTIFICADOR_CHAR;
	}
	
	if (strcmp(type, "boolean") == 0) {
		return TIPO_IDENTIFICADOR_BOOLEAN;
	}	
}