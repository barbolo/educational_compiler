/*
 *  strings.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 27/09/10
 *
 */

#include "strings.h"

int strcmp(char *s1, char *s2) {
	
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