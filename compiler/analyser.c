/*
 *  analyser.c
 *  compiler
 *
 *  Created by Filipe Morgado Simões de Campos e Rafael Barbolo Lopes on 24/09/10.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "reader.h"
#include "analyser.h"
#include "tables.h"

void get_next_token() {
	
	char temp_string[500];
	char stra[3];
	int counter;
	
	token.type = TOKEN_TYPE_IGNORED;
	token.value = NULL;
	
	if (reading_head.current == EOF) {
		/* return a END_OF_FILE token if the file was completely read */
		
		token.type = TOKEN_TYPE_END_OF_FILE;
		
	} else {
		/* extract a token from file */
		
		while (reading_head.current != EOF && token.type == TOKEN_TYPE_IGNORED) {
			/* chars being discarted */
			
			/* the transducer automata will execute a transition to consume the current char */
			token.type = transducer_consume_input(reading_head.current, reading_head.next);
			
			read_next_char();
		}
		
		
		/* 
		 * the previous char will not be dicarted because it created a transition to a
		 * valid state with transducer automata
		 */
		temp_string[0] = reading_head.previous;
		counter = 1;
		
		token.line = reading_head.line;
		token.column = reading_head.column-1;
		
		while (reading_head.current != EOF && token.type == TOKEN_TYPE_INCOMPLETE) {
			/* building token */
			
			/* the transducer automata will execute a transition to consume the current char */
			token.type = transducer_consume_input(reading_head.current, reading_head.next);
			
			temp_string[counter] = reading_head.current;
			counter += 1;
			
			read_next_char();
		}

		
		/* allocate memory to token value */
		token.value = (char*) malloc(counter*sizeof(char));
		while (counter > 0) {
			/* fill each char of the token value */
			token.value[counter-1] = temp_string[counter-1];
			counter -= 1;
		}
		
		
		if (token.type == TOKEN_TYPE_IGNORED) {
			free(token.value);
			token.value = NULL;
		} else if (token.type == TOKEN_TYPE_INCOMPLETE) {
			token.type = TOKEN_TYPE_INVALID;
		} else if (token.type == TOKEN_TYPE_IDENTIFIER && (find_by_key(&table_reserved_words, token.value) >= 0)) {
			token.type = TOKEN_TYPE_RESERVED_WORD;
		}
		
		token.index = update_semantic_tables();
		
	}
	
}
