#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstring>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "imageloader.h"

static int jogoON = 0;
static int jogadorGanhou = 1;
static int oponenteGanhou = 2;
static int jogoOFF = 3;
static int cam1 = 4;
static int cam2 = 5;
static int cam3 = 6;
static int cam4 = 7;

class Cores
{
    float r;
    float g;
    float b;

public:
    Cores(float r, float g, float b);
    float getCorR();
    float getCorG();
    float getCorB();
};

class Ponto
{
    float x;
    float y;
    float z;

public:
    Ponto(float x, float y, float z);
    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
};

double calculaDistancia(Ponto p1, Ponto p2);

typedef struct
{
    //Vertex coordinate
    double X;
    double Y;
    double Z;
    //Vertex normal
    double nX;
    double nY;
    double nZ;
    //Vertex texture coordinate
    double U;
    double V;
} VERTICES;

typedef struct
{
    VERTICES *vtx;
    int numVtx;
    double radius;
} OBJ;

void desenhaCubo();
void DrawAxes();
OBJ *CreateSphere(double R, double space);
GLuint LoadTextureRAW(const char *filename);

#endif // UTILS_H
