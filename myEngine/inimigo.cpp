#include "includes.h"
#include "cenario.cpp"
#include "armaInimiga.cpp"

int VELOCIDADE = 4;


bool isRunning = true;
int E_TAM = 30; // tamanho do efeito de explosao apos o tiro


// variables inimigo
float inimigoX; // initial position x
float inimigoY = 10; // initial position y
float inimigoWH = 38; // size

float vellx = VELOCIDADE; // velocity on the x
float velly = -VELOCIDADE; // velocity on the y

float explosaoX;
float explosaoY;
float explosaoW = E_TAM;
float explosaoH = E_TAM;


unsigned int inimigo_texture = 0;
unsigned int explosao_texture = 0;


int vidaInimigo = 10;

bool explosao = false;

bool controleRand = false; // aparecimento randomico


// ----movimento bola--------

void movimentoInimigo()
{
	// posicao randomica que o inimigo aparece
	if (controleRand == false)
	{
		srand(time(NULL));
		inimigoX = rand()%500 + 1;

		// executa so uma vez(inicio do jogo)
		controleRand = true;
	}
	
	// bate nas laterais da tela
	if (inimigoX < 0)
	{
		vellx = -vellx;
	}

	else if (inimigoX+inimigoWH > 600)
	{
		vellx = -vellx;
	}

	else if (inimigoY < 0)
	{
		velly = -velly;
		contAtq += 1;

		ataque(); // funcao para o ataque - armaInimigo.cpp
	}

	else if ((inimigoY+inimigoWH > 400)) // if colide down part, restart the game, all number return to the initial values
	//     if inimigo colide bottom  or  all bricks are destroyed
	{
		//isRunning = false;
		velly = -velly;
	}
}



void desenhaInimigo()
{

	glBindTexture(GL_TEXTURE_2D, inimigo_texture);

	glBegin(GL_QUADS);

	glTexCoord2d(0,0); glVertex2f(inimigoX, inimigoY);
	glTexCoord2d(1,0); glVertex2f(inimigoX+inimigoWH, inimigoY);
	glTexCoord2d(1,1); glVertex2f(inimigoX+inimigoWH, inimigoY+inimigoWH);
	glTexCoord2d(0,1); glVertex2f(inimigoX, inimigoY+inimigoWH);

	glEnd();
}

void desenhaExplosao()
{
	glBindTexture(GL_TEXTURE_2D, explosao_texture);

	glBegin(GL_QUADS);

	glTexCoord2d(0,0); glVertex2f(explosaoX, explosaoY);
	glTexCoord2d(1,0); glVertex2f(explosaoX+explosaoW, explosaoY);
	glTexCoord2d(1,1); glVertex2f(explosaoX+explosaoW, explosaoY+explosaoH);
	glTexCoord2d(0,1); glVertex2f(explosaoX, explosaoY+explosaoH);

	glEnd();
}


void tiroExplosao()
{
	if (explosao == true)
	{
		desenhaExplosao();
	}

	explosao = false;
}
