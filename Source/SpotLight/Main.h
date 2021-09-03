#pragma once
#include"Dxlib.h"

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1280

#define NO_NAME 0

#define ENEMY1_NAME 1
#define ENEMY2_NAME 2
#define ENEMY3_NAME 3

#define PLAYER_NAME 4

void GameInit();
void GameMain();
void WIN_Text();


class CAMERA;
class PLAYER;
class STAGE;
class ENEMY;

extern int Number_count;
extern int win_timer;//勝利を表示し続けるカウント
extern bool player_win;
extern bool enemy_win;

extern bool DrawFlg;//drawcountをカウントするときのflg
extern int draw_timer;//drawを表示し続ける秒数
extern int draw_count;//drawを表示していい時に使うカウント


extern int Time_IN_count;//敵がスポットライトに入ったら数える
extern bool player_judge;//プレイヤーがスポットライトに入ったときのflg
extern bool enemy_judge;//敵がスポットライトに入ったら入ったときのflg
extern int Win_NameOld;//誰がスポットライトに入っていたか#defineで数字管理
extern int Win_NameNow;//誰がスポットライトに入っていたか#defineで数字管理

/*サドンデス用変数*/
extern bool Sadondes_flg;//サドンデスを行うかどうかtrueなら行っている。
/*サドンデス用変数*/

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

	//サドンデス用関数
	void Sadondes();
	void Sadondes_check();
	void Sadondes_Init();

private:
	bool c_ready;		//ボタンを押してメインを開始する変数
	int c_dispTime;		//READYとGOの表示時間カウント
	int c_resultdispTime;	//リザルトで文字の表示に使用するカウント
	int c_PressBDispTime;	//Press Bを表示・点滅させる変数
	bool c_OnePass;			//スコア計算を一回だけ参照
	bool c_ResultBack;		//リザルトでタイトルに戻るという表記を表示させる
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
