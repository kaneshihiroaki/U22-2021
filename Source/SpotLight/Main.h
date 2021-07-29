#pragma once
#include"Dxlib.h"

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

};

//extern int g_NowKey;

extern char key[256];
