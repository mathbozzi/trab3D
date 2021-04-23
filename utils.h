#ifndef UTILS_H_
#define UTILS_H_
#include "imageloader.h"
#include <GL/glut.h>

GLuint LoadTextureRAW( const char * filename );
void DisplayPlane (GLuint texture);
void DrawObj(double size);
void DrawAxes(double size);



#endif /*UTILS_H_*/