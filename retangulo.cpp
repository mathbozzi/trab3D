#include "retangulo.h"

using namespace std;

Retangulo::Retangulo()
{
}

Retangulo::Retangulo(int x, int y, int width, int height /*, Cor cor*/)
{
    this->posicao.setX(x);
    this->posicao.setY(y);
    this->posicao.setZ(0);
    this->altura = height;
    this->largura = width;
    // this->cor = cor;
    // strokeLargura = 1;
    // strokeCor = Cor(127, 127, 127);
}

void Retangulo::Draw(GLuint textura, Cores cor)
{
    // if (_textura != NULL)
    //     this->textura = *_textura;

    // if (flag == DRAW_2D)
    // {
    //     vector<Ponto> vertices = getVertices();

    //     // desenha o poligono
    //     if (vertices.size() == 4)
    //     {
    //         glBegin(GL_POLYGON);
    //         glColor3f(cor.r, cor.g, cor.b);
    //         for (Ponto v : vertices)
    //             glVertex2f(v.x, v.y);
    //         glEnd();
    //     }

    //     // desenha as arestas
    //     if (drawStroke && vertices.size() == 4)
    //     {
    //         glPointSize(strokeLargura);
    //         glBegin(GL_LINE_LOOP);
    //         glColor3f(strokeCor.r, strokeCor.g, strokeCor.b);
    //         for (Ponto v : vertices)
    //             glVertex2f(v.x, v.y);
    //         glEnd();
    //     }
    // }
    // else

    // vector<Ponto> vertices = getVertices();


    vector<Ponto> vertices;
    vertices.push_back(posicao);
    vertices.push_back(Ponto(posicao.getX() + largura, posicao.getY(), posicao.getZ()));
    vertices.push_back(Ponto(posicao.getX() + largura, posicao.getY() + altura, posicao.getZ()));
    vertices.push_back(Ponto(posicao.getX(), posicao.getY() + altura, posicao.getZ()));

    double textureS = 1;
    glPushMatrix();
    glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
    // if (_textura != NULL)
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f(vertices[0].getX(), vertices[0].getY(), std::abs(vertices[0].getZ()));
    glTexCoord2f(0, textureS);
    glVertex3f(vertices[1].getX(), vertices[1].getY(), std::abs(vertices[1].getZ()));
    glTexCoord2f(textureS, textureS);
    glVertex3f(vertices[2].getX(), vertices[2].getY(), std::abs(vertices[2].getZ()));
    glTexCoord2f(textureS, 0);
    glVertex3f(vertices[3].getX(), vertices[3].getY(), std::abs(vertices[3].getZ()));
    glEnd();
    glPopMatrix();
}

void Retangulo::DrawArestas()
{
    // vector<Ponto> vertices = getVertices();
    vector<Ponto> vertices;
    vertices.push_back(posicao);
    vertices.push_back(Ponto(posicao.getX() + largura, posicao.getY(), posicao.getZ()));
    vertices.push_back(Ponto(posicao.getX() + largura, posicao.getY() + altura, posicao.getZ()));
    vertices.push_back(Ponto(posicao.getX(), posicao.getY() + altura, posicao.getZ()));

    //  glPointSize(strokeLargura);
    glBegin(GL_LINE_LOOP);
    Cores c = Cores(1.0, 1.0, 1.0);
    glColor3f(c.getCorR(), c.getCorG(), c.getCorB());
    for (Ponto v : vertices)
        glVertex2f(v.getX(), v.getY());
    glEnd();
}

// vector<Ponto> Retangulo::getVertices()
// {
//     vector<Ponto> vertices;
//     vertices.push_back(posicao);
//     vertices.push_back(Ponto(posicao.x + largura, posicao.y, posicao.z));
//     vertices.push_back(Ponto(posicao.x + largura, posicao.y + altura, posicao.z));
//     vertices.push_back(Ponto(posicao.x, posicao.y + altura, posicao.z));
//     return vertices;
// }

bool Retangulo::estaDentro(Ponto p)
{
    bool h = (p.getX() >= posicao.getX() && p.getX() <= posicao.getX() + largura);
    bool v = (p.getY() >= posicao.getY() && p.getY() <= posicao.getY() + altura);
    return (h && v);
}

// void Retangulo::DrawCubo(Retangulo *r, float profundidade, float textureS)
// {
//     Ponto _posicao = r->posicao;
//     float height = r->altura;
//     float width = r->largura;
//     int inverterNormal = 1;

