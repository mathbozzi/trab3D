#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include "arena.h"
#include "imageloader.h"

using namespace std;

Arena::Arena(float x, float y, float z, float width, float height, Cor c)
{
	Point p = {x, y, z};
	this->pos = p;
	this->width = width;
	this->height = height;
	this->altura = 0;
	this->cor = c;
	// this->textura = LoadTextureRAW("/textura/ring.bmp");
}

void desenhaArena(float width, float height, Cor c)
{
	glColor3f(c.r, c.g, c.b);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(width, 0);
	glVertex2f(width, height);
	glVertex2f(0, height);
	glEnd();
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

GLuint LoadTextureRAW( const char * filename )
{

    GLuint texture;
    
    Image* image = loadBMP(filename);

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
//    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                             0,                            //0 for now
                             GL_RGB,                       //Format OpenGL uses for image
                             image->width, image->height,  //Width and height
                             0,                            //The border of the image
                             GL_RGB, //GL_RGB, because pixels are stored in RGB format
                             GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                               //as unsigned numbers
                             image->pixels);               //The actual pixel data
    delete image;

    return texture;
}