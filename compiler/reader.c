/*
 *  reader.c
 *  compilador
 *
 *  Created by Filipe Morgado Simões de Campos on 24/09/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "reader.h"


void init_reader(reader_type read_head){
	
	file_pointer = NULL;
	
	first_time = 1;
	
	read_head.last = 0;
	read_head.current = 0;
	read_head.next = 0;
	
}


reader_type get_next_char(char *filename, reader_type read_head){
 
	//To use files in C programs, you must declare a file variable to use. This variable must be of type FILE, and be declared as a pointer type.

	int caracter;
	
	
	// Test if file is already opened.
	if (file_pointer == NULL) {

		file_pointer = fopen( filename, "r" );

		// Testing if file was opened successfully.
		if( file_pointer == NULL ) {
			
			printf("File, %s, can not be opened.\n",filename);
			
			read_head.current = -1;
			read_head.last = -1;
			read_head.next = -1;
			
			return read_head;
			//exit(1);
		}
	}
	
	
	// Get next char
	
	//If it is the firs time reading the file:
	if (first_time == 1) {

		caracter = 0;
		caracter = fgetc( file_pointer );
		if (caracter != EOF) {
			read_head.current = ((char)caracter);
		}
		else {
			fclose( file_pointer );
			read_head.current = EOF;
			read_head.next = EOF;
			return read_head;
		}		
		
		caracter = 0;
		caracter = fgetc( file_pointer );
		if (caracter != EOF) {
			read_head.next = ((char)caracter);
		}
		else {
			fclose( file_pointer );
			read_head.next = EOF;
			return read_head;
		}
		
		first_time = 0;
	}
	//If not, get the new char and update the old ones.
	else {
		
		//Update last
		read_head.last = read_head.current;
		
		//Update current
		if (read_head.next == EOF) {
			//avoid the program to read after EOF
			read_head.current = read_head.next;
			return read_head;
		}
		else {
			read_head.current = read_head.next;
		}

		
		//Get new one.
		caracter = 0;
		caracter = fgetc( file_pointer );
		
		if (caracter != EOF) {
			read_head.next = ((char)caracter);
		}
		else {
			fclose( file_pointer );
			read_head.next = EOF;
		}
		
	}

  return read_head;
 
 }