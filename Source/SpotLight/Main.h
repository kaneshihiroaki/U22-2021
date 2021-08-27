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

extern int judge_count2;//プレイヤーがスポットライトに入ったら数える
extern int judge_count3;//敵がスポットライトに入ったら数える
extern bool player_judge;//プレイヤーがスポットライトに入ったときのflg
extern bool enemy_judge;//敵がスポットライトに入ったら入ったときのflg

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
	int c_resultdispTime;	//リザルトで文字の表示に使用するカウント
	bool OnePass;
	bool onecheck = false;
	int c_VictorNum = 0;	//勝者格納よう変数

	const int c_dispTimeMax = 60;	//GO表示時間
	const int c_readyMaxTime = 240;		//READYの表示時間いっぱい
	const int c_resultdispMaxTime = 180;	//リザルトの表示時間
	//const int c_pointcal = 10;		//リザルトのポイント計算

	int LoadSound();
	int CountMaxPoint(int* point);	//リザルトでだれが一番ポイントを取得したのか計算

	CAMERA* c_camera;
	PLAYER* c_player;
	STAGE* c_stage;
	ENEMY* c_enemy;
	CHARACTER* c_chara;
};

//extern int g_NowKey;

extern char key[256];
