#ifndef READER_H
#define READER_H
/*
 *  reader.h
 *  compilador
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 *
 * This file is responsable for reading the caracters from the source code and returning it 
 * to the compiler. It is specially used by the lexical analysis step.  
 *
 *
 */

struct reader {
	char last;
	char current;
	char next;
};


int first_time;
struct reader reader_head;
FILE * file_pointer;



/*****************************************************************************
 name: get_next_char
 purpose: get the next char from the file being scanend.
 args: filename --> name of the file to be read.
 returns: next char.
 *****************************************************************************/
char get_next_char(char *filename);

/*****************************************************************************
 name: init_reader
 purpose: init_reader variables.
 args: nothin.g
 returns: nothing.
 *****************************************************************************/
void init_reader();



#endif