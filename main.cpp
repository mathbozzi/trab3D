#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include "tinyxml2.h"
#include "jogo.h"
#include "retangulo.h"
#include "circulo.h"
#include "utils.h"
#include "imageloader.h"

using namespace std;
using namespace tinyxml2;

void *font = GLUT_BITMAP_9_BY_15;
static char pontos[100];
int keyStatus[256];

Jogo jogo;
int contaSocoLutador = 0;
int contaSocoOponente = 0;
int xAntigo;
int yAntigo = 0;
int botaoDirPress = 0;
int width = 500;
int height = 500;
bool flagSoco = false;
bool flagSoco2 = true;
bool socoOponente = false;
float velocidadeLutador = 0.2;
float velocidadeOponente = 0.1;
double tamanhozFar;

void init()
{
    glEnable(GL_DEPTH_TEST);
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
    jogo.texturaParede1 = LoadTextureRAW("textura/pbatalha.bmp");
    jogo.texturaParede2 = LoadTextureRAW("textura/pbatalha2.bmp");
    jogo.texturaParede3 = LoadTextureRAW("textura/pbatalha3.bmp");
    jogo.texturaParede4 = LoadTextureRAW("textura/pbatalha4.bmp");
    jogo.texturaChao = LoadTextureRAW("textura/chaodbz.bmp");
    jogo.texturaCeuDia = LoadTextureRAW("textura/ceudbz.bmp");
    jogo.texturaParedeEs1 = LoadTextureRAW("textura/candrade.bmp");
    jogo.texturaParedeEs2 = LoadTextureRAW("textura/candrade2.bmp");
    jogo.texturaParedeEs3 = LoadTextureRAW("textura/candrade3.bmp");
    jogo.texturaParedeEs4 = LoadTextureRAW("textura/candrade4.bmp");
    jogo.texturaEsChao = LoadTextureRAW("textura/gramaca.bmp");
    jogo.texturaEsCeuDia = LoadTextureRAW("textura/nublado.bmp");
    jogo.texturaCeuNoite = LoadTextureRAW("textura/stars1.bmp");
}

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

void display(void)
{
    glClearColor(1, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (jogo.lutaAtual == jogadorGanhou)
    {
        jogo.desenhaMiniMapa(width, height);
        sprintf(pontos, "VOCE GANHOU! PARABENS! :D");
        char *pontuacao = pontos;
        PrintText(0.05, 0.05, pontuacao, 1, 1, 1);

        int cam = jogo.camera;
        jogo.camera = cam4;
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(70, width / 200, 1, tamanhozFar);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, height - 200, width, 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1);
        jogo.desenhaJogo();

        jogo.camera = cam;
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(90, width / (height - 200), 1, tamanhozFar);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, 0, width, height - 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1);
        jogo.desenhaJogo();
    }
    else if (jogo.lutaAtual == oponenteGanhou)
    {
        jogo.desenhaMiniMapa(width, height);
        sprintf(pontos, "VOCE PERDEU! TENTE NOVAMENTE! :C");
        char *pontuacao = pontos;
        PrintText(0.05, 0.05, pontuacao, 1, 1, 1);

        int cam = jogo.camera;
        jogo.camera = cam4;
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(70, width / 200, 1, tamanhozFar);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, height - 200, width, 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1);
        jogo.desenhaJogo();

        jogo.camera = cam;
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(90, width / (height - 200), 1, tamanhozFar);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, 0, width, height - 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1);
        jogo.desenhaJogo();
    }
    else
    {
        jogo.desenhaMiniMapa(width, height);
        sprintf(pontos, "Lutador: %2d x %2d Oponente", contaSocoLutador, contaSocoOponente);
        char *pontuacao = pontos;
        PrintText(0.05, 0.05, pontuacao, 1, 1, 1);

        int cam = jogo.camera;
        jogo.camera = cam4;
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(70, width / 200, 1, tamanhozFar);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, height - 200, width, 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1);
        jogo.desenhaJogo();

        jogo.camera = cam;
        {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(90, width / (height - 200), 1, tamanhozFar);
            glMatrixMode(GL_MODELVIEW);
            glViewport(0, 0, width, height - 200);
            glLoadIdentity();
        }
        glScalef(1, -1, 1);
        jogo.desenhaJogo();
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    width = w;
    height = h;
}

