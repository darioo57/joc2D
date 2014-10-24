#include "cGame.h"
#include "Globals.h"


cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"tileset0.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"Sprites/metalslug_P1.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(32,32);
	Player.SetTile(START_PLAYERX, START_PLAYERY);
	Player.SetWidthHeight(32,32);
	Player.SetState(STATE_LOOKRIGHT);

	//Easy rebel shotgun initialization
	res = Data.LoadImage(IMG_ENEMY, "Sprites/rebel_infantry_shotgun_R1.png", GL_RGBA);
	if (!res) return false;
	Enemy.SetWidthHeight(66, 40);
	Enemy.SetTile(10, 6);
	Enemy.SetWidthHeight(66, 40);
	Enemy.SetState(STATE_LOOKRIGHT);
	Enemy.SetBulletSize(4, 4);
	Enemy2.SetWidthHeight(66, 40);
	Enemy2.SetTile(18, 6);
	Enemy2.SetWidthHeight(66, 40);
	Enemy2.SetState(STATE_LOOKLEFT);
	Enemy2.SetBulletSize(4, 4);

	res = Data.LoadImage(IMG_BALA_BOLA, "Sprites/bala_bola.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_BALA_PISTOLA, "Sprites/bala_pistola.png", GL_RGBA);
	if (!res) return false;

	maximumRightTranslation = (SCENE_WIDTH-FINISH_PLAYERX+START_PLAYERX+4)*TILE_SIZE;

	return res;
}

bool cGame::Loop()
{
	bool res=true;
	res = Process();
	if (res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	//Process Input
	int x, y;
	Player.GetPosition(&x, &y);
	/*Deixem moure si estem dins del mapa*/
	if ((x/TILE_SIZE >= 0) && (x/TILE_SIZE < SCENE_WIDTH-1))
	{
		if (keys[27])	res = false;

		if (keys[GLUT_KEY_UP])			Player.Jump(Scene.GetMap());
		if (keys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetMap());
		else if (keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
		else Player.Stop();

		int x2, y2;
		Player.GetPosition(&x2, &y2);
		Enemy.ShotRight(x2, y2);
		Enemy2.ShotLeft(x2, y2);


		//Game Logic
		Player.Logic(Scene.GetMap());
		//Enemy.Logic(Scene.GetMap());
		//Enemy2.Logic(Scene.GetMap());
	}
	else
	{
		/*Identifiquem a quin limit estem*/
		if (x / TILE_SIZE < 0)
		{
			Player.MoveRight(Scene.GetMap());
		}
		else
		{
			Player.MoveLeft(Scene.GetMap());
		}
	}
	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	int x, y;
	Player.GetPosition(&x,&y);
	/*Mirem no sortir del mapa*/
	if ((x/TILE_SIZE - START_PLAYERX) >= 0 && (x/TILE_SIZE + FINISH_PLAYERX < SCENE_WIDTH))
	{
		glTranslatef(-x + START_PLAYERX*TILE_SIZE, 0.0f, 0.0f);
	}
	if (x / TILE_SIZE + FINISH_PLAYERX >= SCENE_WIDTH)
	{
		glTranslatef(-maximumRightTranslation, 0.0f, 0.0f);
	}
	Scene.Draw(Data.GetID(IMG_BLOCKS));
	Player.Draw(Data.GetID(IMG_PLAYER));
	Enemy.Draw(Data.GetID(IMG_ENEMY), Data.GetID(IMG_BALA_BOLA));
	Enemy2.Draw(Data.GetID(IMG_ENEMY), Data.GetID(IMG_BALA_BOLA));

	glutSwapBuffers();
}
