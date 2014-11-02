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

class cRectab
{
public:
	int left, top,
		right, bottom;
};

class secondPlayer
{
public:
	secondPlayer(void);
	secondPlayer(int x, int y, int w, int h);
	~secondPlayer(void);

	void Draw(int tex_id, int tex_id_bala, int act, bool shoot);
	void SetPosition(int x, int y);
	void GetPosition(int *x, int *y);
	void SetTile(int tx, int ty);
	void GetTile(int *tx, int *ty);
	void SetWidthHeight(int w, int h);
	void GetWidthHeight(int *w, int *h);
	void SetNumLifes(int lifes);
	int GetNumLifes();

	bool Collides(cRectab *rc);
	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map);
	void GetArea(cRectab *rc);
	vector<int> GetBulletPosX();
	void GetBulletPosY(vector<int> *auxVY);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, char sentit);
	void DrawRectBullet(char sentit, int tex_id_bala, int numb);

	void MoveRight(int *map);
	void MoveLeft(int *map);
	void MoveLeftExtrem(int *map);
	void Jump(int *map);
	void Stop();
	void Logic(int *map);
	bool LogicBullets(vector<int> vp, int ymax, int ymin);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

private:

	int lifes;
	int x, y;
	int w, h;
	int state;
	int bx, by;
	vector<int> vxL;
	vector<int> vxR;
	vector<int> vpos;
	vector<int> vxLauxX;
	vector<int> auxscreen_y;
	vector<int> auxscreen_y2;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq, delay;
};
