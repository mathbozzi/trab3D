#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include "input.h"
#include "lutador.h"
#include "utils.h"
#include "arena.h"

using namespace std;
Arena *arenaSVG = NULL;
Lutador *lutadorPrincipal = NULL;

//Controles gerais
int zoom = 100;
int lookatToggle = 1;
double camXYAngle=0;
double camXZAngle=0;
int lastX = 0;
int lastY = 0;
int buttonDown=0;

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_LIGHT0);
}


void reshape (int w, int h)
{
    //Ajusta o tamanho da tela com a janela de visualizacao
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    // if (w <= h)
    //     gluPerspective (45, (GLfloat)h/(GLfloat)w, 1, 1000);
    // else
        gluPerspective (90, (GLfloat)w/(GLfloat)h, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        lastX = x;
        lastY = y;
        buttonDown = 1;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        buttonDown = 0;
    }
    glutPostRedisplay();
}

void mouse_motion(int x, int y)
{
    if (!buttonDown)
        return;
    
    camXZAngle -= x - lastX;
    camXYAngle += y - lastY;

    lastX = x;
    lastY = y;
    glutPostRedisplay();
}

void display(void)
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // PrintText(0.1, 0.1, "Movable Camera", 0,1,0);
    

    //Utiliza uma esfera de raio zoom para guiar a posicao da camera
    //baseada em dois angulos (do plano XZ e do plano XY)
    gluLookAt(zoom * sin(camXZAngle * M_PI / 180) * cos((camXYAngle * M_PI / 180)),
              zoom * sin((camXYAngle * M_PI / 180)),
              zoom * cos(camXZAngle * M_PI / 180) * cos((camXYAngle * M_PI / 180)),
              0, 0, 0,
              0, 1, 0);

    // if (cameraToggle == 1)
    // {
    //     displayPrimeiraPessoa();
    // }
    // else if (cameraToggle == 2)
    // {
    //     displayTerceiraPessoa();
    // }
    // else
    //     displayOlho();

    // glFlush();

    // gluLookAt((arenaSVG->get_width() - arenaSVG->get_width() * 0.2), arenaSVG->get_height() / 2, 0, 0, 0, 0, 0, 1, 0);

    GLfloat light_position[] = {20.0, 3.0, 0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    DrawAxes(1.5);

    arenaSVG->desenhaArena();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    // static bool textureEnebled = true;
    // static bool lightingEnebled = true;
    // static bool smoothEnebled = true;
    switch (key)
    {
    
    case '+':
        zoom++;
        break;
    case '-':
        zoom--;
        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    string arquivo;
    if (argc > 1)
    {
        arquivo = argv[1];
    }
    else
    {
        cout << "Digite o caminho da arena" << endl;
        cout << "Exemplo: ./trabalhocg arenas/arena_1.svg" << endl;
        return 0;
    }
    if (arquivo != "")
    {
        parseSVGFile(arquivo);
        arenaSVG->set_altura(lutadorPrincipal->ObtemAltura() * 2);
        arenaSVG->MudaCoordZ(-arenaSVG->ObtemAltura());

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE |
                            GLUT_RGB |
                            GLUT_DEPTH);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 0);
        glutCreateWindow("RING");
        init();
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);
        glutMotionFunc(mouse_motion);
        glutMouseFunc(mouse);
        glutMainLoop();
        return 0;
    }
}