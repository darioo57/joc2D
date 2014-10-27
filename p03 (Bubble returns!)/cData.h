#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		13

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
#define IMG_NIVELL2N 11
#define IMG_CREDITS_IMG 12
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
