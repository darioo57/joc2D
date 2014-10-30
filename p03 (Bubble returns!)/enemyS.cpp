#include "enemyS.h"

int aaa = -1, bbb = -1;
bool bL = false, bR = false;

enemyS::enemyS() {}
enemyS::~enemyS(){}

void enemyS::Draw(int tex_id, int tex_id_bala, int estat)
{
	float xo = 0.0f, yo = 0.0f, xf = 0.0f, yf = 0.0f;
	char psentit = 'X';

	if (estat == 0) {
		switch (GetState())
		{
			//1
		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.0f;
			psentit = 'L';
			break;
			//4
		case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 0.0f;
			psentit = 'R';
			break;
			//1..3
			//11 sprites en dues files 1/11=0.0909
		case STATE_WALKLEFT:	xo = 0.093f + (GetFrame()*0.0909f);
			if (xo > 0.92f) yo = 0.5f;
			psentit = 'L';
			NextFrame(22);
			break;
			//4..6
		case STATE_WALKRIGHT:	xo = 0.093f + (GetFrame()*0.0909f);
			if (xo > 0.92f) yo = 0.5f;
			psentit = 'R';
			NextFrame(22);
			break;
		}
		xf = xo + 0.0909f;
		yf = yo + 0.5f;

		if (psentit == 'L') {
			DrawRect(tex_id, xo, yo, xf, yf, psentit, false);
			for (int i = 0; i < 100; ++i) {
				if (i <= aaa) {
					DrawRectBullet(psentit, tex_id_bala, i);
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
			DrawRect(tex_id, xo, yo, xf, yf, psentit, false);
			for (int i = 0; i < 100; ++i) {
				if (i <= bbb) {
					DrawRectBullet(psentit, tex_id_bala, i);
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

	else if (estat == 1) {	//mort
		if (GetFrame() == 5) {
			xo = 0.833333f;
			xf = 1.0f;
			yo = 0.0f;
			yf = 1.0f;
			switch (GetState())
			{
			case STATE_LOOKLEFT:
				psentit = 'L';
				break;
			case STATE_LOOKRIGHT:
				psentit = 'R';
				break;
			case STATE_WALKLEFT:
				psentit = 'L';
				break;
			case STATE_WALKRIGHT:
				psentit = 'R';
				break;
			}
		}
		else {
			switch (GetState())
			{
			case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.0f;
				psentit = 'L';
				break;
			case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 0.0f;
				psentit = 'R';
				break;
				//1/6=0.16667
			case STATE_WALKLEFT:	xo = 0.16667f + (GetFrame()*0.16667f);
				psentit = 'L';
				break;
			case STATE_WALKRIGHT:	xo = 0.16667f + (GetFrame()*0.16667f);
				psentit = 'R';
				break;
			}
			NextFrame(6);
			xf = xo + 0.16667f;
			yf = 1.0f;
		}
		DrawRect(tex_id, xo, yo, xf, yf, psentit, true);
	}
}
