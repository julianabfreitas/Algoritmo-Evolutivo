#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM_POP 10

//CRIANDO POPULAÇÃO
float** pop(){ //CADA INDIVÍDUO É UMA LISTA DE NUMEROS E A A POPULAÇÃO É UMA LISTA DE INDIVÍDUOS

    float** p;
    p = (float**)malloc(NUM_POP*sizeof(float*));
    int i, j;
    for(i=0; i<NUM_POP; i++){
        p[i] = (float*)malloc(2*sizeof(float));
    }

    for(i=0; i<NUM_POP; i++){
        for(j=0; j<2; j++){
            p[i][j] = 50 - rand()%100;
        }
    }

    return p;
}

//METODO DE AVALIZAÇÃO
float avaliacao(float* individuo){
    float nota;
    nota = ((individuo[0]*individuo[0] + individuo[1] - 11)*(individuo[0]*individuo[0] + individuo[1] - 11)) +
    ((individuo[0] + individuo[1]*individuo[1] - 7)*(individuo[0] + individuo[1]*individuo[1] - 7));
    return nota;
}

//ESCOLHENDO PAIS
int geradores(float** populacao){

    int posicao1 = rand()%NUM_POP;
    int posicao2 = rand()%NUM_POP;

    float nota1 = avaliacao(populacao[posicao1]);
    float nota2 = avaliacao(populacao[posicao2]);

    if(fabs(nota1)<fabs(nota2)){
        return posicao1;
    }
    else{
        return posicao2;
    }
}

//MELHOR DE TODOS
float* fica_melhor(float** populacao){
    float* melhor_carinha = (float*)malloc(2*sizeof(float));
    int pos_melhor_nota = 0, i;
    float melhor_nota=avaliacao(populacao[0]);

    for(i=1; i<NUM_POP; i++){
        if(avaliacao(populacao[i])<melhor_nota){
            melhor_nota=avaliacao(populacao[i]);
            pos_melhor_nota=i;
        }
    }
    melhor_carinha[0] = populacao[pos_melhor_nota][0];
    melhor_carinha[1] = populacao[pos_melhor_nota][1];
    return melhor_carinha;
}

//CRIA NOVO INDIVIDUO
float* ind(float** populacao){
    float *mae = populacao[geradores(populacao)];
    float *pai = populacao[geradores(populacao)];

    float *novo_individuo = (float*)malloc(2*sizeof(float));

    novo_individuo[0] = (mae[0] + pai[0])/2;
    novo_individuo[1] = (mae[1] + pai[1])/2;

    return novo_individuo;
}

//MUTACAO
void muta_ae(float** populacao, int contador){
    int i, j, k;
    int n = pow(0.1,contador/75);
    for(i = 1; i<NUM_POP; i++){
        for(j = 0; j<2; j++){
            k = rand()%3;
            if(k == 1){
                populacao[i][j] += n;
            }
            else if(k == 2){
                populacao[i][j] -= n;
            }
        }
    }
}

//CRIA NOVA POPULACAO
float** nova_pop(float** populacao, int contador){
    float** population = (float**)malloc(NUM_POP*sizeof(float*));
    int i;
    population[0] = fica_melhor(populacao);
    for(i=1; i<NUM_POP; i++){
        population[i] = ind(populacao);
    }
    muta_ae(population, contador);
    return population;

}

//IMPRIME POPULACAO
void imprime(float** populacao){
    int i, j;

    for(i=0; i<NUM_POP; i++){
        for(j=0; j<2; j++){
            printf("%f ", populacao[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}


int main(){

    srand(time(NULL)); //INICIALIZA AS COISAS - AJUDA OS VALORES A VARIAREM BASTANTE
    float** populacao = pop();
    imprime(populacao);

    int contador = 0;
    int i;

    while(contador!=400){
        float** populacao_nova = nova_pop(populacao, contador);
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
