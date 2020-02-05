#ifndef RGB_H

	#define LN_SCREEN 600		// Número de pixeis de comprimento da tela
	#define H_SCREEN 600		// Número de pixeis de altura da tela

	#define LOOP_SIZE 100       //Quantidade de repetições

	typedef struct pixel PIXEL; //Struct que guarda cada pixel
	struct pixel{
	    int x;
	    int y;
	    int r;
	    int g;
	    int b;
	};

	int** pop(); //Cria a população inicial com números aleatórios de RGB

	int avaliacao(int* individuo); //Fitness function

	int geradores(int** populacao); //Gera os pais

	int* fica_melhor(int** populacao); //Faz com que o melhor indivíduo não seja perdido

	int* ind(int** populacao); //Cria um novo indivíduo cruzando mãe e pai

	void muta_ae(int** populacao, int contador); //Mutação

	int** nova_pop(int** populacao, int contador); //Cria nova população

	void imprime(int** populacao); //Imprime na tela a população em questão

#endif



