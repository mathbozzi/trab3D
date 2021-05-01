#include <iostream>
//#include <limits>
#include <stdlib.h>
#include <time.h>

#include <GL/glut.h>
#include "tinyxml2.h"
//#include "input.h"
#include "jogo.h"
#include "retangulo.h"
#include "circulo.h"
//#include "Tiro.h"
#include "utils.h"
#include "imageloader.h"

using namespace std;
using namespace tinyxml2;

bool keystates[256];

Jogo jogo;
float velocidadeLutador = 0.2;
float velocidadeOponente = 0.1;
int xAntigo;
int yAntigo = 0;
int botaoPress = 0;
bool flagSoco = false;
int contaSocoLutador = 0;
static char pontos[100];
void *font = GLUT_BITMAP_9_BY_15;

//bool isDrawn = false;
//bool desativarOponente = false;
// int mouseUltimoX;
// int mouseUltimoY;

int width = 500;
int height = 500;

void init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    jogo.jogador.texturaCabeca = LoadTextureRAW("textura/cabeca.bmp");
    jogo.jogador.texturaCamisa = LoadTextureRAW("textura/camisa3.bmp");
    jogo.jogador.texturaPele = LoadTextureRAW("textura/pele.bmp");
    jogo.jogador.texturaBermuda = LoadTextureRAW("textura/bermuda.bmp");
    jogo.jogador.texturaLuva = LoadTextureRAW("textura/luva1.bmp");
    jogo.oponente.texturaCabeca = LoadTextureRAW("textura/rostoOponente.bmp");
    jogo.oponente.texturaCamisa = LoadTextureRAW("textura/camisa1.bmp");
    jogo.oponente.texturaBermuda = LoadTextureRAW("textura/bermudaOponente.bmp");
    jogo.oponente.texturaPele = LoadTextureRAW("textura/pele.bmp");
    jogo.oponente.texturaLuva = LoadTextureRAW("textura/luva2.bmp");
    jogo.texturaParede1 = LoadTextureRAW("textura/candrade.bmp");
    jogo.texturaParede2 = LoadTextureRAW("textura/candrade2.bmp");
    jogo.texturaParede3 = LoadTextureRAW("textura/candrade3.bmp");
    jogo.texturaParede4 = LoadTextureRAW("textura/candrade4.bmp");
    jogo.texturaChao = LoadTextureRAW("textura/gramaca.bmp");
    jogo.texturaCeuDia = LoadTextureRAW("textura/nublado.bmp");
    jogo.texturaCeuNoite = LoadTextureRAW("textura/stars1.bmp");
}

