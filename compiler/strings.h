#ifndef STRING_H
#define STRING_H

/*
 *  strings.h
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 27/09/10
 *
 */

#include <stdlib.h>

/*****************************************************************************
 name: strcmp
 purpose: compares two string and return 1 if they have the same value and 0 if not.
 args: string s1 and string s2
 returns: true or false (1 or 0)
 *****************************************************************************/

int strcmp(char *s1, char *s2);

int strlen(char * src);

char *strcpy(char * src);

#endif