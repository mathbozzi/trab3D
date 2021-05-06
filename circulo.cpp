#include "circulo.h"

Circulo::Circulo() {}

Circulo::Circulo(Ponto posicao, int raio)
{
	this->posicao = posicao;
	this->raio = raio;
}

void Circulo::circuloMMapa(Cores cor)
{
	glColor3f(cor.getCorR(), cor.getCorG(), cor.getCorB());
	glBegin(GL_POLYGON);
	float angulo, x, y;
	for (int i = 0; i < 10; i++)
	{
		angulo = 2.0f * M_PI * i / float(10);
		x = raio * cosf(angulo);
		y = raio * sinf(angulo);
		glVertex2f(x + posicao.getX(), y + posicao.getY());
	}
	glEnd();
}

bool Circulo::dentroArea(Circulo c)
{
	return (calculaDistancia(c.posicao, this->posicao) < (this->raio + c.raio));
}
