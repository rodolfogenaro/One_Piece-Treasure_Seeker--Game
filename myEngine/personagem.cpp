#include "includes.h"
#include "tiro.cpp"

float GRAVITY = 5;
int VIDAS = 10;
float VelFLY = 13;

// tamanho e posicao do personagem
float myX = 100;
float myY = 250;
float width = 30;
float height = 70;

bool left = false, right = false, voar = false; // inicia tudo false para o carro

unsigned int pad_texture = 0;

bool morreu = false;

bool damagePerson = false;
bool damagePersonAcido = false;

void moviPerson()
{
	myY += GRAVITY;

	if (left == true) // left pressed
	{
		myX -= 8; // minus 0.5 on the x, velocity
		
		if (voar == true)
		{
			myY -= VelFLY;
		}
	}
	else if (right == true)
	{
		myX += 8; // plus 0.5 ont the x

		if (voar == true)
		{
			myY -= VelFLY;
		}
	}
	else if (voar == true)
	{
		myY -= VelFLY;
	}

	if (myX < 0)
	{
		myX = 0;
	}
	else if (myX+width > 600)
	{
		myX = 600 - width;
	}
	else if (myY < 0)
	{
		myY = 0;
	}
	else if (myY+height > 400)
	{
		morreu = true;
	}

}


void desenhaPersonagem()
{
	glBindTexture(GL_TEXTURE_2D, pad_texture); // what texture going to use (image)

	// drawing quad (pad)
	glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINE_TRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

	// create the image in the quad created before
	// coord texture      coord quad
	glTexCoord2d(0,0);    glVertex2f(myX, myY); // up left
	glTexCoord2d(1,0);    glVertex2f(myX + width, myY); // up right
	glTexCoord2d(1,1);    glVertex2f(myX + width, myY + height); // down right
	glTexCoord2d(0,1);    glVertex2f(myX, myY + height); // down left

	glEnd(); // end drawing
}


bool danoPerson()
{
	if (damagePerson == true)
	{
		glColor4ub(255, 0, 0, 255); // dano vermelho
	}

	else if (damagePersonAcido == true)
	{
		glColor4ub(0, 255, 0, 255); // dano verde
	}

	damagePerson = false;
	damagePersonAcido = false;

	return false;
}