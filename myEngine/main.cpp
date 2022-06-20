/*    g++ -o main main.cpp -lSDLmain -lSDL -lGL   */
#include "init.cpp"

int main(int argc, char* args[])
{
// --------------------INICIALIZA----------------------------------------------------	

	inicializaSDL(); // init.cpp

//-----------------------------------------------------------------------------------

	std::cout << "O jogo esta executando!"<< std::endl;	

//---------------------CRIA BLOCOS---------------------------------------------------

	criaBlocos(); // blocos.cpp

//-----------------------------------------------------------------------------------

	// carrega a imagem dentro dos parentesis
	pad_texture = loadTexture("imagens/person.png");
	inimigo_texture = loadTexture("imagens/monstro.png");
	brick_texture = loadTexture("imagens/bloco2.png");
	back_texture = loadTexture("imagens/fundoEstatico.png");
	tiro_texture = loadTexture("imagens/tiro.png");
	explosao_texture = loadTexture("imagens/sangue.png");

	// ataque inimigo	
	ataque2_texture = loadTexture("imagens/atq2.png");	
	armaAlien_texture = loadTexture("imagens/armaAlien.png");

	// Som										1 - mono	2 - stereo
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Chunk *somTiro = NULL;
	Mix_Chunk *somExplosao = NULL;

	// carrega WAV
	somTiro = Mix_LoadWAV("audio/tiro.wav");
	somExplosao = Mix_LoadWAV("audio/sangue.wav");

	// carrega MP3
	Mix_Music *music = NULL;
	music = Mix_LoadMUS("audio/musicaFundo.mp3");
	Mix_PlayMusic(music, -1);


	SDL_Delay(250);
	// game loop
	while(isRunning)
	{

//-----------------------------TECLAS---------------------------------------------

		eventos(); // init.cpp

		if(somAtirar == true)
		{
			Mix_PlayChannel(-1, somTiro, 0); // 0 repeticoes
		}

//--------------------------------------------------------------------------------

// -------------------------MOVIMENTO PERSONAGEM----------------------------------
		
		tiro(); // tiro.cpp
		moviPerson(); // personagem.cpp


//--------------------------------------------------------------------------------

		caiu(); // colisao.cpp

//--------------------COLISAO INIMIGO BLOCO---------------------------------------

		colisaoInimigoBloco(); // colisao.cpp
		colisaoTiroInimigo(); // colisao.cpp

		if (somColTiroInimigo == true)
		{
			Mix_PlayChannel(-1, somExplosao, 0);
		}

//--------------------------------------------------------------------------------

//----------------------movimento bola--------------------------------------------
		
		movimentoInimigo(); // inimigo.cpp

//--------------------------------------------------------------------------------

//--------------------COLISAO PERSONAGEM INIMIGO----------------------------------

		colisaoPersonagemInimigo(); // colisao.cpp
		colisaoAtaquePersonagem(); // acido caiu no personagem

//--------------------------------------------------------------------------------

//--------------------COLISAO PERSONAGEM BLOCO------------------------------------

		colisaoPersonagemBloco(); //colisao.cpp

//--------------------------------------------------------------------------------

//-------------------------------RENDERIZACAO-------------------------------------

		renderiza(); // init.cpp

//--------------------------------------------------------------------------------

	}

	Mix_FreeChunk(somTiro);
	somTiro = NULL;

	Mix_FreeChunk(somExplosao);
	somExplosao = NULL;

	Mix_CloseAudio();

	SDL_Quit();

return 0;
}