#pragma once
#include"Dxlib.h"

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1280


void GameInit();
void GameMain();

class CAMERA;
class PLAYER;
class STAGE;
class ENEMY;

class MAIN 
{
public:
	MAIN();
	~MAIN();

	int GameState;		//ÉQÅ[ÉÄÇÃèÛë‘

	void Game_Main();
	void Game_Title();

private:

	CAMERA* c_camera;
	PLAYER* c_player;
	STAGE* c_stage;
	ENEMY* c_enemy;
	CHARACTER* c_chara;
};

//extern int g_NowKey;

extern char key[256];
