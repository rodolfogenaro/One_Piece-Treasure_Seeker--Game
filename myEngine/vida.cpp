#include "includes.h"

// tamanho e posicao vida inimigo
float enemyLifeX = 480;
float enemyLifeY = 20;
float ELwidth = 110;
float ELheight = 15;

//tamanho e posicao vida personagem
float personLifeX = 20;
float personLifeY = 20;
float PLwidth = 110;
float PLheight = 15;

// contorno vida inimigo
float contornoEnemyX = 475;
float contornoEnemyY = 15;
float CEwidth = 120;
float CEheight = 25;

//contorno vida personagem
float contornoPersonX = 15;
float contornoPersonY = 15;
float CPwidth = 120;
float CPheight = 25;

void desenhaContornoEnemy()
{
	//glBindTexture(GL_TEXTURE_2D, pad_texture); // what texture going to use (image)

	glColor4ub(0, 0, 0, 255);

	// drawing quad (pad)
	glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINE_TRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

	
	glVertex2f(contornoEnemyX, contornoEnemyY); // up left
	glVertex2f(contornoEnemyX + CEwidth, contornoEnemyY); // up right
	glVertex2f(contornoEnemyX + CEwidth, contornoEnemyY + CEheight); // down right
	glVertex2f(contornoEnemyX, contornoEnemyY + CEheight); // down left		

	// create the image in the quad created before
	// coord texture      coord quad
	

	glEnd(); // end drawing
}

void desenhaEnemyLife()
{
	//glBindTexture(GL_TEXTURE_2D, pad_texture); // what texture going to use (image)

	glColor4ub(255, 0, 0, 255);

	// drawing quad (pad)
	glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINE_TRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

	
	glVertex2f(enemyLifeX, enemyLifeY); // up left
	glVertex2f(enemyLifeX + ELwidth, enemyLifeY); // up right
	glVertex2f(enemyLifeX + ELwidth, enemyLifeY + ELheight); // down right
	glVertex2f(enemyLifeX, enemyLifeY + ELheight); // down left		

	// create the image in the quad created before
	// coord texture      coord quad
	

	glEnd(); // end drawing
}

void desenhaContornoPerson()
{
	//glBindTexture(GL_TEXTURE_2D, pad_texture); // what texture going to use (image)

	glColor4ub(0, 0, 0, 255);

	// drawing quad (pad)
	glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINE_TRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

	
	glVertex2f(contornoPersonX, contornoPersonY); // up left
	glVertex2f(contornoPersonX + CPwidth, contornoPersonY); // up right
	glVertex2f(contornoPersonX + CPwidth, contornoPersonY + CPheight); // down right
	glVertex2f(contornoPersonX, contornoPersonY + CPheight); // down left		

	// create the image in the quad created before
	// coord texture      coord quad
	

	glEnd(); // end drawing
}

void desenhaPersonLife()
{
	//glBindTexture(GL_TEXTURE_2D, pad_texture); // what texture going to use (image)

	glColor4ub(0, 255, 0, 255);

	// drawing quad (pad)
	glBegin(GL_QUADS); // GL_POINTS, GL_LINES, GL_LINE_TRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON

	
	glVertex2f(personLifeX, personLifeY); // up left
	glVertex2f(personLifeX + PLwidth, personLifeY); // up right
	glVertex2f(personLifeX + PLwidth, personLifeY + PLheight); // down right
	glVertex2f(personLifeX, personLifeY + PLheight); // down left		

	// create the image in the quad created before
	// coord texture      coord quad
	

	glEnd(); // end drawing
}
