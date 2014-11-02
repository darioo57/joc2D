#pragma once

#include "cData.h"

#define HEIGHT_INICIAL	400
#define WIDTH_INICIAL	800

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
	void CarregaPantalla();

private:
	cData Data;
};