//     glPushMatrix();
//     glTranslatef(0, 0, _posicao.z * inverterNormal);
//     glColor3f(r->cor.getCorR(), r->cor.getCorG(), r->cor.getCorB());
//     glBindTexture(GL_TEXTURE_2D, textureS);

//     glBegin(GL_POLYGON); /* f1: front */
//     glNormal3f(-1.0f * inverterNormal, 0.0f, 0.0f);

//     glTexCoord2f(textureS, 0);
//     glVertex3f(_posicao.x, _posicao.y, 0.0f);
//     glTexCoord2f(textureS, textureS);
//     glVertex3f(_posicao.x, _posicao.y, profundidade);
//     glTexCoord2f(0, textureS);
//     glVertex3f(_posicao.x + width, _posicao.y, profundidade);
//     glTexCoord2f(0, 0);
//     glVertex3f(_posicao.x + width, _posicao.y, 0.0f);
//     glEnd();

//     glBegin(GL_POLYGON); /* f2: bottom */
//     glNormal3f(0.0f, 0.0f, -1.0f * inverterNormal);

//     glTexCoord2f(textureS, 0);
//     glVertex3f(_posicao.x, _posicao.y, 0.0f);
//     glTexCoord2f(textureS, textureS);
//     glVertex3f(_posicao.x + width, _posicao.y, 0.0f);
//     glTexCoord2f(0, textureS);
//     glVertex3f(_posicao.x + width, _posicao.y + height, 0.0f);
//     glTexCoord2f(0, 0);
//     glVertex3f(_posicao.x, _posicao.y + height, 0.0f);
//     glEnd();

//     glBegin(GL_POLYGON); /* f3:back */
//     glNormal3f(1.0f * inverterNormal, 0.0f, 0.0f);

//     glTexCoord2f(textureS, 0);
//     glVertex3f(_posicao.x + width, _posicao.y + height, 0.0f);
//     glTexCoord2f(textureS, textureS);
//     glVertex3f(_posicao.x + width, _posicao.y + height, profundidade);
//     glTexCoord2f(0, textureS);
//     glVertex3f(_posicao.x, _posicao.y + height, profundidade);
//     glTexCoord2f(0, 0);
//     glVertex3f(_posicao.x, _posicao.y + height, 0.0f);
//     glEnd();

//     glBegin(GL_POLYGON); /* f4: top */
//     glNormal3f(0.0f, 0.0f, 1.0f * inverterNormal);

//     glTexCoord2f(textureS, 0);
//     glVertex3f(_posicao.x + width, _posicao.y + height, profundidade);
//     glTexCoord2f(textureS, textureS);
//     glVertex3f(_posicao.x + width, _posicao.y, profundidade);
//     glTexCoord2f(0, textureS);
//     glVertex3f(_posicao.x, _posicao.y, profundidade);
//     glTexCoord2f(0, 0);
//     glVertex3f(_posicao.x, _posicao.y + height, profundidade);
//     glEnd();

//     glBegin(GL_POLYGON); /* f5: left */
//     glNormal3f(0.0f, 1.0f * inverterNormal, 0.0f);

//     glTexCoord2f(0, 0);
//     glVertex3f(_posicao.x, _posicao.y, 0.0f);
//     glTexCoord2f(textureS, 0);
//     glVertex3f(_posicao.x, _posicao.y + height, 0.0f);
//     glTexCoord2f(textureS, textureS);
//     glVertex3f(_posicao.x, _posicao.y + height, profundidade);
//     glTexCoord2f(0, textureS);
//     glVertex3f(_posicao.x, _posicao.y, profundidade);
//     glEnd();

//     glBegin(GL_POLYGON); /* f6: right */
//     glNormal3f(0.0f, -1.0f * inverterNormal, 0.0f);

//     glTexCoord2f(textureS, 0);
//     glVertex3f(_posicao.x + width, _posicao.y, 0.0f);
//     glTexCoord2f(textureS, textureS);
//     glVertex3f(_posicao.x + width, _posicao.y, profundidade);
//     glTexCoord2f(0, textureS);
//     glVertex3f(_posicao.x + width, _posicao.y + height, profundidade);
//     glTexCoord2f(0, 0);
//     glVertex3f(_posicao.x + width, _posicao.y + height, 0.0f);
//     glEnd();
//     glPopMatrix();
// }
