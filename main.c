#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_POP 10

//CRIANDO POPULA��O
int** pop(){ //CADA INDIV�DUO � UMA LISTA DE NUMEROS E A A POPULA��O � UMA LISTA DE INDIV�DUOS

    int** p; // p ser� nossa pop
    p = (int**)malloc(NUM_POP*sizeof(int*)); //alocando mem�ria para nossa pop
    int i, j;
    for(i=0; i<NUM_POP; i++){
        p[i] = (int*)malloc(3*sizeof(int));
    }

    for(i=0; i<NUM_POP; i++){ //gerando o genoma do indiv�duo (par�metros rgb)
        for(j=0; j<3; j++){
            p[i][j] = rand()%256; //os valores rgb v�o de 0 a 255
        }
    }

    return p;
}

//METODO DE AVALIZA��O (fitness fuction)
int avaliacao(int* individuo){
    int nota = 0; //a melhor nota � 510
    int x; //maximiza 1
    int y; //maximiza 2
    int maior, menor, medio;

    if(individuo[0]>individuo[1]){
        if(individuo[2]>individuo[0]){
            maior = 2; //o elemento que vamos maximizar
            medio = 0;
            menor = 1;
        }else{
            if(individuo[2]>individuo[1]){
                maior = 0;
                medio = 2;
                menor = 1;
            }else{
                maior = 0;
                medio = 1;
                menor = 2;
            }
        }
    }

    else if(individuo[1]>individuo[0]){
        if(individuo[2]>individuo[1]){
                maior = 2;
                medio = 1;
                menor = 0;
        }else{
            if(individuo[2]>individuo[0]){
                maior = 1;
                medio = 2;
                menor = 0;
            }else{
                maior = 1;
                medio = 0;
                menor = 2;
            }

        }
    }
    else if(individuo[0] == individuo[1]){
        if(individuo[2] > individuo[0]){
            maior = 2;
            medio = 1;
            menor = 0;
        }else{
            maior = 0;
            medio = 1;
            menor = 2;
        }
    }

    x = (255 - individuo[maior]) + individuo[medio] + individuo[menor];
    y = (255 - individuo[maior]) + (255 - individuo[medio]) + individuo[menor];

    if(x<y){
        nota = x;
    }else{
        nota = y;
    }

    return nota;
}

//GERANDO PAIS
int geradores(int** populacao){

    //Escolhe aleatoriamente dois indiv�duos da popula��o
    int posicao1 = rand()%NUM_POP;
    int posicao2 = rand()%NUM_POP;

    //Calcula a nota desses indiv�duos
    int nota1 = avaliacao(populacao[posicao1]);
    int nota2 = avaliacao(populacao[posicao2]);

    //Compara a nota desses indiv�duos e retorna o de maior nota
    if(nota1<nota2){
        return posicao1;
    }
    else{
        return posicao2;
    }
}

//MELHOR DE TODOS
int* fica_melhor(int** populacao){
    int* melhor_carinha = (int*)malloc(3*sizeof(int)); //aloca espa�o pro indiv�duo de maior nota
    int pos_melhor_nota = 0, i; //define que a primeira posi��o sempre ser� do indiv�duo de maior nota
    int melhor_nota = avaliacao(populacao[0]); //vari�vel que guarda a melhor nota para futuras compara��es
                                                 //inicialmente igualamos a melhor nota ao primeiro individuo

    //compara a nota de todos os indiv�duos da popula��o e guarda o melhor
    for(i=1; i<NUM_POP; i++){
        if(avaliacao(populacao[i])<melhor_nota){
            melhor_nota = avaliacao(populacao[i]);
            pos_melhor_nota = i;
        }
    }

    //atribuindo os par�metros ao melhor carinha
    melhor_carinha[0] = populacao[pos_melhor_nota][0];
    melhor_carinha[1] = populacao[pos_melhor_nota][1];
    melhor_carinha[2] = populacao[pos_melhor_nota][2];

    return melhor_carinha; //retorna o melhor cara
}

//CRIA NOVO INDIVIDUO
int* ind(int** populacao){

    //chama a fun��o geradores para conseguir os melhores m�e e pai
    int *mae = populacao[geradores(populacao)];
    int *pai = populacao[geradores(populacao)];

    int *novo_individuo = (int*)malloc(3*sizeof(int)); //aloca espa�o para o novo indiv�deuo

    //cruzando pais
    novo_individuo[0] = (mae[0] + pai[0])/2;
    novo_individuo[1] = (mae[1] + pai[1])/2;
    novo_individuo[2] = (mae[2] + pai[2])/2;

    return novo_individuo;
}

//MUTACAO
void muta_ae(int** populacao, int contador){
    int i, j, k; //vari�veis
    int n = 3; //varia��o
    for(i = 1; i<NUM_POP; i++){ //adicionando ou tirando 3 unidades do rgb
        for(j = 0; j<3; j++){
            k = rand()%3;
            if(k == 1){
                populacao[i][j] += n;
                if(populacao[i][j] > 255){ //verificando se passa do limite
                    populacao[i][j] -= n;
                }
            }
            else if(k == 2){
                populacao[i][j] -= n;
                if(populacao[i][j] < 0){ //verificando se passa do limite
                    populacao[i][j] += n;
                }
            }
        }
    }
}

//CRIA NOVA POPULACAO
int** nova_pop(int** populacao, int contador){
    int** population = (int**)malloc(NUM_POP*sizeof(int*)); //alocando espa�o pra popula��o inteira
    int i;
    population[0] = fica_melhor(populacao); //salvando o melhor na primeira posi��o
    for(i=1; i<NUM_POP; i++){ //colocando cada indiv�duo numa nova posi��o
        population[i] = ind(populacao);
    }
    muta_ae(population, contador); //mutando
    return population;

}

//IMPRIME POPULACAO
void imprime(int** populacao){
    int i, j;

    for(i=0; i<NUM_POP; i++){
        for(j=0; j<3; j++){
            printf("%d ", populacao[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}


int main(){

    srand(time(NULL)); //INICIALIZA AS COISAS - AJUDA OS VALORES A VARIAREM BASTANTE
    int** populacao = pop();
    imprime(populacao);

    int contador = 0;
    int i;

    while(contador!=400){
        int** populacao_nova = nova_pop(populacao, contador);
        imprime(populacao_nova);

        for(i=0; i<NUM_POP; i++){
            free(populacao[i]);
        }
        free(populacao);

        populacao = populacao_nova;

        contador++;
    }

    for(i=0; i<NUM_POP; i++){
        free(populacao[i]);
    }
    free(populacao);

    return 0;
}
