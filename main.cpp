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

Jogo jogo;
float velocidadeLutador = 0.2;
float velocidadeOponente = 0.1;
//bool isDrawn = false;
//bool desativarOponente = false;
bool keystates[256];
int mouseUltimoX;
int mouseUltimoY;

int width = 500;
int height = 500;

// camera controls
int lastX = 0;
int lastY = 0;
int buttonDown = 0;

void init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    // carrega as texturas
    jogo.jogador.textura = LoadTextureRAW("images/earth.bmp");
    jogo.oponente.textura = LoadTextureRAW("images/lava.bmp");
    jogo.texturaChao = LoadTextureRAW("images/madeira.bmp");
    jogo.texturaParede = LoadTextureRAW("images/ring1.bmp");
    jogo.texturaCeu = LoadTextureRAW("images/stars1.bmp");
    // arena.texturas["chao"] = Textura("grama.bmp");
    // arena.texturas["tiro"] = Textura("lava.bmp");
    // arena.texturas["objetos"] = Textura("earth.bmp");
    // arena.texturas["posto"] = Textura("ring1.bmp");
    // arena.texturas["ceu"] = Textura("ceu-claro.bmp");
    // arena.texturas["jogadorCorpo"] = Textura("azul.bmp");
    // arena.texturas["jogadorCanhao"] = Textura("azul.bmp");
    // arena.texturas["jogadorHelice"] = Textura("azul-claro.bmp");
    // arena.texturas["inimigoCorpo"] = Textura("vermelho.bmp");
    // arena.texturas["inimigoCanhao"] = Textura("vermelho.bmp");
    // arena.texturas["inimigoHelice"] = Textura("vermelho-claro.bmp");
}

void projecao(double _near, double _far, Retangulo viewport, double angulo)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    double _ratio = viewport.largura / viewport.altura;
    gluPerspective(angulo, _ratio, _near, _far);

    glMatrixMode(GL_MODELVIEW);

    glViewport(viewport.posicao.getX(), viewport.posicao.getY(), viewport.largura, viewport.altura);
    glLoadIdentity();
}

