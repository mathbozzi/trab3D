#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include "lutador.h"
#include "oponente.h"
#include "arena.h"
#include "input.h"
#include "camera.h"

using namespace std;

int animate = 0;
int keyStatus[256];
static char pontos[100];
void *font = GLUT_BITMAP_9_BY_15;

static bool luminosidade = true;
static bool luz = true;

Arena *arenaSVG = NULL;
Lutador *lutadorPrincipal = NULL;
Oponente *lutadorOponente = NULL;
Camera *camera1;
Camera *camera2;
Camera *camera3;
Vector3 lastMousePos = Vector3(0,0,0);

GLfloat ambientPlayer[] = {0.0, 0.0, 0.0, 1.0};
GLfloat diffusePlayer[] = {0.0, 1.0, 0.0, 1.0};
GLfloat specularPlayer[] = {1.0, 1.0, 1.0, 1.0};


void updateSpot();
void initSpot();

void displayPlayerVision()
{
    glViewport(0,arenaSVG->get_height()*0.72,arenaSVG->get_width(),arenaSVG->get_height()*0.28);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective (45, (GLfloat)500/(GLfloat)200, 1, -50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Vector3 handInicio = lutadorPrincipal->posicaoOlho();
    Vector3 handFinal = lutadorPrincipal->posicaoLuva();

    gluLookAt(
		handInicio.x,handInicio.y,handInicio.z-10,
		handFinal.x,handFinal.y,handInicio.z-15,
		0,0,1
	);
    initSpot();
    arenaSVG->render(false);
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientPlayer);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusePlayer);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularPlayer);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);
    player->render(false);
    glPopMatrix();
}
