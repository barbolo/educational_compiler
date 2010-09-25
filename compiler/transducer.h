#ifndef TRANSDUCER_H
#define TRANSDUCER_H



/*
 *  transducer.h
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 *
 *	The transducer is an implementation of a finite automata.
 *	It offers a function that receives the actual STATE of the automata and
 *	the INPUT char, and it returns the NEXT_STATE and the OUTPUT.
 *
 *	The OUTPUT may be a token type or an empty string.
 *
 */

// preciso de uma tabela de transicoes
// preciso de uma tabela de tipos de tokens
// tabela de estado? acho que fica na propria de transicoes
// método "add_transition", "add_state". Entrada é sempre um char. saída é um id da tabela de tipos de tokens ou -1.

typedef int State;
typedef int TokenType;

struct Output {
	State state;
	TokenType type;
};




Por exemplo, se no estado 1, para qualquer entrada de A a Z for para o estado 2, eu só faço:
for(i=(int)'A'; i <= (int)'Z'; i++) {
	tabelaTransicao[1][i] = 2;
}

int 


#endif