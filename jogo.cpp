#include "jogo.h"

using namespace std;

Jogo::Jogo()
{
    this->lutaAtual = jogoON;
    camera = cam1;
    camSubida = 135;
}

void Jogo::desenhaJogo()
{
    glPushMatrix();
    {
        cameras();
        luzes();
        jogador.desenhaLutador({0.0, 1.0, 0.0});
        oponente.desenhaLutador({1.0, 0, 0});
        desenhaRing();
    }
    glPopMatrix();
}

void Jogo::desenhaMiniMapa(float width, float heigth)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    {
        glLoadIdentity();
        glOrtho(0, width, heigth, 0, -1, 1);
        glPushAttrib(GL_ENABLE_BIT);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glTranslatef(width - (ring.width/4) - 2, heigth - (ring.height/4) - 2, 0);
        glScalef(0.25, 0.25, 1);
    }
    glPushMatrix();

    jogador.aCirc.circuloMMapa({0, 1, 0});
    oponente.aCirc.circuloMMapa({1, 0, 0});
    ring.desenhaRetMiniMapa();

    glPopMatrix();
    glEnable(GL_LIGHTING);
    glPopAttrib();
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void Jogo::desenhaRing()
{
    int alturaArena = jogador.aCirc.raio * 3 * 2;

    glPushMatrix();
    {
        // desenha o chão
        glPushMatrix();
        {
            ring.pos.setZ(0);
            if (this->cenario)
                ring.desenhaRetangulo(this->texturaChao, {0, 0, 1});
            else
                ring.desenhaRetangulo(this->texturaEsChao, {0, 0, 1});
        }
        glPopMatrix();

        // desenha o céu
        glPushMatrix();
        {
            ceu = ring;
            ceu.pos.setZ(-alturaArena);
            if (this->luz)
            {
                if (this->cenario)
                    ceu.desenhaRetangulo(this->texturaCeuDia, {1, 1, 1});
                else
                    ceu.desenhaRetangulo(this->texturaEsCeuDia, {1, 1, 1});
            }
            else
            {
                ceu.desenhaRetangulo(this->texturaCeuNoite, {1, 1, 1});
            }
        }
        glPopMatrix();

        // desenha os cantos
        glPushMatrix();
        {
            Retangulo lado1 = Retangulo(-alturaArena, 0, alturaArena, ring.height);
            glRotatef(90, 0, 1, 0);
            if (this->cenario)
                lado1.desenhaRetangulo(this->texturaParede3, {0, 1, 1});
            else
                lado1.desenhaRetangulo(this->texturaParedeEs3, {0, 1, 1});
        }
        glPopMatrix();

        glPushMatrix();
        {
            Retangulo lado2 = Retangulo(0, -alturaArena, ring.width, alturaArena);
            glRotatef(-90, 1, 0, 0);
            if (this->cenario)
                lado2.desenhaRetangulo(this->texturaParede2, {0, 1, 1});
            else
                lado2.desenhaRetangulo(this->texturaParedeEs2, {0, 1, 1});
        }
        glPopMatrix();

        glPushMatrix();
        {
            Retangulo lado3 = Retangulo(0, 0, alturaArena, ring.height);
            glTranslatef(ring.width, 0, 0);
            glRotatef(-90, 0, 1, 0);
            if (this->cenario)
                lado3.desenhaRetangulo(this->texturaParede1, {0, 1, 1});
            else
                lado3.desenhaRetangulo(this->texturaParedeEs1, {0, 1, 1});
        }
        glPopMatrix();

        glPushMatrix();
        {
            Retangulo lado4 = Retangulo(0, 0, ring.width, alturaArena);
            glTranslatef(0, ring.height, 0);
            glRotatef(90, 1, 0, 0);
            if (this->cenario)
                lado4.desenhaRetangulo(this->texturaParede4, {0, 1, 1});
            else
                lado4.desenhaRetangulo(this->texturaParedeEs4, {0, 1, 1});
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void Jogo::cameras()
{
    if (camera == cam1)
    {
        Ponto pCam = jogador.aCirc.posicao;
        Ponto dCam = jogador.direcaoLutador();

        pCam.setX(pCam.getX() + dCam.getX() * 0.9 * this->jogador.aCirc.raio / 2);
        pCam.setY(pCam.getY() + dCam.getY() * 0.9 * this->jogador.aCirc.raio / 2);
        pCam.setZ(pCam.getZ() + dCam.getZ() * 15 + this->jogador.aCirc.raio * 2.25);
        Ponto l = Ponto(pCam.getX() + dCam.getX(), pCam.getY() + dCam.getY(), pCam.getZ() + dCam.getZ());
        gluLookAt(pCam.getX(), pCam.getY(), pCam.getZ(), l.getX(), l.getY(), l.getZ(), 0, 0, -1);
    }
    else if (camera == cam2)
    {
        Ponto pCam = jogador.verificaSocoDir();
        Ponto dCam = jogador.direcaoLutador();

        pCam.setX(pCam.getX() - dCam.getX() * 0.7 * this->jogador.aCirc.raio);
        pCam.setY(pCam.getY() - dCam.getY() * 0.7 * this->jogador.aCirc.raio);
        pCam.setZ(pCam.getZ() + this->jogador.aCirc.raio / 2);
        Ponto l = Ponto(pCam.getX() + dCam.getX(), pCam.getY() + dCam.getY(), pCam.getZ() + dCam.getZ());
        gluLookAt(pCam.getX(), pCam.getY(), pCam.getZ(), l.getX(), l.getY(), l.getZ(), 0, 0, -1);
    }
    else if (camera == cam3)
    {
        Ponto pCam = Ponto(0, 0, 0);
        pCam.setX(jogador.aCirc.posicao.getX());
        pCam.setY(jogador.aCirc.posicao.getY());
        pCam.setZ(jogador.aCirc.posicao.getZ() * 4);
        Ponto dCam = Ponto(0, 0, 0);
        dCam.setZ(cos(camSubida * M_PI / 180.0));
        pCam.setZ(pCam.getZ() + camDistanciaJogador * -dCam.getZ());

        if (pCam.getZ() < 30)
        {
            dCam.setX(sin(camRotacao * M_PI / 180.0));
            dCam.setY(cos(camRotacao * M_PI / 180.0));
            pCam.setZ(30);
        }
        else
        {
            dCam.setX(sin(camRotacao * M_PI / 180.0) * sin(camSubida * M_PI / 180.0));
            dCam.setY(cos(camRotacao * M_PI / 180.0) * sin(camSubida * M_PI / 180.0));
        }
        pCam.setX(pCam.getX() + camDistanciaJogador * -dCam.getX());
        pCam.setY(pCam.getY() + camDistanciaJogador * -dCam.getY());
        gluLookAt(pCam.getX(), pCam.getY(), pCam.getZ(), jogador.aCirc.posicao.getX(), jogador.aCirc.posicao.getY(), jogador.aCirc.posicao.getZ(), 0, 0, -1);
    }
    else if (camera == cam4)
    {
        Ponto pCam = oponente.aCirc.posicao;
        Ponto dCam = oponente.direcaoLutador();

        pCam.setX(pCam.getX() + dCam.getX() * 0.9 * this->oponente.aCirc.raio / 2);
        pCam.setY(pCam.getY() + dCam.getY() * 0.9 * this->oponente.aCirc.raio / 2);
        pCam.setZ(pCam.getZ() + dCam.getZ() * 15 + this->oponente.aCirc.raio * 2.25);
        Ponto l = Ponto(pCam.getX() + dCam.getX(), pCam.getY() + dCam.getY(), pCam.getZ() + dCam.getZ());
        gluLookAt(pCam.getX(), pCam.getY(), pCam.getZ(), l.getX(), l.getY(), l.getZ(), 0, 0, -1);
    }
}

void Jogo::luzes()
{
    if (!luz)
    {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        glEnable(GL_LIGHT3);
        glPushMatrix();
        {
            glTranslatef(this->jogador.aCirc.posicao.getX(), this->jogador.aCirc.posicao.getY(), jogador.aCirc.raio * 6);
            GLfloat spot_direction[] = {0.0, 0.0, -1.0};
            GLfloat light_ambient[] = {.6, .6, .6, 1.0};
            GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
            GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
            GLfloat light_position2[] = {0.0, 0.0, 0.0, 1.0};
            glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
            glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
            glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
            glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
            glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45);
            glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
            glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(this->oponente.aCirc.posicao.getX(), this->oponente.aCirc.posicao.getY(), jogador.aCirc.raio * 6);
            GLfloat spot_direction[] = {0.0, 0.0, -1.0};
            GLfloat light_ambient[] = {.6, .6, .6, 1.0};
            GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
            GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
            GLfloat light_position2[] = {0.0, 0.0, 0.0, 1.0};
            glLightfv(GL_LIGHT3, GL_POSITION, light_position2);
            glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
            glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
            glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
            glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45);
            glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
            glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
        }
        glPopMatrix();
    }
    else
    {
        glDisable(GL_LIGHT2);
        glDisable(GL_LIGHT3);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat light_color[] = {1.0, 1.0, 1.0, 1.0};

        glPushMatrix();
        {
            glPushAttrib(GL_ENABLE_BIT);
            glTranslatef(ring.width / 2.0, ring.height / 2.0, jogador.aCirc.raio * 10);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            glLightfv(GL_LIGHT1, GL_AMBIENT, light_color);
            glPopAttrib();
        }
        glPopMatrix();
    }
}
