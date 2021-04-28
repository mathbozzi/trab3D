#include "utils.h"

Ponto::Ponto(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Cores::Cores(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

float Cores::getCorR()
{
    return this->r;
}

float Cores::getCorG()
{
    return this->g;
}

float Cores::getCorB()
{
    return this->b;
}

float Ponto::getX()
{
    return this->x;
}

float Ponto::getY()
{
    return this->y;
}

float Ponto::getZ()
{
    return this->z;
}

void Ponto::setX(float x)
{
    this->x = x;
}

void Ponto::setY(float y)
{
    this->y = y;
}

void Ponto::setZ(float z)
{
    this->z = z;
}

double calculaDistancia(Ponto p1, Ponto p2)
{
    return sqrt((p2.getX() - p1.getX()) * (p2.getX() - p1.getX()) + (p2.getY() - p1.getY()) * (p2.getY() - p1.getY()) + (p2.getZ() - p1.getZ()) * (p2.getZ() - p1.getZ()));
}

void desenhaCubo()
{
    static GLfloat n[6][3] =
        {
            {-1.0, 0.0, 0.0},
            {0.0, 1.0, 0.0},
            {1.0, 0.0, 0.0},
            {0.0, -1.0, 0.0},
            {0.0, 0.0, 1.0},
            {0.0, 0.0, -1.0}};
    static GLint faces[6][4] =
        {
            {0, 1, 2, 3},
            {3, 2, 6, 7},
            {7, 6, 5, 4},
            {4, 5, 1, 0},
            {5, 6, 2, 1},
            {7, 4, 0, 3}};
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1.0/ 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1.0 / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1.0 / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1.0 / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -1.0 / 2; //-z
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = 0;

    int textureS = 1;

    for (i = 5; i >= 0; i--) 
    {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(textureS, 0);
        glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(textureS, textureS);
        glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(0, textureS);
        glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(0, 0);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

OBJ *CreateSphere(double R, double space)
{
    OBJ *obj = new OBJ;

    obj->numVtx = (180 / space) *
                  (2 + 360 / (2 * space)) * 4;
    obj->vtx = new VERTICES[obj->numVtx];
    obj->radius = R;

    int n;
    double vR, lVR;
    double hR, lHR;
    double norm;
    n = 0;
    for (vR = 0; vR <= 180 - space; vR += space)
    {
        for (hR = 0; hR <= 360 + 2 * space; hR += 2 * space)
        {
            lVR = vR;
            lHR = hR;
            obj->vtx[n].X = R *
                            sin(lHR / 180 * M_PI) *
                            sin(lVR / 180 * M_PI);
            obj->vtx[n].Y = R *
                            cos(lHR / 180 * M_PI) *
                            sin(lVR / 180 * M_PI);
            obj->vtx[n].Z = R *
                            cos(lVR / 180 * M_PI);
            obj->vtx[n].V = lVR / 180;
            obj->vtx[n].U = lHR / 360;
            norm = sqrt(
                obj->vtx[n].X * obj->vtx[n].X +
                obj->vtx[n].Y * obj->vtx[n].Y +
                obj->vtx[n].Z * obj->vtx[n].Z);
            obj->vtx[n].nX = obj->vtx[n].X / norm;
            obj->vtx[n].nY = obj->vtx[n].Y / norm;
            obj->vtx[n].nZ = obj->vtx[n].Z / norm;
            n++;

            lVR = vR + space;
            lHR = hR;
            obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
            obj->vtx[n].V = lVR / 180;
            obj->vtx[n].U = lHR / 360;
            norm = sqrt(obj->vtx[n].X * obj->vtx[n].X + obj->vtx[n].Y * obj->vtx[n].Y + obj->vtx[n].Z * obj->vtx[n].Z);
            obj->vtx[n].nX = obj->vtx[n].X / norm;
            obj->vtx[n].nY = obj->vtx[n].Y / norm;
            obj->vtx[n].nZ = obj->vtx[n].Z / norm;
            n++;

            lVR = vR;
            lHR = hR + space;
            obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
            obj->vtx[n].V = lVR / 180;
            obj->vtx[n].U = lHR / 360;
            norm = sqrt(obj->vtx[n].X * obj->vtx[n].X + obj->vtx[n].Y * obj->vtx[n].Y + obj->vtx[n].Z * obj->vtx[n].Z);
            obj->vtx[n].nX = obj->vtx[n].X / norm;
            obj->vtx[n].nY = obj->vtx[n].Y / norm;
            obj->vtx[n].nZ = obj->vtx[n].Z / norm;
            n++;

            lVR = vR + space;
            lHR = hR + space;
            obj->vtx[n].X = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            obj->vtx[n].Z = R * cos(lVR / 180 * M_PI);
            obj->vtx[n].V = lVR / 180;
            obj->vtx[n].U = lHR / 360;
            norm = sqrt(obj->vtx[n].X * obj->vtx[n].X + obj->vtx[n].Y * obj->vtx[n].Y + obj->vtx[n].Z * obj->vtx[n].Z);
            obj->vtx[n].nX = obj->vtx[n].X / norm;
            obj->vtx[n].nY = obj->vtx[n].Y / norm;
            obj->vtx[n].nZ = obj->vtx[n].Z / norm;
            n++;
        }
    }
    return obj;
}

GLuint LoadTextureRAW(const char *filename)
{

    GLuint texture;

    Image *image = loadBMP(filename);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,               //Always GL_TEXTURE_2D
                 0,                           //0 for now
                 GL_RGB,                      //Format OpenGL uses for image
                 image->width, image->height, //Width and height
                 0,                           //The border of the image
                 GL_RGB,                      //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE,            //GL_UNSIGNED_BYTE, because pixels are stored
                                              //as unsigned numbers
                 image->pixels);              //The actual pixel data
    delete image;

    return texture;
}

void DrawAxes()
{
    GLfloat color_r[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat color_g[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat color_b[] = {0.0, 0.0, 1.0, 1.0};

    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    //x axis
    glPushMatrix();
    glColor3fv(color_r);
    glScalef(5, 0.3, 0.3);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(5.0);
    glPopMatrix();

    //y axis
    glPushMatrix();
    glColor3fv(color_g);
    glRotatef(90, 0, 0, 1);
    glScalef(5, 0.3, 0.3);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(5.0);
    glPopMatrix();

    //z axis
    glPushMatrix();
    glColor3fv(color_b);
    glRotatef(-90, 0, 1, 0);
    glScalef(5, 0.3, 0.3);
    glTranslatef(0.5, 0, 0); // put in one end
    glutSolidCube(5.0);
    glPopMatrix();
    glPopAttrib();
}