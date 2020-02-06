#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <GL/glut.h>
#include "rgb.h"

using namespace std;

static int win(0); //Função da OpenGL

#define NUM_POP 100

int x_inicial = 90; //coordenada de x
int x = 0; //auxiliar pra ajudar na coordenada x
int y = 45; //coordenada de y
int i = 0; //auxiliar
int a = 0; //auxiliar pra percorrer o vetor 


void imprime_pop(int **populacao){ //printa um cenário em pirâmide começando de baixo pra cima
    if(a==99){ //quando acabarem as linhas não há o que printar mais
        y = 45;  
        i = 0; 
        a = 0; 
        return;
    }
    x = x_inicial; //iguala o auxiliar ao x_inicial correspondente a cada linha
    while(i != 9){ //enquando o i for diferente ao numero de elementos daquela linha
        glBegin(GL_POINTS); //printa os pontos
            glColor3ub(populacao[a][0],populacao[a][1], populacao[a][2]);
            glVertex2i(x, y);
        glEnd();
        x += 50; //altera o valor de x
        i++; //cresce i
        a++;
    }
    y += 50; //decresce a posição em y
    i = 0; //zera i
    imprime_pop(populacao);
}

int main(int argc, char* argv[]){
    
    int j;

    time_t t; srand((unsigned) time(&t)); //Renova a semente da função rand() para evitar repetição dos números sorteados

    //Funções e procedimentos da OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(LN_SCREEN, H_SCREEN);
    glutCreateWindow("Adaptação RGB");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0.0, (float) LN_SCREEN, (float) H_SCREEN, 0.0);
    glPointSize(20);

    int** populacao = comeca_pop(); //cria a população

    imprime_pop(populacao);

    glFlush();

    for(int loop=0; loop<LOOP_SIZE; loop++){
        int** populacao_nova = nova_pop(populacao);
        usleep(500000); //1seg
        imprime_pop(populacao_nova);
        glFlush();
        for(j=0; j<NUM_POP; j++){
            free(populacao[j]);
        }
        free(populacao);

        populacao = populacao_nova;

    }

    for(j=0; j<NUM_POP; j++){
        free(populacao[j]);
    }
    free(populacao);

    
    glutMainLoop();
}
