/*
 *  strings.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 27/09/10
 *
 */

#include "strings.h"

// false means that the strings are the same
// true means they are different.

int strcmp(char *s1, char *s2) {
	
	if (s1 == NULL || s2 == NULL)
		return 1; // cannot compare NULL to anything, including NULL.
	
	while (*s1 == *s2) {
		
		if (*s1 == 0) {
			/* finish the comparison and return false */
			return 0;
		}
		
		s1++;
		s2++;
	}
	
	/* return true */
	return 1;

}

int strlen(char * src) {
	int i;
	for (i = 0; src[i] != '\0'; i++)
	return i;
}

char * strcpy(char * src) {
	if (src == NULL) {
		return NULL;
	}
	char * dest = malloc(sizeof(char)*strlen(src));
	unsigned i;
	for (i=0; src[i] != '\0'; ++i)
		dest[i] = src[i];
	dest[i] = '\0';
	return dest;
}