#include "menu.h"
#include "Globals.h"
#include "cGame.h"


menu::menu()
{

}


menu::~menu()
{
}

int menu::dinsBoto(int clickX, int clickY)
{
	int mitatBotoX = WIDTH_BUTTON / 2;
	int mitatBotoY = HEIGHT_BUTTON / 2;
	int x = GAME_WIDTH/2;
	if ((x - mitatBotoX<clickX && clickX<x + mitatBotoX) && ((GAME_HEIGHT / 4) - mitatBotoY<clickY && clickY<(GAME_HEIGHT / 4) + mitatBotoY))
	{/*Boto Iniciar Partida*/
		pantallaCarregar = 1;
		iniciarPartida = true;
		return 0;
	}
	else if ((x - mitatBotoX<clickX && clickX<x + mitatBotoX) && ((GAME_HEIGHT / 2) - mitatBotoY<clickY && clickY<(GAME_HEIGHT / 2) + mitatBotoY))
	{/*Boto Instruccions*/
		pantallaCarregar = 2;
		return 0;
	}
	else if ((x - mitatBotoX<clickX && clickX<x + mitatBotoX) && (((GAME_HEIGHT / 4) * 3) - mitatBotoY<clickY && clickY<((GAME_HEIGHT / 4) * 3) + mitatBotoY))
	{/*Boto Credits*/
		pantallaCarregar = 3;
		return 0;
	}
	else if ((x - mitatBotoX<clickX && clickX<x + mitatBotoX) && ((GAME_HEIGHT / 3) - mitatBotoY<clickY && clickY<(GAME_HEIGHT / 3) + mitatBotoY))
	{/*Boto Nivell 1*/
		if(iniciarPartida) return 1;
		else return 0;
	}
	else if ((x - mitatBotoX<clickX && clickX<x + mitatBotoX) && ((GAME_HEIGHT / 3)*2 - mitatBotoY<clickY && clickY<(GAME_HEIGHT / 3)*2 + mitatBotoY))
	{/*Boto Nivell 2 negat o normal*/
		if (iniciarPartida && !nivell2Blocked) return 2;
		else return 0;
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

	pantallaCarregar = 0;
	bool res = false;
	res = Data.LoadImage(IMG_INICI_JOC, "Botons/iniciar_partida.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_INSTRUCCIONS, "Botons/instruccions.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_CREDITS, "Botons/credits.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_NIVELL1, "Botons/nivell1.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_NIVELL2, "Botons/nivell2.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_NIVELL2N, "Botons/nivell2Not.png", GL_RGBA);
	if (!res) return false;
	//res = Data.LoadImage(IMG_CREDITS_IMG, "Botons/creditsIMG.png", GL_RGBA);
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
	//glClear(GL_COLOR_BUFFER_BIT);
	if (pantallaCarregar == 0)
	{
		CarregaBoto(1);
		CarregaBoto(2);
		CarregaBoto(3);
		iniciarPartida = false;
	}
	else if (pantallaCarregar == 1)
	{
		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CarregaBoto(4);
		if (nivell2Blocked)
		{
			CarregaBoto(6);
		}
		else
		{
			CarregaBoto(5);
		}
	}
	else if (pantallaCarregar == 2)
	{
	}
	else if (pantallaCarregar == 3)
	{

	}
}

void menu::CarregaBoto(int caseImage)
{
		float xo, yo, xf, yf;
		int screen_x, screen_y, h, w;
		xf = 0.0f; xo = xf + 1.0f;
		yo = 0.0f; yf = 1.0f;
		/*Posicio Pantalla*/
		int ID = 0;
		if (caseImage == 1)
		{
			ID = Data.GetID(IMG_INICI_JOC);
			screen_x = GAME_WIDTH / 2 - WIDTH_BUTTON/2;
			screen_y = (GAME_HEIGHT / 4) * 3 - HEIGHT_BUTTON/2;
		}
		else if (caseImage == 2)
		{
			ID = Data.GetID(IMG_INSTRUCCIONS);
			screen_x = GAME_WIDTH / 2 - WIDTH_BUTTON/2;
			screen_y = GAME_HEIGHT / 2 - HEIGHT_BUTTON/2;
		}
		else if (caseImage == 3)
		{
			ID = Data.GetID(IMG_CREDITS);
			screen_x = GAME_WIDTH / 2 - WIDTH_BUTTON/2;
			screen_y = GAME_HEIGHT / 4 - HEIGHT_BUTTON/2;
		}
		else if (caseImage == 4)
		{
			ID = Data.GetID(IMG_NIVELL1);
			screen_x = GAME_WIDTH / 2 - WIDTH_BUTTON / 2;
			screen_y = (GAME_HEIGHT / 3) * 2 - HEIGHT_BUTTON / 2;
		}
		else if (caseImage == 5)
		{
			ID = Data.GetID(IMG_NIVELL2);
			screen_x = GAME_WIDTH / 2 - WIDTH_BUTTON / 2;
			screen_y = (GAME_HEIGHT / 3) - HEIGHT_BUTTON / 2;
		}
		else if (caseImage == 6)
		{
			ID = Data.GetID(IMG_NIVELL2N);
			screen_x = GAME_WIDTH / 2 - WIDTH_BUTTON / 2;
			screen_y = (GAME_HEIGHT / 3) - HEIGHT_BUTTON / 2;
		}
		else
		{
			return;
		}
		/*Amplada, Alçacada repectivament*/
		w = WIDTH_BUTTON; h = HEIGHT_BUTTON;
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

void menu::bloquejaNivell2()
{
	nivell2Blocked = true;
}

void menu::desbloquejaNivell2()
{
	nivell2Blocked = false;
}

void menu::CarregaLletra()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST); // also disable the depth test so renders on top
	glRasterPos2f(10, 10);
	glColor3f(0.0, 1.0, 0.0); // Green
	char* s = "Respect mah authoritah!";//23
	for (char* i = s; i != s + 23; ++i)
	{
		char c = *i;
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
	}
	
	glEnable(GL_DEPTH_TEST); // Turn depth testing back on
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}
