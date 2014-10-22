#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "enemyS.h"

#define GAME_WIDTH	1266//640
#define GAME_HEIGHT 668//480

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	cScene Scene;
	cPlayer Player;
	cData Data;
	enemyS Enemy;
	enemyS Enemy2;
};
