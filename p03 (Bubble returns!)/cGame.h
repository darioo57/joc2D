#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "enemyS.h"
#include "menu.h"

#define GAME_WIDTH	80*16
#define GAME_HEIGHT 40*16
#define START_PLAYERX 4
#define START_PLAYERY 10
#define FINISH_PLAYERX (GAME_WIDTH/16)-6

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
	int maximumRightTranslation;
};
