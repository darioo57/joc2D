#pragma once

#include "cData.h"

#define HEIGHT_BUTTON 40
#define WIDTH_BUTTON 180

class menu
{
public:

	menu();
	~menu();

	int ReadMouse(int button, int state, int x, int y);
	bool init();

	bool Loop();
	bool Process();
	void Render();

	int dinsBoto(int clickX, int clickY);
	void CarregaBoto(int caseImage);
	void desbloquejaNivell2();
	void bloquejaNivell2();
	void CarregaLletra();

private:
	cData Data;
	int pantallaCarregar;
	bool nivell2Blocked;
	bool iniciarPartida;
};

