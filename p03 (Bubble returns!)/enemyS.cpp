#include "enemyS.h"

enemyS::enemyS() {}
enemyS::~enemyS(){}

void enemyS::Draw(int tex_id, int tex_id_bala)
{
	float xo = 0.0f, yo = 0.0f, xf = 0.0f, yf = 0.0f;
	char sentit = 'L';

	switch (GetState())
	{
		//1
		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.0f;
								sentit = 'L';
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 0.0f;
								sentit = 'R';
								break;
		//1..3
		//11 sprites en dues files 1/11=0.0909
		case STATE_WALKLEFT:	xo = 0.093f + (GetFrame()*0.0909f);
								if (xo > 0.92f) yo = 0.5f;
								sentit = 'L';
								NextFrame(22);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.093f + (GetFrame()*0.0909f);
								if (xo > 0.92f) yo = 0.5f;
								sentit = 'R';
								NextFrame(22);
								break;
	}
	xf = xo + 0.0909f;
	yf = yo + 0.5f;

	if (sentit == 'L') DrawRect(tex_id, xo, yo, xf, yf, sentit, tex_id_bala);
	else DrawRect(tex_id, xo, yo, xf, yf, sentit, tex_id_bala);
}
