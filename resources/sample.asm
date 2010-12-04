		@  /0
		SC main

main	K	/0
		LD	K_0	; carrega constante 5 no acumulador
		MM	a	; armazena conteúdo do acumulador na variável a
		LD	K_1	; carrega constante 1 no acumulador
		MM	b	; armazena conteúdo do acumulador na variável b
		#	main
		HM /0


		@	/200	; começo da área de dados
a		K		=0	; declaração da variável a
b		K		=0	; declaração da variável b
K_0		K		=5 ; declaração da constante K_0
K_1		K		=1 ; declaração da constante K_1
