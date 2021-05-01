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
    Retangulo(int x, int y, int width, int height/*, Cor cor = Cor(0.0f,0.0f,0.0f)*/);
    Ponto posicao = Ponto(0,0,0);
    // Cor cor;
    std::string id;
    int altura;
    int largura;
    // int strokeLargura;
    // Cor strokeCor;
    //Textura textura;
    // int fatorRepeticaoTextura = 1;
    bool estaDentro(Ponto p);
    void Draw(GLuint textura,Cores cor);

    // void Draw(int flag = DRAW_2D, Textura *_textura = NULL, bool drawStroke = NO_STROKE);
    void DrawArestas();
    // static void DrawCubo(Retangulo *r, float profundidade, float textureS = 1);
    // std::vector<Ponto> getVertices();
};

#endif // RETANGULO_H
