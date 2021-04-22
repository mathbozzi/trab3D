#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include "arena.h"
#include "utils.h"

using namespace std;

Arena::Arena(float x, float y, float z, float width, float height, Cor c)
{
	Point p = {x, y, z};
	this->pos = p;
	this->width = width;
	this->height = height;
	this->altura = 0;
	this->cor = c;
	//this->textura = LoadTextureRAW("textura/stars1.bmp");
}

void Arena::desenhaArena()
{

    GLuint chao = LoadTextureRAW("textura/earth.bmp");
    GLuint paredes = LoadTextureRAW("textura/stars1.bmp");

	cout << this->altura << endl;
	cout << this->width << endl;
	cout << this->height << endl;
    glPushMatrix(); //chao
        glScalef(this->width,1,this->height);
        glTranslatef(0,0,0);
        DisplayPlane (chao);
    glPopMatrix();

    glPushMatrix();//parede frente
        glTranslatef(0,this->altura,0);
        glScalef(this->width,this->altura,1);
        glTranslatef(0,0,this->height);
        glRotatef(90,1,0,0);
        DisplayPlane (paredes);
    glPopMatrix();

    glPushMatrix();// parede fundo
        glTranslatef(0,this->altura,0);
        glScalef(this->width,this->altura,1);
        glTranslatef(0,0,-this->height);
        glRotatef(90,1,0,0);
        DisplayPlane (paredes);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,this->altura,0);
        glScalef(1,this->altura,this->height);
        glTranslatef(-this->width,0,0);
        glRotatef(90,0,0,1);
        DisplayPlane (paredes);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,this->altura,0);
        glScalef(1,this->altura,this->height);
        glTranslatef(this->width,0,0);
        glRotatef(90,0,0,1);
        DisplayPlane (paredes);
    glPopMatrix();

}

Point Arena::ObtemPos()
{
	return this->pos;
}

void Arena::set_vertex(Point p)
{
	this->pos = p;
}

float Arena::get_width()
{
	return this->width;
}

float Arena::get_height()
{
	return this->height;
}

Cor Arena::ObtemCor()
{
	return this->cor;
}

float Arena::ObtemAltura()
{
    return this->altura;
}

float Arena::ObtemCoordZ()
{
    return this->pos.z;
}

void Arena::MudaCoordZ(float newz)
{
    this->pos.z = newz;
}

void Arena::set_altura(float newaltura)
{
    this->altura = newaltura;
}
