#pragma once

#include "rebelShotgun.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

class enemyS : public rebelShotgun
{
public:
	enemyS();
	~enemyS();

	void Draw(int tex_id, int tex_id_bala);
};