void display(void)
{
    glClearColor(1, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (jogo.statusPartida == jogadorGanhou || jogo.statusPartida == oponenteGanhou)
    {
        glViewport(0, 0, width, height);
        glLoadIdentity();
        jogo.DrawResultado();
    }
    else
    {
        jogo.DrawMiniMapa(width, height);
        // cockpit permanente
        int cameraAtual = jogo.camera;
        jogo.camera = cam1; // seta a camera do cockpit
        projecao(5, 1000, Retangulo(0, height - 200, width, 200), 60);
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        jogo.Draw(true);

        // câmera escolhida
        jogo.camera = cameraAtual;
        projecao(5, 1000, Retangulo(0, 0, width, height - 200), 90);
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
    static GLdouble accTimeMover = 0;
    static GLdouble accTimeAtirar = 0;
    GLdouble currentTime;
    GLdouble timeDifference;

    // Elapsed time from the initiation of the game.
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDifference = currentTime - previousTime; // Elapsed time from the previous frame.
    previousTime = currentTime;                  //Update previous time

    // modifica a velocidade da helice de acordo com o status
    //if (jogo.jogador.estaVoando()) jogo.jogador.aumentarVelocidadeHelice();
    // else jogo.jogador.diminuirVelocidadeHelice();
    // for (unsigned int i = 0; i < jogo.inimigos.size(); i++) {
    //     if (jogo.inimigos[i].estaVoando()) jogo.inimigos[i].aumentarVelocidadeHelice();
    //     else jogo.inimigos[i].diminuirVelocidadeHelice();
    // }

    // não precisa atualizar nada, se a partida não estiver em andamento
    if (jogo.statusPartida != jogoON)
    {
        glutPostRedisplay();
        return;
    }

    // // verifica se o jogador jogadorGanhou (restadou todos objetos e matou todos inimigos)
    // if (jogo.statusPartida == jogoON && jogo.jogador.objetosResgatados == jogo.nObjetos && jogo.inimigos.size() == 0) {
    //     jogo.statusPartida = jogadorGanhou;
    //     cout << "Parabéns! Você jogadorGanhou a partida!!!" << endl;
    //     return;
    // }

    // verifica se o jogador oponenteGanhou por causa da falta de combustível
    // if (jogo.jogador.getNivelCombustivel() <= 0) {
    //     jogo.statusPartida = oponenteGanhou;
    //     cout << "Você oponenteGanhou por falta de combustível! Que vergonha..." << endl;
    //     return;
    // }

    // consumir combustível e atualizar mostrador
    //jogo.jogador.consumirCombustivel(timeDifference);

    // // reabastecimento
    // if (!jogo.jogador.estaVoando() && jogo.postoAbastecimento.estaDentro(jogo.jogador.getPosicao())) {
    //     if (jogo.jogador.getNivelCombustivel() != 1.0) cout << "O jogador reabasteceu! (" << (jogo.jogador.getNivelCombustivel() * 100.0) << "% -> 100%)" << endl;
    //     jogo.jogador.reabastercer();
    // }

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
    //         jogo.statusPartida = oponenteGanhou;
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

    jogo.oponente.moverFrente(timeDifference);

    if (keystates['a'])
        jogo.jogador.girarEsquerda();
    if (keystates['d'])
        jogo.jogador.girarDireita();
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

void mouse(int button, int state, int x, int y)
{
    if (jogo.statusPartida != jogoON && jogo.statusPartida != jogoOFF)
        return;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && jogo.statusPartida != jogoOFF)
    {
        // // atira
        // if (jogo.jogador.estaVoando()) {
        //     jogo.tiros.push_back(jogo.jogador.atirar());
        //     cout << "O jogador atirou!" << endl;
        // }
    }

    // movimenta câmera ao redor do helicóptero
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        lastX = x;
        lastY = y;
        buttonDown = 1;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        buttonDown = 0;
    }
}

void mouseMotion(int x, int y)
{
    if (jogo.statusPartida != jogoON && jogo.statusPartida != jogoOFF)
        return;

    // if (x != mouseUltimoX) jogo.jogador.moverCanhao((x - mouseUltimoX)/2, 0);
    // if (y != mouseUltimoY) jogo.jogador.moverCanhao(0, (y - mouseUltimoY)/2);
    // atualiza o valor do ultimo x
    mouseUltimoX = x;
    mouseUltimoY = y;
}

void mouseClickMotion(int x, int y)
{
    if (jogo.statusPartida != jogoON && jogo.statusPartida != jogoOFF)
        return;

    // código do Thiago
    if (!buttonDown)
        return;

    jogo.camYaw -= x - lastX;
    jogo.camPitch += y - lastY;

    jogo.camPitch = (int)jogo.camPitch % 360;
    if (jogo.camPitch > 179)
        jogo.camPitch = 179;
    if (jogo.camPitch < 1)
        jogo.camPitch = 1;
    jogo.camYaw = (int)jogo.camYaw % 360;

    lastX = x;
    lastY = y;
}

void keyup(unsigned char key, int x, int y)
{
    keystates[key] = false;
}

void keyboard(unsigned char key, int x, int y)
{
    keystates[key] = true;
    if (key == 27)
        exit(0);

    static bool textureEnabled = true;
    static bool lightingEnabled = true;
    static bool smoothEnabled = true;

    switch (key)
    {
    case '1':
        jogo.camera = cam1; // câmera no cockpit
        break;
    case '2':
        jogo.camera = cam2; // câmera no canhão
        break;
    case '3':
        jogo.camera = cam3; // câmera que segue o jogador
        break;
    // case 'e':
    //     jogo.jogador.desenharEsfera();
    //     break;
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
        if (jogo.statusPartida == jogoOFF)
            jogo.statusPartida = jogoON;
        else
            jogo.statusPartida = jogoOFF;
        break;
    case 'c':
        jogo.mostrarCameraCockpit = !jogo.mostrarCameraCockpit;
        break;
    case 'm':
        jogo.mostrarMinimapa = !jogo.mostrarMinimapa;
        break;
        // case 'b':
        //     desativarOponente = !desativarOponente;
        //     break;
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
                float x,y;
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
                float x,y;
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
            float x,y;
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
    
    //jogo.postoAbastecimento = postoAbastecimento;
    //jogo.objetosResgate = objetosResgate;

    personagem.posicao.setZ(TAMANHO_LUTADORES / 2.0);
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

    adversario.posicao.setZ(TAMANHO_LUTADORES / 2.0);
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

    Ponto pinit = Ponto(0,0,0);
    pinit.setX(adversario.posicao.getX() - personagem.posicao.getX());
    pinit.setY(adversario.posicao.getY() - personagem.posicao.getY());

    double angulorad = atan2(pinit.getY(), pinit.getX());
    double angulograu = (angulorad * 180) / M_PI;
    jogo.jogador.angulo = angulograu;
    jogo.oponente.angulo = -((180 - angulograu) * 2) - (angulograu + 180);

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
    glutInitWindowPosition(100, 100);
    glutCreateWindow("RING");
    init();

    // event 'binding'
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyup);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(mouseMotion);
    glutMotionFunc(mouseClickMotion);
    glutReshapeFunc(reshape);

    // glut main loop
    glutMainLoop();
    // }
    return 0;
}