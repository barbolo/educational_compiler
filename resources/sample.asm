		@	/0
		SC	main

main	K		/0
		LD		K_0		;	AC = K_0
		*		K_1		;	AC = AC*K_1
		MM		TEMP1		;	TEMPX = AC
		LD		TEMP1		;	AC = TEMP1
		-		K_2		;	AC = AC-K_2
		MM		TEMP2		;	TEMPX = AC
		LD	TEMP2	; carrega constante ; no acumulador
		MM	a	; armazena conteúdo do acumulador na variável a
		#	main
		HM /0


		@	/200	; começo da área de dados
a		K		=0	; declaração da variável a
K_0		K		=4 ; declaração da constante K_0
K_1		K		=5 ; declaração da constante K_1
K_2		K		=10 ; declaração da constante K_2
TEMP1		K		=0 ; declaração da variável temporária TEMP1
TEMP2		K		=0 ; declaração da variável temporária TEMP2
