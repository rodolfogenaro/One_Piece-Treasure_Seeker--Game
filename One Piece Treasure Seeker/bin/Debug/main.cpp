// g++ -o main main.cpp -lSDLmain -lSDL -lGL -lSDL_image

#include <SDL.h>
#include "SDL_opengl.h"
#include <stdio.h>
#include "SDL_image.h"
#include "string"
#include "SDL_mixer.h"

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

     //PARA USO DO AUDIO

     int frequencia = 47500;
     Uint16 formato = AUDIO_S16SYS;
     int canais = 2;
     int buffer = 4096;

     Mix_OpenAudio(frequencia, formato, canais, buffer); //inicializa o audio

     Mix_Music *music;
     music = Mix_LoadMUS("sounds\\One PiecePirate Warriors 3 OST-Main Menu.mp3");

     Mix_PlayMusic(music, -1);

     Mix_Chunk *effectsound1;
     effectsound1 = Mix_LoadWAV("sounds\\snd_00325.wav"); // efeito sonoro para prosseguir menu

     Mix_Chunk *effectsound2;
     effectsound2 = Mix_LoadWAV("sounds\\snd_00003.wav"); // efeito sonoro para retroceder menu

     Mix_Chunk *effectsound3;
     effectsound3 = Mix_LoadWAV("sounds\\snd_00308.wav"); // efeito sonoro para movimento do mouse em cima de algum botao
     int controladorsommenu2 = 0;
     int controladorsommenu5 = 0;

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


     //LOOP DO JOGO
     while (executando)
     {
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
                             if (menuatual == 2 || menuatual == 5)
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
                     }
                     else if(menuatual == 5)
                     {
                         Mix_PlayChannel(-1, effectsound2, 0);
                         voltarmenu2 = true;
                         voltarmenu1 = false;
                         abrirmenu2 = false;
                         abrirmenu5 = false;
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
                             }
                             else if(menuatual == 5)
                             {
                                 Mix_PlayChannel(-1, effectsound2, 0);
                                 voltarmenu2 = true;
                                 voltarmenu1 = false;
                                 abrirmenu2 = false;
                                 abrirmenu5 = false;
                             }
                         }
                 }
             }
             if(eventos.type == SDL_MOUSEBUTTONDOWN)
             {
                 if (eventos.button.button == SDL_BUTTON_LEFT)
                 {
                         if(x>95 && y>590 && x<403 && y<740)
                         {
                             if(menuatual == 2)
                             {
                                 Mix_PlayChannel(-1, effectsound1, 0);
                                 abrirmenu5 = true; // botao "pirate" para abrir menu 5
                                 voltarmenu1 = false;
                                 abrirmenu2 = false;
                                 voltarmenu2 = false;
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
                             characterselected = 1; //Ace foi selecionado
                         }
                         else if(x>370 && y>284 && x<568 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             characterselected = 2; //Zoro foi selecionado
                         }
                         else if(x>584 && y>284 && x<782 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             characterselected = 3; //Luffy foi selecionado
                         }
                         else if(x>798 && y>284 && x<996 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             characterselected = 4; //Sanji foi selecionado
                         }
                         else if(x>1012 && y>284 && x<1210 && y<482)
                         {
                             Mix_PlayChannel(-1, effectsound1, 0);
                             voltarmenu2 = true;
                             abrirmenu2 = false;
                             voltarmenu1 = false;
                             abrirmenu5 = false;
                             characterselected = 5; //Nami foi selecionada
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
         // desligar som (colocar imagem "straw hat flag")
         if(botaosomdesligar == true)
         {
             if(menuatual == 2 || menuatual == 5)
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

         glPopMatrix(); //fecha a matriz

         //ANIMACAO
         SDL_GL_SwapBuffers();
     }

     printf ("\n Executando \n");

     //SDL_Delay(5000); //espera 5 segundos para fechar

    //glDisable(GL_BLEND);

    SDL_FreeSurface(icon);

    Mix_FreeChunk(effectsound1); //liberar arquivo .WAV
    Mix_FreeChunk(effectsound2);
    Mix_FreeChunk(effectsound3);
    Mix_FreeMusic(music); //liberar arquivo .MP3
    Mix_CloseAudio();

    SDL_Quit();

return 0;
}
