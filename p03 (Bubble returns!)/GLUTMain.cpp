
#include "Globals.h"
#include "cGame.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cGame Game;
menu Menu;
float time0;
bool menu;

void AppRender()
{
	Game.Render();
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
	Game.ReadMouse(button,state,x,y);
}
void AppIdle()
{
	if (menu && (glutGet(GLUT_ELAPSED_TIME) - time0) > 1000 / 60) {
		time0 = glutGet(GLUT_ELAPSED_TIME);
		if (!Menu.Loop()) exit(0);
	}
	else if (!menu && (glutGet(GLUT_ELAPSED_TIME) - time0) > 1000 / 60) {
		time0 = glutGet(GLUT_ELAPSED_TIME);
		if (!Game.Loop()) exit(0);
	}

}

void load_menu(int argc, char** argv)
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

	bool carrega = false;
	carrega = Menu.init();
	time0 = glutGet(GLUT_ELAPSED_TIME);
	menu = false;
	
	//glutMainLoop();
}

void inicialitza_joc()
{
	//Game initializations
	Game.Init();
	time0 = glutGet(GLUT_ELAPSED_TIME);

	//Application loop
	glutMainLoop();
}

void main(int argc, char** argv)
{
	load_menu(argc, argv);
	inicialitza_joc();
}
