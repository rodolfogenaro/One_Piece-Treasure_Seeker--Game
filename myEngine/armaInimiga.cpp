#include "includes.h"

float ATQ = 10; // velocidade ataque do inimigo

int hrAtaque = 2; // quantidade de batidas no teto para o inimigo atacar
int posYSaidaAtaque = -8; // posicao inicial de todos os tiros (y)

float velArmaAlien = 2;


float armaAlienX = 288;
float armaAlienY = 0;
float armaAlienW = 40;
float armaAlienH = 20;



// tiro do meio
float ataque2X;
float ataque2Y = posYSaidaAtaque;
bool ataque2Alive;



float ataqueWH = 15; // dimensoes ataque


unsigned int ataque2_texture = 0;

unsigned int armaAlien_texture = 0;

int contAtq = 1; // controle de batidas no teto
bool inimigoAtaca = false;

void ataque()
{
	// se bater no teto hrAtaque vezes o inimigo ataca
	if (contAtq == hrAtaque)
	{
		inimigoAtaca = true;
	}
	else if(contAtq > hrAtaque)
	{
		contAtq = 0;
	}
}



void desenhaAtq2()
{
	if (ataque2Alive == true)
	{
		glBindTexture(GL_TEXTURE_2D, ataque2_texture);

		glBegin(GL_QUADS);

		glTexCoord2d(0,0); glVertex2f(ataque2X, ataque2Y);
		glTexCoord2d(1,0); glVertex2f(ataque2X+ataqueWH, ataque2Y);
		glTexCoord2d(1,1); glVertex2f(ataque2X+ataqueWH, ataque2Y+ataqueWH);
		glTexCoord2d(0,1); glVertex2f(ataque2X, ataque2Y+ataqueWH);

		glEnd();

		ataque2Y += ATQ;
	}
}




void desenhaArmaAlien()
{
	glBindTexture(GL_TEXTURE_2D, armaAlien_texture);

	glBegin(GL_QUADS);

	glTexCoord2d(0,0); glVertex2f(armaAlienX, armaAlienY);
	glTexCoord2d(1,0); glVertex2f(armaAlienX+armaAlienW, armaAlienY);
	glTexCoord2d(1,1); glVertex2f(armaAlienX+armaAlienW, armaAlienY+armaAlienH);
	glTexCoord2d(0,1); glVertex2f(armaAlienX, armaAlienY+armaAlienH);

	glEnd();
}


void movimentoArmaAlien()
{
	armaAlienX += velArmaAlien;
	
	ataque2X = armaAlienX+12;	
 
	if (inimigoAtaca == true)
	{
		
		ataque2Alive = true;
				
		desenhaAtq2();		

		if (ataque2Y > HEIGHT)
		{
			ataque2Alive = false;
			ataque2X = armaAlienX+12;
			ataque2Y = posYSaidaAtaque;
		}

	}
}