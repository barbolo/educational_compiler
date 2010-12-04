/*
 *  writer.c
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 04/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "writer.h"

void initialize_writer(char * path) {
	output = fopen(path, "w");
}

void close_writer() {
	fclose(output);
}

void write(char * content) {
	fprintf(output, content);
}