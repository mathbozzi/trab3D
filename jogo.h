#ifndef JOGO_H
#define JOGO_H

#include <iostream>
#include <cmath>
#include "utils.h"
#include "retangulo.h"
#include "circulo.h"
#include "lutador.h"

class Jogo
{
public:
    Jogo();
    Retangulo ring;
    Retangulo ceu;
    Lutador jogador;
    Lutador oponente;
    GLuint texturaChao, texturaParede1, texturaParede2,
        texturaParede3, texturaParede4, texturaEsChao, texturaParedeEs1, texturaParedeEs2,
        texturaParedeEs3, texturaParedeEs4, texturaEsCeuDia, texturaCeuDia, texturaCeuNoite;
    int lutaAtual;
    int camera;
    bool luz = true;
    bool cenario = true;
    bool movOponente = false;
    double camRotacao;
    double camSubida;
    double camDistanciaJogador;
    void luzes();
    void cameras();
    void desenhaJogo();
    void desenhaRing();
    void desenhaMiniMapa(float width, float height);
};

#endif // JOGO_H