void verificaSeAcertouSoco(Ponto p, Ponto o)
{
    double dist = calculaDistancia(p, o);

    if (dist >= jogo.jogador.aCirc.raio / (jogo.jogador.aCirc.raio * 0.275) + jogo.oponente.aCirc.raio / 2.0)
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
}

void verificaSeAcertouSocoOponente(Ponto p, Ponto o)
{
    double dist = calculaDistancia(p, o);

    if (dist >= jogo.oponente.aCirc.raio / (jogo.oponente.aCirc.raio * 0.275) + jogo.jogador.aCirc.raio / 2.0)
    {
        flagSoco2 = true;
    }
    else
    {
        if (flagSoco2)
        {
            contaSocoOponente += 1;
            flagSoco2 = false;
        }
    }
}

void idle()
{
    static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDifference;

    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime;
    previousTime = currentTime;

    if (jogo.lutaAtual != jogoON)
    {
        glutPostRedisplay();
        return;
    }
    if (contaSocoLutador >= 10)
    {
        jogo.lutaAtual = jogadorGanhou;
        return;
    }
    if (contaSocoOponente >= 10)
    {
        jogo.lutaAtual = oponenteGanhou;
        return;
    }

    if (keyStatus['A'] == 1 || keyStatus['a'] == 1)
        jogo.jogador.angulo -= 1;
    if (keyStatus['D'] == 1 || keyStatus['d'] == 1)
        jogo.jogador.angulo += 1;
    if (keyStatus['W'] == 1 || keyStatus['w'] == 1)
        jogo.jogador.andaFrente(timeDifference);
    if (keyStatus['S'] == 1 || keyStatus['s'] == 1)
        jogo.jogador.andaTras(timeDifference);

    Ponto jogadorNovoP = jogo.jogador.aCirc.posicao;
    int jogadorRaio = jogo.jogador.aCirc.raio;
    if (jogadorNovoP.getX() < jogadorRaio)
        jogo.jogador.aCirc.posicao.setX(jogadorRaio);
    if (jogadorNovoP.getX() > jogo.ring.width - jogadorRaio)
        jogo.jogador.aCirc.posicao.setX(jogo.ring.width - jogadorRaio);
    if (jogadorNovoP.getY() < jogadorRaio)
        jogo.jogador.aCirc.posicao.setY(jogadorRaio);
    if (jogadorNovoP.getY() > jogo.ring.height - jogadorRaio)
        jogo.jogador.aCirc.posicao.setY(jogo.ring.height - jogadorRaio);

    Ponto oponenteNovoP = jogo.oponente.aCirc.posicao;
    int oponenteRaio = jogo.oponente.aCirc.raio;
    if (oponenteNovoP.getX() < oponenteRaio)
        jogo.oponente.aCirc.posicao.setX(oponenteRaio);
    if (oponenteNovoP.getX() > jogo.ring.width - oponenteRaio)
        jogo.oponente.aCirc.posicao.setX(jogo.ring.width - oponenteRaio);
    if (oponenteNovoP.getY() < oponenteRaio)
        jogo.oponente.aCirc.posicao.setY(oponenteRaio);
    if (oponenteNovoP.getY() > jogo.ring.height - oponenteRaio)
        jogo.oponente.aCirc.posicao.setY(jogo.ring.height - oponenteRaio);

    Circulo cOponente = jogo.oponente.aCirc;
    if (jogo.jogador.aCirc.dentroArea(cOponente) && !(keyStatus['S'] == 1 || keyStatus['s'] == 1))
    {
        jogo.jogador.andaTras(timeDifference);
    }
    else if (jogo.jogador.aCirc.dentroArea(cOponente) && (keyStatus['S'] == 1 || keyStatus['s'] == 1))
    {
        jogo.jogador.andaFrente(timeDifference);
    }
    jogo.oponente.theta1 = 15;
    jogo.oponente.theta2 = 90;
    jogo.oponente.theta3 = 15;
    jogo.oponente.theta4 = 90;

    if (!jogo.movOponente)
    {
        return;
    }

    Ponto pinit = Ponto(0, 0, 0);
    pinit.setX(jogo.oponente.aCirc.posicao.getX() - jogo.jogador.aCirc.posicao.getX());
    pinit.setY(jogo.oponente.aCirc.posicao.getY() - jogo.jogador.aCirc.posicao.getY());

    double angulorad = atan2(pinit.getY(), pinit.getX());
    double angulograu = (angulorad * 180) / M_PI;
    jogo.oponente.angulo = -((180 - angulograu) * 2) - (angulograu + 180);
    jogo.oponente.andaFrente(timeDifference);

    Circulo cJogador = jogo.jogador.aCirc;
    if (jogo.oponente.aCirc.dentroArea(cJogador))
    {
        jogo.oponente.andaTras(timeDifference);

        if (!socoOponente)
        {
            socoOponente = true;

            unsigned seed = time(0);
            srand(seed);
            int i = ((int)width / 2 * 0.4) + rand() % ((int)width / 2);
            if (i > ((int)width / 2))
            {
                i = ((int)width / 2);
            }
            unsigned seed2 = time(0);
            srand(seed2);
            int x = rand() % 2;
            if (x % 2 == 0)
            {
                {
                    jogo.oponente.theta1 = (15 + i * (65 / (width / 2.0)));
                    jogo.oponente.theta2 = (90 + i * (-55 / (width / 2.0)));
                    //tentar fazer um loop devagar
                    Ponto pSocoDir = jogo.oponente.verificaSocoDir();
                    Ponto pontoCabecaJogador = jogo.jogador.aCirc.posicao;
                    pontoCabecaJogador = {pontoCabecaJogador.getX(), pontoCabecaJogador.getY(), pontoCabecaJogador.getZ() * (float)4.5};
                    verificaSeAcertouSocoOponente(pSocoDir, pontoCabecaJogador);
                }
                jogo.oponente.theta3 = 15;
                jogo.oponente.theta4 = 90;
            }
            else
            {
                {
                    jogo.oponente.theta3 = (15 + i * 1.5 * (65 / (height / 2.0)));
                    jogo.oponente.theta4 = (90 - i * (55 / (height / 2.0)));
                    //tentar fazer um loop devagar
                    Ponto pSocoEsq = jogo.oponente.verificaSocoEsq();
                    Ponto pontoCabecaJogador = jogo.jogador.aCirc.posicao;
                    pontoCabecaJogador = {pontoCabecaJogador.getX(), pontoCabecaJogador.getY(), pontoCabecaJogador.getZ() * (float)4.5};
                    verificaSeAcertouSocoOponente(pSocoEsq, pontoCabecaJogador);
                }
                jogo.oponente.theta1 = 15;
                jogo.oponente.theta2 = 90;
            }
            socoOponente = false;
        }
    }
    glutPostRedisplay();
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
    if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_UP)
    {
        botaoDirPress = 0;
    }
    if (botao == GLUT_RIGHT_BUTTON && estado == GLUT_DOWN)
    {
        xAntigo = x;
        yAntigo = y;
        botaoDirPress = 1;
    }
}

