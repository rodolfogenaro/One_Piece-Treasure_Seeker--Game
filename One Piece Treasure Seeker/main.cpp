// g++ -o main main.cpp -lSDLmain -lSDL -lGL -lSDL_image

#include <SDL.h>
#include "SDL_opengl.h"
#include <stdio.h>
#include "SDL_image.h"
#include "string"
#include "SDL_mixer.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

GLuint loadTexture(const std::string&fileName) {

	SDL_Surface *imagem = IMG_Load(fileName.c_str()); // carrega imagem
	SDL_DisplayFormatAlpha(imagem); // formato alpha
	unsigned objetct(0); // cria textura
	glGenTextures(1, &objetct); // gera textura
	glBindTexture(GL_TEXTURE_2D, objetct); // tipo de textura, 2D

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagem->w, imagem->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagem->pixels);

	SDL_FreeSurface(imagem);

	return objetct;
}

int main (int argc, char* args[]) {

     SDL_Init(SDL_INIT_EVERYTHING);

    // CODIGO

    // MEMORIA
     SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
     SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
     SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
     SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

     //nome janela
     SDL_WM_SetCaption("One Piece Treasure Seeker", NULL);

     //tamanho da janela
     SDL_SetVideoMode(1366, 768, 32/*BITS por pixel*/, SDL_OPENGL); //pode substituir "SDL_OPENGL" por "FULLSCREEN"

     //cor
     glClearColor(1,1,1,1);

     //area exibida
     glViewport(0,0,1366,768);

     //sombreamento da janela
     glShadeModel(GL_SMOOTH);

     //2D
     glMatrixMode(GL_PROJECTION); //aplicacao na matriz atual
     glLoadIdentity(); //desenho geometrico

     //3D
     glDisable(GL_DEPTH_TEST);

     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     bool executando = true; //saber se o programa esta executando

     SDL_Event eventos; //saber se os cliques, tanto de mouse quanto de teclado, estao funcionando

     //PARA USO DE TEXTOS

     //TTF_Init();

     //TTF_Font *fonte = TTF_OpenFont("fonts\\Helv-Children.ttf", 14); // define fonte e tamanho

     //SDL_Color corFonte1 = {0, 0, 0}; // cor preta
     //SDL_Color corFonte2 = {255, 0, 0}; //cor vermelha

     //SDL_Surface *dica1 = TTF_RenderText_Solid(fonte, "ON LINE 1 THERE ARE:", corFonte1);

     //SDL_Rect localTexto = {};

     //PARA USO DO AUDIO

     int frequencia = 47500;
     Uint16 formato = AUDIO_S16SYS;
     int canais = 2;
     int buffer = 4096;

     Mix_OpenAudio(frequencia, formato, canais, buffer); //inicializa o audio

     Mix_Music *music;
     music = Mix_LoadMUS("sounds\\One PiecePirate Warriors 3 OST-Main Menu.mp3"); // Menu 1, 2, 4 e 5
     //music = Mix_LoadMUS("sounds\\One Piece Pirate Warriors 3 OST I WANT TO LIVE~Pirate Warriors 3 Mix~.mp3"); // Menu 3
     Mix_PlayMusic(music, -1);

     Mix_Chunk *effectsound1;
     effectsound1 = Mix_LoadWAV("sounds\\snd_00325.wav"); // efeito sonoro para prosseguir menu

     Mix_Chunk *effectsound2;
     effectsound2 = Mix_LoadWAV("sounds\\snd_00003.wav"); // efeito sonoro para retroceder menu

     Mix_Chunk *effectsound3;
     effectsound3 = Mix_LoadWAV("sounds\\snd_00308.wav"); // efeito sonoro para movimento do mouse em cima de algum botao
     int controladorsommenu2 = 0;
     int controladorsommenu5 = 0;

     Mix_Chunk *effectsound4;
     effectsound4 = Mix_LoadWAV("sounds\\GTA V WastedBusted Sound Effect edited.wav"); // efeito sonoro para "SE FODEU"
     int contadorsomgtav = 0;

     Mix_Chunk *effectsound5;
     effectsound5 = Mix_LoadWAV("sounds\\God Sound Effect.wav"); // musica classica de One Piece apos vitoria
     int contadorsomgod = 0;

     //PARA USO DA IMAGEM

     SDL_Surface *icon;
     icon = IMG_Load("images\\Logo.png");

     SDL_WM_SetIcon(icon, NULL); // colocando icone no aplicativo

     unsigned int menu1 = 0;
     menu1 = loadTexture("images\\Menu 1.png");

     unsigned int menu2 = 0;
     menu2 = loadTexture("images\\Menu 2.png");

     //unsigned int seletormenu2 = 0;
     //seletormenu2 = loadTexture("images\\seletor.png");
     unsigned int botaoplaycomseletor = 0;
     botaoplaycomseletor = loadTexture("images\\botaoplaycomseletor.png");
     unsigned int botaoscorescomseletor = 0;
     botaoscorescomseletor = loadTexture("images\\botaoscorescomseletor.png");
     unsigned int botaopiratecomseletor = 0;
     botaopiratecomseletor = loadTexture("images\\botaopiratecomseletor.png");

     unsigned int somstrawhatflag = 0;
     somstrawhatflag = loadTexture("images\\straw hat flag.png");
     unsigned int substituicaostrawhatflag = 0;
     substituicaostrawhatflag = loadTexture("images\\substituir straw hat flag.png");
     unsigned int substituicaostrawhatflag2 = 0;
     substituicaostrawhatflag2 = loadTexture("images\\substituir straw hat flag (menu 3).png");

     unsigned int menu5 = 0;
     menu5 = loadTexture("images\\Menu 5.png");

     //personagens em menu 5
     unsigned int iconLuffywithmotion = 0;
     iconLuffywithmotion = loadTexture("images\\Icone Luffy.png");
     unsigned int iconZorowithmotion = 0;
     iconZorowithmotion = loadTexture("images\\Icone Zoro.png");
     unsigned int iconSanjiwithmotion = 0;
     iconSanjiwithmotion = loadTexture("images\\Icone Sanji.png");
     unsigned int iconNamiwithmotion = 0;
     iconNamiwithmotion = loadTexture("images\\Icone Nami.png");
     unsigned int iconAcewithMotion = 0;
     iconAcewithMotion = loadTexture("images\\Icone Ace.png");

     unsigned int hpZoro = 0;
     hpZoro = loadTexture("images\\Icone Zoro (Menu 5).png");

     unsigned int menu3 = 0;
     menu3 = loadTexture("images\\Menu 3.png");

     unsigned int health = 0;
     health = loadTexture("images\\HP menor.png");

     //quadrados da matriz de piratas, ilhas e bussolas
     unsigned int quadradopirata = 0;
     quadradopirata = loadTexture("images\\found pirate.png");
     unsigned int quadradoilha = 0;
     quadradoilha = loadTexture("images\\found island.png");
     unsigned int quadradobussola = 0;
     quadradobussola = loadTexture("images\\found bussola.png");

     // mensagem de fim de jogo
     unsigned int sefudeu = 0;
     sefudeu = loadTexture("images\\se fudeu.png");
     unsigned int youfoundonepiece = 0;
     youfoundonepiece = loadTexture("images\\you won.png");

     // dicas de linhas
     unsigned int linhailha0 = 0;
     linhailha0 = loadTexture("images\\linha 0 ilha.png");
     unsigned int linhailha1 = 0;
     linhailha1 = loadTexture("images\\linha 1 ilha.png");
     unsigned int linhailha2 = 0;
     linhailha2 = loadTexture("images\\linha 2 ilha.png");
     unsigned int linhailha3 = 0;
     linhailha3 = loadTexture("images\\linha 3 ilha.png");
     unsigned int linhailha4 = 0;
     linhailha4 = loadTexture("images\\linha 4 ilha.png");
     unsigned int linhailha5 = 0;
     linhailha5 = loadTexture("images\\linha 5 ilha.png");
     // dicas de colunas
     unsigned int colunailha0 = 0;
     colunailha0 = loadTexture("images\\coluna 0 ilha.png");
     unsigned int colunailha1 = 0;
     colunailha1 = loadTexture("images\\coluna 1 ilha.png");
     unsigned int colunailha2 = 0;
     colunailha2 = loadTexture("images\\coluna 2 ilha.png");
     unsigned int colunailha3 = 0;
     colunailha3 = loadTexture("images\\coluna 3 ilha.png");
     unsigned int colunailha4 = 0;
     colunailha4 = loadTexture("images\\coluna 4 ilha.png");
     unsigned int colunailha5 = 0;
     colunailha5 = loadTexture("images\\coluna 5 ilha.png");


     // icone especialmente para vida no menu 5

     bool abrirmenu2 = false;
     int menuatual = 1;

     bool seletormenu2play = false;
     bool seletormenu2scores = false;
     bool seletormenu2pirate = false;

     bool botaosomdesligar = false;
     bool botaosomligar = false;
     int countsom = 1;

     bool voltarmenu1 = false;

     bool abrirmenu5 = false;
     bool voltarmenu2 = false;

     //personagens do menu 5
     bool mousenoLuffy = false;
     bool mousenoZoro = false;
     bool mousenoSanji = false;
     bool mousenaNami = false;
     bool mousenoAce = false;
     int characterselected = 3; // personagem selecionado: 1(Ace), 2(Zoro), 3(Luffy), 4(Sanji), 5(Nami)

     //matriz do Menu 3 (piratas)
     int ipirata[10], jpirata[10];
     int np=0;

     //matriz do Menu 3 (ilhas)
     int iilha[5], jilha[5];
     int ni=0;

     //matriz do Menu 3 (bussolas)
     int ibussola[85], jbussola[85];
     int nb=0;

     bool abrirmenu3 = false;

     int i, j;
     int count1=0, count2=0;
     int **M;
     M = (int**) calloc(10, sizeof(int*));
     for (i=0;i<10;i++)
     {
         M[i] = (int*) calloc(10, sizeof(int));
     }
     srand( (unsigned)time(NULL) );
     while (count1<10)
     {
         i = rand()%10;
         j = rand()%10;
         if (M[i][j]==0)
         {
             M[i][j] = 1; // 1 == pirata
             count1++;
         }
     }
     while (count2<5)
     {
         i = rand()%10;
         j = rand()%10;
         if(M[i][j]==0)
         {
             M[i][j] = 2; // 2 == ilha
             count2++;
         }
     }
     for(i=0;i<10;i++)
     {
         for(j=0;j<10;j++)
         {
             if(M[i][j]==0)
             {
                 M[i][j] = 3; // 3 == bussola
             }
         }
     }

     bool abrirquadradopirata[10];
     for(i=0;i<10;i++)
     {
         abrirquadradopirata[i] = false;
     }

     bool abrirquadradoilha[5];
     for(i=0;i<5;i++)
     {
         abrirquadradoilha[i] = false;
     }

     bool abrirquadradobussola[85];
     for(i=0;i<85;i++)
     {
         abrirquadradobussola[i] = false;
     }

     int contadorclick[100];
     for (i=0;i<100;i++)
     {
         contadorclick[i] = 0;
     }

     bool perdeuojogo = false;
     bool ganhouojogo = false;

     bool recomecarjogo = false;

     bool dica = false;
     int dl, dc; // diaca de linha, dica de coluna
     int ilhanalinha, ilhanacoluna; // quantas ilhas ha em tal limha e em tal coluna
     int quadradoatual;


     //LOOP DO JOGO
     while (executando)
     {
         if(recomecarjogo == true)
         {
             for(i=0;i<10;i++)
             {
                for(j=0;j<10;j++)
                {
                    M[i][j] = 0;
                }
             }
             srand( (unsigned)time(NULL) );
             count1 = 0;
             count2 = 0;
             while (count1<10)
             {
                i = rand()%10;
                j = rand()%10;
                if (M[i][j]==0)
                {
                    M[i][j] = 1; // 1 == pirata
                    count1++;
                }
             }
             while (count2<5)
             {
                i = rand()%10;
                j = rand()%10;
                if(M[i][j]==0)
                {
                    M[i][j] = 2; // 2 == ilha
                    count2++;
                }
             }
             for(i=0;i<10;i++)
             {
                for(j=0;j<10;j++)
                {
                    if(M[i][j]==0)
                    {
                        M[i][j] = 3; // 3 == bussola
                    }
                }
             }
             np = 0;
             ni = 0;
             nb = 0;
             voltarmenu2 = true;
             menuatual = 2;
             Mix_ResumeMusic();
             contadorsomgtav = 0;
             contadorsomgod = 0;
             for(i=0;i<100;i++)
             {
                 contadorclick[i] = 0;
             }
             for(i=0;i<10;i++)
             {
                 abrirquadradopirata[i] = false;
             }
             for(i=0;i<5;i++)
             {
                 abrirquadradoilha[i] = false;
             }
             for(i=0;i<85;i++)
             {
                 abrirquadradobussola[i] = false;
             }
             recomecarjogo = false;
         }
         else if(dica == true)
         {
             ilhanalinha = 0;
             ilhanacoluna = 0;
             for(i=0;i<10;i++)
             {
                 if(M[dl][i]==2)
                 {
                     ilhanalinha++;
                 }
                 if(M[i][dc]==2)
                 {
                     ilhanacoluna++;
                 }
             }
             dica = false;
         }
         else if(recomecarjogo == false && dica == false){
         //eventos
         //saber se alguma tecla foi usada/clicada
         while (SDL_PollEvent(&eventos))
         {
             //fecha com o "x" da janela
             int x=eventos.motion.x;
             int y=eventos.motion.y;
             if (eventos.type == SDL_QUIT)
             {
                 executando = false;
             }

             // botao (backspace) para abrir o menu 2
             if(eventos.type == SDL_KEYDOWN) //tecla pressionada para voltar a pagina anterior
             {
                 if(eventos.key.keysym.sym == SDLK_SPACE) //verifica se a tecla "Esc" foi pressionada
                 {
                     if(menuatual == 1)
                     {
                         Mix_PlayChannel(-1, effectsound1, 0);
                         abrirmenu2 = true;
                         voltarmenu1 = false;
                         abrirmenu5 = false;
                         voltarmenu2 = false;
                     }
                 }
             }
             if(eventos.type == SDL_MOUSEBUTTONDOWN)
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                     if(menuatual == 1)
                     {
                         if(x>579 && y>646 && x<786 && y<685)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             abrirmenu2 = true;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             voltarmenu2 = false;
                         }
                     }
                 }
             }
             /*else if(eventos.type == SDL_KEYUP) //verifica se a tecla pressionada foi solta
             {
                 if(eventos.key.keysym.sym == SDLK_SPACE) //verifica se a tecla "enter" foi pressionada
                 {
                     abrirmenu2 = false;
                 }
             }*/
             // coordenadas do mouse
             switch(eventos.type)
             {
                 case SDL_MOUSEMOTION:
                    // botao play do menu 2
                    if(x>95 && y>215 && x<403 && y<365)
                    {
                        if(controladorsommenu2 == 0 && menuatual == 2)
                        {
                            Mix_PlayChannel(-1, effectsound3, 0);
                            controladorsommenu2 = 1;
                        }
                        seletormenu2play = true;
                    }
                    else if(x>95 && y>402 && x<403 && y<552)
                    {
                        if(controladorsommenu2 == 0 && menuatual == 2)
                        {
                            Mix_PlayChannel(-1, effectsound3, 0);
                            controladorsommenu2 = 1;
                        }
                        seletormenu2scores = true;
                    }
                    else if(x>95 && y>590 && x<403 && y<740)
                    {
                        if(controladorsommenu2 == 0 && menuatual == 2)
                        {
                            Mix_PlayChannel(-1, effectsound3, 0);
                            controladorsommenu2 = 1;
                        }
                        seletormenu2pirate = true;
                    }
                    else
                    {
                        seletormenu2play = false;
                        seletormenu2scores = false;
                        seletormenu2pirate = false;
                        controladorsommenu2 = 0;
                    }
                    //icone dos personagens em movimento (menu 5)
                    if(x>584 && y>284 && x<782 && y<482)
                    {
                        if(controladorsommenu5 == 0 && menuatual == 5)
                        {
                            Mix_PlayChannel(-1, effectsound3, 0);
                            controladorsommenu5 = 1;
                        }
                        mousenoLuffy = true;
                    }
                    else if(x>370 && y>284 && x<568 && y<482)
                    {
                        if(controladorsommenu5 == 0 && menuatual == 5)
                        {
                            Mix_PlayChannel(-1, effectsound3, 0);
                            controladorsommenu5 = 1;
                        }
                        mousenoZoro = true;
                    }
                    else if(x>798 && y>284 && x<996 && y<482)
                    {
                        if(controladorsommenu5 == 0 && menuatual == 5)
                        {
                            Mix_PlayChannel(-1, effectsound3, 0);
                            controladorsommenu5 = 1;
                        }
                        mousenoSanji = true;
                    }
                    else if(x>1012 && y>284 && x<1210 && y<482)
                    {
                        if(controladorsommenu5 == 0 && menuatual == 5)
                        {
                            Mix_PlayChannel(-1, effectsound3, 0);
                            controladorsommenu5 = 1;
                        }
                        mousenaNami = true;
                    }
                    else if(x>156 && y>284 && x<354 && y<482)
                    {
                        if(controladorsommenu5 == 0 && menuatual == 5)
                        {
                            Mix_PlayChannel(-1, effectsound3, 0);
                            controladorsommenu5 = 1;
                        }
                        mousenoAce = true;
                    }
                    else
                    {
                        mousenoLuffy = false;
                        mousenoZoro = false;
                        mousenoSanji = false;
                        mousenaNami = false;
                        mousenoAce = false;
                        controladorsommenu5 = 0;
                    }
             }
             if(eventos.type == SDL_MOUSEBUTTONDOWN)
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                         if(x>1171 && y>50 && x<1294 && y<173)
                         {
                             if (menuatual == 2 || menuatual == 5 || menuatual == 3)
                             {
                                 if(countsom==1)
                                 {
                                    Mix_PauseMusic();
                                    botaosomdesligar = true;
                                    botaosomligar = false;
                                 }
                                 else if (countsom==2)
                                 {
                                    Mix_ResumeMusic();
                                    botaosomligar = true;
                                    botaosomdesligar = false;
                                 }
                             }
                         }
                 }
             }
             if(eventos.type == SDL_KEYDOWN) //tecla pressionada para voltar a pagina anterior
             {
                 if(eventos.key.keysym.sym == SDLK_ESCAPE) //verifica se a tecla "Esc" foi pressionada
                 {
                     if(menuatual == 2)
                     {
                         Mix_PlayChannel(-1, effectsound2, 0);
                         voltarmenu1 = true;
                         abrirmenu2 = false;
                         abrirmenu5 = false;
                         voltarmenu2 = false;
                         abrirmenu3 = false;
                     }
                     else if(menuatual == 5 || menuatual == 3)
                     {
                         Mix_PlayChannel(-1, effectsound2, 0);
                         voltarmenu2 = true;
                         voltarmenu1 = false;
                         abrirmenu2 = false;
                         abrirmenu5 = false;
                         abrirmenu3 = false;
                     }
                 }
             }
             if(eventos.type == SDL_MOUSEBUTTONDOWN)
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                         if(x>1163 && y>578 && x<1311 && y<678)
                         {
                             if(menuatual == 2)
                             {
                                 Mix_PlayChannel(-1, effectsound2, 0);
                                 voltarmenu1 = true;
                                 abrirmenu2 = false;
                                 abrirmenu5 = false;
                                 voltarmenu2 = false;
                                 abrirmenu3 = false;
                             }
                             else if(menuatual == 5 || menuatual == 3)
                             {
                                 Mix_PlayChannel(-1, effectsound2, 0);
                                 voltarmenu2 = true;
                                 voltarmenu1 = false;
                                 abrirmenu2 = false;
                                 abrirmenu5 = false;
                                 abrirmenu3 = false;
                             }
                         }
                 }
             }
             if(eventos.type == SDL_MOUSEBUTTONDOWN)
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                         if(x>95 && y>214 && x<403 && y<365)
                         {
                             if(menuatual == 2)
                             {
                                 Mix_PlayChannel(-1, effectsound1, 0);
                                 abrirmenu3 = true; // botao "play" para abrir menu 3
                                 abrirmenu5 = false;
                                 voltarmenu1 = false;
                                 abrirmenu2 = false;
                                 voltarmenu2 = false;
                             }
                         }
                         else if(x>95 && y>590 && x<403 && y<740)
                         {
                             if(menuatual == 2)
                             {
                                 Mix_PlayChannel(-1, effectsound1, 0);
                                 abrirmenu5 = true; // botao "pirate" para abrir menu 5
                                 voltarmenu1 = false;
                                 abrirmenu2 = false;
                                 voltarmenu2 = false;
                                 abrirmenu3 = false;
                             }
                         }
                 }
             }
             // selecao de personagens no menu 5
             if(eventos.type == SDL_MOUSEBUTTONDOWN)
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                     if(menuatual == 5)
                     {
                         if(x>156 && y>284 && x<354 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             abrirmenu3 = false;
                             characterselected = 1; //Ace foi selecionado
                         }
                         else if(x>370 && y>284 && x<568 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             abrirmenu3 = false;
                             characterselected = 2; //Zoro foi selecionado
                         }
                         else if(x>584 && y>284 && x<782 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             abrirmenu3 = false;
                             characterselected = 3; //Luffy foi selecionado
                         }
                         else if(x>798 && y>284 && x<996 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             abrirmenu3 = false;
                             characterselected = 4; //Sanji foi selecionado
                         }
                         else if(x>1012 && y>284 && x<1210 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             abrirmenu3 = false;
                             characterselected = 5; //Nami foi selecionada
                         }
                     }
                 }
             }
             if(eventos.type == SDL_MOUSEBUTTONDOWN) // click em quadrados da matriz no Menu 3
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                     if(menuatual == 3)
                     {
                         if(x>420 && y>178 && x<479 && y<237)
                         {
                             if(contadorclick[0] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][0]==1) // 1 == pirata
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 0;
                             }
                             contadorclick[0]=1;
                             }
                         }
                         else if(x>478 && y>178 && x<537 && y<237)
                         {
                             if(contadorclick[1] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 1;
                             }
                             contadorclick[1] = 1;
                             }
                         }
                         else if(x>536 && y>178 && x<596 && y<237)
                         {
                             if(contadorclick[2] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 2;
                             }
                             contadorclick[2]=1;
                             }
                         }
                          else if(x>595 && y>178 && x<655 && y<237)
                         {
                             if(contadorclick[3] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 3;
                             }
                             contadorclick[3]=1;
                             }
                         }
                          else if(x>653 && y>178 && x<712 && y<237)
                         {
                             if(contadorclick[4] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 4;
                             }
                             contadorclick[4]=1;
                             }
                         }
                          else if(x>711 && y>178 && x<770 && y<237)
                         {
                             if(contadorclick[5] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 5;
                             }
                             contadorclick[5]=1;
                             }
                         }
                          else if(x>770 && y>178 && x<829 && y<237)
                         {
                             if(contadorclick[6] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 6;
                             }
                             contadorclick[6]=1;
                             }
                         }
                          else if(x>828 && y>178 && x<887 && y<237)
                         {
                             if(contadorclick[7] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 7;
                             }
                             contadorclick[7]=1;
                             }
                         }
                          else if(x>886 && y>178 && x<945 && y<237)
                         {
                             if(contadorclick[8] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 8;
                             }
                             contadorclick[8]=1;
                             }
                         }
                          else if(x>945 && y>178 && x<1004 && y<237)
                         {
                             if(contadorclick[9] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[0][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 179;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[0][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 179;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[0][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 179;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 0;
                                 dc = 9;
                             }
                             contadorclick[9]=1;
                             }
                         }
                          else if(x>420 && y>236 && x<479 && y<295)
                         {
                             if(contadorclick[10] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 0;

                             }
                             contadorclick[10]=1;
                             }
                         }
                         else if(x>478 && y>236 && x<537 && y<295)
                         {
                             if(contadorclick[11] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 1;
                             }
                             contadorclick[11]=1;
                             }
                         }
                         else if(x>536 && y>236 && x<595 && y<295)
                         {
                             if(contadorclick[12] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 2;
                             }
                             contadorclick[12]=1;
                             }
                         }
                         else if(x>595 && y>236 && x<654 && y<295)
                         {
                             if(contadorclick[13] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 3;
                             }
                             contadorclick[13]=1;
                             }
                         }
                         else if(x>653 && y>236 && x<712 && y<295)
                         {
                             if(contadorclick[14] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 4;
                             }
                             contadorclick[14]=1;
                             }
                         }
                         else if(x>711 && y>236 && x<770 && y<295)
                         {
                             if(contadorclick[15] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 5;
                             }
                             contadorclick[15]=1;
                             }
                         }
                         else if(x>770 && y>236 && x<829 && y<295)
                         {
                             if(contadorclick[16] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 6;
                             }
                             contadorclick[16]=1;
                             }
                         }
                         else if(x>828 && y>236 && x<887 && y<295)
                         {
                             if(contadorclick[17] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 7;
                             }
                             contadorclick[17]=1;
                             }
                         }
                         else if(x>886 && y>236 && x<945 && y<295)
                         {
                             if(contadorclick[18] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 8;
                             }
                             contadorclick[18]=1;
                             }
                         }
                         else if(x>945 && y>236 && x<1004 && y<295)
                         {
                             if(contadorclick[19] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[1][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 237;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[1][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 237;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[1][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 237;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 1;
                                 dc = 9;
                             }
                             contadorclick[19]=1;
                             }
                         }
                         else if(x>420 && y>294 && x<479 && y<354)
                         {
                             if(contadorclick[20] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 0;
                             }
                             contadorclick[20]=1;
                             }
                         }
                         else if(x>478 && y>294 && x<537 && y<354)
                         {
                             if(contadorclick[21] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 1;
                             }
                             contadorclick[21]=1;
                             }
                         }
                         else if(x>536 && y>294 && x<595 && y<354)
                         {
                             if(contadorclick[22] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 2;
                             }
                             contadorclick[22]=1;
                             }
                         }
                         else if(x>595 && y>294 && x<654 && y<354)
                         {
                             if(contadorclick[23] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 3;
                             }
                             contadorclick[23]=1;
                             }
                         }
                         else if(x>653 && y>294 && x<712 && y<354)
                         {
                             if(contadorclick[24] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 4;
                             }
                             contadorclick[24]=1;
                             }
                         }
                         else if(x>711 && y>294 && x<770 && y<354)
                         {
                             if(contadorclick[25] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 5;
                             }
                             contadorclick[25]=1;
                             }
                         }
                         else if(x>770 && y>294 && x<829 && y<354)
                         {
                             if(contadorclick[26] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 6;
                             }
                             contadorclick[26]=1;
                             }
                         }
                         else if(x>828 && y>294 && x<887 && y<354)
                         {
                             if(contadorclick[27] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 7;
                             }
                             contadorclick[27]=1;
                             }
                         }
                         else if(x>886 && y>294 && x<946 && y<354)
                         {
                             if(contadorclick[28] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 8;
                             }
                             contadorclick[28]=1;
                             }
                         }
                         else if(x>945 && y>294 && x<1004 && y<354)
                         {
                             if(contadorclick[29] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[2][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 295;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[2][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 295;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[2][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 295;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 2;
                                 dc = 9;
                             }
                             contadorclick[29]=1;
                             }
                         }
                         else if(x>420 && y>353 && x<479 && y<412)
                         {
                             if(contadorclick[30] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 0;
                             }
                             contadorclick[30]=1;
                             }
                         }
                          else if(x>478 && y>353 && x<537 && y<412)
                         {
                             if(contadorclick[31] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 1;
                             }
                             contadorclick[31]=1;
                             }
                         }
                          else if(x>536 && y>353 && x<595 && y<412)
                         {
                             if(contadorclick[32] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 2;
                             }
                             contadorclick[32]=1;
                             }
                         }
                          else if(x>595 && y>353 && x<654 && y<412)
                         {
                             if(contadorclick[33] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 3;
                             }
                             contadorclick[33]=1;
                             }
                         }
                          else if(x>653 && y>353 && x<712 && y<412)
                         {
                             if(contadorclick[34] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 4;
                             }
                             contadorclick[34]=1;
                             }
                         }
                          else if(x>711 && y>353 && x<770 && y<412)
                         {
                             if(contadorclick[35] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 5;
                             }
                             contadorclick[35]=1;
                             }
                         }
                          else if(x>770 && y>353 && x<829 && y<412)
                         {
                             if(contadorclick[36] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 6;
                             }
                             contadorclick[36]=1;
                             }
                         }
                          else if(x>828 && y>353 && x<887 && y<412)
                         {
                             if(contadorclick[37] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 7;
                             }
                             contadorclick[37]=1;
                             }
                         }
                          else if(x>886 && y>353 && x<945 && y<412)
                         {
                             if(contadorclick[38] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 8;
                             }
                             contadorclick[38]=1;
                             }
                         }
                          else if(x>945 && y>353 && x<1004 && y<412)
                         {
                             if(contadorclick[39] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[3][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 354;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[3][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 354;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[3][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 354;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 3;
                                 dc = 9;
                             }
                             contadorclick[39]=1;
                             }
                         }
                          else if(x>420 && y>411 && x<478 && y<470)
                         {
                             if(contadorclick[40] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 0;
                             }
                             contadorclick[40]=1;
                             }
                         }
                          else if(x>478 && y>411 && x<537 && y<470)
                         {
                             if(contadorclick[41] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 1;
                             }
                             contadorclick[41]=1;
                             }
                         }
                          else if(x>536 && y>411 && x<595 && y<470)
                         {
                             if(contadorclick[42] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 2;
                             }
                             contadorclick[42]=1;
                             }
                         }
                          else if(x>595 && y>411 && x<654 && y<470)
                         {
                             if(contadorclick[43] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 3;
                             }
                             contadorclick[43]=1;
                             }
                         }
                          else if(x>653 && y>411 && x<712 && y<470)
                         {
                             if(contadorclick[44] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 4;
                             }
                             contadorclick[44]=1;
                             }
                         }
                          else if(x>711 && y>411 && x<771 && y<470)
                         {
                             if(contadorclick[45] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 5;
                             }
                             contadorclick[45]=1;
                             }
                         }
                          else if(x>770 && y>411 && x<829 && y<470)
                         {
                             if(contadorclick[46] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 6;
                             }
                             contadorclick[46]=1;
                             }
                         }
                          else if(x>828 && y>411 && x<887 && y<470)
                         {
                             if(contadorclick[47] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 7;
                             }
                             contadorclick[47]=1;
                             }
                         }
                          else if(x>886 && y>411 && x<945 && y<470)
                         {
                             if(contadorclick[48] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 8;
                             }
                             contadorclick[48]=1;
                             }
                         }
                          else if(x>945 && y>411 && x<1004 && y<470)
                         {
                             if(contadorclick[49] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[4][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 412;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[4][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 412;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[4][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 412;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 4;
                                 dc = 9;
                             }
                             contadorclick[49]=1;
                             }
                         }
                          else if(x>420 && y>469 && x<479 && y<528)
                         {
                             if(contadorclick[50] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 0;
                             }
                             contadorclick[50]=1;
                             }
                         }
                         else if(x>478 && y>469 && x<537 && y<528)
                         {
                             if(contadorclick[51] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 1;
                             }
                             contadorclick[51]=1;
                             }
                         }
                         else if(x>536 && y>469 && x<595 && y<528)
                         {
                             if(contadorclick[52] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 2;
                             }
                             contadorclick[52]=1;
                             }
                         }
                         else if(x>595 && y>469 && x<654 && y<528)
                         {
                             if(contadorclick[53] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 3;
                             }
                             contadorclick[53]=1;
                             }
                         }
                         else if(x>653 && y>469 && x<712 && y<528)
                         {
                             if(contadorclick[54] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 4;
                             }
                             contadorclick[54]=1;
                             }
                         }
                         else if(x>711 && y>469 && x<770 && y<528)
                         {
                             if(contadorclick[55] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 5;
                             }
                             contadorclick[55]=1;
                             }
                         }
                         else if(x>770 && y>469 && x<829 && y<528)
                         {
                             if(contadorclick[56] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 6;
                             }
                             contadorclick[56]=1;
                             }
                         }
                         else if(x>828 && y>469 && x<887 && y<528)
                         {
                             if(contadorclick[57] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 7;
                             }
                             contadorclick[57]=1;
                             }
                         }
                         else if(x>886 && y>469 && x<945 && y<528)
                         {
                             if(contadorclick[58] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 8;
                             }
                             contadorclick[58]=1;
                             }
                         }
                         else if(x>945 && y>469 && x<1004 && y<528)
                         {
                             if(contadorclick[59] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[5][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 470;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[5][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 470;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[5][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 470;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 5;
                                 dc = 9;
                             }
                             contadorclick[59]=1;
                             }
                         }
                         else if(x>420 && y>528 && x<479 && y<587)
                         {
                             if(contadorclick[60] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 0;
                             }
                             contadorclick[60]=1;
                             }
                         }
                         else if(x>478 && y>528 && x<537 && y<587)
                         {
                             if(contadorclick[61] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 1;
                             }
                             contadorclick[61]=1;
                             }
                         }
                         else if(x>536 && y>528 && x<595 && y<587)
                         {
                             if(contadorclick[62] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 2;
                             }
                             contadorclick[62]=1;
                             }
                         }
                         else if(x>595 && y>528 && x<654 && y<587)
                         {
                             if(contadorclick[63] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 3;
                             }
                             contadorclick[63]=1;
                             }
                         }
                         else if(x>653 && y>528 && x<712 && y<587)
                         {
                             if(contadorclick[64] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 4;
                             }
                             contadorclick[64]=1;
                             }
                         }
                         else if(x>711 && y>528 && x<769 && y<587)
                         {
                             if(contadorclick[65] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 5;
                             }
                             contadorclick[65]=1;
                             }
                         }
                         else if(x>770 && y>528 && x<829 && y<587)
                         {
                             if(contadorclick[66] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 6;
                             }
                             contadorclick[66]=1;
                             }
                         }
                         else if(x>828 && y>528 && x<887 && y<587)
                         {
                             if(contadorclick[67] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 7;
                             }
                             contadorclick[67]=1;
                             }
                         }
                         else if(x>886 && y>528 && x<945 && y<587)
                         {
                             if(contadorclick[68] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 8;
                             }
                             contadorclick[68]=1;
                             }
                         }
                         else if(x>945 && y>528 && x<1004 && y<587)
                         {
                             if(contadorclick[69] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[6][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 529;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[6][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 529;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[6][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 529;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 6;
                                 dc = 9;
                             }
                             contadorclick[69]=1;
                             }
                         }
                         else if(x>420 && y>586 && x<479 && y<645)
                         {
                             if(contadorclick[70] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 0;
                             }
                             contadorclick[70]=1;
                             }
                         }
                         else if(x>478 && y>586 && x<537 && y<645)
                         {
                             if(contadorclick[71] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 1;
                             }
                             contadorclick[71]=1;
                             }
                         }
                         else if(x>536 && y>586 && x<595 && y<645)
                         {
                             if(contadorclick[72] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 2;
                             }
                             contadorclick[72]=1;
                             }
                         }
                         else if(x>595 && y>586 && x<654 && y<645)
                         {
                             if(contadorclick[73] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 3;
                             }
                             contadorclick[73]=1;
                             }
                         }
                         else if(x>653 && y>586 && x<712 && y<645)
                         {
                             if(contadorclick[74] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 4;
                             }
                             contadorclick[74]=1;
                             }
                         }
                         else if(x>711 && y>586 && x<770 && y<645)
                         {
                             if(contadorclick[75] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 5;
                             }
                             contadorclick[75]=1;
                             }
                         }
                         else if(x>770 && y>586 && x<829 && y<645)
                         {
                             if(contadorclick[76] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 6;
                             }
                             contadorclick[76]=1;
                             }
                         }
                         else if(x>828 && y>586 && x<887 && y<645)
                         {
                             if(contadorclick[77] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 7;
                             }
                             contadorclick[77]=1;
                             }
                         }
                         else if(x>886 && y>586 && x<943 && y<645)
                         {
                             if(contadorclick[78] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 8;
                             }
                             contadorclick[78]=1;
                             }
                         }
                         else if(x>945 && y>586 && x<1004 && y<645)
                         {
                             if(contadorclick[79] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[7][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 587;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[7][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 587;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[7][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 587;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 7;
                                 dc = 9;
                             }
                             contadorclick[79]=1;
                             }
                         }
                         else if(x>420 && y>644 && x<479 && y<703)
                         {
                             if(contadorclick[80] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 0;
                             }
                             contadorclick[80]=1;
                             }
                         }
                         else if(x>478 && y>644 && x<537 && y<703)
                         {
                             if(contadorclick[81] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 1;
                             }
                             contadorclick[81]=1;
                             }
                         }
                         else if(x>536 && y>644 && x<595 && y<703)
                         {
                             if(contadorclick[82] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 2;
                             }
                             contadorclick[82]=1;
                             }
                         }
                         else if(x>595 && y>644 && x<654 && y<703)
                         {
                             if(contadorclick[83] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 3;
                             }
                             contadorclick[83]=1;
                             }
                         }
                         else if(x>653 && y>644 && x<712 && y<703)
                         {
                             if(contadorclick[84] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 4;
                             }
                             contadorclick[84]=1;
                             }
                         }
                         else if(x>711 && y>644 && x<770 && y<703)
                         {
                             if(contadorclick[85] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 712;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 712;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 712;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 5;
                             }
                             contadorclick[85]=1;
                             }
                         }
                         else if(x>770 && y>644 && x<829 && y<703)
                         {
                             if(contadorclick[86] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 6;
                             }
                             contadorclick[86]=1;
                             }
                         }
                         else if(x>828 && y>644 && x<887 && y<703)
                         {
                             if(contadorclick[87] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 7;
                             }
                             contadorclick[87]=1;
                             }
                         }
                         else if(x>886 && y>644 && x<945 && y<703)
                         {
                             if(contadorclick[88] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 8;
                             }
                             contadorclick[88]=1;
                             }
                         }
                         else if(x>945 && y>644 && x<1004 && y<703)
                         {
                             if(contadorclick[89] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[8][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 645;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[8][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 645;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[8][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 645;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 8;
                                 dc = 9;
                             }
                             contadorclick[89]=1;
                             }
                         }
                         else if(x>420 && y>702 && x<479 && y<761)
                         {
                             if(contadorclick[90] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][0]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 421;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][0]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 421;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][0]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 421;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 0;
                             }
                             contadorclick[90]=1;
                             }
                         }
                          else if(x>478 && y>702 && x<537 && y<761)
                         {
                             if(contadorclick[91] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][1]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 479;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][1]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 479;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][1]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 479;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 1;
                             }
                             contadorclick[91]=1;
                             }
                         }
                          else if(x>536 && y>702 && x<595 && y<761)
                         {
                             if(contadorclick[92] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][2]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 537;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][2]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 537;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][2]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 537;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 2;
                             }
                             contadorclick[92]=1;
                             }
                         }
                          else if(x>595 && y>702 && x<654 && y<761)
                         {
                             if(contadorclick[93] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][3]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 596;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][3]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 596;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][3]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 596;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 3;
                             }
                             contadorclick[93]=1;
                             }
                         }
                          else if(x>653 && y>702 && x<712 && y<761)
                         {
                             if(contadorclick[94] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][4]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 654;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][4]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 654;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][4]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 654;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 4;
                             }
                             contadorclick[94]=1;
                             }
                         }
                          else if(x>712 && y>702 && x<771 && y<761)
                         {
                             if(contadorclick[95] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][5]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 713;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][5]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 713;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][5]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 713;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 5;
                             }
                             contadorclick[95]=1;
                             }
                         }
                          else if(x>770 && y>702 && x<829 && y<761)
                         {
                             if(contadorclick[96] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][6]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 771;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][6]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 771;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][6]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 771;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 6;
                             }
                             contadorclick[96]=1;
                             }
                         }
                          else if(x>828 && y>702 && x<887 && y<761)
                         {
                             if(contadorclick[97] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][7]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 829;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][7]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 829;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][7]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 829;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 7;
                             }
                             contadorclick[97]=1;
                             }
                         }
                          else if(x>886 && y>702 && x<945 && y<761)
                         {
                             if(contadorclick[98] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][8]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 887;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][8]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 887;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][8]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 887;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 8;
                             }
                             contadorclick[98]=1;
                             }
                         }
                          else if(x>945 && y>702 && x<1004 && y<761)
                         {
                             if(contadorclick[99] < 1){
                             Mix_PlayChannel(-1, effectsound3, 0);
                             if(M[9][9]==1)
                             {
                                 abrirquadradopirata[np] = true;
                                 ipirata[np] = 946;
                                 jpirata[np] = 703;
                                 np++;
                                 quadradoatual = 0;
                             }
                             else if(M[9][9]==2) // 2 == ilha
                             {
                                 abrirquadradoilha[ni] = true;
                                 iilha[ni] = 946;
                                 jilha[ni] = 703;
                                 ni++;
                                 quadradoatual = 1;
                             }
                             else if(M[9][9]==3)
                             {
                                 abrirquadradobussola[nb] = true;
                                 ibussola[nb] = 946;
                                 jbussola[nb] = 703;
                                 nb++;
                                 quadradoatual = 2;
                                 dica = true;
                                 dl = 9;
                                 dc = 9;
                             }
                             contadorclick[99]=1;
                             }
                         }
                     }
                 }
             }
             if(eventos.type == SDL_MOUSEBUTTONDOWN) // click apos "SE FODEU" para retornar ao menu 2
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                     if(perdeuojogo == true)
                     {
                         voltarmenu2 = true;
                         abrirmenu2 = false;
                         abrirmenu3 = false;
                         abrirmenu5 = false;
                         voltarmenu1 = false;
                         perdeuojogo = false; // para voltar ao menu 2
                         Mix_ResumeMusic();
                         recomecarjogo = true;
                     }
                     else if(ganhouojogo == true)
                     {
                         voltarmenu2 = true;
                         abrirmenu2 = false;
                         abrirmenu3 = false;
                         abrirmenu5 = false;
                         voltarmenu1 = false;
                         ganhouojogo = false; // para voltar ao menu 2
                         Mix_ResumeMusic();
                         recomecarjogo = true;
                     }
                 }
             }
             if(eventos.type == SDL_MOUSEBUTTONDOWN) // click apos "SE FODEU" para retornar ao menu 2
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                     if(menuatual == 3)
                     {
                         if(characterselected == 1 && np == 4)
                         {
                             if(contadorsomgtav == 0)
                             {
                                 Mix_PlayChannel(-1, effectsound4, 0);
                                 contadorsomgtav = 1;
                             }
                         }
                         else if (characterselected == 2 && np == 5)
                         {
                             if(contadorsomgtav == 0)
                             {
                                 Mix_PlayChannel(-1, effectsound4, 0);
                                 contadorsomgtav = 1;
                             }
                         }
                         else if(characterselected == 3 && np == 6)
                         {
                             if(contadorsomgtav == 0)
                             {
                                 Mix_PlayChannel(-1, effectsound4, 0);
                                 contadorsomgtav = 1;
                             }
                         }
                         else if(characterselected == 4 && np == 5)
                         {
                             if(contadorsomgtav == 0)
                             {
                                 Mix_PlayChannel(-1, effectsound4, 0);
                                 contadorsomgtav = 1;
                             }
                         }
                         else if(characterselected == 5 && np == 3)
                         {
                             if(contadorsomgtav == 0)
                             {
                                 Mix_PlayChannel(-1, effectsound4, 0);
                                 contadorsomgtav = 1;
                             }
                         }
                         else if(ni == 5)
                         {
                             if(contadorsomgod == 0)
                             {
                                 Mix_PlayChannel(-1, effectsound5, 0);
                                 contadorsomgod = 1;
                             }
                         }
                     }
                 }
             }
         }
         //LOGICA

         //MOVIMENT0


         //RENDERIZACAO
         glClear(GL_COLOR_BUFFER_BIT); // limpa o buffer

         glPushMatrix(); //inicia a matriz

         glOrtho(0, 1366, 768, 0, -1, 1); //dimensoes da matriz

         glColor4ub(255, 255, 255, 255); //cor branca (mantem cores originais da imagem sendo carregada)

         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, menu1);

         //inicia desenho da imagem
         glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

         glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
         glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
         glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
         glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

         glEnd(); //fecha desenho da imagem

         glDisable(GL_TEXTURE_2D);

         if (abrirmenu2 == true || voltarmenu2 == true)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, menu2);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);

             menuatual = 2;
         }
         // onde o seletor vai estar no menu 2
         if (seletormenu2play == true && menuatual == 2)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, botaoplaycomseletor);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(39, 165); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(461, 165); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(461, 415); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(39, 415); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);
         }
         else if(seletormenu2scores == true && menuatual == 2)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, botaoscorescomseletor);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(39, 354); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(461, 354); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(461, 604); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(39, 604); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);
         }
         else if(seletormenu2pirate == true && menuatual == 2)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, botaopiratecomseletor);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(39, 543); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(461, 543); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(461, 768); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(39, 768); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);
         }

         if(menuatual == 2)
         {
             if (voltarmenu1 == true)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, menu1);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);

                 menuatual = 1;
             }
         }
         if (abrirmenu5 == true)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, menu5);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);

             menuatual = 5;
         }
         // icone ampliado dos personagens (menu 5)
         if (mousenoLuffy == true && menuatual == 5)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, iconLuffywithmotion);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(560, 262); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(804, 262); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(804, 506); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(560, 506); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);
         }
         else if (mousenoZoro == true && menuatual == 5)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, iconZorowithmotion);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(337, 204); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(590, 204); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(590, 506); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(337, 506); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);
         }
         else if (mousenoSanji == true && menuatual == 5)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, iconSanjiwithmotion);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(754, 262); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(1019, 262); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(1019, 506); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(754, 506); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);
         }
         else if (mousenaNami == true && menuatual == 5)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, iconNamiwithmotion);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(989, 262); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(1255, 262); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(1255, 506); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(989, 506); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);
         }
         else if (mousenoAce == true && menuatual == 5)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, iconAcewithMotion);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(132, 262); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(398, 262); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(398, 506); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(132, 506); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);
         }
         // Menu 5
         if (abrirmenu3 == true)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, menu3);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);

             menuatual = 3;
         }
         // desligar som (colocar imagem "straw hat flag")
         if(botaosomdesligar == true)
         {
             if(menuatual == 2 || menuatual == 5 || menuatual == 3)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, somstrawhatflag);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(1171, 50); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(1294, 50); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(1294, 173); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(1171, 173); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);

                 countsom = 2;
             }
         }
         else if(botaosomligar == true)
         {
             if(menuatual == 2 || menuatual == 5)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, substituicaostrawhatflag);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(1171, 50); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(1294, 50); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(1294, 173); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(1171, 173); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);

                 countsom = 1;
             }
             else if(menuatual == 3)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, substituicaostrawhatflag2);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(1098, 3); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(1344, 3); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(1344, 228); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(1098, 228); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);

                 countsom = 1;
             }
         }
         // Personagem escolhido para jogar no Menu 3
         if (menuatual == 3)
         {
             if(characterselected == 1)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, iconAcewithMotion);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(10, 10); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(149, 10); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(149, 138); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(10, 138); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
                 //vidas (coracoes)
                 if (np < 4)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(143, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(243, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(243, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(143, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(249, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(349, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(349, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(249, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 2)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(355, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(455, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(455, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(355, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 1)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(461, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(561, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(561, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(461, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
             }
             else if(characterselected == 2)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, hpZoro);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(4, 0); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(137, 0); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(137, 138); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(4, 138); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
                 //vidas (coracoes)
                 if (np < 5)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(143, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(243, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(243, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(143, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 4)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(249, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(349, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(349, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(249, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(355, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(455, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(455, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(355, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 2)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(461, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(561, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(561, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(461, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 1)
                 {
                      glEnable(GL_TEXTURE_2D);
                      glBindTexture(GL_TEXTURE_2D, health);

                      //inicia desenho da imagem
                      glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                      glTexCoord2d(0, 0);  glVertex2f(567, 32); // primeiro ponto
                      glTexCoord2d(1, 0);  glVertex2f(667, 32); // segundo ponto
                      glTexCoord2d(1, 1);  glVertex2f(667, 118); // terceiro ponto
                      glTexCoord2d(0, 1);  glVertex2f(567, 118); // quarto ponto

                      glEnd(); //fecha desenho da imagem

                      glDisable(GL_TEXTURE_2D);

                 }
             }
             else if(characterselected == 3)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, iconLuffywithmotion);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(10, 10); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(138, 10); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(138, 138); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(10, 138); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
                 // vidas (coracoes)
                 if (np < 6)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(143, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(243, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(243, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(143, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 5)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(249, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(349, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(349, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(249, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 4)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(355, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(455, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(455, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(355, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(461, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(561, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(561, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(461, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 2)
                 {
                      glEnable(GL_TEXTURE_2D);
                      glBindTexture(GL_TEXTURE_2D, health);

                      //inicia desenho da imagem
                      glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                      glTexCoord2d(0, 0);  glVertex2f(567, 32); // primeiro ponto
                      glTexCoord2d(1, 0);  glVertex2f(667, 32); // segundo ponto
                      glTexCoord2d(1, 1);  glVertex2f(667, 118); // terceiro ponto
                      glTexCoord2d(0, 1);  glVertex2f(567, 118); // quarto ponto

                      glEnd(); //fecha desenho da imagem

                      glDisable(GL_TEXTURE_2D);

                 }
                 if (np < 1)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(673, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(773, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(773, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(673, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
             }
             else if(characterselected == 4)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, iconSanjiwithmotion);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 10); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(138, 10); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(138, 138); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 138); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
                 //vidas (coracoes)
                 if (np < 5)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(143, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(243, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(243, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(143, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 4)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(249, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(349, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(349, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(249, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(355, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(455, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(455, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(355, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 2)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(461, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(561, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(561, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(461, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 1)
                 {
                      glEnable(GL_TEXTURE_2D);
                      glBindTexture(GL_TEXTURE_2D, health);

                      //inicia desenho da imagem
                      glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                      glTexCoord2d(0, 0);  glVertex2f(567, 32); // primeiro ponto
                      glTexCoord2d(1, 0);  glVertex2f(667, 32); // segundo ponto
                      glTexCoord2d(1, 1);  glVertex2f(667, 118); // terceiro ponto
                      glTexCoord2d(0, 1);  glVertex2f(567, 118); // quarto ponto

                      glEnd(); //fecha desenho da imagem

                      glDisable(GL_TEXTURE_2D);

                 }
             }
             else if(characterselected == 5)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, iconNamiwithmotion);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(10, 10); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(150, 10); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(150, 138); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(10, 138); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
                 //vidas (coracoes)
                 if (np < 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(143, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(243, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(243, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(143, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 2)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(249, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(349, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(349, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(249, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
                 if(np < 1)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, health);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(355, 32); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(455, 32); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(455, 118); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(355, 118); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);
                 }
             }
         }
         if(menuatual == 3)
         {
             //np == numero de piratas abertos
             if(np>0)
             {
                 if (abrirquadradopirata[0] == true)
                 {
                    i=0;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradopirata[1] == true)
                 {
                    i=1;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradopirata[2] == true)
                 {
                    i=2;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradopirata[3] == true)
                 {
                    i=3;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradopirata[4] == true)
                 {
                    i=4;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }if (abrirquadradopirata[5] == true)
                 {
                    i=5;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradopirata[6] == true)
                 {
                    i=6;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradopirata[7] == true)
                 {
                    i=7;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradopirata[8] == true)
                 {
                    i=8;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradopirata[9] == true)
                 {
                    i=9;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradopirata);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ipirata[i], jpirata[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ipirata[i], jpirata[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ipirata[i], 58+jpirata[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ipirata[i], 58+jpirata[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
             }
             //ni == numero de ilhas abertas
             if(ni>0)
             {
                 if (abrirquadradoilha[0] == true)
                 {
                    i=0;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradoilha);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(iilha[i], jilha[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+iilha[i], jilha[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+iilha[i], 58+jilha[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(iilha[i], 58+jilha[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradoilha[1] == true)
                 {
                    i=1;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradoilha);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(iilha[i], jilha[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+iilha[i], jilha[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+iilha[i], 58+jilha[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(iilha[i], 58+jilha[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradoilha[2] == true)
                 {
                    i=2;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradoilha);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(iilha[i], jilha[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+iilha[i], jilha[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+iilha[i], 58+jilha[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(iilha[i], 58+jilha[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradoilha[3] == true)
                 {
                    i=3;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradoilha);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(iilha[i], jilha[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+iilha[i], jilha[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+iilha[i], 58+jilha[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(iilha[i], 58+jilha[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradoilha[4] == true)
                 {
                    i=4;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradoilha);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(iilha[i], jilha[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+iilha[i], jilha[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+iilha[i], 58+jilha[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(iilha[i], 58+jilha[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
             }
             //nb == numero de bussolas abertas
             if(nb>0)
             {
                 if (abrirquadradobussola[0] == true)
                 {
                    i=0;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[1] == true)
                 {
                    i=1;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[2] == true)
                 {
                    i=2;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[3] == true)
                 {
                    i=3;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[4] == true)
                 {
                    i=4;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[5] == true)
                 {
                    i=5;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[6] == true)
                 {
                    i=6;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[7] == true)
                 {
                    i=7;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[8] == true)
                 {
                    i=8;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[9] == true)
                 {
                    i=9;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[10] == true)
                 {
                    i=10;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[11] == true)
                 {
                    i=11;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[12] == true)
                 {
                    i=12;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[13] == true)
                 {
                    i=13;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[14] == true)
                 {
                    i=14;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[15] == true)
                 {
                    i=15;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[16] == true)
                 {
                    i=16;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[17] == true)
                 {
                    i=17;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[18] == true)
                 {
                    i=18;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[19] == true)
                 {
                    i=19;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[20] == true)
                 {
                    i=20;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[21] == true)
                 {
                    i=21;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[22] == true)
                 {
                    i=22;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[23] == true)
                 {
                    i=23;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[24] == true)
                 {
                    i=24;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[25] == true)
                 {
                    i=25;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[26] == true)
                 {
                    i=26;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[27] == true)
                 {
                    i=27;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[28] == true)
                 {
                    i=28;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[29] == true)
                 {
                    i=29;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[30] == true)
                 {
                    i=30;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[31] == true)
                 {
                    i=31;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[32] == true)
                 {
                    i=32;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[33] == true)
                 {
                    i=33;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[34] == true)
                 {
                    i=34;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[35] == true)
                 {
                    i=35;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[36] == true)
                 {
                    i=36;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[37] == true)
                 {
                    i=37;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[38] == true)
                 {
                    i=38;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[39] == true)
                 {
                    i=39;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[40] == true)
                 {
                    i=40;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[41] == true)
                 {
                    i=41;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[42] == true)
                 {
                    i=42;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[43] == true)
                 {
                    i=43;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[44] == true)
                 {
                    i=44;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[45] == true)
                 {
                    i=45;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[46] == true)
                 {
                    i=46;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[47] == true)
                 {
                    i=47;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[48] == true)
                 {
                    i=48;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[49] == true)
                 {
                    i=49;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[50] == true)
                 {
                    i=50;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[51] == true)
                 {
                    i=51;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[52] == true)
                 {
                    i=52;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[53] == true)
                 {
                    i=53;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[54] == true)
                 {
                    i=54;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[55] == true)
                 {
                    i=55;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[56] == true)
                 {
                    i=56;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[57] == true)
                 {
                    i=57;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[58] == true)
                 {
                    i=58;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[59] == true)
                 {
                    i=59;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[60] == true)
                 {
                    i=60;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[61] == true)
                 {
                    i=61;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[62] == true)
                 {
                    i=62;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[63] == true)
                 {
                    i=63;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[64] == true)
                 {
                    i=64;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[65] == true)
                 {
                    i=65;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[66] == true)
                 {
                    i=66;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[67] == true)
                 {
                    i=67;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[68] == true)
                 {
                    i=68;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[69] == true)
                 {
                    i=69;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[70] == true)
                 {
                    i=70;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[71] == true)
                 {
                    i=71;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[72] == true)
                 {
                    i=72;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[73] == true)
                 {
                    i=73;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[74] == true)
                 {
                    i=74;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[75] == true)
                 {
                    i=75;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[76] == true)
                 {
                    i=76;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[77] == true)
                 {
                    i=77;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[78] == true)
                 {
                    i=78;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[79] == true)
                 {
                    i=79;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[80] == true)
                 {
                    i=80;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[81] == true)
                 {
                    i=81;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[82] == true)
                 {
                    i=82;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[83] == true)
                 {
                    i=83;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
                 if (abrirquadradobussola[84] == true)
                 {
                    i=84;

                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, quadradobussola);

                    //inicia desenho da imagem
                    glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                    glTexCoord2d(0, 0);  glVertex2f(ibussola[i], jbussola[i]); // primeiro ponto
                    glTexCoord2d(1, 0);  glVertex2f(58+ibussola[i], jbussola[i]); // segundo ponto
                    glTexCoord2d(1, 1);  glVertex2f(58+ibussola[i], 58+jbussola[i]); // terceiro ponto
                    glTexCoord2d(0, 1);  glVertex2f(ibussola[i], 58+jbussola[i]); // quarto ponto

                    glEnd(); //fecha desenho da imagem

                    glDisable(GL_TEXTURE_2D);
                 }
             }


         }
         //"SE FODEU" para quando perder o jogo
         if(characterselected == 1)
         {
             if(np == 4 && menuatual == 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, sefudeu);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);

                     perdeuojogo = true;
                     Mix_PauseMusic();
                 }
         }
         else if(characterselected == 2)
         {
             if(np == 5 && menuatual == 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, sefudeu);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);

                     perdeuojogo = true;
                     Mix_PauseMusic();
                 }
         }
         else if(characterselected == 3)
         {
             if(np == 6 && menuatual == 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, sefudeu);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);

                     perdeuojogo = true;
                     Mix_PauseMusic();
                 }
         }
         else if(characterselected == 4)
         {
             if(np == 5 && menuatual == 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, sefudeu);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);

                     perdeuojogo = true;
                     Mix_PauseMusic();
                 }
         }
         else if(characterselected == 5)
         {
             if(np == 3 && menuatual == 3)
                 {
                     glEnable(GL_TEXTURE_2D);
                     glBindTexture(GL_TEXTURE_2D, sefudeu);

                     //inicia desenho da imagem
                     glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                     glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
                     glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
                     glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
                     glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                     glEnd(); //fecha desenho da imagem

                     glDisable(GL_TEXTURE_2D);

                     perdeuojogo = true;
                     Mix_PauseMusic();
                 }
         }
         // "YOU FOUND ONE PIECE" quando ganhar o jogo
         if(ni == 5 && menuatual == 3)
         {
             glEnable(GL_TEXTURE_2D);
             glBindTexture(GL_TEXTURE_2D, youfoundonepiece);

             //inicia desenho da imagem
             glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

             glTexCoord2d(0, 0);  glVertex2f(0, 0); // primeiro ponto
             glTexCoord2d(1, 0);  glVertex2f(1366, 0); // segundo ponto
             glTexCoord2d(1, 1);  glVertex2f(1366, 768); // terceiro ponto
             glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

             glEnd(); //fecha desenho da imagem

             glDisable(GL_TEXTURE_2D);

             ganhouojogo = true;
             Mix_PauseMusic();
         }
         // Dicas
         if(quadradoatual == 2 && menuatual == 3)
         {
             // quantas ilhas tem em tal linha
             if(ilhanalinha == 0)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, linhailha0);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 179); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 179); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 462); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 462); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanalinha == 1)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, linhailha1);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 179); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 179); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 462); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 462); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanalinha == 2)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, linhailha2);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 179); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 179); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 462); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 462); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanalinha == 3)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, linhailha3);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 179); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 179); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 462); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 462); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanalinha == 4)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, linhailha4);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 179); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 179); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 462); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 462); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanalinha == 5)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, linhailha5);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 179); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 179); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 462); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 462); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             //quantas ilhas tem em tal coluna
             if(ilhanacoluna == 0)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, colunailha0);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 468); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 468); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 768); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanacoluna == 1)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, colunailha1);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 468); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 468); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 768); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanacoluna == 2)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, colunailha2);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 468); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 468); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 768); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanacoluna == 3)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, colunailha3);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 468); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 468); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 768); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanacoluna == 4)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, colunailha4);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 468); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 468); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 768); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
             else if(ilhanacoluna == 5)
             {
                 glEnable(GL_TEXTURE_2D);
                 glBindTexture(GL_TEXTURE_2D, colunailha5);

                 //inicia desenho da imagem
                 glBegin(GL_QUADS); //GL_POINTS, GL_LINES, GL_LINES_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

                 glTexCoord2d(0, 0);  glVertex2f(0, 468); // primeiro ponto
                 glTexCoord2d(1, 0);  glVertex2f(362, 468); // segundo ponto
                 glTexCoord2d(1, 1);  glVertex2f(362, 768); // terceiro ponto
                 glTexCoord2d(0, 1);  glVertex2f(0, 768); // quarto ponto

                 glEnd(); //fecha desenho da imagem

                 glDisable(GL_TEXTURE_2D);
             }
         }

         //SDL_BlitSurface(dica1, NULL, icon, &localTexto);

         glPopMatrix(); //fecha a matriz

         //ANIMACAO
         SDL_GL_SwapBuffers();
         }
     }

     printf ("\n Executando \n");

     //SDL_Delay(5000); //espera 5 segundos para fechar

    //glDisable(GL_BLEND);

    SDL_FreeSurface(icon);
    //SDL_FreeSurface(dica1);

    //TTF_CloseFont(fonte);

    Mix_FreeChunk(effectsound1); //liberar arquivo .WAV
    Mix_FreeChunk(effectsound2);
    Mix_FreeChunk(effectsound3);
    Mix_FreeChunk(effectsound4);
    Mix_FreeChunk(effectsound5);
    Mix_FreeMusic(music); //liberar arquivo .MP3
    Mix_CloseAudio();
    //TTF_Quit();

    SDL_Quit();

return 0;
}
