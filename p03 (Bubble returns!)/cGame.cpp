#include "cGame.h"
#include "Globals.h"

bool dead = false;
bool shoot = false;
bool l3 = false, l4 = false;

cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;
	yetiID = 14;

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
	Player.SetPosition(START_PLAYERX*TILE_SIZE, START_PLAYERY*TILE_SIZE);
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

	res = Data.LoadImage(IMG_FONS, "metal_slug_sub.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_YETIWALK, "Sprites/yetiWalk.png", GL_RGBA);//5
	if (!res) return false;
	res = Data.LoadImage(IMG_YETIDEAD, "Sprites/yetiDead.png", GL_RGBA);//6
	if (!res) return false;
	res = Data.LoadImage(IMG_YETIATTACK1, "Sprites/yetiAtaca1.png", GL_RGBA);//7
	if (!res) return false;
	res = Data.LoadImage(IMG_YETIATTACK2, "Sprites/yetiAtaca2.png", GL_RGBA);//8
	if (!res) return false;
	Yeti.SetWidthHeight(90, 70);
	Yeti.SetState(STATE_LOOKLEFT);
	Yeti.SetTile(80, 6);

	res = Data.LoadImage(IMG_BALA_BOLA, "Sprites/bala_bola.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_BALA_PISTOLA, "Sprites/bala_pistola.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PLAYER_DEAD, "Sprites/metalslug_dead.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_ENEMY_DEAD, "Sprites/rebel_dead.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_PLAYER_SHOOT, "Sprites/metalslug_shoot.png", GL_RGBA);
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
	shoot = false;
	//Process Input
	int x, y;
	Player.GetPosition(&x, &y);
	/*Deixem moure si estem dins del mapa*/
	if ((x / TILE_SIZE >= 0) && (x / TILE_SIZE < SCENE_WIDTH - 1))
	{
		if (keys[27])	res = false;

		if (!dead)
		{
			if (keys[108]) shoot = true; //lletra 'l'
			if (!shoot) {
				if (keys[GLUT_KEY_UP])			Player.Jump(Scene.GetMap());
				if (keys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetMap());
				else if (keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
				else Player.Stop();
			}
		}

		int x2, y2;
		Player.GetPosition(&x2, &y2);
		if (!l3) Enemy.ShotRight(x2, y2);
		if (!l4) Enemy2.ShotLeft(x2, y2);
		yetiID = Yeti.decision(Scene.GetMap(), x2, y2);


		//Game Logic
		Player.Logic(Scene.GetMap());

		int by_a, by_b, by2_a, by2_b;
		vector<int> auxVY;
		Enemy.GetBulletPosY(&by_a, &by_b);
		Enemy2.GetBulletPosY(&by2_a, &by2_b);
		Player.GetBulletPosY(&auxVY);
		if (!l3) {
			bool l1 = Player.LogicBullets(Enemy.GetBulletPosX(), by_a, by_b);
			if (l1) dead = true;
		}
		if (!l4) {
			bool l2 = Player.LogicBullets(Enemy2.GetBulletPosX(), by2_a, by2_b);
			if (l2) dead = true;
		}
		if (!l3) l3 = Enemy.LogicBullets(Player.GetBulletPosX(), auxVY);
		if (!l4) l4 = Enemy2.LogicBullets(Player.GetBulletPosX(), auxVY);

	}
	else
	{
		/*Identifiquem a quin limit estem*/
		if (!dead)
		{
			if (x / TILE_SIZE < 0)
			{
				Player.MoveRight(Scene.GetMap());
			}
			else
			{
				Player.MoveLeft(Scene.GetMap());
			}
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
	Player.GetPosition(&x, &y);
	/*Mirem no sortir del mapa*/
	if ((x / TILE_SIZE - START_PLAYERX) >= 0 && (x / TILE_SIZE + FINISH_PLAYERX < SCENE_WIDTH))
	{
		glTranslatef(-x + START_PLAYERX*TILE_SIZE, -16.0f, 0.0f);
	}
	if (x / TILE_SIZE + FINISH_PLAYERX >= SCENE_WIDTH)
	{
		glTranslatef(-maximumRightTranslation, -16.0f, 0.0f);
	}
	Scene.Draw(Data.GetID(IMG_BLOCKS), Data.GetID(IMG_FONS));

	if (dead) Player.Draw(Data.GetID(IMG_PLAYER_DEAD), Data.GetID(IMG_BALA_PISTOLA), 1, shoot);	//segon parametre = 1, animacio mort
	else {
		if (shoot) Player.Draw(Data.GetID(IMG_PLAYER_SHOOT), Data.GetID(IMG_BALA_PISTOLA), 0, shoot); //shoot true, animacio dispara
		else Player.Draw(Data.GetID(IMG_PLAYER), Data.GetID(IMG_BALA_PISTOLA), 0, shoot);	//segon parametre = 0, animacio moviment
	}
	if (l3)  Enemy.Draw(Data.GetID(IMG_ENEMY_DEAD), Data.GetID(IMG_BALA_BOLA), 1);
	else  Enemy.Draw(Data.GetID(IMG_ENEMY), Data.GetID(IMG_BALA_BOLA), 0);
	if (l4) Enemy2.Draw(Data.GetID(IMG_ENEMY_DEAD), Data.GetID(IMG_BALA_BOLA), 1);
	else Enemy2.Draw(Data.GetID(IMG_ENEMY), Data.GetID(IMG_BALA_BOLA), 0);
	
	Yeti.Draw(Data, yetiID);

	glutSwapBuffers();
}
