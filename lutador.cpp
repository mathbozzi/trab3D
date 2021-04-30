#include "lutador.h"
#include <stdio.h>

using namespace std;

OBJ *cabeca;

Lutador::Lutador()
{
    area.posicao.setZ(this->area.raio / 2.0);
    //anguloHelice = 0;
    //angulo = 180;
    anguloCanhaoYaw = 0;
    anguloCanhaoPitch = 0;

    //voando = false;
    //velocidadeHelice = 1;
    //tempoAtualDeVoo = 0;
    //objetosResgatados = 0;
    // corCorpo = Cor(0,1,1);
}

void Lutador::Draw(Cores cor)
{
    // draw3d = (flag == DRAW_2D) ? false : true;

    // if (desenhaEsfera)
    //     area.Draw();
    // glPushMatrix();
    // glTranslatef(300, 300, 105);
    // DrawAxes();
    // glPopMatrix();

    glPushMatrix();

    // move ele para a posição do circulo do jogador
    glTranslatef(this->area.posicao.getX(), this->area.posicao.getY(), this->area.posicao.getZ());

    // redimensiona ele para caber dentro do circulo
    // printf("%d",this->area.raio);
    // glScalef(this->area.raio/(this->area.raio *0.3), this->area.raio/(this->area.raio *0.3) , 1);
    // glScalef(this->area.raio * 2 / 85.0, this->area.raio * 2 / 85.0, 1);

    // ajustarAngulo();
    glRotatef(angulo, 0, 0, 1);

    //desenharCanhao(canhao);
    desenharCorpo(cor);
    //desenharHelice(helice);

    glPopMatrix();
}

