#include <stdio.h>
#include <stdlib.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glut.h>
#include <math.h>

#include "Venusaur.h"
// O importe abaixo é para renderizar um objeto exportado do blender
#include "func.h"

void changeSize(int w, int h);
void SetUpLights();
void renderScene(void);
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

//--------------------------------------------------------------------
// Variaveis globais
// Angulo de rotação da camera
float angle=0.0;
// Vetor atual representando a diração da camera
float lx=0.0f,lz=-1.0f;
// Coordenadas de X e Z para posição da camera
float x=30.0f,z=35.0f;
//Incializa a figura com cor branca
float red=1.0f, blue=1.0f, green=1.0f;
// Angulo de rotação da figura
float anglem = 0.0f;
//--------------------------------------------------------------------

void changeSize(int w, int h) {
    // Prevenção caso a janela tenha uma altura 0
    if (h == 0){
        h = 1;
    }
    float ratio =  w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    // Reseta a Matrix
    glLoadIdentity();
    // Set na viewport para a janela
    glViewport(0, 0, w, h);
    // Set de perspective
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    // Muda a matrix
    glMatrixMode(GL_MODELVIEW);
}

void SetUpLights() {
    float pos[] = {10, 10, 10, 0};
    float ambient[] = {0.3, 0.3, 0.3, 1};
    float white[] = {1, 1, 1, 1};
    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_LIGHT0);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reseta a matriz
    glLoadIdentity();
    // Set na camera e visualização
    gluLookAt(x, 1.0f, z,
                x+lx, 1.0f, z+lz,
                0.0f, 1.0f,  0.0f);
    //TODO - arrumar para criar o "chão"
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    glRotatef(anglem, 0.0f, 1.0f, 0.0f);
    glColor3f(red,green,blue);
    DrawAllMeshes();
    SetUpLights();
    anglem+=0.1f;
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

void processSpecialKeys(int key, int x, int y) {
float fraction = 0.1f;
    switch(key) {
        case GLUT_KEY_F1 :
            red = 1.0;
            green = 0.0;
            blue = 0.0;
        break;
        case GLUT_KEY_F2 :
            red = 0.0;
            green = 1.0;
            blue = 0.0;
        break;
        case GLUT_KEY_F3 :
            red = 0.0;
            green = 0.0;
            blue = 1.0;
        break;
        case GLUT_KEY_LEFT :
            angle -= 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
        break;
        case GLUT_KEY_RIGHT :
            angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
        break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
        break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
        break;
    }
}

int main(int argc, char **argv) {
    // Inicializa o glut e cria a janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Projeto de Computacao Grafica");
    // Registra os callbacks
    InitMesh();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    // Registro de callback para teclado
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    // Ciclo de evento para não encerrar
    glutMainLoop();
    return 1;
}