#include "secondPlayer.h"
#include "cScene.h"
#include "Globals.h"

int paaaa = -1, pbbbb = -1;
bool pbLL = false, pbRR = false;
char sentitt = 'X';
bool disparaa = false;

secondPlayer::secondPlayer(void)
{
	seq = 0;
	delay = 0;
	vxLauxX = vector<int>(1000, 0);
	vxL = vector<int>(1000, 0);
	vxR = vector<int>(1000, 0);
	vpos = vector<int>(2000, 0);
	auxscreen_y = vector<int>(1000, 0);
	auxscreen_y2 = vector<int>(1000, 0);
	jumping = false;
}
secondPlayer::~secondPlayer(void){}

secondPlayer::secondPlayer(int posx, int posy, int width, int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}

void secondPlayer::Draw(int tex_id, int tex_id_bala, int act, bool shoot)
{
	float xo = 0.0f, yo = 0.0f, xf = 0.052632f, yf = 1.0f;
	sentitt = 'X';
	if (act == 1)	//act = 1 -> animacio mort
	{
		if (GetFrame() == 18) {
			xo = 0.947368f;
			xf = 1.0f;
			yo = 0.0f;
			yf = 1.0f;
		}
		else {
			switch (GetState())
			{
				//19 sprites 1/19= 0.05263157894736842105263157894737
			case STATE_LOOKLEFT:
				sentitt = 'L';
				break;

			case STATE_LOOKRIGHT:
				sentitt = 'R';
				break;

			}
			xo = 0.052632f + (GetFrame()*0.052632f);
			yo = 0.0f;
			NextFrame(19);

			xf = xo + 0.052632f;
			yf = 1.0f;
		}

	}
	else if (shoot) //shoot -> animacio disparaa
	{
		switch (GetState())
		{

		case STATE_LOOKLEFT:
			sentitt = 'L';
			break;

		case STATE_LOOKRIGHT:
			sentitt = 'R';
			break;

		case STATE_WALKLEFT:
			sentitt = 'L';
			break;

		case STATE_WALKRIGHT:
			sentitt = 'R';
			break;
		}
		if (GetFrame() == 0 && !disparaa) {
			disparaa = true;
		}
		else if (GetFrame() != 0) {
			disparaa = false;
		}

		xo = 0.25f + (GetFrame()*0.25f);	yo = 0.0f;
		NextFrame(4);
		xf = xo + 0.25f;
		yf = 1.0f;
	}
	else //act = 0 -> animacio moviment
	{
		switch (GetState())
		{

		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.0f;
			sentitt = 'L';
			break;

		case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 0.0f;
			break;

		case STATE_WALKLEFT:	xo = 0.111f + (GetFrame()*0.111f);	yo = 0.0f;
			sentitt = 'L';
			NextFrame(9);
			break;

		case STATE_WALKRIGHT:	xo = 0.111f + (GetFrame()*0.111f);	yo = 0.0f;
			sentitt = 'R';
			NextFrame(9);
			break;
		}
		xf = xo + 0.111f;
		yf = 1.0f;
	}

	DrawRect(tex_id, xo, yo, xf, yf, sentitt);

	for (int i = 0; i < 1000; ++i) {
		if (i <= paaaa) {
			DrawRectBullet('L', tex_id_bala, i);
		}
		if (i <= pbbbb) {
			DrawRectBullet('R', tex_id_bala, i);
		}
	}

	if (sentitt == 'L') {
		if (paaaa < 999) {
			if (shoot) {
				pbLL = true;
				shoot = false;
			}
			if (pbLL) {
				if (disparaa) paaaa = paaaa + 1;
				pbLL = false;
			}
		}
		else paaaa = 0;
	}

	if (sentitt == 'R') {
		if (pbbbb < 999) {
			if (shoot) {
				pbRR = true;
				shoot = false;
			}
			if (pbRR) {
				if (disparaa) pbbbb = pbbbb + 1;
				pbRR = false;
			}
		}
		else pbbbb = 0;
	}
}

