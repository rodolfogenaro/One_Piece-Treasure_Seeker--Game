#include "includes.h"

#define BRICKS 57 // quantidade de blocos
#define B_WID 32
#define B_HEI 32

// estrutura do bloco
struct Brick
{
	float x;
	float y;
	float width;
	float height;
	bool alive;
};

int DESTROYED = 0; // blocos destruidos

unsigned int brick_texture = 0;
unsigned int back_texture = 0;

Brick bricks[BRICKS]; // cria um vetor de estruturas (blocos)



void criaBlocos()
{
	// cria todos os blocos
	for (int n = 0, x = 0, y = 380; n < BRICKS; n++, x += B_WID) // coloca um bloco na frente do outro
	{
		// se passar da tela desce a linha
		if (x > 580)
		{
			x = 0;
			y -= B_HEI;

			//x = 540; // return to 4
			//y -= 20; // jump for the other line
		}

		bricks[n].x = x;
		bricks[n].y = y;
		bricks[n].width = B_WID;
		bricks[n].height = B_HEI;
		bricks[n].alive = true; // true ainda nao colidiu (exibe)
	}
}



void desenhaBlocos()
{
	glColor4ub(129,29,11,255);

	glBindTexture(GL_TEXTURE_2D, brick_texture);

	glBegin(GL_QUADS);

	// drawing the bricks
	for (int n = 0; n < BRICKS; n++)
	{
		if (bricks[n].alive == true)
		{

			glTexCoord2d(0,0); glVertex2f(bricks[n].x, bricks[n].y);
			glTexCoord2d(1,0); glVertex2f(bricks[n].x + bricks[n].width, bricks[n].y);
			glTexCoord2d(1,1); glVertex2f(bricks[n].x + bricks[n].width, bricks[n].y + bricks[n].height);
			glTexCoord2d(0,1); glVertex2f(bricks[n].x, bricks[n].y + bricks[n].height);
		}

	}

	glEnd();
}


void desenhaFundo()
{

	glBindTexture(GL_TEXTURE_2D, back_texture);

	// quad of the background
	glBegin(GL_QUADS);

	glTexCoord2d(0,0); glVertex2f(0,0);
	glTexCoord2d(1,0); glVertex2f(600,0);
	glTexCoord2d(1,1); glVertex2f(600,400);
	glTexCoord2d(0,1); glVertex2f(0,400);

	glEnd();
}