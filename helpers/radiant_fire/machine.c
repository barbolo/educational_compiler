//////////////////////////////////////////////////////////
////////// GENERATED BY RADIANT FIRE LOADER //////////////
//////////////////////////////////////////////////////////

void init_ape_machines() {
	/* load machines */
  Machine programa, comando, expressao, condicao;
  

	/* Machine 0: programa */
  programa.machine_id = APE_MACHINE_PROGRAMA_ID; // 0
  programa.initial_state = 0;
  programa.current_state = 0;
  initialize_machine_transitions(&programa);
	programa.final_states[0] = 12;
	programa.final_states[1] = -1;

	/* token transitions */
	programa.token_transitions		[0][APE_TOKEN_FUNCTIONS_ID]		=		1;
	programa.token_transitions		[1][APE_TOKEN_BOOLEAN_ID]		=		2;
	programa.token_transitions		[1][APE_TOKEN_CHAR_ID]		=		2;
	programa.token_transitions		[1][APE_TOKEN_INT_ID]		=		2;
	programa.token_transitions		[1][APE_TOKEN_MAIN_ID]		=		3;
	programa.token_transitions		[1][APE_TOKEN_VOID_ID]		=		2;
	programa.token_transitions		[2][APE_TOKEN_ID_ID]		=		4;
	programa.token_transitions		[3][APE_TOKEN_ABRE_CHAVES_ID]		=		5;
	programa.token_transitions		[4][APE_TOKEN_ABRE_PARENTESES_ID]		=		6;
	programa.token_transitions		[5][APE_TOKEN_BEGIN_ID]		=		9;
	programa.token_transitions		[5][APE_TOKEN_BOOLEAN_ID]		=		7;
	programa.token_transitions		[5][APE_TOKEN_CHAR_ID]		=		7;
	programa.token_transitions		[5][APE_TOKEN_INT_ID]		=		7;
	programa.token_transitions		[5][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		8;
	programa.token_transitions		[6][APE_TOKEN_BOOLEAN_ID]		=		10;
	programa.token_transitions		[6][APE_TOKEN_CHAR_ID]		=		10;
	programa.token_transitions		[6][APE_TOKEN_FECHA_PARENTESES_ID]		=		11;
	programa.token_transitions		[6][APE_TOKEN_INT_ID]		=		10;
	programa.token_transitions		[7][APE_TOKEN_ID_ID]		=		18;
	programa.token_transitions		[8][APE_TOKEN_BEGIN_ID]		=		9;
	programa.token_transitions		[9][APE_TOKEN_FECHA_CHAVES_ID]		=		12;
	programa.token_transitions		[10][APE_TOKEN_ID_ID]		=		24;
	programa.token_transitions		[11][APE_TOKEN_ABRE_CHAVES_ID]		=		13;
	programa.token_transitions		[13][APE_TOKEN_BEGIN_ID]		=		16;
	programa.token_transitions		[13][APE_TOKEN_BOOLEAN_ID]		=		14;
	programa.token_transitions		[13][APE_TOKEN_CHAR_ID]		=		14;
	programa.token_transitions		[13][APE_TOKEN_INT_ID]		=		14;
	programa.token_transitions		[13][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		15;
	programa.token_transitions		[14][APE_TOKEN_ID_ID]		=		22;
	programa.token_transitions		[15][APE_TOKEN_BEGIN_ID]		=		16;
	programa.token_transitions		[16][APE_TOKEN_FECHA_CHAVES_ID]		=		1;
	programa.token_transitions		[16][APE_TOKEN_RETURN_ID]		=		17;
	programa.token_transitions		[18][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		8;
	programa.token_transitions		[18][APE_TOKEN_VIRGULA_ID]		=		20;
	programa.token_transitions		[19][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		21;
	programa.token_transitions		[20][APE_TOKEN_BOOLEAN_ID]		=		7;
	programa.token_transitions		[20][APE_TOKEN_CHAR_ID]		=		7;
	programa.token_transitions		[20][APE_TOKEN_INT_ID]		=		7;
	programa.token_transitions		[21][APE_TOKEN_FECHA_CHAVES_ID]		=		1;
	programa.token_transitions		[22][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		15;
	programa.token_transitions		[22][APE_TOKEN_VIRGULA_ID]		=		23;
	programa.token_transitions		[23][APE_TOKEN_BOOLEAN_ID]		=		14;
	programa.token_transitions		[23][APE_TOKEN_CHAR_ID]		=		14;
	programa.token_transitions		[23][APE_TOKEN_INT_ID]		=		14;
	programa.token_transitions		[24][APE_TOKEN_FECHA_PARENTESES_ID]		=		11;
	programa.token_transitions		[24][APE_TOKEN_VIRGULA_ID]		=		25;
	programa.token_transitions		[25][APE_TOKEN_BOOLEAN_ID]		=		10;
	programa.token_transitions		[25][APE_TOKEN_CHAR_ID]		=		10;
	programa.token_transitions		[25][APE_TOKEN_INT_ID]		=		10;

	/* machine transitions */
	programa.machine_transitions		[9][APE_MACHINE_COMANDO_ID]		=		9;
	programa.machine_transitions		[16][APE_MACHINE_COMANDO_ID]		=		16;
	programa.machine_transitions		[17][APE_MACHINE_EXPRESSAO_ID]		=		19;

	/* Machine 1: comando */
  comando.machine_id = APE_MACHINE_COMANDO_ID; // 1
  comando.initial_state = 0;
  comando.current_state = 0;
  initialize_machine_transitions(&comando);
	comando.final_states[0] = 11;
	comando.final_states[1] = 19;
	comando.final_states[2] = -1;

	/* token transitions */
	comando.token_transitions		[0][APE_TOKEN_ID_ID]		=		1;
	comando.token_transitions		[0][APE_TOKEN_IF_ID]		=		2;
	comando.token_transitions		[0][APE_TOKEN_PRINT_ID]		=		5;
	comando.token_transitions		[0][APE_TOKEN_SCAN_ID]		=		4;
	comando.token_transitions		[0][APE_TOKEN_WHILE_ID]		=		3;
	comando.token_transitions		[1][APE_TOKEN_ABRE_PARENTESES_ID]		=		7;
	comando.token_transitions		[1][APE_TOKEN_IGUAL_ID]		=		6;
	comando.token_transitions		[2][APE_TOKEN_ABRE_PARENTESES_ID]		=		13;
	comando.token_transitions		[3][APE_TOKEN_ABRE_PARENTESES_ID]		=		24;
	comando.token_transitions		[4][APE_TOKEN_ABRE_PARENTESES_ID]		=		16;
	comando.token_transitions		[5][APE_TOKEN_ABRE_PARENTESES_ID]		=		8;
	comando.token_transitions		[7][APE_TOKEN_ID_ID]		=		9;
	comando.token_transitions		[8][APE_TOKEN_STRING_ID]		=		10;
	comando.token_transitions		[9][APE_TOKEN_FECHA_PARENTESES_ID]		=		11;
	comando.token_transitions		[10][APE_TOKEN_FECHA_PARENTESES_ID]		=		12;
	comando.token_transitions		[10][APE_TOKEN_SOMA_ID]		=		8;
	comando.token_transitions		[12][APE_TOKEN_PONTO_E_VIRGULA_ID]		=		11;
	comando.token_transitions		[14][APE_TOKEN_FECHA_PARENTESES_ID]		=		15;
	comando.token_transitions		[15][APE_TOKEN_ABRE_CHAVES_ID]		=		17;
	comando.token_transitions		[16][APE_TOKEN_BOOLEAN_ID]		=		18;
	comando.token_transitions		[16][APE_TOKEN_CHAR_ID]		=		18;
	comando.token_transitions		[16][APE_TOKEN_INT_ID]		=		18;
	comando.token_transitions		[17][APE_TOKEN_FECHA_CHAVES_ID]		=		19;
	comando.token_transitions		[18][APE_TOKEN_VIRGULA_ID]		=		20;
	comando.token_transitions		[19][APE_TOKEN_ELSE_ID]		=		21;
	comando.token_transitions		[20][APE_TOKEN_ID_ID]		=		22;
	comando.token_transitions		[21][APE_TOKEN_ABRE_CHAVES_ID]		=		23;
	comando.token_transitions		[22][APE_TOKEN_FECHA_PARENTESES_ID]		=		12;
	comando.token_transitions		[23][APE_TOKEN_FECHA_CHAVES_ID]		=		11;
	comando.token_transitions		[25][APE_TOKEN_FECHA_PARENTESES_ID]		=		21;

	/* machine transitions */
	comando.machine_transitions		[6][APE_MACHINE_EXPRESSAO_ID]		=		12;
	comando.machine_transitions		[7][APE_MACHINE_CONDICAO_ID]		=		9;
	comando.machine_transitions		[7][APE_MACHINE_EXPRESSAO_ID]		=		9;
	comando.machine_transitions		[8][APE_MACHINE_CONDICAO_ID]		=		10;
	comando.machine_transitions		[8][APE_MACHINE_EXPRESSAO_ID]		=		10;
	comando.machine_transitions		[13][APE_MACHINE_CONDICAO_ID]		=		14;
	comando.machine_transitions		[17][APE_MACHINE_COMANDO_ID]		=		17;
	comando.machine_transitions		[23][APE_MACHINE_COMANDO_ID]		=		23;
	comando.machine_transitions		[24][APE_MACHINE_CONDICAO_ID]		=		25;

	/* Machine 2: expressao */
  expressao.machine_id = APE_MACHINE_EXPRESSAO_ID; // 2
  expressao.initial_state = 0;
  expressao.current_state = 0;
  initialize_machine_transitions(&expressao);
	expressao.final_states[0] = 2;
	expressao.final_states[1] = 3;
	expressao.final_states[2] = -1;

	/* token transitions */
	expressao.token_transitions		[0][APE_TOKEN_ABRE_PARENTESES_ID]		=		1;
	expressao.token_transitions		[0][APE_TOKEN_ID_ID]		=		2;
	expressao.token_transitions		[0][APE_TOKEN_INTEIRO_ID]		=		3;
	expressao.token_transitions		[2][APE_TOKEN_ABRE_PARENTESES_ID]		=		5;
	expressao.token_transitions		[2][APE_TOKEN_DIVISAO_ID]		=		0;
	expressao.token_transitions		[2][APE_TOKEN_MULTIPLICACAO_ID]		=		0;
	expressao.token_transitions		[2][APE_TOKEN_SOMA_ID]		=		0;
	expressao.token_transitions		[2][APE_TOKEN_SUBTRACAO_ID]		=		0;
	expressao.token_transitions		[3][APE_TOKEN_DIVISAO_ID]		=		0;
	expressao.token_transitions		[3][APE_TOKEN_MULTIPLICACAO_ID]		=		0;
	expressao.token_transitions		[3][APE_TOKEN_SOMA_ID]		=		0;
	expressao.token_transitions		[3][APE_TOKEN_SUBTRACAO_ID]		=		0;
	expressao.token_transitions		[4][APE_TOKEN_FECHA_PARENTESES_ID]		=		3;
	expressao.token_transitions		[5][APE_TOKEN_ID_ID]		=		4;

	/* machine transitions */
	expressao.machine_transitions		[1][APE_MACHINE_EXPRESSAO_ID]		=		4;
	expressao.machine_transitions		[5][APE_MACHINE_CONDICAO_ID]		=		4;
	expressao.machine_transitions		[5][APE_MACHINE_EXPRESSAO_ID]		=		4;

	/* Machine 3: condicao */
  condicao.machine_id = APE_MACHINE_CONDICAO_ID; // 3
  condicao.initial_state = 0;
  condicao.current_state = 0;
  initialize_machine_transitions(&condicao);
	condicao.final_states[0] = 4;
	condicao.final_states[1] = -1;

	/* token transitions */
	condicao.token_transitions		[0][APE_TOKEN_BOOLEANO_ID]		=		4;
	condicao.token_transitions		[0][APE_TOKEN_NOT_ID]		=		3;
	condicao.token_transitions		[1][APE_TOKEN_DIFERENTE_ID]		=		5;
	condicao.token_transitions		[1][APE_TOKEN_IGUAL_IGUAL_ID]		=		5;
	condicao.token_transitions		[1][APE_TOKEN_MAIOR_ID]		=		5;
	condicao.token_transitions		[1][APE_TOKEN_MAIOR_IGUAL_ID]		=		5;
	condicao.token_transitions		[1][APE_TOKEN_MENOR_ID]		=		5;
	condicao.token_transitions		[1][APE_TOKEN_MENOR_IGUAL_ID]		=		5;
	condicao.token_transitions		[2][APE_TOKEN_AND_ID]		=		8;
	condicao.token_transitions		[2][APE_TOKEN_OR_ID]		=		8;
	condicao.token_transitions		[3][APE_TOKEN_ABRE_PARENTESES_ID]		=		6;
	condicao.token_transitions		[7][APE_TOKEN_FECHA_PARENTESES_ID]		=		4;

	/* machine transitions */
	condicao.machine_transitions		[0][APE_MACHINE_CONDICAO_ID]		=		2;
	condicao.machine_transitions		[0][APE_MACHINE_EXPRESSAO_ID]		=		1;
	condicao.machine_transitions		[5][APE_MACHINE_EXPRESSAO_ID]		=		4;
	condicao.machine_transitions		[6][APE_MACHINE_CONDICAO_ID]		=		7;
	condicao.machine_transitions		[8][APE_MACHINE_CONDICAO_ID]		=		4;

  /* initialize ape machines */
  ape_parser.initial_machine = programa;
  ape_parser.current_machine = programa;
	ape_parser.machines[0] = programa;
	ape_parser.machines[1] = comando;
	ape_parser.machines[2] = expressao;
	ape_parser.machines[3] = condicao;
}

//////////////////////////////////////////////////////////