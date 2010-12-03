#ifndef ACTIONS_H
#define ACTIONS_H

/*
 *  actions.h
 *  compiler
 *
 *
 */

#include "machine.h"

void (*semantic_functions_tokens[100][100][100]) ();
void (*semantic_functions_machines[100][100][100]) ();

void default_action();

void init_semantic_actions();



//hum... vamo fazer assim:
// vo criar uma scope_hastable e uma sybol_table_hastable e deixo a hastable antiga la como antes.
//aí vai ter q fazer qdo inicia o programa ele iniciar a primeira tabela de simbolos dentro dessa hashtable dos escopos...
// cada celula desse hastable de escopos vai ter uma tabela de simbolos e ponteiros pra próxima tabela de simbolos e pra anterior.
// e qdo aparecer um { vai ter q criar e adicionar mais uma tabela de simbolos no hashtable de escopos.




//Pointer to the Symbol Table of the current scope
//hash_table * current_sybol_table_scope;

//Pointer to the Symbol Table of the next scope
//hash_table * next_sybol_table_scope;

//Pointer to the Symbol Table of the last scope
//hash_table * last_sybol_table_scope;






/*
//Vou rascunhar o q deve ser feito...

-- Filipe --- pretendo fazer isso hj ---

- definir os campos da tabelade simbolos, implelmeta-los e criar as funções pra manipular a T.S. e seus campos
 exemplos:
	- fç q busca na T.S. (vai ter q buscar em TODAS as TS, todos os escopos) um identificador. (toda vez q vier um identificador precisa procurar ele naS tabelaS de simbolos... se nao tiver em lugar nenhum é pq deu erro!)
	- fç q insere um dado na TS
	- fç q vincula as tabelas de simbolo dos escopos (acho q isso é qdo cria uma nova tabela pq veio um novo escopo, 
		  vc tem q atualizar a variável q diz em q escopo está atualmente e tb mandar a tabela do escopo anteriror apontar pa essa do novo escopo)
	- fç q pega cada um dos atributos
	- fç q testa se o identificador é variável
  
- verificar se um identificador já esta em uso.
 
- criar as pilhas de operadores e operandos pra poder executar as expressões. além disso tb tem q criar as fç pra manipular elas
 pra pilha é padrão...: inicia pilha, consulta pilha, empilha, desempilha.... mas tem tb as q regem o funcionamento das expressões

-- Filipe --- pretendo fazer isso hj ---
 
 
- qdo iniciar novos escopos, tem q criar a nova tabela de simbolos. sempre q vier "{" está se criando um escopo novo??????

- qdo finaliza escopos, tem q deletar a tabela de simbolos correspondente. sempre q vier "}" está se fechando um escopo??????
 
- checar os tipos dos dados nas operações
 
- podemos começar tentado gerar um código pra: main {} e ir incrementando até chegar no progrma completo.
   pelo q entendi, pra cada coisa da gramática vai ter q ver q código q deve ser gerado e q fç devem 
   ser chamadas a cada uma das transições pra poder gerar o código final (tipo o item 5.6.2 do livro do JJ).... ou seja, Tem q ser forte!!  
 
- vai ter q ter um lugar pra guardar variáeis temporárias... o livro sugere um array e um "i" q guarde a posição da variável atual... sei la se isso é bom.

- fazer a mvn imprimir uma string (tem q fazer um loop pq ela só imprime um caracter por vez... algo assim)
 
- gerenciamento de memória e prâmetros de fç ainda são misteriosos.

- arrumar completamente aquilo de nao deixar o léxico adicionar simbolos q nao est˜åo sendo delcarados e sim utilizados.
 ver arquivo syntatic.c
 nessa parte:
 
 //Decide if it is a declaration of an identifier.
 //code to do that.
 is_declaration = 1;


*/


#endif