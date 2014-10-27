#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	char sentit = 'L';
	
	if (tex_id == 6)
	{
		switch (GetState())
		{
		//19 sprites 1/19= 0.05263157894736842105263157894737
		case STATE_LOOKLEFT:	xo = 0.052632f + (GetFrame()*0.052632);	yo = 0.0f;
			sentit = 'L';
			NextFrame(19);
			break;

		case STATE_LOOKRIGHT:	xo = 0.052632 + (GetFrame()*0.052632);	yo = 0.0f;
			sentit = 'R';
			NextFrame(19);
			break;
		}
	}
	else
	{
		switch (GetState())
		{

		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.0f; //yo = 0.25f;
			sentit = 'L';
			break;

		case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 0.0f; //yo = 0.25f;
			sentit = 'R';
			break;

		case STATE_WALKLEFT:	xo = 0.111f + (GetFrame()*0.111f);	yo = 0.0f;	//yo = 0.25f + (GetFrame()*0.25f);
			sentit = 'L';
			NextFrame(9);
			break;

		case STATE_WALKRIGHT:	xo = 0.111f + (GetFrame()*0.111f);	yo = 0.0f; //yo = 0.25f + (GetFrame()*0.25f);
			sentit = 'R';
			NextFrame(9);
			break;
		}
		xf = xo + 0.111f;
		yf = 1.0f;
		//yf = yo - 0.25f;
	}

	if (sentit == 'L') DrawRect(tex_id,xo,yo,xf,yf,sentit);
	else DrawRect(tex_id, xo, yo, xf, yf,sentit);
}
