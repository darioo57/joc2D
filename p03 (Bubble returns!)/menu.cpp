#include "menu.h"
#include "Globals.h"
#include "cGame.h"
bool firstLoading = true;

menu::menu()
{

}


menu::~menu()
{
}

int menu::dinsBoto(int clickX, int clickY)
{
	if ((260 < clickX && clickX < 530) && (145 < clickY && clickY < 175))
	{/*Boto Iniciar Partida*/
		return 1;
	}
	else if ((260 < clickX && clickX < 530) && (190 < clickY && clickY < 225))
	{/*Boto Instruccions*/
		return 2;
	}
	else if ((260 < clickX && clickX < 530) && (240 < clickY && clickY < 280))
	{/*Boto Credits*/
		return 3;
	}
	else if ((260 < clickX && clickX < 530) && (295 < clickY && clickY < 330))
	{/*Boto Nivell 1*/
		return 4;
	}
	return 0;
}

int menu::ReadMouse(int button, int state, int x, int y)
{
	return dinsBoto(x,y);
}

bool menu::init()
{
	glClearColor(0.1f, 0.5f, 0.1f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);

	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	bool res = false;
	res = Data.LoadImage(IMG_INICI_JOC, "Botons/metalSlug1.png", GL_RGBA);
	if (!res) return false;
	return true;
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
	CarregaPantalla();
}

void menu::CarregaPantalla()
{
	float xo, yo, xf, yf;
	int screen_x, screen_y, h, w;
	xf = 0.0f; xo = xf + 1.0f;
	yo = 0.0f; yf = 1.0f;
	/*Posicio Pantalla*/
	int ID = 0;
	ID = Data.GetID(IMG_INICI_JOC);
	
	screen_x = 0;
	screen_y = 0;
	/*Amplada, Alçacada repectivament*/
	w = WIDTH_INICIAL; h = HEIGHT_INICIAL;
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ID);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yf);		glVertex2i(screen_x + w, screen_y);
	glTexCoord2f(xf, yf);		glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);		glVertex2i(screen_x, screen_y + h);
	glTexCoord2f(xo, yo);		glVertex2i(screen_x + w, screen_y + h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glutSwapBuffers();
}
