

float VELTIRO = 35;

// tamanho e posicao do tiro
float tiroX; // recebe a posicao do personagem
float tiroY;
float tiroWid = 6;
float tiroHei = 3;
bool tiroAlive;

bool atirar = false;

unsigned int tiro_texture = 0;

void tiro()
{
	if (atirar == true)
	{
		tiroX += VELTIRO;
	}
}


void desenhaTiro()
{
	if (tiroAlive == true)
	{
		glBindTexture(GL_TEXTURE_2D, tiro_texture);

		glBegin(GL_QUADS);

		glTexCoord2d(0,0);   glVertex2f(tiroX, tiroY);
		glTexCoord2d(1,0);   glVertex2f(tiroX + tiroWid, tiroY);
		glTexCoord2d(1,1);   glVertex2f(tiroX + tiroWid, tiroY + tiroHei);
		glTexCoord2d(0,1);   glVertex2f(tiroX, tiroY + tiroHei);

		glEnd();
	}
	
}