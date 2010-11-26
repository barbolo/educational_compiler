#include <stdio.h>
#include <stdlib.h>
#include "reader.h"
#include "token.h"
#include "analyser.h"
#include "tables.h"
#include "sintatic.h"

int main (int argc, const char * argv[]) {
	
	/* initialize the file reader */
	init_reader("../../../resources/sample.edu");
	
	/* initialize transducer automata transitions */
	initialize_transitions();
	
	/* initialize semantic tables */
	initialize_semantic_tables();
	
	// inicia as máquinas do autômato de pilha estruturado
	init_ape_machines();
	
	/* call sintatic analyser*/
	run_sintatic();
	
	return 0;
}