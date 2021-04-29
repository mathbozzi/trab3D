#include "jogo.h"

using namespace std;

Jogo::Jogo()
{
    this->lutaAtual = jogoON;
    camera = cam3;
    // camYaw = 180;
    camPitch = 135;
    // camDistanciaJogador = 200;
}

void Jogo::Draw(bool cockpitPermanente)
{
    // if (!cockpitPermanente)
    //     DrawOrtho(&Jogo::DrawIndicadores);

    glPushMatrix();
    defineCamera(mostrarCameraCockpit);
    defineLuz0();
    defineLuz1();

    // desenhaOrigemDoSC();

    // for (Lutador h : inimigos)
    //     h.Draw(DRAW_3D, &texturas["inimigoCorpo"], &texturas["inimigoHelice"], &texturas["inimigoCanhao"]);

    jogador.Draw({0.0, 1.0, 0.0});
    oponente.Draw({1.0, 0, 0});

    DrawArena();

    // for (Circle c : objetosResgate)
    //     c.Draw(DRAW_3D, &texturas["objetos"]);
    // for (Tiro t : tiros)
    //     t.Draw(DRAW_3D, &texturas["tiro"]);

    glPopMatrix();
}

void Jogo::DrawMiniMapa(float _w, float _h)
{

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, _w, _h, 0, -1, 1);
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glTranslatef(_w - (arena.largura * 0.25) - 5, _h - (arena.altura * 0.25) - 5, 0);
    glScalef(0.25, 0.25, 1);
    glPushMatrix();

    arena.DrawArestas();
    //postoAbastecimento.Draw(DRAW_2D);
    // for (Circle c : objetosResgate)
    //     c.Draw(DRAW_2D);
    // for (Tiro t : tiros)
    //     t.Draw(DRAW_2D);
    //for (Lutador h : inimigos)

    oponente.area.Draw2d({1, 0, 0});
    jogador.area.Draw2d({0, 1, 0});

    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Jogo::DrawArena()
{
    int alturaArena = jogador.area.raio * 7;
    // Textura *texturaParede = &texturas["posto"];

    glPushMatrix();
    {

        // desenha o chão
        arena.posicao.setZ(0);
        // arena.cor = Cor("lightgray");
        arena.Draw(this->texturaChao, {0, 0, 1}); // mudar Jogo

        // desenha o céu
        glPushMatrix();
        {
            ceu = arena;
            ceu.posicao.setZ(-alturaArena); // sinal negativo significa inversão da Normal
            // ceu.fatorRepeticaoTextura = 1;
            ceu.Draw(this->texturaCeu, {1, 1, 1});
        }
        glPopMatrix();

        // desenha as paredes
        glPushMatrix();
        {
            Retangulo parede1 = Retangulo(-alturaArena, 0, alturaArena, arena.altura);
            glRotatef(90, 0, 1, 0);
            parede1.Draw(this->texturaParede, {0, 1, 1});
        }
        glPopMatrix();

        glPushMatrix();
        {
            Retangulo parede2 = Retangulo(0, -alturaArena, arena.largura, alturaArena);
            glRotatef(-90, 1, 0, 0);
            parede2.Draw(this->texturaParede, {0, 1, 1});
        }
        glPopMatrix();

        glPushMatrix();
        {
            Retangulo parede3 = Retangulo(0, 0, alturaArena, arena.altura);
            glTranslatef(arena.largura, 0, 0);
            glRotatef(-90, 0, 1, 0);
            parede3.Draw(this->texturaParede, {0, 1, 1});
        }
        glPopMatrix();

        glPushMatrix();
        {
            Retangulo parede4 = Retangulo(0, 0, arena.largura, alturaArena);
            glTranslatef(0, arena.altura, 0);
            glRotatef(90, 1, 0, 0);
            parede4.Draw(this->texturaParede, {0, 1, 1});
        }
        glPopMatrix();

        //desenha o posto de abastecimento
        // glPushMatrix();
        // glTranslatef(0, 0, 0.2);
        // postoAbastecimento.Draw(DRAW_3D, &texturas["posto"]);
        // glPopMatrix();
    }
    glPopMatrix();
}

