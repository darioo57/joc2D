#include "cScene.h"
#include "Globals.h"
#include "cGame.h"

cScene::cScene(void)
{
	actualX = 1;
	actualY = 1;
}

cScene::~cScene(void)
{
}

void cScene::setPosition(int x, int y)
{
	actualX = x;
	actualY = y;
}

void cScene::drawBackground(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	float repatTimes = 1;
	float x = -1.0f;
	float y = -1.0f;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, x); glVertex3f(0.0f, GAME_HEIGHT + 16, 0.0f);
	glTexCoord2f(y*repatTimes, x); glVertex3f(SCENE_WIDTH*TILE_SIZE + 16 * 2, GAME_HEIGHT + 16, 0.0f);
	glTexCoord2f(y*repatTimes, 0.0f); glVertex3f(SCENE_WIDTH*TILE_SIZE + 16 * 2, 0.0f, 0.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[16];
	int i,j,px,py;
	char tile;
	float coordx_tile, coordy_tile;

	res=true;

	if(level<10) sprintf(file,"%s0%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);
	else		 sprintf(file,"%s%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);
		glBegin(GL_QUADS);
	
			for(j=SCENE_HEIGHT-1;j>=0;j--)
			{
				px = (actualX*TILE_SIZE);// SCENE_Xo;
				py = (actualY*TILE_SIZE) + (j*TILE_SIZE);// SCENE_Yo;
				

				for(i=0;i<SCENE_WIDTH;i++)
				{
					fscanf(fd,"%c",&tile);
					if(tile=='0')
					{
						//Tiles must be != 0 !!!
						map[(j*SCENE_WIDTH)+i]=0;
					}
					else
					{
						//Tiles = 1,2,3,...
						map[(j*SCENE_WIDTH)+i] = tile-48;

						if(map[(j*SCENE_WIDTH)+i]%2) coordx_tile = 0.0f;
						else						 coordx_tile = 0.5f;
						if(map[(j*SCENE_WIDTH)+i]<3) coordy_tile = 0.0f;
						else						 coordy_tile = 0.5f;

						//BLOCK_SIZE = 16, FILE_SIZE = 32
						// 16 / 32 = 0.5
						/*Aixo pinta el mapa*/
						glTexCoord2f(coordx_tile       ,coordy_tile+0.5f);	glVertex2i(px           ,py           );
						glTexCoord2f(coordx_tile+0.5f  ,coordy_tile+0.5f);	glVertex2i(px+BLOCK_SIZE,py           );
						glTexCoord2f(coordx_tile+0.5f  ,coordy_tile     );	glVertex2i(px+BLOCK_SIZE,py+BLOCK_SIZE);
						glTexCoord2f(coordx_tile       ,coordy_tile     );	glVertex2i(px           ,py+BLOCK_SIZE);
					}
					px+=TILE_SIZE;
				}
				fscanf(fd,"%c",&tile); //pass enter
			}

		glEnd();
	glEndList();

	fclose(fd);

	return res;
}

void cScene::Draw(int tex_id, int neng_id)
{
	drawBackground(neng_id);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}
int* cScene::GetMap()
{
	return map;
}