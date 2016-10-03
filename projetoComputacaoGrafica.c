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


GLfloat xRotated, yRotated, zRotated;
GLdouble radius=1;
static const float MY_PI = 3.1415926536f;

void drawHalfSphere(GLfloat r);
void drawCircle(float radius, float thickness);
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
float x=5.0f,z=55.0f;
//Incializa a figura com cor branca
float red=1.0f, blue=1.0f, green=1.0f;
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
                0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glColor3f(0.4f, 0.5f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f,  100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(red,green,blue);
    glRotatef(-90.0,1.0,0.0,0.0);
    DrawAllMeshes();
    glPopMatrix();
    //Desenhando a pokebola
    glPushMatrix();
    glTranslatef(0.0,0.0,-10.0);
    glColor3f(1, 0, 0); 
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    drawHalfSphere(radius);
    glRotatef(180,1.0,0.0,0.0);
    glColor3f(1, 1, 1);
    drawHalfSphere(radius);
    glRotatef(90,1.0,0.0,0.0);
    glColor3f(0, 0, 0); 
    drawCircle(radius + 0.01, radius/10.);
    glRotatef(90,1.0,0.0,0.0);
    glColor3f(1, 1, 1);
    glTranslatef(0.0,0.0,radius);
    drawCircle(0.2, 0.1);
    drawCircle(0.2, 0.1);
    glPopMatrix();
    glFlush();
    SetUpLights();
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
    switch (key) {
        case 'w':
            if (xRotated > 360) xRotated = 0;
            xRotated += 10;
            break;
        case 's':
            xRotated -= 10;
            break;
        case 'q':
            zRotated += 10;
            break;
        case 'a':
            zRotated -= 10;
            break;
        case 'e':
            yRotated += 10;
            break;
        case 'd':
            yRotated -= 10;
            break;
    }
    glutPostRedisplay();
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

void drawHalfSphere(GLfloat r) {
    int i, j;
    int scaley = 20;
    int scalex = 20;
    GLfloat v[400][3];

    for (i=0; i<scalex; ++i) {
        for (j=0; j<scaley; ++j) {
            v[i*scaley+j][0]=r*cos(j*2*MY_PI/scaley)*cos(i*MY_PI/(2*scalex));
            v[i*scaley+j][1]=r*sin(i*MY_PI/(2*scalex));
            v[i*scaley+j][2]=r*sin(j*2*MY_PI/scaley)*cos(i*MY_PI/(2*scalex));
        }
    }
    glBegin(GL_QUADS);
    for (i=0; i<scalex-1; ++i) {
        for (j=0; j<scaley; ++j) {
            glVertex3fv(v[i*scaley+j]);
            glVertex3fv(v[i*scaley+(j+1)%scaley]);
            glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
            glVertex3fv(v[(i+1)*scaley+j]);
        }
    }
    glEnd();
}

void drawCircle(float radius, float thickness) {
    float x,y;
    int j;
    glBegin(GL_QUADS);
    x = (float)radius * cos(359 * MY_PI/180.0f);
    y = (float)radius * sin(359 * MY_PI/180.0f);
    for(j = 0; j < 360; j++) {
        glVertex3f(x, y, thickness/1);
        glVertex3f(x, y, -thickness/1);
        x = (float)radius * cos(j * MY_PI/180.0f);
        y = (float)radius * sin(j * MY_PI/180.0f);
        glVertex3f(x, y, -thickness/2);
        glVertex3f(x, y, thickness/2);
    }
    glEnd();
}

int main(int argc, char **argv) {
    // Inicializa o glut e cria a janela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1024,720);
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
