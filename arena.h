#ifndef ARENA_H_
#define ARENA_H_

#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct tPoint
{
    float x;
    float y;
    float z;
} Point;

typedef struct tCor
{
    float r;
    float g;
    float b;
} Cor;

class Arena
{
	Point pos;
	Cor cor;
	float width;
	float height;
	float altura;
	GLuint textura;

public:
	Arena(float x, float y,float z, float width, float height, Cor c);
	Point ObtemPos();
	Cor ObtemCor();
	void desenhaArena();
	void set_vertex(Point p);
	void set_altura(float h);
	float get_width();
	float get_height();
	float ObtemCoordZ();
	float ObtemAltura();
	void MudaCoordZ(float newz);

};

#endif /* ARENA_H_ */
