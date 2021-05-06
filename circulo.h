#ifndef CIRCULO_H
#define CIRCULO_H

#include <math.h>
#include <GL/glut.h>
#include "utils.h"

class Circulo
{
    public:
        Circulo();
        Circulo(Ponto posicao, int raio);
        int raio;
        bool dentroArea(Circulo c);
        void circuloMMapa(Cores cor);
        Ponto posicao = Ponto(0,0,0);
};

#endif // CIRCULO_H