// void Jogo::DrawIndicadores()
// {
//     jogador.desenharCombustivel(10, arena.altura - 10, NUMERO_DE_MARCADORES_COMBUSTIVEL);
//     jogador.desenharResgates(10, arena.altura - 50, nObjetos);
// }

void Jogo::DrawOrtho(void (Jogo::*funcao)(), bool desabilitarTextura, bool desabilitarLuz)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, arena.largura, arena.altura, 0, -1, 1);
    glPushAttrib(GL_ENABLE_BIT);
    if (desabilitarLuz)
        glDisable(GL_LIGHTING);
    if (desabilitarTextura)
        glDisable(GL_TEXTURE_2D);
    (this->*funcao)();
    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Jogo::DrawResultado()
{
    GLuint t;
    switch (lutaAtual)
    {
    case 1: //jogador ganhou
        //t = Textura("win.bmp").get();
        break;
    case 2: //jogador perdeu
        //t = Textura("lose.bmp").get();
        break;
    }

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, t);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);
    glTexCoord2f(0, 1);
    glVertex3f(0, 1, 0);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, 0);
    glTexCoord2f(1, 0);
    glVertex3f(1, 0, 0);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// void Arena::MostraDados()
// {
//     cout << "A arena foi criada com:" << endl;
//     cout << " - " << ((arena.id == "Arena") ? 1 : 0) << " arena" << endl;
//     cout << " - " << ((postoAbastecimento.id == "PostoAbastecimento") ? 1 : 0) << " posto de abastecimento" << endl;
//     cout << " - " << ((jogador.area.id == "Jogador") ? 1 : 0) << " jogador" << endl;
//     //cout << " - " << (oponente.size()) << " inimigo(s)" << endl;
//     //cout << " - " << (objetosResgate.size()) << " objeto(s) de resgate" << endl
//     //<< endl;
// }

// void Arena::ImprimeElemento(Cor corElemento)
// {
//     for (auto i : this->mapaCorID)
//     {
//         if (i.second == corElemento)
//             cout << "Voce clicou em '" << i.first << "'!" << endl;
//     }
// }