void secondPlayer::SetPosition(int posx, int posy)
{
	x = posx;
	y = posy;
}
void secondPlayer::GetPosition(int *posx, int *posy)
{
	*posx = x;
	*posy = y;
}
void secondPlayer::SetTile(int tx, int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void secondPlayer::GetTile(int *tx, int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void secondPlayer::SetWidthHeight(int width, int height)
{
	w = width;
	h = height;
}
void secondPlayer::GetWidthHeight(int *width, int *height)
{
	*width = w;
	*height = h;
}
void secondPlayer::SetNumLifes(int lifes)
{
	this->lifes = lifes;
}
int secondPlayer::GetNumLifes()
{
	return this->lifes;
}
bool secondPlayer::Collides(cRectab *rc)
{
	return ((x>rc->left) && (x + w<rc->right) && (y>rc->bottom) && (y + h<rc->top));
}
bool secondPlayer::CollidesMapWall(int *map, bool right)
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

bool secondPlayer::CollidesMapFloor(int *map)
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

void secondPlayer::GetArea(cRectab *rc)
{
	rc->left = x;
	rc->right = x + w;
	rc->bottom = y;
	rc->top = y + h;
}
vector<int> secondPlayer::GetBulletPosX()
{
	return vpos;
}

void secondPlayer::GetBulletPosY(vector<int> *auxVY)
{
	*auxVY = auxscreen_y;
}

void secondPlayer::DrawRect(int tex_id, float xo, float yo, float xf, float yf, char sentitt)
{
	int screen_x, screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	if (sentitt == 'L') {
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

void secondPlayer::DrawRectBullet(char sentitt, int tex_id_bala, int numb)
{
	int screen_x, screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id_bala);
	glBegin(GL_QUADS);

	if (sentitt == 'R') vxR[numb] += 4;
	if (sentitt == 'L') vxL[numb] += 4;

	if (vxR[numb] > 0) {
		if (vxR[numb] > 4) {
			vpos[numb] = vxR[numb];
			glTexCoord2f(0, 1);		glVertex2i(vxR[numb] + 10, auxscreen_y[numb] + 20);
			glTexCoord2f(1, 1);		glVertex2i(vxR[numb], auxscreen_y[numb] + 20);
			glTexCoord2f(1, 0);		glVertex2i(vxR[numb], auxscreen_y[numb] + 6 + 20);
			glTexCoord2f(0, 0);		glVertex2i(vxR[numb] + 10, auxscreen_y[numb] + 6 + 20);
		}
		else {
			vpos[numb] = vxR[numb] + screen_x;
			vxR[numb] += screen_x;
			auxscreen_y[numb] = screen_y;
		}
	}
	if (vxL[numb] > 0) {
		if (vxL[numb] > 4) {
			vpos[numb] = vxLauxX[numb] + vxL[numb] * (-1);
			glTexCoord2f(0, 1);		glVertex2i(vxLauxX[numb] + vxL[numb] * (-1) + 10, auxscreen_y2[numb] + 20);
			glTexCoord2f(1, 1);		glVertex2i(vxLauxX[numb] + vxL[numb] * (-1), auxscreen_y2[numb] + 20);
			glTexCoord2f(1, 0);		glVertex2i(vxLauxX[numb] + vxL[numb] * (-1), auxscreen_y2[numb] + 6 + 20);
			glTexCoord2f(0, 0);		glVertex2i(vxLauxX[numb] + vxL[numb] * (-1) + 10, auxscreen_y2[numb] + 6 + 20);
		}
		else {
			vxLauxX[numb] = screen_x;
			auxscreen_y2[numb] = screen_y;
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void secondPlayer::MoveLeft(int *map)
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

void secondPlayer::MoveRight(int *map)
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

void secondPlayer::Stop()
{
	switch (state)
	{
	case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
	case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
	}
}
void secondPlayer::Jump(int *map)
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
void secondPlayer::Logic(int *map)
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

bool secondPlayer::LogicBullets(vector<int> vp, int ymax, int ymin)
{
	for (int j = 0; j < vp.size(); ++j) {
		if (x > 0 && (x - 20 <= vp[j] && x + w - 20 >= vp[j])) { //tocat en eix X, x a un costat mes l'amplada del personatge, restem 20 (a ull) per fer impacte amb dibuix
			if (y > 0 && (y + h >= ymax - 15 && y <= ymin - 15)) return true; //tocat en eix y, y a la base mes alcada personatge
		}
	}
	return false;
}

void secondPlayer::NextFrame(int max)
{
	delay++;
	if (delay == FRAME_DELAY)
	{
		seq++;
		seq %= max;
		delay = 0;
	}
}
int secondPlayer::GetFrame()
{
	return seq;
}
int secondPlayer::GetState()
{
	return state;
}
void secondPlayer::SetState(int s)
{
	state = s;
}