void movimentoBraco(int x, int y)
{
    if (jogo.lutaAtual != jogoON && jogo.lutaAtual != jogoOFF)
        return;

    if (!botaoDirPress)
    {
        int newX = x;
        int newY = height - y;
        if (x - xAntigo > 0)
        {
            if (x - xAntigo <= width / 2.0)
            {
                jogo.jogador.theta1 = (15 + (x - xAntigo) * (65 / (width / 2.0)));
                jogo.jogador.theta2 = (90 + (x - xAntigo) * (-55 / (width / 2.0)));
                Ponto pSocoDir = jogo.jogador.verificaSocoDir();
                Ponto pontoCabecaOponente = jogo.oponente.aCirc.posicao;
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
                Ponto pontoCabecaOponente = jogo.oponente.aCirc.posicao;
                pontoCabecaOponente = {pontoCabecaOponente.getX(), pontoCabecaOponente.getY(), pontoCabecaOponente.getZ() * (float)4.5};
                verificaSeAcertouSoco(pSocoEsq, pontoCabecaOponente);
            }
        }
    }
    else
    {
        jogo.camRotacao -= x - xAntigo;
        jogo.camSubida += y - yAntigo;
        jogo.camSubida = (int)jogo.camSubida % 360;
        if (jogo.camSubida > 150)
            jogo.camSubida = 150;
        xAntigo = x;
        yAntigo = y;
    }
}

