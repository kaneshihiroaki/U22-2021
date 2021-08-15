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
bool player_win=false;
 
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

	GameState = 2;
	
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 背景の色
	SetBackgroundColor(255, 255, 255);

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
			c_main->Game_Title();
			break;
		case 1:
			c_main->Game_init();
			break;
		case 2:
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
	c_stage->Stage_Make();

	if (!Collision_Player) {
		for (int i = 0; i < ENEMY_MAX; i++) {
			c_enemy->Enemy_State(i, c_player, c_camera);
		}
		c_enemy->Enemy_Creat();
	}
	//printfDx("%d\n", c_enemy->GetEnemyMoveKey(2));
	//c_enemy->debug();

	c_player->Player_Controller();
	c_player->Player_Move(c_camera,c_enemy);
	
	c_camera->Camera_Control(c_stage);
	

	judge_count = 0;
	player_win = false;
	if (c_player->CheckHit(c_player->c_Position, LightPos)) {
		judge_count++;
		player_win = true;
		
	}

	if (c_enemy->EnemyCheckHit(c_enemy->c_ObjPos, LightPos)) {
		judge_count++;
	}
	if (judge_count == 1) {
		if (player_win) {
			Key_Look = true;
			SetFontSize(200);
			DrawString(490, 120, "Win", GetColor(0xff, 0x00, 0x00));
		}
		else {
			Key_Look = true;
			SetFontSize(200);
			DrawString(440, 120, "Lose", GetColor(0x00, 0x00, 0xff));
		}
	}

	if (!Collision_Player) {
		MV1DrawModel(c_player->c_PlayerModel);
	}
	if (Build_bool) {
		Build_Time();
	}
	if (GameJudge) {
		SetFontSize(50);
		DrawString(570, 5, "Judge", GetColor(0x00, 0x00, 0x00));
		Game_Judge();

		if (((g_NowKey & PAD_INPUT_1) != 0)) {
			GameState = 1;
		}
	}

	Light();

}

void MAIN::Game_Title() {
	SetFontSize(100);
	DrawFormatString(400, 100, 0x000000, "SpotLight");
	SetFontSize(30);
	//GameJudge = false;
	DrawFormatString(460, 300, 0x000000, "Bボタンでゲームスタート");
	if (((g_NowKey & PAD_INPUT_2) != 0) || CheckHitKey(KEY_INPUT_I)) {
		GameState = 1;
		LightFlg = false;
		Key_Look = false;
		Win = false;
		Lose = false;
		GameJudge = false;
	}

}