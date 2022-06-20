#include "includes.h"
#include "colisao.cpp"

// eventos
SDL_Event event;

// variavel controle som
bool somAtirar = false;
bool somVoar = false;



// -------------------------------------funcao para carregar imagens----------------------------------------------------

GLuint loadTexture(const std::string&fileName)
{
	SDL_Surface *image = IMG_Load(fileName.c_str()); // carregar imagem

	SDL_DisplayFormatAlpha(image); // formato do diplay

	// criar textura
	unsigned object(0);

	glGenTextures(1, &object); // gera textura

	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

	//libera interface
	SDL_FreeSurface(image);

	return object;
}
//----------------------------------------------------------------------------------------------------------------------


// --------------------------------------------------inicializa tudo do SDL---------------------------------------------
void inicializaSDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);



	// Memory usage
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//nome janela
	SDL_WM_SetCaption(" My first window ", NULL);

	// cria a janela com as dimensoes escolhidas
	SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL); // SDL_OPENGL, SDL_FULLSCREEN

	// limpa tela RGB
	glClearColor(1,1,1,1);

	// porção da tela que sera mostrada
	glViewport(0,0,WIDTH, HEIGHT);

	// sombreamento
	glShadeModel(GL_SMOOTH);

	// 2D renderizacao
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	// transparencia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//-----------------------------------------------------------------------------------------------------------------------


// -------------------------------------------------------teclas--------------------------------------------------------- 
void eventos()
{

	
	// EVENTS (teclas pressionadas)
	while(SDL_PollEvent(&event))
	{
		// fechar janela com o x
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}

		// fechar com esc
		if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;
		}

		// teclas para o carro (direita e esquerda)
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_LEFT) // verified if the left key is pressed
			{
				left = true; // was pressed
			}

			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				right = true; // was pressed
			}

			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				voar = true;
			}

			else if (event.key.keysym.sym == SDLK_f)
			{
				tiroX = myX + 15;
				tiroY = myY + 30;
				somAtirar = true;
			}
		}

		else if (event.type == SDL_KEYUP) // released
		{
			if (event.key.keysym.sym == SDLK_LEFT)
			{
				left = false; // was released
			}

			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				right = false; // was released
			}

			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				voar = false;
			}

			else if (event.key.keysym.sym == SDLK_f)
			{
				somAtirar = false;
				atirar = true;
				tiroAlive = true;
			}
		}

	}
}


//--------------------------------------------------------------------------------------------------------------

void renderiza()
{
		//RENDERING part
		glClear(GL_COLOR_BUFFER_BIT);

		//Start a matrix to draw
		glPushMatrix();

		// dimension of the matrix
		glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);

		glColor4ub(255, 255 ,255, 255);

		glEnable(GL_TEXTURE_2D);

//---------------------------------------------FUNDO------------------------------------------------------------

		desenhaFundo();

//------------------------------------------ARMA ALIEN-------------------------------------------------------

		tiroExplosao();

		movimentoArmaAlien(); // desenha a arma e o ataque

		desenhaArmaAlien();

		// arma alien inverte a direcao apos bater nas laterais
		if (armaAlienX > 550)
		{
			velArmaAlien = -velArmaAlien;
		}
		else if (armaAlienX < 50)
		{
			velArmaAlien = -velArmaAlien;
		}

		

//---------------------------------PERSONAGEM-------------------------------------------------------------------

		if (atirar == true)
		{
			desenhaTiro();
		}

		
		desenhaInimigo();

		danoPerson();
		desenhaPersonagem();


//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------BLOCOS------------------------------------------------------

		desenhaBlocos();

//--------------------------------------------------------------------------------------------------------------

//--------------------------------------------------VIDA------------------------------------------------------
		desenhaContornoEnemy();		
		desenhaEnemyLife();
		desenhaContornoPerson();
		desenhaPersonLife();

//--------------------------------------------------------------------------------------------------------------

		glDisable(GL_TEXTURE_2D); // disable the image, its same of the end(), but is this a texture		

		//End matrix
		glPopMatrix();

		SDL_GL_SwapBuffers();
}