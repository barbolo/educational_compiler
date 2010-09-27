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

#include <stdio.h>

struct reader {
	char last;
	char current;
	char next;
};

typedef struct reader reader_type;


int first_time;
FILE * file_pointer;



/*****************************************************************************
 name: get_next_char
 purpose: get the next char from the file being scanend.
 args: filename --> name of the file to be read and the structure where the chars are stored, read_head;
 returns: reader_type read_head.
 *****************************************************************************/
reader_type get_next_char(char *filename, reader_type read_head);

/*****************************************************************************
 name: init_reader
 purpose: init_reader variables.
 args: nothin.g
 returns: nothing.
 *****************************************************************************/
void init_reader();



#endif