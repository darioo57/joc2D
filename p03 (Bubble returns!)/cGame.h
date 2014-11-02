#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "enemyS.h"
#include "menu.h"
#include "yeti.h"
#include "secondPlayer.h"

#define GAME_WIDTH	50*16
#define GAME_HEIGHT 25*16
#define START_PLAYERX 4
#define START_PLAYERY 10
#define FINISH_PLAYERX (GAME_WIDTH/16)-6
#define START_PLAYER2X 6
#define START_PLAYER2Y 10
#define FINISH_PLAYER2X (GAME_WIDTH/16)-6

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init(int level, bool multiplayer);
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

	void resetAttributes();

private:
	unsigned char keys[256];
	cScene Scene;
	cPlayer Player;
	cData Data;
	enemyS Enemy;
	enemyS Enemy2;
	enemyMine Enemy_M;
	yeti Yeti;
	secondPlayer Player2;
	int maximumRightTranslation;
	int yetiDecision;
	bool tocado;
	bool multiplayer;
	int level;
};
