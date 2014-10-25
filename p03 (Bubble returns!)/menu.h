#pragma once

#include "cData.h"
class menu
{
public:
	menu();
	~menu();

	bool init();

	bool Loop();
	bool Process();
	void Render();

private:
	cData Data;

};

