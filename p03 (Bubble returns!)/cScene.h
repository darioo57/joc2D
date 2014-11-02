#pragma once

#include "cData.h"
#include "cTexture.h"

#define SCENE_Xo		TILE_SIZE
#define SCENE_Yo		TILE_SIZE
#define SCENE_WIDTH		247
#define SCENE_HEIGHT	25

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16
#define BLOCK_SIZE		16

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	void setPosition(int x, int y);
	void drawBackground(int tex_id);
	bool LoadLevel(int level);
	void Draw(int tex_id, int neng_id);
	int *GetMap();

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
	int actualX;
	int actualY;
	cData Data;
};
