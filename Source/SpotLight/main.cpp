#include "DxLib.h"
#include <math.h>
#include <list>
#include"Camera.h"
#include "Player.h"
#include "Stage.h"
#include "enemy.h"
#include "Main.h"
#include "Debug.h"
//ゲームの状態
int GameState = 0;

int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];


MAIN::MAIN()
{
	GameState = 0;
}

MAIN::~MAIN()
{
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 背景の色
	SetBackgroundColor(255, 255, 255);

	SetMainWindowText("３Ｄ");
	ChangeWindowMode(TRUE);

	if (DxLib_Init() < 0) return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	SetCameraNearFar(100.0f, 50000.0f);

	//	 Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	
	MAIN *c_main = new MAIN();

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
			c_main->Game_Main();
			break;
		case 1:
			c_main->Game_Title();
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
			c_enemy->Enemy_Move(i);
			
		}
		c_enemy->Enemy_Creat();
	}
	
	c_player->Player_Controller(c_camera->c_SinParam, c_camera->c_CosParam);
	
	c_camera->Camera_Control(c_player->c_Position);


	if (!Collision_Player) {
		MV1DrawModel(c_player->c_PlayerModel);
	}
	if (Build_bool) {
		Build_Time();
	}
	if (GameJudge) {
		DrawString(290, 10, "Judge", GetColor(0x00, 0x00, 0x00));
		Game_Judge();

		if (((g_NowKey & PAD_INPUT_1) != 0)) {
			GameState = 1;
		}
	}
}

void MAIN::Game_Title() {
	DrawFormatString(100, 100, 0x000000, "SpotLight");
	DrawFormatString(100, 120, 0x000000, "Bボタンでゲームスタート");
	if (((g_NowKey & PAD_INPUT_2) != 0)) {
		GameState = 0;
	}

}