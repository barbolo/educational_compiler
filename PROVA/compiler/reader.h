#ifndef READER_H
#define READER_H
/*
 *  reader.h
 *  compilador
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 *
 * This file is responsable for reading the caracters from the source code and returning it 
 * to the compiler. It is specially used by the lexical analysis step.  
 *
 *
 */


/* struct used to read a file */
typedef struct reader_type {
	FILE * file_pointer; // pointer to the file being read

	/* last, current and next chars */
	char previous; // last char
	char current;
	char next;
	
	/* column and line of the cursor in the file */
	int line;
	int column;
} Reader;


/* global variable: reading head */
Reader reading_head;


/*****************************************************************************
 name: read_next_char
 purpose: read the next char from the file being scanned.
 args: 
 returns: 
 *****************************************************************************/
void read_next_char();

/*****************************************************************************
 name: init_reader
 purpose: initialize the file reader.
 args: filename
 returns: 
 *****************************************************************************/
void init_reader(char *filename);



#endif