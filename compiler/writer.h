#ifndef WRITER_H
#define WRITER_H

/*
 *  writer.h
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 04/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>

FILE *output;

void initialize_writer(char * path);

void close_writer();

void write(char * content);

#endif