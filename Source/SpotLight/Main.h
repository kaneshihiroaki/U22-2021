#pragma once
#include"Dxlib.h"

void GameInit();
void GameMain();

class MAIN
{
public:
	MAIN();
	~MAIN();

	int GameState;		//ÉQÅ[ÉÄÇÃèÛë‘

	void Game_Main();
	void Game_Title();


private:

	CAMERA* c_camera = new CAMERA();
	PLAYER* c_player = new PLAYER();
	STAGE* c_stage = new STAGE();
	ENEMY* c_enemy = new ENEMY();

};

//extern int g_NowKey;

extern char key[256];
