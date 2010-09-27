/*
 *  reader.c
 *  compilador
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

void init_reader(char *filename) {
	
	/* open file */
	reading_head.file_pointer = fopen(filename, "r");
	
	/* raise an error and end the execution if the file could not be opened */
	if( reading_head.file_pointer == NULL ) {
		printf("ERROR: \n\tFile \"%s\" could not be opened. \n\tCheck its path, name and extension.\n",filename);
		exit(1);
	}
	
	/* update the reading head */
	reading_head.previous = 0;
	reading_head.current = fgetc(reading_head.file_pointer);
	reading_head.next = fgetc(reading_head.file_pointer);
	reading_head.line = 1;
	reading_head.column = 1;
	
}

void read_next_char() {
	/* update the heading read */
	reading_head.previous = reading_head.current;
	reading_head.current = reading_head.next;
	reading_head.next = fgetc(reading_head.file_pointer);
	
	if (reading_head.previous == '\n') {
		reading_head.line += 1;
		reading_head.column = 0;
	}
	reading_head.column += 1;
}