void Lutador::desenharCorpo(Cores cor)
{

    glPushMatrix();
    {
        glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
        glBindTexture(GL_TEXTURE_2D, this->textura);
        // glTranslatef(0, 0, 1);

        // if (textura != NULL)
        // glBindTexture(GL_TEXTURE_2D, textura->get());

        //perna direita
        glPushMatrix();
        {
            glTranslatef(0, this->area.raio / 4, this->area.raio / 2);
            glRotatef(this->anguloPerna, 0, 1, 0); // angulo perna
            glPushMatrix();
            {
                glScalef(this->area.raio / 4, this->area.raio / 4, this->area.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glTranslatef(0, 0, -this->area.raio / 2);
            glScalef(this->area.raio / 4, this->area.raio / 4, this->area.raio);
            desenhaCubo();
        }
        glPopMatrix();

        //perna esquerda
        glPushMatrix();
        {
            glTranslatef(0, -this->area.raio / 4, this->area.raio / 2);
            glRotatef(-this->anguloPerna, 0, 1, 0); // angulo perna
            glPushMatrix();
            {
                glScalef(this->area.raio / 4, this->area.raio / 4, this->area.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glTranslatef(0, 0, -this->area.raio / 2);
            glScalef(this->area.raio / 4, this->area.raio / 4, this->area.raio);
            desenhaCubo();
        }
        glPopMatrix();

        // // tronco
        glPushMatrix();
        {
            glTranslatef(0, 0, 1.5 * this->area.raio);
            glScalef(this->area.raio / 2, this->area.raio, 2 * this->area.raio);
            desenhaCubo();
        }
        glPopMatrix();

        // desenha braco direito
        glPushMatrix();
        {
            glTranslatef(0, this->area.raio / 2 * 0.95, 1.5 * this->area.raio * 0.92);
            glRotatef(90, 1, 0, 0);
            glRotatef(-this->theta1, 0, 1, 0);
            glRotatef(this->thetaElevacao, 0, 0, 1); // angulo de elevacao do braço
            glPushMatrix();
            {
                glScalef(this->area.raio / 6, this->area.raio / 6, 2 * this->area.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glTranslatef(0, 0, 2 * (-this->area.raio) / 2 * 0.92);
            glRotatef(-this->theta2, 0, 1, 0);
            glPushMatrix();
            {
                glScalef(this->area.raio / 7, this->area.raio / 7, 2 * this->area.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glTranslatef(0, 0, -this->area.raio / 2 * 2);
            // DrawAxes();

            // desenha luva
            glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
            //if (_textura != NULL) glBindTexture(GL_TEXTURE_2D, textura.get());
            OBJ *obj = CreateSphere(this->area.raio / 5, 10);
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
            glTranslatef(0, -this->area.raio / 2 * 0.95, 1.5 * this->area.raio * 0.92);
            glRotatef(-90, 1, 0, 0);
            glRotatef(-this->theta3, 0, 1, 0);
            glRotatef(-this->thetaElevacao, 0, 0, 1); // angulo de elevacao do braço
            glPushMatrix();
            {
                glScalef(this->area.raio / 6, this->area.raio / 6, 2 * this->area.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glTranslatef(0, 0, -this->area.raio / 2 * 0.92 * 2);
            glRotatef(-this->theta4, 0, 1, 0);
            glPushMatrix();
            {
                glScalef(this->area.raio / 7, this->area.raio / 7, 2 * this->area.raio);
                desenhaCubo();
            }
            glPopMatrix();
            glTranslatef(0, 0, -this->area.raio / 2 * 2);
            // DrawAxes();

            // desenha luva
            glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
            //if (_textura != NULL) glBindTexture(GL_TEXTURE_2D, textura.get());
            OBJ *obj = CreateSphere(this->area.raio / 5, 10);
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
            glTranslatef(0, 0, this->area.raio * 2);
            //if (_textura != NULL) glBindTexture(GL_TEXTURE_2D, textura.get());
            OBJ *obj = CreateSphere(this->area.raio / 2, 10);
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

            // desenha nariz
            glTranslatef(this->area.raio / 2, 0, 0);
            OBJ *obj2 = CreateSphere(this->area.raio / 2 * 0.3, 10);
            glBegin(GL_TRIANGLE_STRIP);
            {
                for (int i = 0; i < obj2->numVtx; i++)
                {
                    glNormal3f(obj2->vtx[i].nX, obj2->vtx[i].nY, obj2->vtx[i].nZ);
                    glTexCoord2f(obj2->vtx[i].U, obj2->vtx[i].V);
                    glVertex3f(obj2->vtx[i].X, obj2->vtx[i].Y, obj2->vtx[i].Z);
                }
                delete[] obj2->vtx;
                glEnd();
            }
            // DrawAxes();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

Ponto Lutador::verificaSocoDir()
{
    Ponto luvaDir = {0.0, 0.0, this->thetaElevacao};

    // antebraço + rotação
    Ponto a = {0.0, this->area.raio * (float)1.0, 0.0};
    luvaDir = translated(luvaDir, a);
    luvaDir = rotated(luvaDir, -this->theta2);

    // // braco direito ate cotovelo + rotacao
    Ponto b = {0, (float)0.92 * this->area.raio, 0};
    luvaDir = translated(luvaDir, b);
    luvaDir = rotated(luvaDir, -this->theta1);

    Ponto c = {0, this->area.raio / (float)2.0 * (float)0.95, (float)1.5 * this->area.raio * (float)0.92};
    luvaDir = translated(luvaDir, c);

    luvaDir = rotated(luvaDir, this->angulo);

    luvaDir = translated(luvaDir, this->area.posicao);

    luvaDir = {luvaDir.getX(),luvaDir.getY(),luvaDir.getZ()*(float)0.92};

    // cout << "******" << endl;
    // cout << luvaDir.getX() << endl;
    // cout << luvaDir.getY() << endl;
    // cout << luvaDir.getZ() << endl;
    // luvaDir = {luvaDir.getX(), luvaDir.getY(), luvaDir.getZ()};

    return luvaDir;
}

Ponto Lutador::verificaSocoEsq()
{
    Ponto luvaEsq = {0.0, 0.0, this->thetaElevacao};

    // antebraço + rotação
    Ponto a = {0.0, -this->area.raio * (float)1.0, 0.0};
    luvaEsq = translated(luvaEsq, a);
    luvaEsq = rotated(luvaEsq, this->theta4);

    // // braco direito ate cotovelo + rotacao
    Ponto b = {0, -(float)0.92 * this->area.raio, 0};
    luvaEsq = translated(luvaEsq, b);
    luvaEsq = rotated(luvaEsq, this->theta3);

    Ponto c = {0, -this->area.raio / (float)2.0 * (float)0.95, (float)1.5 * this->area.raio * (float)0.92};
    luvaEsq = translated(luvaEsq, c);

    luvaEsq = rotated(luvaEsq, this->angulo);

    luvaEsq = translated(luvaEsq, this->area.posicao);

    luvaEsq = {luvaEsq.getX(),luvaEsq.getY(),luvaEsq.getZ()*(float)0.92};

    // cout << "******" << endl;
    // cout << luvaEsq.getX() << endl;
    // cout << luvaEsq.getY() << endl;
    // cout << luvaEsq.getZ() << endl;
    // luvaEsq = {luvaEsq.getX(), luvaEsq.getY(), luvaEsq.getZ()};

    return luvaEsq;
}

Ponto Lutador::translated(Ponto p, Ponto pAntigo)
{
    p.setX(p.getX() + pAntigo.getX());
    p.setY(p.getY() + pAntigo.getY());
    p.setZ(p.getZ() + pAntigo.getZ());
    // p.x += pAntigo.x;
    // p.y += pAntigo.y;
    return p;
}

Ponto Lutador::rotated(Ponto p, float angle)
{
    Ponto rotated = {0, 0, p.getZ()};
    rotated.setX(p.getX() * cos(M_PI * angle / 180.0) - p.getY() * sin(M_PI * angle / 180.0));
    rotated.setY(p.getX() * sin(M_PI * angle / 180.0) + p.getY() * cos(M_PI * angle / 180.0));
    // rotated.setZ(p.getZ() + p.getX() * cos((angle + 90) * M_PI / 180.0));
    return rotated;
}

Ponto Lutador::getDirecao()
{
    return Ponto(cos((angulo)*M_PI / 180.0), sin((angulo)*M_PI / 180.0), 0);
}


// Ponto Lutador::rotatedZ(Ponto p, float angle)
// {
//     Ponto rotated = {0, 0, 0};
//     // rotated.setX(p.getX() * cos(M_PI * angle / 180.0) - p.getY() * sin(M_PI * angle / 180.0));
//     rotated.setY(p.getX() * sin(M_PI * angle / 180.0) + p.getY() * cos(M_PI * angle / 180.0));
//     return rotated;
// }

// void Lutador::desenharCanhao(Textura *textura)
// {
//     if (!draw3d)
//     {
//         glPushMatrix();
//         glTranslatef(20, 0, 0);                // move para o topo do corpo
//         glRotatef(anguloCanhaoYaw, 0, 0, 1);   // rotaciona, se quiser
//         glRotatef(anguloCanhaoPitch, 0, 1, 0); // rotaciona, se quiser
//         Rect(0, -2, 25, 4, Cor("darkgreen")).Draw(WITH_STROKE);
//         glPopMatrix();
//     }
//     else
//     {
//         glPushMatrix();
//         glColor3f(Cor("darkgreen").r, Cor("darkgreen").g, Cor("darkgreen").b);

//         if (textura != NULL)
//             glBindTexture(GL_TEXTURE_2D, textura->get());

//         glTranslatef(16, 0, 0);                // move para o topo do corpo
//         glRotatef(anguloCanhaoYaw, 0, 0, 1);   // rotaciona, se quiser
//         glRotatef(anguloCanhaoPitch, 0, 1, 0); // rotaciona, se quiser
//         glScalef(25, 4, 4);
//         glTranslatef(0.5, 0, 0);
//         desenhaCubo(1.0, 1);
//         glPopMatrix();
//     }
// }

// void Lutador::desenharHelice(Textura *textura)
// {
//     if (!draw3d)
//     {
//         glPushMatrix();
//         glRotatef(anguloHelice, 0, 0, 1);

//         glColor3f(79 / 255.0, 129 / 255.0, 189 / 255.0);
//         glBegin(GL_TRIANGLES);
//         glVertex2f(40.0, 3.0);
//         glVertex2f(0.0, 0.0);
//         glVertex2f(40.0, -3.0);
//         glEnd();
//         glBegin(GL_TRIANGLES);
//         glVertex2f(-40.0, 3.0);
//         glVertex2f(0.0, 0.0);
//         glVertex2f(-40.0, -3.0);
//         glEnd();
//         glBegin(GL_TRIANGLES);
//         glVertex2f(3.0, 40.0);
//         glVertex2f(0.0, 0.0);
//         glVertex2f(-3.0, 40.0);
//         glEnd();
//         glBegin(GL_TRIANGLES);
//         glVertex2f(3.0, -40.0);
//         glVertex2f(0.0, 0.0);
//         glVertex2f(-3.0, -40.0);
//         glEnd();
//         Circulo(Ponto(0, 0), 3, Cor("darkgreen")).Draw();
//         glPopMatrix();
//     }
//     else
//     {
//         double altura_helice = 1.5;
//         glPushMatrix();
//         glColor3f(79 / 255.0, 129 / 255.0, 189 / 255.0);
//         if (textura != NULL)
//             glBindTexture(GL_TEXTURE_2D, textura->get());
//         glRotatef(anguloHelice, 0, 0, 1);
//         glTranslatef(0, 0, (TAMANHO_LUTADORES / 2.0) + altura_helice);
//         glPushMatrix();
//         glScalef(80, 3, altura_helice);
//         desenhaCubo(1.0, 1);
//         glPopMatrix();
//         glPushMatrix();
//         glScalef(3, 80, altura_helice);
//         desenhaCubo(1.0, 1);
//         glPopMatrix();
//         Circulo(Ponto(0, 0), 2, Cor("darkgreen")).Draw(DRAW_3D, textura);
//         glPopMatrix();
//     }
// }

// void Lutador::desenharCombustivel(float _posicaoX, float _posicaoY, int _numeroDeMostradores)
// {
//     int mostradorAltura = 15;
//     int mostradorLargura = 10;
//     int mostradorEspaco = 5;
//     int nMostradores = _numeroDeMostradores;
//     //double nivel = nMostradores * getNivelCombustivel();

//     glPushMatrix();
//     glTranslatef(_posicaoX, _posicaoY - mostradorAltura, 0);
//     for (int i = 0; i < nMostradores; i++)
//     {
//         int x = i * (mostradorLargura + mostradorEspaco);
//         Cor cor = (i < nivel) ? Cor("green") : Cor("red");
//         Rect(x, 0, mostradorLargura, mostradorAltura, cor).Draw(WITH_STROKE);
//     }
//     glPopMatrix();
// }

// void Lutador::consumirCombustivel(GLdouble timeDiff)
// {
//     if (estaVoando() && tempoAtualDeVoo <= tempoMaximoDeVoo)
//         tempoAtualDeVoo += timeDiff / 1000.0;
// }

// double Lutador::getNivelCombustivel()
// {
//     return 1 - (tempoAtualDeVoo / tempoMaximoDeVoo);
// }

// void Lutador::reabastercer() { tempoAtualDeVoo = 0; }

// bool Lutador::resgatar(Circulo objeto)
// {
//     if (!objeto.estaTocando(this->area))
//         return false;
//     this->objetosResgatados++;
//     return true;
// }

// void Lutador::desenharResgates(float _posicaoX, float _posicaoY, int _nObjetos)
// {
//     int mostradorRaio = 7;
//     int mostradorEspaco = 5;
//     double shiftX = mostradorRaio;

//     glPushMatrix();
//     glTranslatef(_posicaoX + shiftX, _posicaoY - (2 * mostradorRaio), 0);
//     for (int i = 0; i < _nObjetos; i++)
//     {
//         int x = i * ((2 * mostradorRaio) + mostradorEspaco);
//         Cor cor = (i < objetosResgatados) ? Cor("green") : Cor("blue");
//         Circulo(Ponto(x, 0), mostradorRaio, cor).Draw();
//     }
//     glPopMatrix();
// }

// void Lutador::girarHelice()
// {
//     if (anguloHelice != 360)
//         anguloHelice += 5 * velocidadeHelice;
//     else
//         anguloHelice = 0;
// }

//bool Lutador::estaVoando() { return (area.posicao.z > TAMANHO_LUTADORES / 2.0); };
//void Lutador::decolar() { voando = true; }
//void Lutador::pousar() { voando = false; }
// void Lutador::subir() { area.posicao.z++; }
// void Lutador::descer()
// {
//     if (estaVoando())
//         area.posicao.z--;
// }

// void Lutador::girarDireita()
// {
//     // if (!estaVoando())
//     //     return;
//     angulo += 1;
// }
// void Lutador::girarEsquerda()
// {
//     // if (!estaVoando())
//     //     return;
//     angulo -= 1;
// }

Ponto Lutador::getProximaPosicao(GLdouble timeDiff)
{
    Ponto novaPosicao = Ponto(0, 0, 0);
    float alphaRadians = (360.0 - angulo) * (M_PI / 180.0);
    novaPosicao.setX(area.posicao.getX() + cos(alphaRadians) * velocidade * timeDiff);
    novaPosicao.setY(area.posicao.getY() - sin(alphaRadians) * velocidade * timeDiff);
    return novaPosicao;
}

void Lutador::moverFrente(GLdouble timeDiff)
{
    // if (!estaVoando())
    //     return;
    float alphaRadians = (360.0 - angulo) * (M_PI / 180.0);
    area.posicao.setX(area.posicao.getX() + cos(alphaRadians) * velocidade * timeDiff);
    area.posicao.setY(area.posicao.getY() - sin(alphaRadians) * velocidade * timeDiff);
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

void Lutador::moverTras(GLdouble timeDiff)
{
    // if (!estaVoando())
    //     return;
    float alphaRadians = (360.0 - angulo) * (M_PI / 180.0);
    area.posicao.setX(area.posicao.getX() - cos(alphaRadians) * velocidade * timeDiff);
    area.posicao.setY(area.posicao.getY() + sin(alphaRadians) * velocidade * timeDiff);

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

// void Lutador::aumentarVelocidadeHelice()
// {
//     if (velocidadeHelice <= HELICE_VEL_MAXIMA - 0.03)
//         velocidadeHelice += 0.03;
//     else
//         velocidadeHelice = HELICE_VEL_MAXIMA;
// }
// void Lutador::diminuirVelocidadeHelice()
// {
//     if (velocidadeHelice >= HELICE_VEL_MINIMA + 0.03)
//         velocidadeHelice -= 0.03;
//     else
//         velocidadeHelice = HELICE_VEL_MINIMA;
// }

// void Lutador::mirar(Ponto alvo)
// {

//     // mira - yaw
//     double anguloRadianos = angulo * M_PI / 180.0;

//     // a -> direção, b -> posição, c -> alvo
//     Ponto a = Ponto(this->area.posicao.x + cos(anguloRadianos), this->area.posicao.y + sin(anguloRadianos));
//     Ponto b = this->area.posicao;
//     Ponto c = alvo;

//     Ponto ab = Ponto(b.x - a.x, b.y - a.y);
//     Ponto cb = Ponto(b.x - c.x, b.y - c.y);

//     float dot = (ab.x * cb.x + ab.y * cb.y);   // dot product
//     float cross = (ab.x * cb.y - ab.y * cb.x); // cross product

//     float deltaAnguloRadiano = atan2(cross, dot);
//     float deltaAngulo = deltaAnguloRadiano * 180.0 / M_PI;

//     angulo += deltaAngulo;

//     // mira - pitch
//     // a2 -> direção, b -> posição, c -> alvo
//     Ponto p, d;
//     getInfoCanhao(p, d); // direção
//     Ponto a2 = Ponto(b.x + d.x, b.y + d.y, b.z + d.z);

//     Ponto ab2 = Ponto(b.x - a2.x, 0, b.z - a2.z);
//     Ponto cb2 = Ponto(b.x - c.x, 0, b.z - c.z);

//     float dot2 = (ab2.x * cb2.x + ab2.z * cb2.z);   // dot product
//     float cross2 = (ab2.x * cb2.z - ab2.z * cb2.x); // cross product

//     float deltaAnguloRadiano2 = atan2(cross2, dot2);
//     float deltaAngulo2 = deltaAnguloRadiano2 * 180.0 / M_PI;

//     anguloCanhaoPitch += deltaAngulo2;
//     if (anguloCanhaoPitch < 0)
//         anguloCanhaoPitch = 0;
//     if (anguloCanhaoPitch > 45)
//         anguloCanhaoPitch = 45;
// }

// Tiro Lutador::atirar()
// {
//     Ponto direcao, pontaCanhao;
//     getInfoCanhao(pontaCanhao, direcao);
//     return Tiro(pontaCanhao, direcao, id, this->velocidadeTiro);
// }

// void Lutador::getInfoCanhao(Ponto &pontaCanhao, Ponto &direcao)
// {
//     double degree2rad = M_PI / 180.0;

//     double direcao_x = cos((anguloCanhaoYaw + angulo) * degree2rad) * sin((anguloCanhaoPitch + 90) * degree2rad);
//     double direcao_y = sin((anguloCanhaoYaw + angulo) * degree2rad) * sin((anguloCanhaoPitch + 90) * degree2rad);
//     double direcao_z = cos((anguloCanhaoPitch + 90) * degree2rad);
//     direcao = Ponto(direcao_x, direcao_y, direcao_z);

//     Ponto baseCanhao = Ponto((area.raio * 4 / 9) * cos(angulo * degree2rad), (area.raio * 4 / 9) * sin(angulo * degree2rad), 0);

//     Ponto pontaCanhaoInicial = Ponto(0, 0, 0);
//     double tamanho = area.raio * 2 / 3;
//     pontaCanhaoInicial.setX(baseCanhao.getX() + tamanho * cos((anguloCanhaoYaw + angulo) * M_PI / 180.0) * sin((anguloCanhaoPitch + 90) * degree2rad));
//     pontaCanhaoInicial.setY(baseCanhao.getY() + tamanho * sin((anguloCanhaoYaw + angulo) * M_PI / 180.0) * sin((anguloCanhaoPitch + 90) * degree2rad));
//     pontaCanhaoInicial.setZ(baseCanhao.getY() + tamanho * cos((anguloCanhaoPitch + 90) * M_PI / 180.0));
//     pontaCanhao = Ponto(this->area.posicao.getX() + pontaCanhaoInicial.getX(), this->area.posicao.getY() + pontaCanhaoInicial.getY(), this->area.posicao.getZ() + pontaCanhaoInicial.getZ());
// }

// void Lutador::ajustarAngulo()
// {
//     this->angulo = (this->angulo > 360) ? (int)this->angulo % 360 : this->angulo;
// }

// void Lutador::moverCanhao(int incrementoYaw, int incrementoPitch)
// {
//     // yaw
//     anguloCanhaoYaw += incrementoYaw;
//     if (anguloCanhaoYaw < -45)
//         anguloCanhaoYaw = -45;
//     if (anguloCanhaoYaw > 45)
//         anguloCanhaoYaw = 45;

//     // pitch
//     anguloCanhaoPitch += incrementoPitch;
//     if (anguloCanhaoPitch < 0)
//         anguloCanhaoPitch = 0;
//     if (anguloCanhaoPitch > 45)
//         anguloCanhaoPitch = 45;
// }

