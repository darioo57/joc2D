#pragma once

#include "cTexture.h"
#include "Globals.h"
#include <vector>
#include <iostream>
using namespace std;

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3

class cRectRebel
{
public:
	int left, top,
		right, bottom;
};

class rebelShotgun
{
public:
	rebelShotgun(void);
	rebelShotgun(int x, int y, int w, int h);
	~rebelShotgun(void);

	void SetPosition(int x, int y);
	void GetPosition(int *x, int *y);
	void SetTile(int tx, int ty);
	void GetTile(int *tx, int *ty);
	void SetWidthHeight(int w, int h);
	void GetWidthHeight(int *w, int *h);

	bool Collides(cRectRebel *rc);
	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map);
	void GetArea(cRectRebel *rc);
	vector<int> GetBulletPos();
	void SetBulletSize(int bposx, int bposy);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, char sentit);
	void DrawRectBullet(char sentit, int tex_id_bala, int numb);

	void MoveRight(int *map);
	void MoveLeft(int *map);
	void ShotRight(int x2, int y2);
	void ShotLeft(int x2, int y2);
	void Jump(int *map);
	void Stop();
	void Logic(int *map);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

private:
	int x, y;
	int w, h;
	int state;
	int bx, by;
	vector<int> vx;
	vector<int> vpos;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq, delay;
};

