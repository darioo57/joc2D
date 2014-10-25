#include "menu.h"
#include "Globals.h"
#include "cGame.h"


menu::menu()
{
}


menu::~menu()
{
}

bool menu::init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	bool res = false;
	res = Data.LoadImage(IMG_BLOCKS, "Botons/batu.png", GL_RGBA);
	if (!res) return false;
	else return true;
}

bool menu::Loop()
{
	bool res = true;
	res = Process();
	if (res) Render();

	return res;
}

bool menu::Process()
{
	return true;
}

void menu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	float xo, yo, xf, yf;
	int screen_x, screen_y, h, w;
	xo = 0.2; xf = 0.4;
	yo = 0.2; yf = 0.4;
	/*Posicio Pantalla*/
	screen_x = 200;
	screen_y = 150;
	/*Amplada, Alçacada repectivament*/
	w = 200; h = 50;
	int IDImage = Data.GetID(IMG_INICI_JOC);

	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yf);		glVertex2i(screen_x + w, screen_y);
	glTexCoord2f(xf, yf);		glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);		glVertex2i(screen_x, screen_y + h);
	glTexCoord2f(xo, yo);		glVertex2i(screen_x + w, screen_y + h);
	glEnd();

	glutSwapBuffers();
}