// codigo lab terra e sol
void RasterChars(GLfloat x, GLfloat y, GLfloat z, const char *text, double r, double g, double b)
{
    //Push to recover original attributes
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    //Draw text in the x, y, z position
    glColor3f(r, g, b);
    glRasterPos3f(x, y, z);
    const char *tmpStr;
    tmpStr = text;
    while (*tmpStr)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *tmpStr);
        tmpStr++;
    }
    glPopAttrib();
}
// codigo lab terra e sol
void PrintText(GLfloat x, GLfloat y, const char *text, double r, double g, double b)
{
    //Draw text considering a 2D space (disable all 3d features)
    glMatrixMode(GL_PROJECTION);
    //Push to recover original PROJECTION MATRIX
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    RasterChars(x, y, 0, text, r, g, b);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// void projecao(double _near, double _far, Retangulo viewport, double angulo)
// {
//     glMatrixMode(GL_PROJECTION);

//     glLoadIdentity();
//     double _ratio = viewport.largura / viewport.altura;
//     gluPerspective(angulo, _ratio, _near, _far);

//     glMatrixMode(GL_MODELVIEW);

//     glViewport(viewport.posicao.getX(), viewport.posicao.getY(), viewport.largura, viewport.altura);
//     glLoadIdentity();
// }

void display(void)
{
    glClearColor(1, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (jogo.lutaAtual == jogadorGanhou)
    {
        sprintf(pontos, "VOCE GANHOU! PARABENS! :D");
        char *pontuacao = pontos;
        PrintText(0.05, 0.05, pontuacao, 1, 1, 1);
        jogo.DrawMiniMapa(width, height);

        int cameraAtual = jogo.camera;
        jogo.camera = cam4; //camera do oponente
        // projecao(5, 1000, Retangulo(0, height - 200, width, 200), 70);
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(70, width / 200, 5, 1000);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, height - 200, width, 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        jogo.Draw(true);

        jogo.camera = cameraAtual;
        // projecao(5, 1000, Retangulo(0, 0, width, height - 200), 90);
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(90, width / (height - 200), 5, 1000);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, 0, width, height - 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        jogo.Draw();
    }
    else if (jogo.lutaAtual == oponenteGanhou)
    {
        sprintf(pontos, "VOCE PERDEU! TENTE NOVAMENTE! :C");
        char *pontuacao = pontos;
        PrintText(0.05, 0.05, pontuacao, 1, 1, 1);
        jogo.DrawMiniMapa(width, height);

        int cameraAtual = jogo.camera;
        jogo.camera = cam4; //camera do oponente
        // projecao(5, 1000, Retangulo(0, height - 200, width, 200), 70);
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(70, width / 200, 5, 1000);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, height - 200, width, 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        jogo.Draw(true);

        jogo.camera = cameraAtual;
        // projecao(5, 1000, Retangulo(0, 0, width, height - 200), 90);
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(90, width / (height - 200), 5, 1000);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, 0, width, height - 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        jogo.Draw();
    }
    else
    {
        jogo.DrawMiniMapa(width, height);
        sprintf(pontos, "Lutador: %2d x %2d Oponente", contaSocoLutador, 0);
        char *pontuacao = pontos;
        PrintText(0.05, 0.05, pontuacao, 1, 1, 1);

        int cameraAtual = jogo.camera;
        jogo.camera = cam4;
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(70, width / 200, 5, 1000);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, height - 200, width, 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        jogo.Draw(true);

        jogo.camera = cameraAtual;
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(90, width / (height - 200), 5, 1000);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, 0, width, height - 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        jogo.Draw();
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    width = w;
    height = h;
}

void idle()
{
    static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDifference;

    // Elapsed time from the initiation of the game.
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime; // Elapsed time from the previous frame.
    previousTime = currentTime;                  //Update previous time

    //para o jogo
    if (jogo.lutaAtual != jogoON)
    {
        glutPostRedisplay();
        return;
    }
    // verifica se o jogador ganhou
    if (contaSocoLutador == 10)
    {
        jogo.lutaAtual = jogadorGanhou;
        return;
    }

    // verifica se o oponente ganhou

    // interação dos tiros
    // for (unsigned int i = 0; i < jogo.tiros.size(); i++) {

    //     // remove os tiros que não estão dentro da janela, senão apenas os move
    //     if (jogo.estaDentro(jogo.tiros[i])) jogo.tiros[i].Mover(timeDifference);
    //     else {
    //         jogo.tiros.erase(jogo.tiros.begin() + i);
    //         cout << "1 tiro saiu da tela! Restam " << jogo.tiros.size() << " tiros na jogo..." << endl;
    //     }
    //
    //     // verifica se algum inimigo foi atingido pelos tiros do jogador
    //     for (unsigned int j = 0; j < jogo.inimigos.size(); j++) {
    //         if (jogo.tiros[i].id_jogador == "Jogador" && jogo.inimigos[j].area.estaDentro(jogo.tiros[i].posicao) && jogo.inimigos[j].estaVoando()){
    //             jogo.inimigos.erase(jogo.inimigos.begin() + j);
    //             cout << "1 inimigo foi destruido! Restam " << jogo.inimigos.size() << " inimigos na jogo..." << endl;
    //             jogo.tiros.erase(jogo.tiros.begin() + i);
    //         }
    //     }
    //
    //     // verifica se algum tiro inimigo acertou o jogador e declara derrota
    //     if (jogo.tiros[i].id_jogador == "Inimigo" && jogo.jogador.area.estaDentro(jogo.tiros[i].posicao) && jogo.jogador.estaVoando()){
    //         jogo.lutaAtual = oponenteGanhou;
    //         cout << "Você foi atingido por um tiro inimigo!" << endl;
    //         // mostra o tiro que acertou o jogador em vermelho
    //         jogo.tiros[i].setCor(Cor("darkred"));
    //     }
    // }

    // ação de resgate
    // for (unsigned int i = 0; i < jogo.objetosResgate.size(); i++) {
    //     if (jogo.jogador.resgatar(jogo.objetosResgate[i])) {
    //         jogo.objetosResgate.erase(jogo.objetosResgate.begin() + i);
    //         cout << "1 objeto foi resgatado! Restam " << jogo.objetosResgate.size() << " objetos na jogo..." << endl;
    //     }
    // }

    //jogo.jogador.girarHelice();
    //for (unsigned int i = 0; i < jogo.inimigos.size(); i++) jogo.inimigos[i].girarHelice();

    // jogo.oponente.moverFrente(timeDifference);

    if (keystates['a'])
        // jogo.jogador.girarEsquerda();
        jogo.jogador.angulo -= 1;
    if (keystates['d'])
        // jogo.jogador.girarDireita();
        jogo.jogador.angulo += 1;
    if (keystates['w'])
        jogo.jogador.moverFrente(timeDifference);
    if (keystates['s'])
        jogo.jogador.moverTras(timeDifference);
    //if (keystates['-']) jogo.jogador.descer();
    //if (keystates['+'] && jogo.jogador.area.posicao.z < (jogo.jogador.area.raio * 5) - TAMANHO_LUTADORES) jogo.jogador.subir();

    // colisao: jogador com os limites da jogo, resposta: impede passagem
    Ponto jogadorNovoP = jogo.jogador.getPosicao();
    int jogadorRaio = jogo.jogador.area.raio;
    if (jogadorNovoP.getX() < jogadorRaio)
        jogo.jogador.area.posicao.setX(jogadorRaio);
    if (jogadorNovoP.getX() > jogo.arena.largura - jogadorRaio)
        jogo.jogador.area.posicao.setX(jogo.arena.largura - jogadorRaio);
    if (jogadorNovoP.getY() < jogadorRaio)
        jogo.jogador.area.posicao.setY(jogadorRaio);
    if (jogadorNovoP.getY() > jogo.arena.altura - jogadorRaio)
        jogo.jogador.area.posicao.setY(jogo.arena.altura - jogadorRaio);

    // colisao: oponente com os limites da jogo, resposta: impede passagem
    Ponto oponenteNovoP = jogo.oponente.getPosicao();
    int oponenteRaio = jogo.oponente.area.raio;
    if (oponenteNovoP.getX() < oponenteRaio)
        jogo.oponente.area.posicao.setX(oponenteRaio);
    if (oponenteNovoP.getX() > jogo.arena.largura - oponenteRaio)
        jogo.oponente.area.posicao.setX(jogo.arena.largura - oponenteRaio);
    if (oponenteNovoP.getY() < oponenteRaio)
        jogo.oponente.area.posicao.setY(oponenteRaio);
    if (oponenteNovoP.getY() > jogo.arena.altura - oponenteRaio)
        jogo.oponente.area.posicao.setY(jogo.arena.altura - oponenteRaio);

    // colisao: entre personagens
    Circulo cOponente = jogo.oponente.area;
    if (jogo.jogador.area.estaTocando(cOponente))
    {
        jogo.jogador.moverTras(timeDifference);
    }
    Circulo cJogador = jogo.jogador.area;
    if (jogo.oponente.area.estaTocando(cJogador))
    {
        jogo.oponente.moverTras(timeDifference);
    }

    // // desativa as ações dos inimigos para demonstrar algum funcionalidade
    // if (desativarOponente) {
    //     glutPostRedisplay();
    //     return;
    // }

    // // mover inimigos
    // accTimeMover += timeDifference / 1000.0;
    // bool mudarAngulo = false;
    // if (accTimeMover >= INTERVALO_MUDANCA_ANGULO_INIMIGOS) {
    //     mudarAngulo = true;
    //     accTimeMover = 0;
    // }
    // accTimeAtirar += timeDifference;
    // bool atirarNoJogador = false;
    // if (accTimeAtirar >= jogo.getIntervaloEntreTiros()) {
    //     atirarNoJogador = true;
    //     accTimeAtirar = 0;
    // }
    // for (unsigned int i = 0; i < jogo.inimigos.size(); i++) {

    //     if (mudarAngulo) jogo.inimigos[i].angulo += (rand() % 90) - 90;

    //     Ponto novoP = jogo.inimigos[i].getProximaPosicao(timeDifference);
    //     int _raio = jogo.inimigos[i].area.raio;

    //     // colisao: limites da jogo, resposta: inverte ângulo no eixo relativo
    //     if ((novoP.x < _raio) || (novoP.x > jogo.arena.largura - _raio)) {
    //         jogo.inimigos[i].angulo = 180 - jogo.inimigos[i].angulo;
    //     }
    //     if ((novoP.y < _raio) || (novoP.y > jogo.arena.altura - _raio)) {
    //         jogo.inimigos[i].angulo = 360 - jogo.inimigos[i].angulo;
    //     }

    //     // colisao: outros helicopteros, resposta: +180º
    //     for (unsigned int j = 0; j < jogo.inimigos.size(); j++) {
    //         double distanciaMinima = jogo.inimigos[i].area.raio + jogo.inimigos[j].area.raio;
    //         if (i != j && calculaDistancia(jogo.inimigos[j].getProximaPosicao(timeDifference), novoP) < distanciaMinima){
    //             jogo.inimigos[i].angulo = jogo.inimigos[i].angulo + 180;
    //             break;
    //         }
    //     }
    //     double distanciaMinima = jogo.jogador.area.raio + jogo.inimigos[i].area.raio;
    //     if (calculaDistancia(jogo.jogador.getProximaPosicao(timeDifference), novoP) < distanciaMinima){
    //         jogo.inimigos[i].angulo = jogo.inimigos[i].angulo + 180;
    //     }

    //     if (atirarNoJogador) {
    //         jogo.inimigos[i].mirar(jogo.jogador.getPosicao());
    //         jogo.tiros.push_back(jogo.inimigos[i].atirar());
    //     }

    //     jogo.inimigos[i].moverFrente(timeDifference);
    // }

    glutPostRedisplay();
}

void verificaSeAcertouSoco(Ponto p, Ponto o)
{
    double dist = calculaDistancia(p, o);

    if (dist >= jogo.jogador.area.raio / (jogo.jogador.area.raio *0.275) + jogo.oponente.area.raio /2.0 ) // mudar aqui
    {
        flagSoco = true;
    }
    else
    {
        if (flagSoco)
        {
            contaSocoLutador += 1;
            flagSoco = false;
        }
    }
    // cout << contaSocoLutador << endl;
}

void mouse(int botao, int estado, int x, int y)
{
    if (jogo.lutaAtual != jogoON && jogo.lutaAtual != jogoOFF)
        return;

    if (botao == GLUT_LEFT_BUTTON && jogo.lutaAtual != jogoOFF)
    {
        if (estado == GLUT_DOWN)
        {
            xAntigo = x;
        }
        else if (estado == GLUT_UP)
        {
            jogo.jogador.theta1 = 15;
            jogo.jogador.theta2 = 90;
            jogo.jogador.theta3 = 15;
            jogo.jogador.theta4 = 90;
        }
    }

    if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
    {
        xAntigo = x;
        yAntigo = y;
        botaoPress = 1;
    }
    if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_UP)
    {
        botaoPress = 0;
    }
}

// void mouseMotion(int x, int y)
// {
//     if (jogo.lutaAtual != jogoON && jogo.lutaAtual != jogoOFF)
//         return;

//     // if (x != mouseUltimoX) jogo.jogador.moverCanhao((x - mouseUltimoX)/2, 0);
//     // if (y != mouseUltimoY) jogo.jogador.moverCanhao(0, (y - mouseUltimoY)/2);
//     // atualiza o valor do ultimo x
//     mouseUltimoX = x;
//     mouseUltimoY = y;
// }

void movimentoBraco(int x, int y)
{
    if (jogo.lutaAtual != jogoON && jogo.lutaAtual != jogoOFF)
        return;

    int newX = x;
    int newY = height - y;
    if (x - xAntigo > 0)
    {
        if (x - xAntigo <= width / 2.0)
        {
            jogo.jogador.theta1 = (15 + (x - xAntigo) * (65 / (width / 2.0)));
            jogo.jogador.theta2 = (90 + (x - xAntigo) * (-55 / (width / 2.0)));
            Ponto pSocoDir = jogo.jogador.verificaSocoDir();
            Ponto pontoCabecaOponente = jogo.oponente.getPosicao();
            pontoCabecaOponente = {pontoCabecaOponente.getX(), pontoCabecaOponente.getY(), pontoCabecaOponente.getZ() * (float)4.5};
            verificaSeAcertouSoco(pSocoDir, pontoCabecaOponente);
        }
    }
    else
    {
        if ((x - xAntigo >= (-height / 2.0)))
        {
            jogo.jogador.theta3 = (15 - (x - xAntigo) * (65 / (height / 2.0)));
            jogo.jogador.theta4 = (90 + (x - xAntigo) * (55 / (height / 2.0)));
            Ponto pSocoEsq = jogo.jogador.verificaSocoEsq();
            Ponto pontoCabecaOponente = jogo.oponente.getPosicao();
            pontoCabecaOponente = {pontoCabecaOponente.getX(), pontoCabecaOponente.getY(), pontoCabecaOponente.getZ() * (float)4.5};
            verificaSeAcertouSoco(pSocoEsq, pontoCabecaOponente);
        }
    }

    if (!botaoPress)
        return;

    jogo.camYaw -= x - xAntigo;
    jogo.camPitch += y - yAntigo;

    jogo.camPitch = (int)jogo.camPitch % 360;
    if (jogo.camPitch > 150)
        jogo.camPitch = 150;
    // if (jogo.camPitch < 30)
    //     jogo.camPitch = 30;
    // jogo.camYaw = (int)jogo.camYaw % 360;

    xAntigo = x;
    yAntigo = y;
}

void keyup(unsigned char key, int x, int y)
{
    keystates[key] = false;
}

void keyboard(unsigned char key, int x, int y)
{
    keystates[key] = true;

    static bool textureEnabled = true;
    static bool lightingEnabled = true;
    static bool smoothEnabled = true;

    switch (key)
    {
    case '1':
        jogo.camera = cam1; 
        break;
    case '2':
        jogo.camera = cam2; // câmera no canhão
        break;
    case '3':
    {
        jogo.camera = cam3; // câmera que segue o jogador
    }
    break;
    case '4':
        jogo.camera = cam4; //
        break;
    case 't':
        if (textureEnabled)
            glDisable(GL_TEXTURE_2D);
        else
            glEnable(GL_TEXTURE_2D);
        textureEnabled = !textureEnabled;
        break;
    case 'l':
        if (lightingEnabled)
            glDisable(GL_LIGHTING);
        else
            glEnable(GL_LIGHTING);
        lightingEnabled = !lightingEnabled;
        break;
    case 'j':
        jogo.ativaLuz0 = !jogo.ativaLuz0;
        break;
    // case 'k':
    //     jogo.ativaLuz1 = !jogo.ativaLuz1;
    //     break;
    case 'r':
        if (smoothEnabled)
            glShadeModel(GL_FLAT);
        else
            glShadeModel(GL_SMOOTH);
        smoothEnabled = !smoothEnabled;
        break;
    case 'p':
        if (jogo.lutaAtual == jogoOFF)
            jogo.lutaAtual = jogoON;
        else
            jogo.lutaAtual = jogoOFF;
        break;
    case 'c':
        jogo.mostrarCameraCockpit = !jogo.mostrarCameraCockpit;
        break;
    case '+':
    {
        if (jogo.camera == cam3)
        {
            int inc = jogo.camDistanciaJogador >= (jogo.jogador.area.raio * 4.65) ? 0 : 1;
            jogo.camDistanciaJogador += inc * 2;
        }
        break;
    }
    case '-':
    {
        if (jogo.camera == cam3)
        {
            int inc = jogo.camDistanciaJogador <= 5 ? 0 : 1;
            jogo.camDistanciaJogador -= inc * 2;
        }

        break;
    }
    // case 'm':
    //     jogo.mostrarMinimapa = !jogo.mostrarMinimapa;
    //     break;
    // case 'b':
    //     desativarOponente = !desativarOponente;
    //     break;
    case 27:
        exit(0);
        break;
    }
}

void trataXML(const char *diretorio)
{
    string caminho;
    XMLDocument arquivo_config, arquivo_svg;
    XMLError arquivoStatus;
    XMLElement *elementos;

    caminho = diretorio;

    arquivoStatus = arquivo_svg.LoadFile(caminho.c_str());

    if (arquivoStatus != XML_SUCCESS)
    {
        cerr << "Erro ao abrir svg" << endl;
        exit(XML_ERROR_FILE_READ_ERROR);
    }

    elementos = arquivo_svg.FirstChild()->FirstChildElement();

    Retangulo arena;
    Circulo personagem;
    Circulo adversario;

    for (; elementos != NULL; elementos = elementos->NextSiblingElement())
    {
        string ele = elementos->Value();
        string cor;

        if (!ele.compare("circle"))
        {
            cor = elementos->FindAttribute("fill")->Value();

            if (cor == "red")
            {
                float x, y;
                elementos->QueryFloatAttribute("cx", &x);
                elementos->QueryFloatAttribute("cy", &y);
                elementos->QueryIntAttribute("r", &adversario.raio);
                adversario.posicao.setX(x);
                adversario.posicao.setY(y);
                // adversario.cor = Cor(cor);
                // jogo.oponente.corCorpo = Cor(1.0,0.0,0.0);
            }
            else
            {
                float x, y;
                elementos->QueryFloatAttribute("cx", &x);
                elementos->QueryFloatAttribute("cy", &y);
                elementos->QueryIntAttribute("r", &personagem.raio);
                personagem.posicao.setX(x);
                personagem.posicao.setY(y);
                // personagem.cor = Cor(cor);
                // jogo.jogador.corCorpo = Cor(0.0,1.0,0.0);
            }
        }
        else if (!ele.compare("rect"))
        {
            float x, y;
            elementos->QueryFloatAttribute("x", &x);
            elementos->QueryFloatAttribute("y", &y);
            elementos->QueryIntAttribute("width", &arena.largura);
            elementos->QueryIntAttribute("height", &arena.altura);
            arena.posicao.setX(x);
            arena.posicao.setY(y);
            cor = elementos->FindAttribute("fill")->Value();

            // arena.cor = Cor(0.0,0.0,1.0);
        }
    }

    personagem.posicao.setX(personagem.posicao.getX() - arena.posicao.getX());
    personagem.posicao.setY(personagem.posicao.getY() - arena.posicao.getY());
    adversario.posicao.setX(adversario.posicao.getX() - arena.posicao.getX());
    adversario.posicao.setY(adversario.posicao.getY() - arena.posicao.getY());

    arena.posicao.setX(0);
    arena.posicao.setY(0);

    // monta a jogo
    jogo.arena = arena;
    jogo.camDistanciaJogador = 4.65 * (personagem.raio);

    //jogo.postoAbastecimento = postoAbastecimento;
    //jogo.objetosResgate = objetosResgate;

    personagem.posicao.setZ(personagem.raio / 2.0);
    jogo.jogador.area = personagem;
    //jogo.jogador.id = personagem.id;
    jogo.jogador.velocidade = velocidadeLutador;
    // printf("%f\n",jogo.jogador.area.raio/2.0);
    // printf("%f\n", TAMANHO_LUTADORES / 2.0);
    // printf("%f\n",areaJogador.posicao.z);
    // areaJogador.posicao.z = jogo.jogador.area.raio/2.0;

    //jogo.jogador.velocidadeTiro = _velTiro;
    //jogo.jogador.tempoMaximoDeVoo = _tempoDeVoo;
    // jogo.jogador.corCorpo = Cor("lightgreen");

    adversario.posicao.setZ(personagem.raio / 2.0);
    jogo.oponente.area = adversario;
    //jogo.oponente.id = adversario.id;
    jogo.oponente.velocidade = velocidadeOponente;
    // areaOponente.posicao.z = jogo.oponente.area.raio/2.0;

    // //jogo.jogador.velocidadeTiro = _velTiro;
    // //jogo.jogador.tempoMaximoDeVoo = _tempoDeVoo;
    // jogo.oponente.corCorpo = Cor("darkgreen");

    // personagem.posicao.x = (personagem.posicao.x - arena.largura/2);
    // personagem.posicao.y = -(-arena.altura/2 + personagem.posicao.y);
    // jogo.jogador.angulo = 0.0;
    // // personagem.theta1 = -45;
    // // personagem.theta2 = 135;
    // // personagem.theta3 = -45;
    // // personagem.theta4 = 135;

    // adversario.posicao.x = (adversario.posicao.x - arena.largura/2);
    // adversario.posicao.y = -(-arena.altura/2 + adversario.posicao.y);
    // jogo.oponente.angulo = 0.0;
    // adversario.p.x = (adversario.p.x - jogo.width / 2);
    // adversario.p.y = -(-jogo.height / 2 + adversario.p.y);
    // adversario.ang = 0.0;
    // adversario.theta1 = -45;
    // adversario.theta2 = 135;
    // adversario.theta3 = -45;
    // adversario.theta4 = 135;

    Ponto pinit = Ponto(0, 0, 0);
    pinit.setX(adversario.posicao.getX() - personagem.posicao.getX());
    pinit.setY(adversario.posicao.getY() - personagem.posicao.getY());

    double angulorad = atan2(pinit.getY(), pinit.getX());
    double angulograu = (angulorad * 180) / M_PI;
    jogo.jogador.angulo = angulograu;
    jogo.oponente.angulo = -((180 - angulograu) * 2) - (angulograu + 180);

    jogo.camYaw = angulograu + 90;

    srand(time(NULL));
}

// ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬ MAIN ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬
int main(int argc, char **argv)
{

    trataXML(argv[1]);

    // glut init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height + 200);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("RING");
    init();

    // event 'binding'
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyup);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    // glutPassiveMotionFunc(mouseMotion);
    glutMotionFunc(movimentoBraco);
    glutReshapeFunc(reshape);

    // glut main loop
    glutMainLoop();
    // }
    return 0;
}