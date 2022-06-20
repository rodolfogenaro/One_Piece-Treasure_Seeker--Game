#include "includes.h"
#include "personagem.cpp"
#include "inimigo.cpp"
#include "vida.cpp"

bool somColTiroInimigo = false;


// colisao
bool checkCollision(float obj1X, float obj1Y, float obj1W, float obj1H, float obj2X, float obj2Y, float obj2W, float obj2H)
{
	if (obj1Y+obj1H < obj2Y) return false;
	else if (obj1Y > obj2Y+obj2H) return false;
	else if (obj1X+obj1W < obj2X) return false;
	else if (obj1X > obj2X+obj2W) return false;

return true;
}

void caiu()
{
	if (morreu == true)
	{	
		isRunning = false;

		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n         CAIU NA LAVA ANIMAL ¬¬!!! \n\n\n\n\n\n\n\n\n\n");
		
	}
}



//-------------------------------INIMIGO BLOCO------------------------------------------------------------

void colisaoInimigoBloco()
{
	//----------------------LOGICA DO INIMIGO--------------------------------------------
	//     colisao inimigo / bloco

	inimigoX += vellx; // declara a velocidade do inimigo

	for (int n = 0; n < BRICKS; n++)
	{
		if (bricks[n].alive == true) // verify if exist some brick
		{		
			if (checkCollision(inimigoX, inimigoY, inimigoWH, inimigoWH, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height) == true)
			{
				vellx = -vellx;
				bricks[n].alive = false; // delete the brick before colide
				DESTROYED += 1;
				break; // return out function, because, before colidin, dont need verify other conditions
			}
		}
	}

	inimigoY += velly;
			

	// other (for) to y axis
	for (int n = 0; n < BRICKS; n++)
	{
		if (bricks[n].alive == true) // verify if exist some brick
		{		
			if (checkCollision(inimigoX, inimigoY, inimigoWH, inimigoWH, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height) == true)
			{
				velly = -velly;
				bricks[n].alive = false; // delete the brick before colide
				DESTROYED += 1;
				break; // return out function, because, before colidin, dont need verify other conditions
			}
		}
	}

	for (int n = 0; n < BRICKS; n++)
	{
		if (bricks[n].alive == true)
		{
			if ((DESTROYED == BRICKS-1))
			{
				//isRunning = false;
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n           O SOLO FOI CONSUMIDO \n SUA UNICA ALTERNATIVA \n EH NAO MORRER!!! \n\n\n\n\n\n\n\n\n");
				
			}
		}
		
	}
	
}


// ----------------------INIMIGO PERSONAGEM----------------------------------------------------------------------------------

void colisaoPersonagemInimigo() // inimigo bate no personagem
{
	// colisao inimigo / personagem
	if (checkCollision(inimigoX, inimigoY, inimigoWH, inimigoWH, myX, myY, width, height) == true)
	{
		VIDAS -= 1;
		PLwidth -= 10;

		damagePerson = true;

		printf("\n Dano personagem %d \n Vida restante %d \n", 10 - VIDAS, VIDAS);

		velly = -velly; // change the inimigo velocity/direction
		vellx = -vellx;

		if (VIDAS <= 0)
		{
			isRunning = false;	
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n        VOCE MORREU HAHAHA!!! \n\n       O INIMIGO TE PEGOU, TROXA  \n\n\n\n\n\n\n\n\n");
		}
	}
}

//--------------------------PERSONAGEM BLOCO----------------------------------------------------------------------------------

void colisaoPersonagemBloco()
{

	// --------------------------------------------Y-------------------------------------------------------------------------------
	for (int n = 0; n < BRICKS; n++)
	{
		if (bricks[n].alive == true) // verify if exist some brick
		{
			// colisao chao
			if ((checkCollision(myX, myY, width, height, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height) == true) && (myY < bricks[n].y))
			{
				float aux;
				aux = (HEIGHT - bricks[n].y); // altura janela - posicao ultimo bloco
				myY = ((HEIGHT - aux) - height) - 0.5; // altura janela - aux - altura personagem

				if ((myY = ((HEIGHT - aux) - height) - 0.5) && (checkCollision(myX, myY, width, height, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height) == true))
				{
					GRAVITY = 0;
				}

				break; // return out function, because, before colidin, dont need verify other conditions
			}

			// colisao teto
			if ((checkCollision(myX, myY, width, height, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height) == true) && (myY > bricks[n].y))
			{
				float aux;
				aux = (0 + bricks[n].y);
				myY = ((0 + aux) + bricks[n].height) + 1;

				break;
			}
		}
	}


	//--------------------------------------------X--------------------------------------------------------------------------------

	for (int n = 0; n < BRICKS; n++)
	{
		if (bricks[n].alive == true) // verify if exist some brick
		{	
			// colisao esquerda
			if ((checkCollision(myX, myY, width, height, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height) == true))
			{
				if ((left == true) && (checkCollision(myX, myY, width, height, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height) == true))
				{
					myX += 8;
				}
				else if ((right == true) && (checkCollision(myX, myY, width, height, bricks[n].x, bricks[n].y, bricks[n].width, bricks[n].height) == true))
				{
					myX -= 8;
				}		

				break; // return out function, because, before colidin, dont need verify other conditions
			}
		}
	}

	//-----------------------------------------------------------------------------------------------------------------------------
}

//----------------------------------------------------------------------------------------------------------------------------


void colisaoTiroInimigo()
{
	

	if (checkCollision(inimigoX, inimigoY, inimigoWH, inimigoWH, tiroX, tiroY, tiroWid, tiroHei) == true)
	{
		explosaoX = inimigoX+inimigoWH;
		explosaoY = inimigoY;		

		tiroAlive = false;
		
		explosao = true; // explosao

		somColTiroInimigo = true;
				

		printf("\n Dano inimigo %d \n Vidas restantes %d \n", 10 - vidaInimigo, vidaInimigo);

		if (vidaInimigo <= 0)
		{

			isRunning = false;
			SDL_Delay(1000); // delay no final para mostrar o dano

			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n           VOCE DERROTOU O INIMIGO!!!\n\n\n\n\n\n\n\n\n");
		}

		vidaInimigo -= 1;
		ELwidth -= 10;
	}
	else
	{
		somColTiroInimigo = false;
	}

}




void colisaoAtaquePersonagem() // acido
{
	if (checkCollision(ataque2X, ataque2Y, ataqueWH, ataqueWH, myX, myY, width, height) == true)
	{
		VIDAS -= 1;
		PLwidth -= 10; // barra de life do personagem dimunui

		damagePersonAcido = true;

		printf("\n Dano personagem %d \n Vida restante %d \n", 10 - VIDAS, VIDAS);

		if (VIDAS <= 0)
		{
			isRunning = false;	
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n        VOCE MORREU HAHAHA!!! \n\n       CHUVA ACIDA  \n\n\n\n\n\n\n\n\n");
		}
	}
}