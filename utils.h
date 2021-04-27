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

// enum {
//     EM_ANDAMENTO,
//     GANHOU,
//     PERDEU,
//     PAUSADO
// };

// enum {
//     DRAW_2D,
//     DRAW_3D
//  };

//  enum {
//     WITH_STROKE = true,
//     NO_STROKE = false
// };

class Ponto
{
public:
    Ponto();
    Ponto(float _x, float _y, float _z = 0) : x(_x), y(_y), z(_z){};
    void print();
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

class Cor
{
public:
    Cor();
    Cor(std::string color_name);
    Cor(int _r, int _g, int _b);
    GLfloat r;
    GLfloat g;
    GLfloat b;
    inline bool operator==(const Cor &c) { return (this->r == c.r && this->g == c.g && this->b == c.b); }
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

void drawBox(GLfloat tamanho, GLfloat textureS = 1);
OBJ *CreateSphere(double R, double space);
GLuint LoadTextureRAW2(const char *filename);

#endif // UTILS_H