void Jogo::defineCamera(bool desenhaCockpit)
{
    if (camera == cam3)
    {
        // inicial
        Ponto posicaoCamera = Ponto(0, 0, 0);
        posicaoCamera.setX(jogador.area.posicao.getX());
        posicaoCamera.setY(jogador.area.posicao.getY());
        posicaoCamera.setZ(jogador.area.posicao.getZ() * 2);

        // desloca a camera em uma 'esfera virtual'
        Ponto direcaoCamera = Ponto(0, 0, 0);
        direcaoCamera.setZ(cos(camPitch * M_PI / 180.0));
        posicaoCamera.setZ(posicaoCamera.getZ() + camDistanciaJogador * -direcaoCamera.getZ());

        // limita a câmera para não passar do chão
        if (posicaoCamera.getZ() < 0)
        // if (posicaoCamera.z <  this->jogador.area.raio)
        {
            // posicaoCamera.z = this->jogador.area.raio;
            direcaoCamera.setX(sin(camYaw * M_PI / 180.0));
            direcaoCamera.setY(cos(camYaw * M_PI / 180.0));
            posicaoCamera.setZ(0);
        }
        else
        {
            direcaoCamera.setX(sin(camYaw * M_PI / 180.0) * sin(camPitch * M_PI / 180.0));
            direcaoCamera.setY(cos(camYaw * M_PI / 180.0) * sin(camPitch * M_PI / 180.0));
        }
        posicaoCamera.setX(posicaoCamera.getX() + camDistanciaJogador * -direcaoCamera.getX());
        posicaoCamera.setY(posicaoCamera.getY() + camDistanciaJogador * -direcaoCamera.getY());

        // posiciona a camera olhando para o jogador
        gluLookAt(posicaoCamera.getX(), posicaoCamera.getY(), posicaoCamera.getZ(), jogador.area.posicao.getX(), jogador.area.posicao.getY(), jogador.area.posicao.getZ(), 0, 0, -1);
    }
    else if (camera == cam2)
    {

        // Ponto posicaoCamera = Ponto(0, 0, 0);
        // Ponto direcaoCamera = Ponto(0, 0, 0);
        // jogador.getInfoCanhao(posicaoCamera, direcaoCamera);

        // // move a camera para cima do canhao
        // posicaoCamera.setZ(posicaoCamera.getZ() + 10);
        // Ponto look = Ponto(posicaoCamera.getX() + direcaoCamera.getX(), posicaoCamera.getY() + direcaoCamera.getY(), posicaoCamera.getZ() + direcaoCamera.getZ());

        // // posiciona a camera olhando para o jogador
        // gluLookAt(posicaoCamera.getX(), posicaoCamera.getY(), posicaoCamera.getZ(), look.getX(), look.getY(), look.getZ(), 0, 0, -1);
    }
    else if (camera == cam1)
    {
        Ponto posicaoCamera = jogador.getPosicao();
        // Ponto direcaoCamera = jogador.getDirecao();
        Ponto direcaoCamera = Ponto(0,0,0);

        // move a camera para o cockpit
        posicaoCamera.setX(posicaoCamera.getX() + direcaoCamera.getX() * 15);
        posicaoCamera.setY(posicaoCamera.getY() + direcaoCamera.getY() * 15 - this->jogador.area.raio / 2.0);
        posicaoCamera.setZ(posicaoCamera.getZ() + direcaoCamera.getZ() * 15 + this->jogador.area.raio * 2.0);

        Ponto look = Ponto(posicaoCamera.getX() + direcaoCamera.getX(), posicaoCamera.getY() + direcaoCamera.getY(), posicaoCamera.getZ() + direcaoCamera.getZ());

        // posiciona a camera olhando para o jogador
        gluLookAt(posicaoCamera.getX(), posicaoCamera.getY(), posicaoCamera.getZ(), look.getX(), look.getY(), look.getZ(), 0, 0, -1);

        // Ponto direcaoCamera = Ponto(0, 0, 0);
        // Ponto posicaoCamera = jogador.getPosicao();
        // // Ponto direcaoCamera = jogador.getDirecao();

        // posicaoCamera.setX(posicaoCamera.getX() + direcaoCamera.getX() * 15);
        // posicaoCamera.setY(posicaoCamera.getY() + direcaoCamera.getY() * 15 - this->jogador.area.raio / 2);
        // posicaoCamera.setZ(posicaoCamera.getZ() + direcaoCamera.getZ() * 15 + this->jogador.area.raio * 2);

        // Ponto look = Ponto(posicaoCamera.getX() + direcaoCamera.getX(), posicaoCamera.getY() + direcaoCamera.getY(), posicaoCamera.getZ() + direcaoCamera.getZ());

        // // posiciona a camera olhando para o jogador
        // gluLookAt(posicaoCamera.getX(), posicaoCamera.getY(), posicaoCamera.getZ(), look.getX(), look.getY(), look.getZ(), 0, 0, -1);
    }
    // else if (camera == cam4)
    // {
    //     // Ponto posicaoCamera = Ponto(0, 0, 0);
    //     // Ponto direcaoCamera = Ponto(0, 0, 0);
    //     Ponto posicaoCamera = oponente.getPosicao();
    //     Ponto direcaoCamera = oponente.getDirecao();

    //     // move a camera para o cockpit
    //     posicaoCamera.setX(posicaoCamera.getX() + direcaoCamera.getX() * 15);
    //     posicaoCamera.setY(posicaoCamera.getY() + direcaoCamera.getY() * 15 + -this->oponente.area.raio / 2);
    //     posicaoCamera.setZ(posicaoCamera.getZ() + direcaoCamera.getZ() * 15 + this->oponente.area.raio * 2);

    //     Ponto look = Ponto(posicaoCamera.getX() + direcaoCamera.getX(), posicaoCamera.getY() + direcaoCamera.getY(), posicaoCamera.getZ() + direcaoCamera.getZ());

    //     // posiciona a camera olhando para o lutador
    //     gluLookAt(posicaoCamera.getX(), posicaoCamera.getY(), posicaoCamera.getZ(), look.getX(), look.getY(), look.getZ(), 0, 0, -1);
    // }

    if (!desenhaCockpit)
        return;

    Ponto posicaoCamera = jogador.getPosicao();
    Ponto direcaoCamera = jogador.getDirecao();

    // move a camera para o cockpit
    posicaoCamera.setX(posicaoCamera.getX() + direcaoCamera.getX() * 15);
    posicaoCamera.setY(posicaoCamera.getY() + direcaoCamera.getY() * 15 - this->jogador.area.raio / 2.0);
    posicaoCamera.setZ(posicaoCamera.getZ() + direcaoCamera.getZ() * 15 + this->jogador.area.raio * 2.0);

    Ponto look = Ponto(posicaoCamera.getX() + direcaoCamera.getX(), posicaoCamera.getY() + direcaoCamera.getY(), posicaoCamera.getZ() + direcaoCamera.getZ());

    glPushMatrix();
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glColor3f(0.0, 1.0, 1.0);
    glTranslatef(look.getX(), look.getY(), look.getZ());
    glRotatef(jogador.angulo, 0, 0, 1);
    glScalef(5, 5, 5);
    glutWireCube(1);
    glEnable(GL_LIGHTING);
    glPopAttrib();
    glPopMatrix();
}

