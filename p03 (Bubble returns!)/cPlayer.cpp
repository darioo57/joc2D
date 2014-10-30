#include "cPlayer.h"

int paaa = -1, pbbb = -1;
bool pbL = false, pbR = false;
char sentit = 'X';
bool dispara = false;

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id, int tex_id_bala, int act, bool shoot)
{	
	float xo = 0.0f, yo = 0.0f, xf = 0.052632f, yf = 1.0f;
	sentit = 'X';
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
				sentit = 'L';
				break;

			case STATE_LOOKRIGHT:
				sentit = 'R';
				break;

			}
			xo = 0.052632f + (GetFrame()*0.052632f);
			yo = 0.0f;
			NextFrame(19);

			xf = xo + 0.052632f;
			yf = 1.0f;
		}

	}
	else if (shoot) //shoot -> animacio dispara
	{
		switch (GetState())
		{

		case STATE_LOOKLEFT:
			sentit = 'L';
			break;

		case STATE_LOOKRIGHT:
			sentit = 'R';
			break;

		case STATE_WALKLEFT:
			sentit = 'L';
			break;

		case STATE_WALKRIGHT:
			sentit = 'R';
			break;
		}
		if (GetFrame() == 0 && !dispara) {
			dispara = true;
		}
		else if (GetFrame() != 0) {
			dispara = false;
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
			sentit = 'L';
			break;

		case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 0.0f;
			break;

		case STATE_WALKLEFT:	xo = 0.111f + (GetFrame()*0.111f);	yo = 0.0f;
			sentit = 'L';
			NextFrame(9);
			break;

		case STATE_WALKRIGHT:	xo = 0.111f + (GetFrame()*0.111f);	yo = 0.0f;
			sentit = 'R';
			NextFrame(9);
			break;
		}
		xf = xo + 0.111f;
		yf = 1.0f;
	}

	DrawRect(tex_id, xo, yo, xf, yf, sentit);

	for (int i = 0; i < 1000; ++i) {
		if (i <= paaa) {
			DrawRectBullet('L', tex_id_bala, i);
		}
		if (i <= pbbb) {
			DrawRectBullet('R', tex_id_bala, i);
		}
	}

	if (sentit == 'L') {
		if (paaa < 999) {
			if (shoot) {
				pbL = true;
				shoot = false;
			}
			if (pbL) {
				if (dispara) paaa = paaa + 1;
				pbL = false;
			}
		}
		else paaa = 0;
	}

	if (sentit == 'R') {
		if (pbbb < 999) {
			if (shoot) {
				pbR = true;
				shoot = false;
			}
			if (pbR) {
				if (dispara) pbbb = pbbb + 1;
				pbR = false;
			}
		}
		else pbbb = 0;
	}
}
