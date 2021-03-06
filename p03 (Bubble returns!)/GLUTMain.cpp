
#include "Globals.h"
#include "cGame.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cGame Game;
menu Menu;
float time0;
int menuChange;
bool ignoreMouse = false;


void inicialitza_joc(int x)
{
	if (x == 1) Game.Init(1,false);
	else if (x == 2) Game.Init(2, false);
	else if (x == 3) Game.Init(1, true);
	else if (x == 4) Game.Init(2, true);
	//Game initializations
	time0 = glutGet(GLUT_ELAPSED_TIME);
	menuChange = 1;

	//Application loop
	glutMainLoop();
}

void inicialitza_menu()
{
	bool carrega = false;
	carrega = Menu.init();
	time0 = glutGet(GLUT_ELAPSED_TIME);
	menuChange = 0;

	glutMainLoop();
}
void AppRender()
{
	//Game.Render();
}
void AppKeyboard(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,true);
}
void AppKeyboardUp(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,false);
}
void AppSpecialKeys(int key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,true);
}
void AppSpecialKeysUp(int key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,false);
}
void AppMouse(int button, int state, int x, int y)
{
	int goToMenu = Menu.ReadMouse(button,state,x,y);
	if (!ignoreMouse)
	{
		if (goToMenu == 0) inicialitza_menu();
		else
		{
			inicialitza_joc(goToMenu);
			ignoreMouse = true;

		}
	}
	Game.ReadMouse(button,state,x,y);
}
void AppIdle()
{
	if (menuChange == 0 && (glutGet(GLUT_ELAPSED_TIME) - time0) > 1000 / 60) {
		time0 = glutGet(GLUT_ELAPSED_TIME);
		if (!Menu.Loop()) exit(0);
	}
	else if (menuChange == 1 && (glutGet(GLUT_ELAPSED_TIME) - time0) > 1000 / 60) {
		time0 = glutGet(GLUT_ELAPSED_TIME);
		if (!Game.Loop()) inicialitza_menu();
	}
}

void resize(int width, int height) {
	// we ignore the params and do:
	glutReshapeWindow(GAME_WIDTH, GAME_HEIGHT);
}

void load_MainWindow(int argc, char** argv)
{
	int res_x, res_y, pos_x, pos_y;

	//GLUT initialization
	glutInit(&argc, argv);

	//RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x >> 1) - (GAME_WIDTH >> 1);
	pos_y = (res_y >> 1) - (GAME_HEIGHT >> 1);

	glutInitWindowPosition(pos_x, pos_y);
	glutInitWindowSize(GAME_WIDTH, GAME_HEIGHT);
	glutCreateWindow("Bubble returns!");

	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	//Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutDisplayFunc(AppRender);
	glutKeyboardFunc(AppKeyboard);
	glutKeyboardUpFunc(AppKeyboardUp);
	glutSpecialFunc(AppSpecialKeys);
	glutSpecialUpFunc(AppSpecialKeysUp);
	glutMouseFunc(AppMouse);
	glutIdleFunc(AppIdle);
	glutReshapeFunc(resize);
}

void main(int argc, char** argv)
{
	menuChange = 0;
	load_MainWindow(argc, argv);
	inicialitza_menu();
}
