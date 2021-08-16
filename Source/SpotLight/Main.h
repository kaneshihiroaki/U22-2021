#pragma once
#include"Dxlib.h"

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1280


void GameInit();
void GameMain();
void WIN_Text();


class CAMERA;
class PLAYER;
class STAGE;
class ENEMY;

extern int judge_count;
extern bool player_win;
extern bool enemy_win;

class MAIN 
{
public:
	MAIN();
	~MAIN();

	int GameState;		//ÉQÅ[ÉÄÇÃèÛë‘

	void Game_init();	//ÉQÅ[ÉÄÇÃèâä˙âª
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
