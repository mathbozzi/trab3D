#ifndef HELICOPTERO_H
#define HELICOPTERO_H

#include <GL/glut.h>
#include <math.h>

#include "retangulo.h"
#include "circulo.h"
// #include "Tiro.h"
#include "utils.h"

/** CORES (RGB)
 * Verde claro:     155, 187, 89
 * Verde escuro:    99, 169, 117
 * Azul:            79, 129, 189
 */

#define TAMANHO_LUTADORES 40
// #define HELICE_VEL_MAXIMA 3.0
// #define HELICE_VEL_MINIMA 0.0

class Lutador
{
public:
    Lutador();
    void moverFrente(GLdouble timeDiff); // OK
    void moverTras(GLdouble timeDiff);   // OK
    void girarDireita();                 // OK
    void girarEsquerda();                // OK
    void ajustarAngulo();
    void desenharCorpo(Cores cor); // OK
    void Draw(Cores cor);          // OK
    Circulo area;
    float angulo;
    float anguloPerna=0;
    int pernaVoltando=false;
    int pernaIndo=true;
    float velocidade;
    float anguloCanhaoYaw, anguloCanhaoPitch; 
    GLuint textura;
    Ponto getPosicao() { return area.posicao; };
    Ponto getDirecao();
    Ponto getProximaPosicao(GLdouble timeDiff);
    void getInfoCanhao(Ponto &pontaCanhao, Ponto &direcao);
    // bool desenhaEsfera = false;

    // float anguloHelice;
    //void moverCanhao(int incrementoYaw, int incrementoPitch);
    //Lutador(float _velocidadeHelice, float _velocidadeHelicoptero, float _velocidadeTiro);
    //void girarHelice();              // OK
    //void decolar();                  // OK
    //void pousar();                   // OK
    //void subir();                    // OK
    //void descer();                   // OK
    //void aumentarVelocidadeHelice(); // OK
    //void diminuirVelocidadeHelice(); // OK
    //void mirar(Ponto alvo);
    //Tiro atirar();
    //bool estaVoando();                           // OK
    //void consumirCombustivel(GLdouble timeDiff); // OK
    //void reabastercer();                         // OK
    //bool resgatar(Circulo objeto);                // OK
    //double getNivelCombustivel();                // OK
    // desenho
    //void desenharCombustivel(float _posicaoX, float _posicaoY, int _numeroDeMostradores);                 // OK
    //void desenharResgates(float _posicaoX, float _posicaoY, int _nObjetos);                               // OK
    //void desenharHelice(Textura *textura);                                                                // OK
    //void desenharCanhao(Textura *textura);                                                                // OK
    // void desenharEsfera() { desenhaEsfera = !desenhaEsfera; }                                             // OK
    //std::string id;
    //float tempoMaximoDeVoo, tempoAtualDeVoo;
    //int objetosResgatados;
    // Cores corCorpo;
    //Textura texturaCorpo;
    // Textura texturaCorpo, texturaHelice, texturaCanhao;
    //float velocidadeHelice;
    //bool voando;
    // bool draw3d = false;
};
//void displayCabeca(GLuint textureSun);

#endif // HELICOPTERO_H
