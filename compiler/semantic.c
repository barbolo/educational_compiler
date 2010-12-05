/*
 *  semantic.c
 *  compiler
 *
 *  Created by Rafael Barbolo Lopes on 04/12/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "semantic.h"

void initialize_semantic() {
	
	current_symbol_table = nova_tabela_de_simbolos();
	
	initialize_semantic_tables();
	
	write("\t\t@\t/0\n");
	write("\t\tSC\tmain\n");
	write("\n");
	write("main\tK\t\t/0\n");
}