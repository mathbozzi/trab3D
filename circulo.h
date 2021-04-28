#ifndef CIRCLE_H
#define CIRCLE_H


#include <math.h>
#include <GL/glut.h>
#include <memory>

#include "utils.h"

class Circulo
{
    public:
        Circulo();
        Circulo(Ponto posicao, int raio);
        Ponto posicao = Ponto(0,0,0);
        // Cor cor;
        std::string id;
        int raio;
        // Textura textura;

        bool estaDentro(Ponto p);
        bool estaTocando(Circulo c);
        // void Draw(int flag = DRAW_2D, Textura *_textura = NULL);
        // void Draw();
        void Draw2d(Cores cor);

        // int numeroDePontos;
        std::unique_ptr<OBJ> criaEsfera();
        void DrawEsfera();
    
};

#endif // CIRCLE_H
