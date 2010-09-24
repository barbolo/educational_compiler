/*
 *  reader.c
 *  compilador
 *
 *  Created by Filipe Morgado Simões de Campos on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>

#include "reader.h"


void init_reader(){
	
	file_pointer = NULL;
	
	first_time = 1;
	
	reader_head.last = 0;
	reader_head.current = 0;
	reader_head.next = 0;
	
}


char get_next_char(char *filename){
 
	//To use files in C programs, you must declare a file variable to use. This variable must be of type FILE, and be declared as a pointer type.

	int caracter;
	
	
	// Test if file is already opened.
	if (file_pointer == NULL) {

		file_pointer = fopen( filename, "r" );

		// Testing if file was opened successfully.
		if( file_pointer == NULL ) {
			printf("File, %s, can not be opened.\n",filename);
			return 0;
			//exit(1);
		}
	}
	
	
	// Get next char
	
	//If it is the firs time reading the file:
	if (first_time == 1) {

		caracter = 0;
		caracter = fgetc( file_pointer );
		if (caracter != EOF) {
			reader_head.current = ((char)caracter);
		}
		else {
			fclose( file_pointer );
			return EOF;
		}		
		
		caracter = 0;
		caracter = fgetc( file_pointer );
		if (caracter != EOF) {
			reader_head.next = ((char)caracter);
		}
		else {
			fclose( file_pointer );
			return EOF;
		}
		
		first_time = 0;
	}
	//If not, get the new char and update the old ones.
	else {
		
		//Update last
		reader_head.last = reader_head.current;
		
		//Update current
		reader_head.current = reader_head.next;
		
		//Get new one.
		caracter = 0;
		caracter = fgetc( file_pointer );
		
		if (caracter != EOF) {
			reader_head.next = ((char)caracter);
		}
		else {
			fclose( file_pointer );
			reader_head.next = EOF;
		}
		
	}

  return reader_head.current;
 
 }