//  g++ -o main main.cpp -lSDLmain -lSDL -lGL

#include <SDL/SDL.h>
#include "SDL/SDL_opengl.h"
#include <stdio.h>

#define BLOCOS 19 //quantidade

// A - elemento 1 - inimigo
// B - elemento 2 - personagem o outro elemento

bool colisao(float Ax, float Ay, float Acomp, float Aalt, float Bx, float By, float Bcomp, float Balt)
{
	if (Ay+Aalt < By) return false;
	else if(Ay > By+Balt) return false;
	else if(Ax+Acomp < Bx) return false;
	else if(Ax > Bx+Bcomp) return false;

	return true; // houve colisao	
}

struct Bloco
{
	float x;
	float y;
	float comp;
	float alt;
	bool vivo;
};

int main(int argc, char* args[])
{
	
	SDL_Init(SDL_INIT_EVERYTHING);

	// memoria
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// nome janela
	SDL_WM_SetCaption("Meu primeiro jogo SDL", NULL);

	// tamanho janela
	SDL_SetVideoMode(600, 400, 32, SDL_OPENGL);

	// cor
	glClearColor(1,1,1,1);

	// area exibida
	glViewport(0,0,600,400);

	// sombra
	glShadeModel(GL_SMOOTH);

	// 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // desenho geometrico

	//3D
	glDisable(GL_DEPTH_TEST);

	bool executando = true;

	SDL_Event eventos;
 
 	// personagem
	float personX = 300;
	float personY = 350;
	float personComp = 50;
	float personAlt = 30;

	// inimigo
	float inimigoX = 50;
	float inimigoY = 200;
	float inimigoCA = 30;

	float velX = 3;
	float velY = 3;

	Bloco blocos[BLOCOS];

	// criacao dos blocos

	for (int n = 0, x = 4, y = 10; n < BLOCOS; n++, x += 61)
	{
		if (x > 560)
		{
			x = 4;
			y += 23;
		}

		blocos[n].x = x;
		blocos[n].y = y;
		blocos[n].comp = 60;
		blocos[n].alt = 20;
		blocos[n].vivo = true;
	}

	bool esq = false, dir = false;

	// loop do jogo
	while(executando)
	{
		// eventos
		while(SDL_PollEvent(&eventos))
		{
			// fecha com o x da janela
			if(eventos.type == SDL_QUIT)
			{
				executando = false;
			}

			// esc
			if (eventos.type == SDL_KEYUP && eventos.key.keysym.sym == SDLK_ESCAPE)
			{
				executando = false;
			}

			// anda ou nao
			if (eventos.type == SDL_KEYDOWN)// tecla pressionada
			{
				if (eventos.key.keysym.sym == SDLK_LEFT)
				{
					esq = true;
				}
				else if (eventos.key.keysym.sym == SDLK_RIGHT)
				{
					dir = true;
				}
			}
			else if (eventos.type == SDL_KEYUP)
			{
				if (eventos.key.keysym.sym == SDLK_LEFT)
				{
					esq = false;
				}
				else if (eventos.key.keysym.sym == SDLK_RIGHT)
				{
					dir = false;
				}
			}
		}

		// LOGICA

		// movimento do personagem
		if (esq == true)// se seta esquerda for pressionada
		{
			personX -= 8;
		}
		else if (dir == true)
		{
			personX += 8;
		}

		if (personX < 0)
		{
			personX = 0;
		}
		else if (personX + personComp > 600)
		{
			personX = 600 - personComp;
		}

		// movimento inimigo
		inimigoX += velX;

		for (int n = 0; n < BLOCOS; n++)
		{
			if (blocos[n].vivo == true)
			{
				if (colisao(inimigoX, inimigoY, inimigoCA, inimigoCA, blocos[n].x, blocos[n].y, blocos[n].comp, blocos[n].alt) == true)
				{
					velX = -velX;
					blocos[n].vivo = false;
					break;
				}
			}
		}

		inimigoY += velY;

		for (int n = 0; n < BLOCOS; n++)
		{
			if (blocos[n].vivo == true)
			{
				if (colisao(inimigoX, inimigoY, inimigoCA, inimigoCA, blocos[n].x, blocos[n].y, blocos[n].comp, blocos[n].alt) == true)
				{
					velY = -velY;
					blocos[n].vivo = false;
					break;
				}
			}
		}

		// logica inimigo
		if (inimigoX < 0)
		{
			velX = -velX;
		}
		else if (inimigoX + inimigoCA > 600)
		{
			velX = -velX;
		}
		else if (inimigoY < 0)
		{
			velY = -velY;
		}
		else if (inimigoY + inimigoCA > 400)
		{
			executando = false;
		}

		if (colisao(inimigoX, inimigoY, inimigoCA, inimigoCA, personX, personY, personComp, personAlt) == true)
		{
			velY = -velY;
		}

		// RENDERIZACAO
		glClear(GL_COLOR_BUFFER_BIT);// LIMPA O BUFFER

		// inicia matriz
		glPushMatrix();

		// dimensoes da matriz
		glOrtho(0, 600, 400, 0, -1, 1);

		//cor
		//glColor3d( 1 ou 0)
		//glColor3f( decimais )
		//glColor3ub( R, G, B ) - 0 ATE 255
		//glColor4ub(R, G, B, A) 0 ATE 255

		glColor4ub(255, 0, 0, 255); // vermelho
		 
		// inicia desenho do personagem
		glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

		glVertex2f(personX, personY); // primeiro ponto
		glVertex2f(personX+personComp, personY); // segundo ponto
		glVertex2f(personX+personComp, personY+personAlt);
		glVertex2f(personX, personY+personAlt);

		// fecha
		glEnd();

		glColor4ub(0, 255, 0, 255);

		// inicia o desenho do inimigo
		glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

		glVertex2f(inimigoX, inimigoY); // primeiro ponto
		glVertex2f(inimigoX+inimigoCA, inimigoY); // segundo ponto
		glVertex2f(inimigoX+inimigoCA, inimigoY+inimigoCA);
		glVertex2f(inimigoX, inimigoY+inimigoCA);

		// fecha
		glEnd();

		glBegin(GL_QUADS);

		glColor4ub(0, 0, 255, 255);

		for (int n = 0; n < BLOCOS; n++)
		{
			if (blocos[n].vivo == true)
			{
				glVertex2f(blocos[n].x, blocos[n].y);
				glVertex2f(blocos[n].x + blocos[n].comp, blocos[n].y);
				glVertex2f(blocos[n].x + blocos[n].comp, blocos[n].y + blocos[n].alt);
				glVertex2f(blocos[n].x, blocos[n].y + blocos[n].alt);
			}
			
		}

		glEnd();

		// fecha matrix
		glPopMatrix();

		//animacao
		SDL_GL_SwapBuffers();

	}
	

	printf("\n Executando \n");

	SDL_Quit();	

	return 0;
}