void Jogo::defineLuz0()
{
    if (!ativaLuz0)
    {
        glDisable(GL_LIGHT0);
        return;
    }

    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glPushMatrix();
    glPushAttrib(GL_ENABLE_BIT);

    // move a luz para a posição desejada
    glTranslatef(arena.largura / 2.0, arena.altura / 2.0, jogador.area.raio * 10);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glPopAttrib();
    glPopMatrix();
}

void Jogo::defineLuz1()
{
    if (!ativaLuz1)
    {
        glDisable(GL_LIGHT1);
        return;
    }

    glEnable(GL_LIGHT1);
    GLfloat light_position[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat light_color[] = {1.0f, 1.0f, 1.0f, 1.0f}; // cor branca

    glPushMatrix();
    glPushAttrib(GL_ENABLE_BIT);

    // move a luz para a posição desejada
    glTranslatef(arena.largura / 2.0, arena.altura / 2.0, 10);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_color);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);

    glPopAttrib();
    glPopMatrix();
}

// void Jogo::desenhaOrigemDoSC()
// {
//     GLfloat mat_ambient_r[] = {1.0, 0.0, 0.0, 1.0};
//     GLfloat mat_ambient_g[] = {0.0, 1.0, 0.0, 1.0};
//     GLfloat mat_ambient_b[] = {0.0, 0.0, 1.0, 1.0};

//     glPushAttrib(GL_ENABLE_BIT);
//     glDisable(GL_LIGHTING);
//     glDisable(GL_TEXTURE_2D);

//     //x axis
//     glPushMatrix();
//     glColor3fv(mat_ambient_r);
//     glScalef(5, 0.3, 0.3);
//     glTranslatef(0.5, 0, 0); // put in one end
//     glutSolidCube(50.0);
//     glPopMatrix();

//     //y axis
//     glPushMatrix();
//     glColor3fv(mat_ambient_g);
//     glRotatef(90, 0, 0, 1);
//     glScalef(5, 0.3, 0.3);
//     glTranslatef(0.5, 0, 0); // put in one end
//     glutSolidCube(50.0);
//     glPopMatrix();

//     //z axis
//     glPushMatrix();
//     glColor3fv(mat_ambient_b);
//     glRotatef(-90, 0, 1, 0);
//     glScalef(5, 0.3, 0.3);
//     glTranslatef(0.5, 0, 0); // put in one end
//     glutSolidCube(50.0);
//     glPopMatrix();
//     glPopAttrib();
// }

// bool Jogo::estaDentro(Tiro tiro)
// {
//     Ponto p = tiro.posicao;
//     int r = tiro.raio;
//     bool dentro_x = (p.x > r && std::abs(p.x - arena.largura) > r);
//     bool dentro_y = (p.y > r && std::abs(p.y - arena.altura) > r);
//     bool dentro_z = (p.z > r && std::abs(p.z - (jogador.area.raio * 5)) > r);
//     return (dentro_x && dentro_y && dentro_z);
// }
