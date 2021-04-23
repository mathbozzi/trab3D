#include <iostream>
//#include <limits>
#include <stdlib.h>
#include <time.h>

#include <GL/glut.h>

#include "input.h"
#include "Arena.h"
//#include "Tiro.h"
#include "EstruturasBasicas.h"
#include "imageloader.h"

//#define INTERVALO_MUDANCA_ANGULO_INIMIGOS 4

using namespace std;

INPUT *input;
Arena arena;
bool isDrawn = false;
//bool desativarOponente = false;
bool keystates[256];
int mouseUltimoX;
int mouseUltimoY;

// janela
int width = 500, height = 500;

// camera controls
int lastX = 0;
int lastY = 0;
int buttonDown = 0;

void init();
void display(void);
void reshape(int w, int h);
void keyboard(unsigned char c, int x, int y);
void keyup(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void mouseClickMotion(int x, int y);
void idle();
void projecao(double _near, double _far, Rect viewport, double angulo = 90.0);

int main(int argc, char **argv)
{
    string arquivo;
    if (argc > 1)
    {
        arquivo = argv[1];
    }
    else
    {
        cout << "Digite o caminho da arena" << endl;
        cout << "Exemplo: ./trabalhocg arenas/arena_1.svg" << endl;
        return 0;
    }
    if (arquivo != "")
    {

        input = new INPUT(arquivo);

        // monta a arena
        arena = input->getArena();
        arena.MostraDados();

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
    }
    return 0;
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    // carrega as texturas
    arena.texturas["chao"] = Textura("grama.bmp");
    arena.texturas["tiro"] = Textura("lava.bmp");
    arena.texturas["objetos"] = Textura("earth.bmp");
    arena.texturas["posto"] = Textura("ring2.bmp");
    arena.texturas["ceu"] = Textura("ceu-claro.bmp");
    arena.texturas["jogadorCorpo"] = Textura("azul.bmp");
    arena.texturas["jogadorCanhao"] = Textura("azul.bmp");
    arena.texturas["jogadorHelice"] = Textura("azul-claro.bmp");
    arena.texturas["inimigoCorpo"] = Textura("vermelho.bmp");
    arena.texturas["inimigoCanhao"] = Textura("vermelho.bmp");
    arena.texturas["inimigoHelice"] = Textura("vermelho-claro.bmp");
}

void display(void)
{
    glClearColor(1, 1, 1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear all pixels both buffers
    glLoadIdentity();

    if (arena.statusPartida == GANHOU || arena.statusPartida == PERDEU)
    {
        glViewport(0, 0, width, height);
        glLoadIdentity();
        arena.DrawResultado();
    }
    else
    {
        arena.DrawMiniMapa(width, height);
        // cockpit permanente
        int cameraAtual = arena.camera;
        arena.camera = CAMERA_1; // seta a camera do cockpit
        projecao(5, 1000, Rect(0, height - 200, width, 200), 60);
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        arena.Draw(true);

        // câmera escolhida
        arena.camera = cameraAtual;
        projecao(5, 1000, Rect(0, 0, width, height - 200), 90);
        glScalef(1, -1, 1); // meu Y é invertido, por causa do 2D que usei como base
        arena.Draw();
    }

    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    width = w;
    height = h;
}

void projecao(double _near, double _far, Rect viewport, double angulo)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    double _ratio = viewport.largura / viewport.altura;
    gluPerspective(angulo, _ratio, _near, _far);

    glMatrixMode(GL_MODELVIEW);

    glViewport(viewport.posicao.x, viewport.posicao.y, viewport.largura, viewport.altura);
    glLoadIdentity();
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
    //if (arena.jogador.estaVoando()) arena.jogador.aumentarVelocidadeHelice();
    // else arena.jogador.diminuirVelocidadeHelice();
    // for (unsigned int i = 0; i < arena.inimigos.size(); i++) {
    //     if (arena.inimigos[i].estaVoando()) arena.inimigos[i].aumentarVelocidadeHelice();
    //     else arena.inimigos[i].diminuirVelocidadeHelice();
    // }

    // não precisa atualizar nada, se a partida não estiver em andamento
    if (arena.statusPartida != EM_ANDAMENTO)
    {
        glutPostRedisplay();
        return;
    }

    // // verifica se o jogador ganhou (restadou todos objetos e matou todos inimigos)
    // if (arena.statusPartida == EM_ANDAMENTO && arena.jogador.objetosResgatados == arena.nObjetos && arena.inimigos.size() == 0) {
    //     arena.statusPartida = GANHOU;
    //     cout << "Parabéns! Você ganhou a partida!!!" << endl;
    //     return;
    // }

    // verifica se o jogador perdeu por causa da falta de combustível
    // if (arena.jogador.getNivelCombustivel() <= 0) {
    //     arena.statusPartida = PERDEU;
    //     cout << "Você perdeu por falta de combustível! Que vergonha..." << endl;
    //     return;
    // }

    // consumir combustível e atualizar mostrador
    //arena.jogador.consumirCombustivel(timeDifference);

    // // reabastecimento
    // if (!arena.jogador.estaVoando() && arena.postoAbastecimento.estaDentro(arena.jogador.getPosicao())) {
    //     if (arena.jogador.getNivelCombustivel() != 1.0) cout << "O jogador reabasteceu! (" << (arena.jogador.getNivelCombustivel() * 100.0) << "% -> 100%)" << endl;
    //     arena.jogador.reabastercer();
    // }

    // interação dos tiros
    // for (unsigned int i = 0; i < arena.tiros.size(); i++) {

    //     // remove os tiros que não estão dentro da janela, senão apenas os move
    //     if (arena.estaDentro(arena.tiros[i])) arena.tiros[i].Mover(timeDifference);
    //     else {
    //         arena.tiros.erase(arena.tiros.begin() + i);
    //         cout << "1 tiro saiu da tela! Restam " << arena.tiros.size() << " tiros na arena..." << endl;
    //     }
    //
    //     // verifica se algum inimigo foi atingido pelos tiros do jogador
    //     for (unsigned int j = 0; j < arena.inimigos.size(); j++) {
    //         if (arena.tiros[i].id_jogador == "Jogador" && arena.inimigos[j].area.estaDentro(arena.tiros[i].posicao) && arena.inimigos[j].estaVoando()){
    //             arena.inimigos.erase(arena.inimigos.begin() + j);
    //             cout << "1 inimigo foi destruido! Restam " << arena.inimigos.size() << " inimigos na arena..." << endl;
    //             arena.tiros.erase(arena.tiros.begin() + i);
    //         }
    //     }
    //
    //     // verifica se algum tiro inimigo acertou o jogador e declara derrota
    //     if (arena.tiros[i].id_jogador == "Inimigo" && arena.jogador.area.estaDentro(arena.tiros[i].posicao) && arena.jogador.estaVoando()){
    //         arena.statusPartida = PERDEU;
    //         cout << "Você foi atingido por um tiro inimigo!" << endl;
    //         // mostra o tiro que acertou o jogador em vermelho
    //         arena.tiros[i].setCor(Cor("darkred"));
    //     }
    // }

    // ação de resgate
    // for (unsigned int i = 0; i < arena.objetosResgate.size(); i++) {
    //     if (arena.jogador.resgatar(arena.objetosResgate[i])) {
    //         arena.objetosResgate.erase(arena.objetosResgate.begin() + i);
    //         cout << "1 objeto foi resgatado! Restam " << arena.objetosResgate.size() << " objetos na arena..." << endl;
    //     }
    // }

    //arena.jogador.girarHelice();
    //for (unsigned int i = 0; i < arena.inimigos.size(); i++) arena.inimigos[i].girarHelice();

    arena.oponente.moverTras(timeDifference);

    if (keystates['a'])
        arena.jogador.girarEsquerda();
    if (keystates['d'])
        arena.jogador.girarDireita();
    if (keystates['w'])
        arena.jogador.moverFrente(timeDifference);
    if (keystates['s'])
        arena.jogador.moverTras(timeDifference);
    //if (keystates['-']) arena.jogador.descer();
    //if (keystates['+'] && arena.jogador.area.posicao.z < (arena.jogador.area.raio * 5) - ALTURA_HELICOPTERO) arena.jogador.subir();

    // colisao: jogador com os limites da arena, resposta: impede passagem
    Ponto jogadorNovoP = arena.jogador.getPosicao();
    int jogadorRaio = arena.jogador.area.raio;
    if (jogadorNovoP.x < jogadorRaio)
        arena.jogador.area.posicao.x = jogadorRaio;
    if (jogadorNovoP.x > arena.mapa.largura - jogadorRaio)
        arena.jogador.area.posicao.x = arena.mapa.largura - jogadorRaio;
    if (jogadorNovoP.y < jogadorRaio)
        arena.jogador.area.posicao.y = jogadorRaio;
    if (jogadorNovoP.y > arena.mapa.altura - jogadorRaio)
        arena.jogador.area.posicao.y = arena.mapa.altura - jogadorRaio;

    // colisao: oponente com os limites da arena, resposta: impede passagem
    Ponto oponenteNovoP = arena.oponente.getPosicao();
    int oponenteRaio = arena.oponente.area.raio;
    if (oponenteNovoP.x < oponenteRaio)
        arena.oponente.area.posicao.x = oponenteRaio;
    if (oponenteNovoP.x > arena.mapa.largura - oponenteRaio)
        arena.oponente.area.posicao.x = arena.mapa.largura - oponenteRaio;
    if (oponenteNovoP.y < oponenteRaio)
        arena.oponente.area.posicao.y = oponenteRaio;
    if (oponenteNovoP.y > arena.mapa.altura - oponenteRaio)
        arena.oponente.area.posicao.y = arena.mapa.altura - oponenteRaio;

    // colisao: entre personagens
    Circle cOponente = arena.oponente.area;
    if (arena.jogador.area.estaTocando(cOponente))
    {
        arena.jogador.moverTras(timeDifference);
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
    // if (accTimeAtirar >= arena.getIntervaloEntreTiros()) {
    //     atirarNoJogador = true;
    //     accTimeAtirar = 0;
    // }
    // for (unsigned int i = 0; i < arena.inimigos.size(); i++) {

    //     if (mudarAngulo) arena.inimigos[i].angulo += (rand() % 90) - 90;

    //     Ponto novoP = arena.inimigos[i].getProximaPosicao(timeDifference);
    //     int _raio = arena.inimigos[i].area.raio;

    //     // colisao: limites da arena, resposta: inverte ângulo no eixo relativo
    //     if ((novoP.x < _raio) || (novoP.x > arena.mapa.largura - _raio)) {
    //         arena.inimigos[i].angulo = 180 - arena.inimigos[i].angulo;
    //     }
    //     if ((novoP.y < _raio) || (novoP.y > arena.mapa.altura - _raio)) {
    //         arena.inimigos[i].angulo = 360 - arena.inimigos[i].angulo;
    //     }

    //     // colisao: outros helicopteros, resposta: +180º
    //     for (unsigned int j = 0; j < arena.inimigos.size(); j++) {
    //         double distanciaMinima = arena.inimigos[i].area.raio + arena.inimigos[j].area.raio;
    //         if (i != j && calculaDistancia(arena.inimigos[j].getProximaPosicao(timeDifference), novoP) < distanciaMinima){
    //             arena.inimigos[i].angulo = arena.inimigos[i].angulo + 180;
    //             break;
    //         }
    //     }
    //     double distanciaMinima = arena.jogador.area.raio + arena.inimigos[i].area.raio;
    //     if (calculaDistancia(arena.jogador.getProximaPosicao(timeDifference), novoP) < distanciaMinima){
    //         arena.inimigos[i].angulo = arena.inimigos[i].angulo + 180;
    //     }

    //     if (atirarNoJogador) {
    //         arena.inimigos[i].mirar(arena.jogador.getPosicao());
    //         arena.tiros.push_back(arena.inimigos[i].atirar());
    //     }

    //     arena.inimigos[i].moverFrente(timeDifference);
    // }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (arena.statusPartida != EM_ANDAMENTO && arena.statusPartida != PAUSADO)
        return;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && arena.statusPartida != PAUSADO)
    {
        // // atira
        // if (arena.jogador.estaVoando()) {
        //     arena.tiros.push_back(arena.jogador.atirar());
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
    if (arena.statusPartida != EM_ANDAMENTO && arena.statusPartida != PAUSADO)
        return;

    // if (x != mouseUltimoX) arena.jogador.moverCanhao((x - mouseUltimoX)/2, 0);
    // if (y != mouseUltimoY) arena.jogador.moverCanhao(0, (y - mouseUltimoY)/2);
    // atualiza o valor do ultimo x
    mouseUltimoX = x;
    mouseUltimoY = y;
}

void mouseClickMotion(int x, int y)
{
    if (arena.statusPartida != EM_ANDAMENTO && arena.statusPartida != PAUSADO)
        return;

    // código do Thiago
    if (!buttonDown)
        return;

    arena.camYaw -= x - lastX;
    arena.camPitch += y - lastY;

    arena.camPitch = (int)arena.camPitch % 360;
    if (arena.camPitch > 179)
        arena.camPitch = 179;
    if (arena.camPitch < 1)
        arena.camPitch = 1;
    arena.camYaw = (int)arena.camYaw % 360;

    lastX = x;
    lastY = y;
}

void keyup(unsigned char key, int x, int y) { keystates[key] = false; }
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
        arena.camera = CAMERA_1; // câmera no cockpit
        break;
    case '2':
        arena.camera = CAMERA_2; // câmera no canhão
        break;
    case '3':
        arena.camera = CAMERA_3; // câmera que segue o helicóptero
        break;
    case 'e':
        arena.jogador.desenharEsfera();
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
        arena.ativaLuz0 = !arena.ativaLuz0;
        break;
    case 'k':
        arena.ativaLuz1 = !arena.ativaLuz1;
        break;
    case 's':
        if (smoothEnabled)
            glShadeModel(GL_FLAT);
        else
            glShadeModel(GL_SMOOTH);
        smoothEnabled = !smoothEnabled;
        break;
    case 'p':
        if (arena.statusPartida == PAUSADO)
            arena.statusPartida = EM_ANDAMENTO;
        else
            arena.statusPartida = PAUSADO;
        break;
    case 'c':
        arena.mostrarCameraCockpit = !arena.mostrarCameraCockpit;
        break;
    case 'm':
        arena.mostrarMinimapa = !arena.mostrarMinimapa;
        break;
        // case 'b':
        //     desativarOponente = !desativarOponente;
        //     break;
    }
}
