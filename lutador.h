#ifndef LUTADOR_H
#define LUTADOR_H

#include <GL/glut.h>
#include <math.h>
#include "retangulo.h"
#include "circulo.h"
#include "utils.h"

class Lutador
{
public:
    Lutador();
    Circulo aCirc;
    GLuint texturaPele;
    GLuint texturaLuva;
    GLuint texturaCabeca;
    GLuint texturaCamisa;
    GLuint texturaBermuda;
    int pernaIndo = true;
    int pernaVoltando = false;
    float angulo;
    float theta1 = 15;
    float theta2 = 90;
    float theta3 = 15;
    float theta4 = 90;
    float anguloPerna = 0;
    float thetaElevacao = 20;
    float velocidade;
    void andaFrente(GLdouble time);
    void andaTras(GLdouble time);
    void desenharCorpo(Cores cor);
    void desenhaLutador(Cores cor);
    Ponto direcaoLutador();
    Ponto verificaSocoDir();
    Ponto verificaSocoEsq();
    Ponto translated(Ponto p, Ponto pAntigo);
    Ponto rotated(Ponto p, float angle);
};

#endif // LUTADOR_H
