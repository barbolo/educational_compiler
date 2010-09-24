

#include <stdio.h>
#include "reader.h"
#include "printer.h"
#include "transducer.h"
#include "lex.h"
#include "symbols.h"



int main (int argc, const char * argv[]) {

	char letra;
    
	init_reader();

	while (letra != EOF) {
		letra = get_next_char("/Users/Filipe/Documents/0 MEUS/Poli/9 Quadrimestre/Linguagens e Compiladores - PCS2056/compilador/educational_compiler/compiler/teste.txt");
		printf("Letra encontrada: %c (apareceu algo?)\n", letra);
	}
	
	
	printf("EOF: %c \n", EOF);
	

	
	
	
	
	
	
	
	//	LOCAL PARA A QUESTÃO 8!
	
	
    return 0;
}
