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

#define NUM_POP 10

int x_inicial= 100;
int x = 0;
int y = 500;
int n = 6;
int i = 0;

void print_cenario(){
    if(n==0){
        return;
    }
    x = x_inicial;
    while(i != n){
        glBegin(GL_POINTS);
            glColor3f(1,0,0);
            glVertex2i(x, y);
        glEnd();
        x +=80;
        i++;
    }
    n--;
    y -= 80;
    x_inicial += 40;
    i = 0;
    print_cenario();
}

int main(int argc, char* argv[]){
    
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
    glPointSize(30);

    print_cenario();

    glFlush();
    
    glutMainLoop();
}
/*
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
}*/