void keyUp(unsigned char key, int x, int y)
{
    keyStatus[key] = 0;
}

void keyPress(unsigned char key, int x, int y)
{
    keyStatus[key] = 1;
    static bool textureEnabled = true;
    static bool lightingEnabled = true;
    static bool smoothEnabled = true;
    switch (key)
    {
    case '1':
        jogo.camera = cam1;
        break;
    case '2':
        jogo.camera = cam2;
        break;
    case '3':
    {
        jogo.camera = cam3;
    }
    break;
    case '4':
        jogo.camera = cam4;
        break;
    case 'm':
        jogo.movOponente = !jogo.movOponente;
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
    case 'r':
        if (smoothEnabled)
            glShadeModel(GL_FLAT);
        else
            glShadeModel(GL_SMOOTH);
        smoothEnabled = !smoothEnabled;
        break;
    case 'n':
        jogo.luz = !jogo.luz;
        break;
    case 'o':
        jogo.cenario = !jogo.cenario;
        break;
    case 'b':
        socoOponente = !socoOponente;
        break;
    case 'p':
        if (jogo.lutaAtual == jogoOFF)
            jogo.lutaAtual = jogoON;
        else
            jogo.lutaAtual = jogoOFF;
        break;
    case '+':
    {
        if (jogo.camera == cam3)
        {
            int inc = jogo.camDistanciaJogador >= (jogo.jogador.aCirc.raio * 4.5) ? 0 : 1;
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

    Retangulo ring;
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
            }
            else
            {
                float x, y;
                elementos->QueryFloatAttribute("cx", &x);
                elementos->QueryFloatAttribute("cy", &y);
                elementos->QueryIntAttribute("r", &personagem.raio);
                personagem.posicao.setX(x);
                personagem.posicao.setY(y);
            }
        }
        else if (!ele.compare("rect"))
        {
            float x, y;
            elementos->QueryFloatAttribute("x", &x);
            elementos->QueryFloatAttribute("y", &y);
            elementos->QueryIntAttribute("width", &ring.width);
            elementos->QueryIntAttribute("height", &ring.height);
            ring.pos.setX(x);
            ring.pos.setY(y);
            cor = elementos->FindAttribute("fill")->Value();
        }
    }

    if (ring.width >= ring.height)
    {
        tamanhozFar = 1.5 * ring.width;
    }
    else
    {
        tamanhozFar = 1.5 * ring.height;
    }

    personagem.posicao.setX(personagem.posicao.getX() - ring.pos.getX());
    personagem.posicao.setY(personagem.posicao.getY() - ring.pos.getY());
    adversario.posicao.setX(adversario.posicao.getX() - ring.pos.getX());
    adversario.posicao.setY(adversario.posicao.getY() - ring.pos.getY());

    ring.pos.setX(0);
    ring.pos.setY(0);
    jogo.ring = ring;

    jogo.camDistanciaJogador = 4.5 * (personagem.raio);

    personagem.posicao.setZ(personagem.raio / 2.0);
    jogo.jogador.aCirc = personagem;
    jogo.jogador.velocidade = velocidadeLutador;

    adversario.posicao.setZ(personagem.raio / 2.0);
    jogo.oponente.aCirc = adversario;
    jogo.oponente.velocidade = velocidadeOponente;

    Ponto pinit = Ponto(0, 0, 0);
    pinit.setX(adversario.posicao.getX() - personagem.posicao.getX());
    pinit.setY(adversario.posicao.getY() - personagem.posicao.getY());

    double angulorad = atan2(pinit.getY(), pinit.getX());
    double angulograu = (angulorad * 180) / M_PI;
    jogo.jogador.angulo = angulograu;
    jogo.oponente.angulo = -((180 - angulograu) * 2) - (angulograu + 180);
    jogo.camRotacao = angulograu;

    srand(time(NULL));
}

// ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬ MAIN ¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬
int main(int argc, char **argv)
{
    trataXML(argv[1]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height + 200);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("RING");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutMotionFunc(movimentoBraco);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}