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
extern int win_timer;//勝利を表示し続けるカウント
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
	void Game_Result();

private:
	bool c_ready;		//ボタンを押してメインを開始する変数
	int c_dispTime;		//READYとGOの表示時間カウント

	const int c_dispTimeMax = 60;	//GO表示時間
	const int c_readyMaxTime = 240;		//READYの表示時間いっぱい
	const int c_pointcal = 10;		//リザルトのポイント計算

	int LoadSound();

	CAMERA* c_camera;
	PLAYER* c_player;
	STAGE* c_stage;
	ENEMY* c_enemy;
	CHARACTER* c_chara;
};

//extern int g_NowKey;

extern char key[256];
