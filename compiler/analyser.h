#ifndef ANALYSER_H
#define ANALYSER_H

/*
 *  analyser.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>

#include "reader.h"
#include "token.h"
#include "transducer.h"

reader_type read_head;

token_type token;
//transducer_type transducer;            !!!!!!!!!!!!!!!          liberar essa linha depois q o transducer tiver pronto        !!!!!!!!!!!!!!!

// é o que vem la do reader... no caso do ruby era todo o condeúdo do arquivos
//@content = content
// ???
//@fixed_content = @content + ' '







/*****************************************************************************
 name: get_next_token
 purpose: get the next token from the source code.
 args: 
 returns: next token.
 *****************************************************************************/

token_type get_next_token();



#endif