#ifndef JOGO_H
#define JOGO_H

#include <iostream>
#include <map>
#include <cmath>
#include "utils.h"
#include "retangulo.h"
#include "circulo.h"
#include "lutador.h"


class Jogo
{
public:
    Jogo();
    Retangulo arena;
    Retangulo ceu;
    Lutador jogador;
    Lutador oponente;
    GLuint texturaChao, texturaParede1, texturaParede2,texturaParede3,texturaParede4, texturaCeuDia,texturaCeuNoite;
    int camera;
    int lutaAtual;
    double camYaw;
    double camPitch;
    double camDistanciaJogador;
    void defineCamera(bool desenhaCockpit = false);
    void defineLuz();
    // void defineLuz1();
    void Draw(bool cockpitPermanente = false);
    void DrawArena();
    void DrawMiniMapa(float _w, float _h);
    // void DrawOrtho(void (Jogo::*funcao)(), bool desabilitarTextura = true, bool desabilitarLuz = true);
    bool mostrarCameraCockpit = false;
    bool ativaLuz0 = true;
    // bool holofote = false;
    // bool ativaLuz1 = true;
    // void DrawResultado();
    // bool mostrarMinimapa = false;
    // double velHelicoptero;


    // void desenhaOrigemDoSC();
    //std::map<std::string, Cor> mapaCorID;

    // int nObjetos;
    // int nInimigos;
    // double frequenciaTiro; // tiros por milissegundos
    //double getIntervaloEntreTiros() { return 1.0 / frequenciaTiro; };

    //void DrawIndicadores();
    //void MostraDados();
    // void ImprimeElemento(Cor corElemento);
    //void exibeResultado();
    // bool estaDentro(Tiro tiro);

    // double velTiro;
};

#endif // JOGO_H
