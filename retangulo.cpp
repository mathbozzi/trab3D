#include "retangulo.h"

using namespace std;

Retangulo::Retangulo()
{
}

Retangulo::Retangulo(int x, int y, int width, int height)
{
    this->pos.setX(x);
    this->pos.setY(y);
    this->pos.setZ(0);
    this->height = height;
    this->width = width;
}

void Retangulo::desenhaRetangulo(GLuint textura, Cores cor)
{
    vector<Ponto> v;
    v.push_back(pos);
    v.push_back(Ponto(pos.getX() + width, pos.getY(), pos.getZ()));
    v.push_back(Ponto(pos.getX() + width, pos.getY() + height, pos.getZ()));
    v.push_back(Ponto(pos.getX(), pos.getY() + height, pos.getZ()));

    double textureS = 1;
    glPushMatrix();
    {
        glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
        glBindTexture(GL_TEXTURE_2D, textura);
        glBegin(GL_QUADS);
        {
            glNormal3f(0, 0, 1);
            glTexCoord2f(0, 0);
            glVertex3f(v[0].getX(), v[0].getY(), abs(v[0].getZ()));
            glNormal3f(0, 0, 1);
            glTexCoord2f(0, textureS);
            glVertex3f(v[1].getX(), v[1].getY(), abs(v[1].getZ()));
            glNormal3f(0, 0, 1);
            glTexCoord2f(textureS, textureS);
            glVertex3f(v[2].getX(), v[2].getY(), abs(v[2].getZ()));
            glNormal3f(0, 0, 1);
            glTexCoord2f(textureS, 0);
            glVertex3f(v[3].getX(), v[3].getY(), abs(v[3].getZ()));
        }
        glEnd();
    }
    glPopMatrix();
}

void Retangulo::desenhaRetMiniMapa()
{
    vector<Ponto> v;
    v.push_back(pos);
    v.push_back(Ponto(pos.getX() + width, pos.getY(), pos.getZ()));
    v.push_back(Ponto(pos.getX() + width, pos.getY() + height, pos.getZ()));
    v.push_back(Ponto(pos.getX(), pos.getY() + height, pos.getZ()));
    glBegin(GL_LINE_LOOP);
    Cores c = Cores(1.0, 1.0, 1.0);
    glColor3f(c.getCorR(), c.getCorG(), c.getCorB());
    for (Ponto v : v)
        glVertex2f(v.getX(), v.getY());
    glEnd();
}
