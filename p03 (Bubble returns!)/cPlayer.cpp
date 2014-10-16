#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	char sentit = 'L';

	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.0f; //yo = 0.25f;
								sentit = 'L';
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.0f;	yo = 0.0f; //yo = 0.25f;
								sentit = 'R';
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 0.111f + (GetFrame()*0.111f);	yo = 0.0f;	//yo = 0.25f + (GetFrame()*0.25f);
								sentit = 'L';
								NextFrame(9);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.111f + (GetFrame()*0.111f);	yo = 0.0f; //yo = 0.25f + (GetFrame()*0.25f);
								sentit = 'R';
								NextFrame(9);
								break;
	}
	xf = xo + 0.111f;
	yf = 1.0f;
	//yf = yo - 0.25f;

	if (sentit == 'L') DrawRect(tex_id,xo,yo,xf,yf,sentit);
	else DrawRect(tex_id, xo, yo, xf, yf,sentit);
}
