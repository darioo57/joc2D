#include <string>
#include "yeti.h"
#include "Globals.h"
#include "cScene.h"


yeti::yeti()
{
}

yeti::yeti(int posx, int posy, int width, int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;

}

yeti::~yeti()
{
}

void yeti::Draw(cData Data, int pos_vector)
{
	float xo, yo, xf, yf;
	char sentit = 'L';
	/*9 Sprites pertant 1/9*/
	float suma = 1.0f;
	int tex_id = Data.GetID(pos_vector);
	if (tex_id == 5)//walk
	{
		suma /= 14.0f;
	}
	else if (tex_id == 6)//dead
	{
		suma /= 10.0f;
	}
	else if (tex_id == 7)//attack1
	{
		suma /= 12.0f;
	}
	else if (tex_id == 8)//attack2
	{
		suma /= 4.0f;
	}
	switch (GetState())
	{

	case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.0f;
							sentit = 'L';
							break;

	case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 0.0f;
							sentit = 'R';
							break;

	case STATE_WALKLEFT:	xo = suma + (GetFrame()*suma);	yo = 0.0f;
							sentit = 'L';
							NextFrame(14);
							break;

	case STATE_WALKRIGHT:	xo = suma + (GetFrame()*suma);	yo = 0.0f;
							sentit = 'R';
							NextFrame(14);
							break;
	case STATE_ATTACK:		xo = suma + (GetFrame()*suma);	yo = 0.0f;
							sentit = 'R';
							NextFrame(12);
							break;
	case STATE_DEAD:		xo = suma + (GetFrame()*suma);	yo = 0.0f;
							sentit = 'R';
							NextFrame(10);
							break;
	}
	xf = xo + suma;
	yf = 1.0f;

	if (sentit == 'L') DrawRect(tex_id, xo, yo, xf, yf, sentit);
	else DrawRect(tex_id, xo, yo, xf, yf, sentit);
}

void yeti::SetPosition(int posx, int posy)
{
	x = posx;
	y = posy;
	life = 100;
}
void yeti::GetPosition(int *posx, int *posy)
{
	*posx = x;
	*posy = y;
}
void yeti::SetTile(int tx, int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void yeti::GetTile(int *tx, int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void yeti::SetWidthHeight(int width, int height)
{
	w = width;
	h = height;
}
void yeti::GetWidthHeight(int *width, int *height)
{
	*width = w;
	*height = h;
}

bool yeti::Collides(cRecta *rc)
{
	return ((x>rc->left) && (x + w<rc->right) && (y>rc->bottom) && (y + h<rc->top));
}
bool yeti::CollidesMapWall(int *map, bool right)
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

bool yeti::CollidesMapFloor(int *map)
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
void yeti::GetArea(cRecta *rc)
{
	rc->left = x;
	rc->right = x + w;
	rc->bottom = y;
	rc->top = y + h;
}
void yeti::DrawRect(int tex_id, float xo, float yo, float xf, float yf, char sentit)
{
	int screen_x, screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	if (sentit == 'L') {
		glTexCoord2f(xo, yf);		glVertex2i(screen_x + w, screen_y);
		glTexCoord2f(xf, yf);		glVertex2i(screen_x, screen_y);
		glTexCoord2f(xf, yo);		glVertex2i(screen_x, screen_y + h);
		glTexCoord2f(xo, yo);		glVertex2i(screen_x + w, screen_y + h);
	}
	else {	//'R'
		glTexCoord2f(xo, yf);		glVertex2i(screen_x, screen_y);
		glTexCoord2f(xf, yf);		glVertex2i(screen_x + w, screen_y);
		glTexCoord2f(xf, yo);		glVertex2i(screen_x + w, screen_y + h);
		glTexCoord2f(xo, yo);		glVertex2i(screen_x, screen_y + h);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void yeti::MoveRight(int *map)
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
void yeti::MoveLeft(int *map)
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

void yeti::attackRight(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) == 0)
	{
		if (CollidesMapWall(map, true))
		{
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		if (state != STATE_WALKRIGHT)
		{
			state = STATE_ATTACK;
			seq = 0;
			delay = 0;
		}
	}
}

void yeti::attackLeft(int *map)
{
	int xaux;

	//Whats next tile?
	if ((x % TILE_SIZE) == 0)
	{
		if (CollidesMapWall(map, true))
		{
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		if (state != STATE_WALKLEFT)
		{
			state = STATE_ATTACK;
			seq = 0;
			delay = 0;
		}
	}
}

void yeti::JumpRight(int *map)
{
	if (!jumping)
	{
		if (CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
			x += STEP_LENGTH;
		}
	}
}

void yeti::JumpLeft(int *map)
{
	if (!jumping)
	{
		if (CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
			x -= STEP_LENGTH;
		}
	}
}

void yeti::Jump(int *map)
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
void yeti::Stop()
{
	switch (state)
	{
	case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
	case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
	}

}
void yeti::Logic(int *map)
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

int yeti::decision(int *map, int x, int y)
{
	
	if (!CollidesMapWall(map, true))
	{
		if (x < this->x && x + 5 * 16 > this->x)
		{
			attackLeft(map);
			OutputDebugString("EsquerraAtaca");
			return 17;
		}
		else if (x > this->x && x - 5 * 16 < this->x)
		{
			attackRight(map);
			OutputDebugString("DretaAtaca");
			return 17;
		}
		else if (x < this->x && x + 15*16 > this->x)
		{
			MoveLeft(map);
			OutputDebugString("Esquerra");
			return 14;
		}
		else if (x > this->x && x - 15*16 < this->x)
		{
			MoveRight(map);
			OutputDebugString("Dreta");
			return 14;
		}
	}
	else
	{
		if (CollidesMapWall(map, false))
		{
			JumpLeft(map);
			OutputDebugString("EsquerraSalta");
			return 14;
		}
		else
		{
			JumpRight(map);
			OutputDebugString("DretaSalta");
			return 14;
		}
	}
	OutputDebugString("RAP");
	return 14;
}
bool yeti::LogicBullets(vector<int> vp)
{
	for (int j = 0; j < vp.size(); ++j) {
		if (x == vp[j]) return true; //tocat en eix X
	}
	return false;
}

int  yeti::GetState()
{
	return state;
}
void yeti::SetState(int s)
{
	state = s;
}

void yeti::NextFrame(int max)
{
	delay++;
	if (delay == FRAME_DELAY)
	{
		seq--;
		seq %= max;
		delay = 0;
	}

}
int  yeti::GetFrame()
{
	return seq;
}
