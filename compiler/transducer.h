#ifndef TRANSDUCER_H
#define TRANSDUCER_H

/*
 *  transducer.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
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

#include "token.h"

#define INVALID_STATE	-1
#define EMPTY_STRING	-1



int transitions;






/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
void init_transducer(/*  TALVEZ PASSE AQEUI UMA VARIAVEL DO TIPO TRANSDUCER_TYPE  */);



/*****************************************************************************
 name: 
 purpose: .
 args: .
 returns: .
 *****************************************************************************/
char * get_token_type_name(int token_type);




#endif