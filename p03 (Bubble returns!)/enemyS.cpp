#include "enemyS.h"

int aaa = -1, bbb = -1;
bool bL = false, bR = false;

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

	if (sentit == 'L') {
		DrawRect(tex_id, xo, yo, xf, yf, sentit);
		for (int i = 0; i < 100; ++i) {
			if (i <= aaa) {
				DrawRectBullet(sentit, tex_id_bala, i);
			}
		}
		if (aaa < 99) {
			if (GetFrame() == 1) bL = true;
			if (bL && GetFrame() != 1) {
				aaa = aaa + 1;
				bL = false;
			}
		}
		else aaa = 0;
	}
	else {
		DrawRect(tex_id, xo, yo, xf, yf, sentit);	
		for (int i = 0; i < 100; ++i) {
			if (i <= bbb) {
				DrawRectBullet(sentit, tex_id_bala, i);
			}
		}
		if (bbb < 99) {
			if (GetFrame() == 1) bR = true;
			if (bR && GetFrame() != 1) {
				bbb = bbb + 1;
				bR = false;
			}
		}
		else bbb = 0;
	}
}
