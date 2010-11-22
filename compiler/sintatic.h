#ifndef SINTATIC_H
#define SINTATIC_H

/*
 *  sintatic.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos on 20/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "token.h"
#include "analyser.h"
#include "tables.h"
#include "ape.h"


//Machine IDs
#define DECLARACOES_MACHINE_ID			0
#define PARAMETROS_MACHINE_ID			1
#define COMANDOS_MACHINE_ID				2
#define EXPRESSAO_MACHINE_ID			3
#define PROGRAMA_MACHINE_ID				4
#define EXPRESSAOBOOLEANA_MACHINE_ID	5
#define TEXTO_MACHINE_ID				6




//Uncle CakePub!!(huehueahuehuae) talvez esses nomes aqui estejam ruins... nao sei dirieot como nomear essa estrutura...pq isso nao é o automato de pilha estrut.
//em si né, é só a estrutura q vai fazendo a leitura do APE.

typedef struct sintatic_reader {
	int next_state;
	int current_state;
	//int id_sementic_actions;
	int id_machine;
	//Token token;
} Sintatic;


/* global sintatic variable */
Sintatic sintatic;









void start_sintatic();

void call_semantic_actions(int id);









#endif