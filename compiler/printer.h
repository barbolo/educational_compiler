#ifndef PRINTER_H
#define PRINTER_H

/*
 *  printer.h
 *  compilador
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

//#include "stringtcc.h"

/*****************************************************************************
 name: print_text
 purpose: to print a text.
 args: text to be printed.
 returns: nothing, but prints the text given as argument.
 *****************************************************************************/
void print_text(char * str);


/*****************************************************************************
 name: print_token
 purpose: to print token type and string.
 args: Token type and token value to be printed
 returns: nothing, but prints something like: "Token ->  Type: bla_bla  Value: bla_bla"
 *****************************************************************************/
void print_token(char * type, char * value);

// QDO DEFINIR DE VEZ QUAL TIPO SERÁ CADA ARGUMENTO AÍ MUDA AQUI DIREITO. (e implementa de fato... meio ñ muito útil esse printer hehehe)

#endif