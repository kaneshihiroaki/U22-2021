#include "DxLib.h"
#include <math.h>
#include <list>
#include"Camera.h"
#include "Player.h"
#include "Stage.h"
#include "enemy.h"
#include "Main.h"
#include "Debug.h"
#include "Light.h"
#include "Character.h"
//ゲームの状態
//int GameState = 0;


int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];
int judge_count = 0;
bool player_win = false;
bool enemy_win = false;
bool judge_win = false;

bool finish;	//ゲームが終わったか判定（true:ゲーム再開 false:タイトルへ戻る)
bool judgefinish = false;	//決着ついたか判定	true:終了 false:続ける

 
MAIN::MAIN()
{
	GameState = 0;

	c_camera = new CAMERA();
	c_player = new PLAYER();
	c_stage = new STAGE();
	c_enemy = new ENEMY();
}

MAIN::~MAIN()
{
}

void MAIN::Game_init() {

	c_player->init();
	c_enemy->init();
	c_stage->init();
	c_camera->init();
	Light_init();

	//勝敗判定初期化
	finish = true;
	judgefinish = false;
	WaitTime = 0;

	//ゲーム開始の演出関連変数初期化
	c_ready = false;
	c_dispTime = 0;

	//初期化したらゲームメインへ
	GameState = 2;
	
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 背景の色
	SetBackgroundColor(250, 250, 250);

	SetMainWindowText("３Ｄ");
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	if (DxLib_Init() < 0) return -1;

	Light_SetUp();


	SetDrawScreen(DX_SCREEN_BACK);

	SetCameraNearFar(100.0f, 50000.0f);

	//	 Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	MAIN *c_main = new MAIN();

	//ゲームステータスをタイトルへ
	c_main->GameState = 0;

	// メインループ(何かキーが押されたらループを抜ける)
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		//入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		if (((g_NowKey & PAD_INPUT_7) != 0) && ((g_NowKey & g_OldKey) == 0)) {
			if (DebugMode) {
				DebugMode = false;
				DebugNum = 1;
			}
			else {
				DebugMode = true;
			}
		}

		switch (c_main->GameState)
		{
		case 0:
			// 背景の色
			SetBackgroundColor(250, 250, 250);
			c_main->Game_Title();
			break;
		case 1:
			c_main->Game_init();
			break;
		case 2:
			// 背景の色
			SetBackgroundColor(35, 35, 35);
			c_main->Game_Main();
			break;

		default:
			break;
		} 

		//デバックコマンド表示
		if (DebugCom() == -1) {
			//デバックするなら入る
		}
		// 裏画面の内容を表画面に反映する
		ScreenFlip();
	}
	// キー入力待ちをする
	WaitKey();

	// ＤＸライブラリの後始末
	DxLib_End();

	return 0;
}

