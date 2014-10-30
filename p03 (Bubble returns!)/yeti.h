#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cData.h"
#include <vector>
#include <iostream>
using namespace std;

#define FRAME_DELAY		8
#define STEP_LENGTH		1
#define JUMP_HEIGHT		9*16
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_ATTACK		4
#define STATE_DEAD			5
#define START_YETIX 80
#define START_YETIY 10

class cRecta
{
public:
	int left, top,
		right, bottom;
};

class yeti
{
public:
	yeti(void);
	yeti(int x, int y, int w, int h);
	~yeti();

	void Draw(cData Data, int pos_vector);
	void SetPosition(int x, int y);
	void GetPosition(int *x, int *y);
	void SetTile(int tx, int ty);
	void GetTile(int *tx, int *ty);
	void SetWidthHeight(int w, int h);
	void GetWidthHeight(int *w, int *h);

	bool Collides(cRecta *rc);
	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map);
	void GetArea(cRecta *rc);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, char sentit);

	void MoveRight(int *map);
	void MoveLeft(int *map);
	void attackRight(int *map);
	void attackLeft(int *map);
	void JumpRight(int *map);
	void JumpLeft(int *map);
	void Jump(int *map);
	void Stop();
	void Logic(int *map);
	int decision(int *map, int x, int y);
	bool LogicBullets(vector<int> vp);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

private:
	int x, y;
	int w, h;
	int state;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq, delay;
	int life;
};