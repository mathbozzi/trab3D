#ifndef RETANGULO_H
#define RETANGULO_H

#include <vector>
#include <GL/glut.h>
#include <cmath>
#include "utils.h"

class Retangulo
{
public:
    Retangulo();
    Retangulo(int x, int y, int width, int height);
    int height;
    int width;
    void desenhaRetMiniMapa();
    void desenhaRetangulo(GLuint textura, Cores cor);
    Ponto pos = Ponto(0, 0, 0);
};

#endif // RETANGULO_H
