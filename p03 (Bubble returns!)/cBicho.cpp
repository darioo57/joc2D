#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void)
{
	seq = 0;
	delay = 0;
	vxLauxX = vector<int>(1000, 0);
	vxL = vector<int>(1000, 0);
	vxR = vector<int>(1000, 0);
	vpos1 = vector<int>(1000, 0);
	vpos2 = vector<int>(1000, 0);
	auxscreen_y = vector<int>(1000, 0);
	auxscreen_y2 = vector<int>(1000, 0);
	jumping = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}
bool cBicho::Collides(cRect *rc)
{
	return ((x>rc->left) && (x+w<rc->right) && (y>rc->bottom) && (y+h<rc->top));
}
bool cBicho::CollidesMapWall(int *map,bool right)
{
	int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if(right)	tile_x += width_tiles;
	
	for(j=0;j<height_tiles;j++)
	{
		if(map[ tile_x + ((tile_y+j)*SCENE_WIDTH) ] != 0)	return true;
	}
	
	return false;
}

bool cBicho::CollidesMapFloor(int *map)
{
	int tile_x,tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if( (x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i=0;
	while((i<width_tiles) && !on_base)
	{
		if( (y % TILE_SIZE) == 0 )
		{
			if(map[ (tile_x + i) + ((tile_y - 1) * SCENE_WIDTH) ] != 0)
				on_base = true;
		}
		else
		{
			if(map[ (tile_x + i) + (tile_y * SCENE_WIDTH) ] != 0)
			{
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}

void cBicho::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;
}
void cBicho::GetBulletPosX(vector<int> *auxX1, vector<int> *auxX2)
{
	*auxX1 = vpos1;
	*auxX2 = vpos2;
}

void cBicho::GetBulletPosY(vector<int> *auxVY1, vector<int> *auxVY2)
{
	*auxVY1 = auxscreen_y;
	*auxVY2 = auxscreen_y2;
}

void cBicho::DrawRect(int tex_id, float xo, float yo, float xf, float yf, char sentit, bool dispara)
{
	int screen_x,screen_y;
	int waux = w, haux = h;
	if (dispara) {
		waux = 40;
		haux = 36;
	}
	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		if (sentit == 'L') {
			glTexCoord2f(xo, yf);		glVertex2i(screen_x + waux, screen_y);
			glTexCoord2f(xf, yf);		glVertex2i(screen_x, screen_y);
			glTexCoord2f(xf, yo);		glVertex2i(screen_x, screen_y + haux);
			glTexCoord2f(xo, yo);		glVertex2i(screen_x + waux, screen_y + haux);
		}
		else {	//'R'
			glTexCoord2f(xo, yf);		glVertex2i(screen_x, screen_y);
			glTexCoord2f(xf, yf);		glVertex2i(screen_x + waux, screen_y);
			glTexCoord2f(xf, yo);		glVertex2i(screen_x + waux, screen_y + haux);
			glTexCoord2f(xo, yo);		glVertex2i(screen_x, screen_y + haux);
		}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cBicho::DrawRectBullet(char sentit, int tex_id_bala, int numb)
{
	int screen_x, screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, tex_id_bala);
		glBegin(GL_QUADS);

		if (sentit == 'R') vxR[numb] += 4;
		if (sentit == 'L') vxL[numb] += 4;

		if (vxR[numb] > 0) {
			if (vxR[numb] > 4) {
				vpos1[numb] = vxR[numb];
				glTexCoord2f(0, 1);		glVertex2i(vxR[numb] + 10, auxscreen_y[numb]);
				glTexCoord2f(1, 1);		glVertex2i(vxR[numb], auxscreen_y[numb]);
				glTexCoord2f(1, 0);		glVertex2i(vxR[numb], auxscreen_y[numb] + 6);
				glTexCoord2f(0, 0);		glVertex2i(vxR[numb] + 10, auxscreen_y[numb] + 6);
			}
			else {
				vpos1[numb] = vxR[numb] + screen_x;
				vxR[numb] += screen_x;
				auxscreen_y[numb] = screen_y + 20;
			}
		}
		if (vxL[numb] > 0) {
			if (vxL[numb] > 4) {
				vpos2[numb] = vxLauxX[numb] + vxL[numb] * (-1);
				glTexCoord2f(0, 1);		glVertex2i(vxLauxX[numb] + vxL[numb] * (-1) + 10, auxscreen_y2[numb]);
				glTexCoord2f(1, 1);		glVertex2i(vxLauxX[numb] + vxL[numb] * (-1), auxscreen_y2[numb]);
				glTexCoord2f(1, 0);		glVertex2i(vxLauxX[numb] + vxL[numb] * (-1), auxscreen_y2[numb] + 6);
				glTexCoord2f(0, 0);		glVertex2i(vxLauxX[numb] + vxL[numb] * (-1) + 10, auxscreen_y2[numb] + 6);
			}
			else {
				vxLauxX[numb] = screen_x;
				vpos2[numb] = vxLauxX[numb] + vxL[numb] * (-1);
				auxscreen_y2[numb] = screen_y + 20;
			}
		}
		glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cBicho::MoveLeft(int *map)
{
	int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if(CollidesMapWall(map,false))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		if(state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}

void cBicho::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMapWall(map,true))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if(state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}

void cBicho::Stop()
{
	switch(state)
	{
		case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
		case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
	}
}
void cBicho::Jump(int *map)
{
	if(!jumping)
	{
		if(CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
		}
	}
}
void cBicho::Logic(int *map)
{
	float alfa;

	if(jumping)
	{
		jump_alfa += JUMP_STEP;
		
		if(jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else
	{
		//Over floor?
		if(!CollidesMapFloor(map))
			y -= (2*STEP_LENGTH);
	}
}

bool cBicho::LogicBullets(vector<int> vp, int ymax, int ymin)
{
	for (int j = 0; j < vp.size(); ++j) {
		if (x > 0 && (x-20 <= vp[j] && x+w-20 >= vp[j])) { //tocat en eix X, x a un costat mes l'amplada del personatge, restem 20 (a ull) per fer impacte amb dibuix
			if (y > 0 && (y+h >= ymax-15 && y <= ymin-15)) return true; //tocat en eix y, y a la base mes alcada personatge
		}
	}
	return false;
}

void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::ResetFrame()
{
	seq = 0;
	delay = 0;
}
void cBicho::SetState(int s)
{
	state = s;
}