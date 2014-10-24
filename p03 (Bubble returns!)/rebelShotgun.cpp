#include "rebelShotgun.h"
#include "cScene.h"
#include "Globals.h"

rebelShotgun::rebelShotgun(void)
{
	seq = 0;
	delay = 0;

	jumping = false;
}
rebelShotgun::~rebelShotgun(void){}

rebelShotgun::rebelShotgun(int posx, int posy, int width, int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void rebelShotgun::SetPosition(int posx, int posy)
{
	x = posx;
	y = posy;
}
void rebelShotgun::GetPosition(int *posx, int *posy)
{
	*posx = x;
	*posy = y;
}
void rebelShotgun::SetTile(int tx, int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void rebelShotgun::GetTile(int *tx, int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void rebelShotgun::SetWidthHeight(int width, int height)
{
	w = width;
	h = height;
}
void rebelShotgun::GetWidthHeight(int *width, int *height)
{
	*width = w;
	*height = h;
}
bool rebelShotgun::Collides(cRectRebel *rc)
{
	return ((x>rc->left) && (x + w<rc->right) && (y>rc->bottom) && (y + h<rc->top));
}
bool rebelShotgun::CollidesMapWall(int *map, bool right)
{
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if (right)	tile_x += width_tiles;

	for (j = 0; j<height_tiles; j++)
	{
		if (map[tile_x + ((tile_y + j)*SCENE_WIDTH)] != 0)	return true;
	}

	return false;
}

bool rebelShotgun::CollidesMapFloor(int *map)
{
	int tile_x, tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if ((x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i = 0;
	while ((i<width_tiles) && !on_base)
	{
		if ((y % TILE_SIZE) == 0)
		{
			if (map[(tile_x + i) + ((tile_y - 1) * SCENE_WIDTH)] != 0)
				on_base = true;
		}
		else
		{
			if (map[(tile_x + i) + (tile_y * SCENE_WIDTH)] != 0)
			{
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}

void rebelShotgun::GetArea(cRectRebel *rc)
{
	rc->left = x;
	rc->right = x + w;
	rc->bottom = y;
	rc->top = y + h;
}

void rebelShotgun::SetBulletSize(int bposx, int bposy)
{
	bx = bposx;
	by = bposy;
}

void rebelShotgun::DrawRect(int tex_id, float xo, float yo, float xf, float yf, char sentit, int tex_id_bala)
{
	int screen_x, screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);
	vx = vx + 1;
	if (xo == 0.0f && yo == 0.0f) vx = 0;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	//eix X = 1/9
	//xo = yo = 0.0f; xf = 0.111f; yf = 1.0f;
	if (sentit == 'R') {
		glTexCoord2f(xo, yf);		glVertex2i(screen_x + w, screen_y);
		glTexCoord2f(xf, yf);		glVertex2i(screen_x, screen_y);
		glTexCoord2f(xf, yo);		glVertex2i(screen_x, screen_y + h);
		glTexCoord2f(xo, yo);		glVertex2i(screen_x + w, screen_y + h);
	}
	else {	//'L'
		glTexCoord2f(xo, yf);		glVertex2i(screen_x, screen_y);
		glTexCoord2f(xf, yf);		glVertex2i(screen_x + w, screen_y);
		glTexCoord2f(xf, yo);		glVertex2i(screen_x + w, screen_y + h);
		glTexCoord2f(xo, yo);		glVertex2i(screen_x, screen_y + h);
	}
	glEnd();

	if (vx != 0) {
		glBindTexture(GL_TEXTURE_2D, tex_id_bala);
		glBegin(GL_QUADS);
		if (sentit == 'R') {
			glTexCoord2f(0, 1);		glVertex2i(vx - 22 + screen_x + bx + w, screen_y + 23);
			glTexCoord2f(1, 1);		glVertex2i(vx - 22 + screen_x + w, screen_y + 23);
			glTexCoord2f(1, 0);		glVertex2i(vx - 22 + screen_x + w, screen_y + by + 23);
			glTexCoord2f(0, 0);		glVertex2i(vx - 22 + screen_x + bx + w, screen_y + by + 23);
		}
		else {	//'L'
			glTexCoord2f(0, 1);		glVertex2i(vx*(-1) + 20 + screen_x, screen_y + 23);
			glTexCoord2f(1, 1);		glVertex2i(vx*(-1) + 20 + screen_x + bx, screen_y + 23);
			glTexCoord2f(1, 0);		glVertex2i(vx*(-1) + 20 + screen_x + bx, screen_y + by + 23);
			glTexCoord2f(0, 0);		glVertex2i(vx*(-1) + 20 + screen_x, screen_y + by + 23);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

void rebelShotgun::MoveLeft(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if (CollidesMapWall(map, false))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		if (state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
void rebelShotgun::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if (CollidesMapWall(map, true))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if (state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}

void rebelShotgun::ShotRight(int x2, int y2)
{
	int x, y;
	GetPosition(&x, &y);
	if (x2 > x) {	//&& y2 <= y + 30) {	//y+30, base enemic + alcada arma
		if (state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
	else state = STATE_LOOKRIGHT;
}

void rebelShotgun::ShotLeft(int x2, int y2)
{
	int x, y;
	GetPosition(&x, &y);
	if (x2 < x) {	// && y2 <= y + 30) {	//y+30, base enemic + alcada arma
		if (state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
	else state = STATE_LOOKLEFT;
}
void rebelShotgun::Stop()
{
	switch (state)
	{
	case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
	case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
	}
}
void rebelShotgun::Jump(int *map)
{
	if (!jumping)
	{
		if (CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
		}
	}
}
void rebelShotgun::Logic(int *map)
{
	float alfa;

	if (jumping)
	{
		jump_alfa += JUMP_STEP;

		if (jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)(((float)JUMP_HEIGHT) * sin(alfa));

			if (jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else
	{
		//Over floor?
		if (!CollidesMapFloor(map))
			y -= (2 * STEP_LENGTH);
	}
}
void rebelShotgun::NextFrame(int max)
{
	delay++;
	if (delay == FRAME_DELAY)
	{
		seq++;
		seq %= max;
		delay = 0;
	}
}
int rebelShotgun::GetFrame()
{
	return seq;
}
int rebelShotgun::GetState()
{
	return state;
}
void rebelShotgun::SetState(int s)
{
	state = s;
}