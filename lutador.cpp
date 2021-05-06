#include "lutador.h"
#include <stdio.h>

using namespace std;

OBJ *cabeca;

Lutador::Lutador()
{
    aCirc.posicao.setZ(this->aCirc.raio / 2.0);
}

void Lutador::desenhaLutador(Cores cor)
{
    glPushMatrix();
    {
        glTranslatef(this->aCirc.posicao.getX(), this->aCirc.posicao.getY(), this->aCirc.posicao.getZ());
        glRotatef(angulo, 0, 0, 1);
        desenharCorpo(cor);
    }
    glPopMatrix();
}

void Lutador::desenharCorpo(Cores cor)
{
    glPushMatrix();
    {
        glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());

        //perna direita
        glPushMatrix();
        {
            glBindTexture(GL_TEXTURE_2D, this->texturaBermuda);
            glTranslatef(0, this->aCirc.raio / 4, this->aCirc.raio / 2);
            glRotatef(this->anguloPerna, 0, 1, 0);
            glPushMatrix();
            {
                glScalef(this->aCirc.raio / 4, this->aCirc.raio / 4, this->aCirc.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, this->texturaPele);
            glTranslatef(0, 0, -this->aCirc.raio / 2);
            glScalef(this->aCirc.raio / 4, this->aCirc.raio / 4, this->aCirc.raio);
            desenhaCubo();
        }
        glPopMatrix();

        //perna esquerda
        glPushMatrix();
        {
            glBindTexture(GL_TEXTURE_2D, this->texturaBermuda);
            glTranslatef(0, -this->aCirc.raio / 4, this->aCirc.raio / 2);
            glRotatef(-this->anguloPerna, 0, 1, 0);
            glPushMatrix();
            {
                glScalef(this->aCirc.raio / 4, this->aCirc.raio / 4, this->aCirc.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, this->texturaPele);
            glTranslatef(0, 0, -this->aCirc.raio / 2);
            glScalef(this->aCirc.raio / 4, this->aCirc.raio / 4, this->aCirc.raio);
            desenhaCubo();
        }
        glPopMatrix();

        // tronco
        glPushMatrix();
        {
            glBindTexture(GL_TEXTURE_2D, this->texturaCamisa);
            glTranslatef(0, 0, 1.5 * this->aCirc.raio);
            glScalef(this->aCirc.raio / 2, this->aCirc.raio, 2 * this->aCirc.raio);
            desenhaCubo();
        }
        glPopMatrix();

        // braco direito
        glPushMatrix();
        {
            glBindTexture(GL_TEXTURE_2D, this->texturaCamisa);
            glTranslatef(0, this->aCirc.raio / 2 * 0.95, 1.5 * this->aCirc.raio * 0.92);
            glRotatef(90, 1, 0, 0);
            glRotatef(-this->theta1, 0, 1, 0);
            glRotatef(this->thetaElevacao, 0, 0, 1);
            glPushMatrix();
            {
                glScalef(this->aCirc.raio / 6, this->aCirc.raio / 6, 2 * this->aCirc.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, this->texturaPele);
            glTranslatef(0, 0, 2 * (-this->aCirc.raio) / 2 * 0.92);
            glRotatef(-this->theta2, 0, 1, 0);
            glPushMatrix();
            {
                glScalef(this->aCirc.raio / 7, this->aCirc.raio / 7, 2 * this->aCirc.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glTranslatef(0, 0, -this->aCirc.raio / 2 * 2);
            // DrawAxes();

            // desenha luva
            glBindTexture(GL_TEXTURE_2D, this->texturaLuva);
            glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
            glRotatef(180, 1, 0, 0);
            glRotatef(180, 0, 1, 0);

            OBJ *obj = CreateSphere(this->aCirc.raio / 5, 10);
            glBegin(GL_TRIANGLE_STRIP);
            {
                for (int i = 0; i < obj->numVtx; i++)
                {
                    glNormal3f(obj->vtx[i].nX, obj->vtx[i].nY, obj->vtx[i].nZ);
                    glTexCoord2f(obj->vtx[i].U, obj->vtx[i].V);
                    glVertex3f(obj->vtx[i].X, obj->vtx[i].Y, obj->vtx[i].Z);
                }
                delete[] obj->vtx;
                glEnd();
            }
        }
        glPopMatrix();

        // desenha braco esquerdo
        glPushMatrix();
        {
            glBindTexture(GL_TEXTURE_2D, this->texturaCamisa);
            glTranslatef(0, -this->aCirc.raio / 2 * 0.95, 1.5 * this->aCirc.raio * 0.92);
            glRotatef(-90, 1, 0, 0);
            glRotatef(-this->theta3, 0, 1, 0);
            glRotatef(-this->thetaElevacao, 0, 0, 1);
            glPushMatrix();
            {
                glScalef(this->aCirc.raio / 6, this->aCirc.raio / 6, 2 * this->aCirc.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glBindTexture(GL_TEXTURE_2D, this->texturaPele);
            glTranslatef(0, 0, -this->aCirc.raio / 2 * 0.92 * 2);
            glRotatef(-this->theta4, 0, 1, 0);
            glPushMatrix();
            {
                glScalef(this->aCirc.raio / 7, this->aCirc.raio / 7, 2 * this->aCirc.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glTranslatef(0, 0, -this->aCirc.raio / 2 * 2);
            // DrawAxes();

            // desenha luva
            glBindTexture(GL_TEXTURE_2D, this->texturaLuva);
            glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
            OBJ *obj = CreateSphere(this->aCirc.raio / 5, 10);
            glBegin(GL_TRIANGLE_STRIP);
            {
                for (int i = 0; i < obj->numVtx; i++)
                {
                    glNormal3f(obj->vtx[i].nX, obj->vtx[i].nY, obj->vtx[i].nZ);
                    glTexCoord2f(obj->vtx[i].U, obj->vtx[i].V);
                    glVertex3f(obj->vtx[i].X, obj->vtx[i].Y, obj->vtx[i].Z);
                }
                delete[] obj->vtx;
                glEnd();
            }
        }
        glPopMatrix();

        // cabeca
        glPushMatrix();
        {
            glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
            glBindTexture(GL_TEXTURE_2D, this->texturaCabeca);
            glTranslatef(0, 0, this->aCirc.raio * 2);
            glPushMatrix();
            glRotatef(180, 0, 1, 0);
            glRotatef(-90, 0, 0, 1);

            OBJ *obj = CreateSphere(this->aCirc.raio / 2, 10);
            glBegin(GL_TRIANGLE_STRIP);
            {
                for (int i = 0; i < obj->numVtx; i++)
                {
                    glNormal3f(obj->vtx[i].nX, obj->vtx[i].nY, obj->vtx[i].nZ);
                    glTexCoord2f(obj->vtx[i].U, obj->vtx[i].V);
                    glVertex3f(obj->vtx[i].X, obj->vtx[i].Y, obj->vtx[i].Z);
                }
                delete[] obj->vtx;
                glEnd();
            }
            glPopMatrix();

            // // desenha nariz
            // glBindTexture(GL_TEXTURE_2D, this->texturaPele);
            // glTranslatef(this->aCirc.raio / 2, 0, 0);
            // OBJ *obj2 = CreateSphere(this->aCirc.raio / 2 * 0.3, 10);
            // glBegin(GL_TRIANGLE_STRIP);
            // {
            //     for (int i = 0; i < obj2->numVtx; i++)
            //     {
            //         glNormal3f(obj2->vtx[i].nX, obj2->vtx[i].nY, obj2->vtx[i].nZ);
            //         glTexCoord2f(obj2->vtx[i].U, obj2->vtx[i].V);
            //         glVertex3f(obj2->vtx[i].X, obj2->vtx[i].Y, obj2->vtx[i].Z);
            //     }
            //     delete[] obj2->vtx;
            //     glEnd();
            // }
            // // DrawAxes();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

Ponto Lutador::verificaSocoDir()
{
    Ponto luvaDir = {0.0, 0.0, this->thetaElevacao};

    // antebraço + rotação
    Ponto a = {0.0, this->aCirc.raio * (float)1.0, 0.0};
    luvaDir = translated(luvaDir, a);
    luvaDir = rotated(luvaDir, -this->theta2);

    // // braco direito ate cotovelo + rotacao
    Ponto b = {0, (float)0.92 * this->aCirc.raio, 0};
    luvaDir = translated(luvaDir, b);
    luvaDir = rotated(luvaDir, -this->theta1);

    Ponto c = {0, this->aCirc.raio / (float)2.0 * (float)0.95, (float)1.5 * this->aCirc.raio * (float)0.92};
    luvaDir = translated(luvaDir, c);

    luvaDir = rotated(luvaDir, this->angulo);

    luvaDir = translated(luvaDir, this->aCirc.posicao);

    luvaDir = {luvaDir.getX(), luvaDir.getY(), luvaDir.getZ() * (float)0.92};

    return luvaDir;
}

Ponto Lutador::verificaSocoEsq()
{
    Ponto luvaEsq = {0.0, 0.0, this->thetaElevacao};

    // antebraço + rotação
    Ponto a = {0.0, -this->aCirc.raio * (float)1.0, 0.0};
    luvaEsq = translated(luvaEsq, a);
    luvaEsq = rotated(luvaEsq, this->theta4);

    // // braco direito ate cotovelo + rotacao
    Ponto b = {0, -(float)0.92 * this->aCirc.raio, 0};
    luvaEsq = translated(luvaEsq, b);
    luvaEsq = rotated(luvaEsq, this->theta3);

    Ponto c = {0, -this->aCirc.raio / (float)2.0 * (float)0.95, (float)1.5 * this->aCirc.raio * (float)0.92};
    luvaEsq = translated(luvaEsq, c);

    luvaEsq = rotated(luvaEsq, this->angulo);

    luvaEsq = translated(luvaEsq, this->aCirc.posicao);

    luvaEsq = {luvaEsq.getX(), luvaEsq.getY(), luvaEsq.getZ() * (float)0.92};

    return luvaEsq;
}

Ponto Lutador::translated(Ponto p, Ponto pAntigo)
{
    p.setX(p.getX() + pAntigo.getX());
    p.setY(p.getY() + pAntigo.getY());
    p.setZ(p.getZ() + pAntigo.getZ());
    return p;
}

Ponto Lutador::rotated(Ponto p, float angle)
{
    Ponto rotated = {0, 0, p.getZ()};
    rotated.setX(p.getX() * cos(M_PI * angle / 180.0) - p.getY() * sin(M_PI * angle / 180.0));
    rotated.setY(p.getX() * sin(M_PI * angle / 180.0) + p.getY() * cos(M_PI * angle / 180.0));
    return rotated;
}

Ponto Lutador::direcaoLutador()
{
    Ponto direcao = Ponto(cos((angulo)*M_PI / 180.0), sin((angulo)*M_PI / 180.0), 0);
    return direcao;
}

void Lutador::andaFrente(GLdouble time)
{
    aCirc.posicao.setX(aCirc.posicao.getX() + cos((360.0 - angulo) * (M_PI / 180.0)) * velocidade * time);
    aCirc.posicao.setY(aCirc.posicao.getY() - sin((360.0 - angulo) * (M_PI / 180.0)) * velocidade * time);

    if (this->anguloPerna < 20 && pernaIndo)
    {
        if (this->anguloPerna == 19)
        {
            pernaVoltando = true;
            pernaIndo = false;
            this->anguloPerna -= 1;
        }
        this->anguloPerna += 1;
    }
    else if (this->anguloPerna < 20 && pernaVoltando)
    {
        if (this->anguloPerna == -19)
        {
            pernaIndo = true;
            pernaVoltando = false;
            this->anguloPerna += 1;
        }
        this->anguloPerna -= 1;
    }
}

void Lutador::andaTras(GLdouble time)
{
    aCirc.posicao.setX(aCirc.posicao.getX() - cos((360.0 - angulo) * (M_PI / 180.0)) * velocidade * time);
    aCirc.posicao.setY(aCirc.posicao.getY() + sin((360.0 - angulo) * (M_PI / 180.0)) * velocidade * time);

    if (this->anguloPerna < 20 && pernaIndo)
    {
        if (this->anguloPerna == 19)
        {
            pernaVoltando = true;
            pernaIndo = false;
            this->anguloPerna -= 1;
        }
        this->anguloPerna += 1;
    }
    else if (this->anguloPerna < 20 && pernaVoltando)
    {
        if (this->anguloPerna == -19)
        {
            pernaIndo = true;
            pernaVoltando = false;
            this->anguloPerna += 1;
        }
        this->anguloPerna -= 1;
    }
}
