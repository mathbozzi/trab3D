#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include "input.h"
#include "lutador.h"
#include "arena.h"

using namespace std;
Arena *arenaSVG = NULL;
Lutador *lutadorPrincipal = NULL;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glShadeModel (GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, (GLsizei)arenaSVG->get_width(),
               (GLsizei)arenaSVG->get_height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,
                   (GLfloat)arenaSVG->get_width() / (GLfloat)arenaSVG->get_height(),
                   1, 1000);
}

void DrawAxes(double size)
{
    GLfloat mat_ambient_r[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient_g[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat mat_ambient_b[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                 no_mat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);

    //x axis red
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION,
                 mat_ambient_r);
    glColor3fv(mat_ambient_r);
    glScalef(size, size * 0.1, size * 0.1);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(1.0);
    glPopMatrix();

    //y axis green
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION,
                 mat_ambient_g);
    glColor3fv(mat_ambient_g);
    glRotatef(90, 0, 0, 1);
    glScalef(size, size * 0.1, size * 0.1);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(1.0);
    glPopMatrix();

    //z axis blue
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_ambient_b);
    glColor3fv(mat_ambient_b);
    glRotatef(-90, 0, 1, 0);
    glScalef(size, size * 0.1, size * 0.1);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(1.0);
    glPopMatrix();
}

void DrawObj(double size)
{
    GLfloat materialEmission[] = {0.00, 0.00, 0.00, 1.0};
    GLfloat materialColor[] = {1.0, 1.0, 0.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {128};
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColor);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(1, 0, 0);
    //glutSolidCube(size);
    glutSolidSphere(size, 20, 10);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 100, 1, 0, 0, 0, 0, 1, 0);

    GLfloat light_position[] = {0.0, 0.0, 10.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPushMatrix();
    glTranslatef(0, 0, 3); // put in one end
    DrawAxes(1.5);
    DrawObj(1.0);
    glPopMatrix();

    DrawAxes(1.5);

    DrawObj(1.0);

    glutSwapBuffers();
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
        glutMainLoop();
        return 0;
    }
}