void MAIN::Game_Main() {
	SetFontSize(100);

	//最初にBボタンを押してゲーム開始
	if (c_ready == true) {

		c_stage->Stage_Make(c_enemy, c_player);

		if (!Collision_Player) {
			for (int i = 0; i < ENEMY_MAX; i++) {
				c_enemy->Enemy_State(i, c_player, c_camera);
			}
			c_enemy->Enemy_Creat();
		}

		//プレイヤーの表示と動きの制御
		c_player->Player_Controller();
		c_player->Player_Move(c_camera, c_enemy);

		c_camera->Camera_Control(c_stage);

		WIN_Text();
		judge_count = 0;
		player_win = false;
		enemy_win = false;
		if (c_player->CheckHit(c_player->c_Position, LightPos)) {
			judge_count++;
			player_win = true;

		}

		if (c_enemy->EnemyCheckHit(c_enemy->c_ObjPos, LightPos)) {
			judge_count++;
			enemy_win = true;
		}
		if (judge_count == 1) {
			if (player_win) {
				if (judge_win == false)
				{
					PLAYER_WIN_COUNT++;
					judge_win = true;
				}

				SetFontSize(100);
				DrawString(360, 120, "PLAYER_WIN", GetColor(0xff, 0x00, 0x00));
			}
			if (enemy_win) {
				if (ENEMY_WIN == 1) {
					Key_Look = true;
					if (judge_win == false)
					{
						ENEMY_WIN_COUNT1++;
						judge_win = true;
					}
					SetFontSize(100);
					DrawString(360, 120, "enemy1_WIN", GetColor(0x00, 0x00, 0xff));
				}
				if (ENEMY_WIN == 2) {
					Key_Look = true;
					if (judge_win == false)
					{
						ENEMY_WIN_COUNT2++;
						judge_win = true;
					}
					SetFontSize(100);
					DrawString(360, 120, "enemy2_WIN", GetColor(0x00, 0x00, 0xff));
				}
				if (ENEMY_WIN == 3) {
					Key_Look = true;
					if (judge_win == false)
					{
						ENEMY_WIN_COUNT3++;
						judge_win = true;
					}
					SetFontSize(100);
					DrawString(360, 120, "enemy3_WIN", GetColor(0x00, 0x00, 0xff));
				}
			}
		}

		if (finish == false) GameState = 0;	//決着ついたらタイトルへ戻る

		if (!Collision_Player) {
			MV1DrawModel(c_player->c_PlayerModel);
		}
		if (Build_bool) {
			Build_Time();
		}
		if (GameJudge) {
			SetFontSize(50);
			DrawString(570, 5, "Judge", GetColor(0x00, 0x00, 0x00));
			SetFontSize(20);
			DrawFormatString(20, 100, 0xFFFFFF, "ENEMYWIN:%d", ENEMY_WIN);
			DrawFormatString(20, 120, 0xFFFFFF, "judge:%d", judge_count);
			Game_Judge();

			if (((g_NowKey & PAD_INPUT_1) != 0)) {
				GameState = 0;
			}
		}

		Light();

		//開始時にGO!を表示
		if (c_dispTime++ <= c_dispTimeOver)DrawFormatString(525, 250, 0x0000FF, "GO!");

	}
	//ボタンを押していない時は始めない
	else {
		DrawFormatString(470, 250, 0xFF0000, "READY?");
	}

	//ボタン押したらゲーム開始
	if (((g_KeyFlg & PAD_INPUT_2) != 0) && c_ready == false) c_ready = true;
}

void MAIN::Game_Title() {
	SetFontSize(100);
	DrawFormatString(400, 100, 0x000000, "SpotLight");
	SetFontSize(30);
	//GameJudge = false;
	DrawFormatString(460, 300, 0x000000, "Bボタンでゲームスタート");
	if (((g_KeyFlg & PAD_INPUT_2) != 0) || CheckHitKey(KEY_INPUT_I)) {
		GameState = 1;
		LightFlg = false;
		Key_Look = false;
		Win = false;
		Lose = false;
		GameJudge = false;
		judge_win = false;
		PLAYER_WIN_COUNT = 0;
		ENEMY_WIN = 0;
		ENEMY_WIN_COUNT1 = 0;
		ENEMY_WIN_COUNT2 = 0;
		ENEMY_WIN_COUNT3 = 0;
	}

}
void WIN_Text() {
	SetFontSize(20);
	DrawFormatString(20, 140, 0xFFFFFF, "PLAYER_WIN:%d", PLAYER_WIN_COUNT);
	DrawFormatString(20, 160, 0xFFFFFF, "ENEMY_WIN_1:%d", ENEMY_WIN_COUNT1);
	DrawFormatString(20, 180, 0xFFFFFF, "ENEMY_WIN_2:%d", ENEMY_WIN_COUNT2);
	DrawFormatString(20, 200, 0xFFFFFF, "ENEMY_WIN_3:%d", ENEMY_WIN_COUNT3);

}