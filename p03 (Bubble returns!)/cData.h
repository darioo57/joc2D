#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		26

//Image identifiers
#define IMG_BLOCKS	0
#define IMG_PLAYER	1
#define IMG_ENEMY   2
#define IMG_BALA_PISTOLA 3
#define IMG_BALA_BOLA 4
#define IMG_INICI_JOC 5
#define IMG_PLAYER_DEAD 6
#define IMG_INSTRUCCIONS 7
#define IMG_CREDITS 8
#define IMG_NIVELL1 9
#define IMG_NIVELL2 10
#define IMG_MULTIPLAYER 11
#define IMG_CREDITS_IMG 12
#define IMG_FONS 13
#define IMG_YETIWALK 14
#define IMG_ENEMY_DEAD 15
#define IMG_YETIDEAD 16
#define IMG_YETIATTACK 17
#define IMG_PLAYER_SHOOT 19
#define IMG_PLAYER_RESUCITAP1 20
#define IMG_ENEMY_MINE 21
#define IMG_MINE 22
#define IMG_BURN 23
#define IMG_RUN 24
#define IMG_TOWER_TANK 25
/*
#define IMG_ENEMY1	2
#define IMG_ENEMY2	3
#define IMG_SHOOT	4
...
*/

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
