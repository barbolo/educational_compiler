
#include <stdio.h>

#include "analyser.h"
#include "hashtable.h"


void reader_test(){	
	char letra;
    
	init_reader();
	
	while (letra != EOF) {
		//letra = get_next_char("../../teste.txt");
		printf("Char found: %c\n", letra);
	}
	
	printf("EOF: %c \n", EOF);
}



void lexical_analysis(){
    
	//char a_char;
	
	init_reader();
	//a_char = get_next_char("../../teste.txt");
	
	
	/*
	input = File.read('../resources/test_lex.poli');
    
	
    analyser = Lex::Analyser.new(input);
    
	while (token = analyser.get_next_token).type != Token::Type::END_OF_FILE {
		puts token.to_str;
	}
	*/
	
	
}



int main (int argc, const char * argv[]) {
	
	lexical_analysis();

	
	
	// testing table hash
	
	int one, two, three, result;
	
	hash_table hash_test;
	
	hash_test = init_table(hash_test);
	
	one = add(&hash_test, "casa");
	two = add(&hash_test, "casa");
	three = add(&hash_test, "amor");
	
	result = find_by_key(&hash_test, "amor");
	
	// test - end
	
    return 0;
}
