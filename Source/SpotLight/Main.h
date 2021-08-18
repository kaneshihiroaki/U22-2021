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

	int GameState;		//ゲームの状態

	void Game_init();	//ゲームの初期化
	void Game_Main();
	void Game_Title();

private:
	bool c_ready;		//ボタンを押してメインを開始する変数
	int c_dispTime;		//GOの表示時間カウント
	const int c_dispTimeOver = 30;	//表示管

	CAMERA* c_camera;
	PLAYER* c_player;
	STAGE* c_stage;
	ENEMY* c_enemy;
	CHARACTER* c_chara;
};

//extern int g_NowKey;

extern char key[256];
