﻿#include "DxLib.h"
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
int win_timer = 0;
bool player_win = false;
bool enemy_win = false;
bool judge_win = false;
//int check_1 = 0;
//int check_2 = 0;
//ゲームサウンド関係
int bgm_title;//タイトル
int bgm_main;//ゲーム中
int drum;//スポットライト動作中
int drum_finish;//スポットライト停止中
int win_sound;//勝利者SE
int player_win_sound;//playerが１位の時のBGM
int enemy_win_sound;//enemyが１位の時のBGM
int player_attack_sound;//playerが攻撃するときのSE


bool finish;	//ゲームが終わったか判定（true:ゲーム再開 false:タイトルへ戻る)
bool judgefinish = false;	//決着ついたか判定	true:終了 false:続ける
int round_count = 0;			//ラウンド数

int maku[18];
int menu[68];
int menu2[68];

int imgC = 17;

int g_play = false;
int g_exit = false;
int state = 0;

MAIN::MAIN()
{
	GameState = 0;
	LoadSound();
	LoadDivGraph("Image/pipo-curtain2.png", 18, 1, 18, 1280, 960, maku); // 画像の分割読み込み
	LoadDivGraph("Image/mes01_f01_d03_c10_05.png", 64, 4, 17, 240, 60, menu); // 画像の分割読み込み
	LoadDivGraph("Image/mes01_f01_d03_c09_05.png", 64, 4, 17, 240, 60, menu2); // 画像の分割読み込み
	
	LPCSTR font_path = "Fonts/Pokemon Solid.ttf"; // 読み込むフォントファイルのパス
	
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

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
	win_timer = 0;
	WaitTime = 0;
	round_count = 0;

	//ゲーム開始の演出関連変数初期化
	c_ready = false;
	c_dispTime = c_readyMaxTime;

	//ライト・リザルト用変数初期化
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
	/*check_1 = 0;
	check_2 = 0;*/

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

	MAIN* c_main = new MAIN();

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

		case 3:
			c_main->Game_Result();
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
	if (CheckSoundMem(bgm_main) == 0) {
		PlaySoundMem(bgm_main, DX_PLAYTYPE_LOOP);
	}
	//オブジェクトの表示
	c_stage->Stage_Make(c_enemy, c_player);
	c_player->Player_Controller();
	if (!Collision_Player)c_enemy->Enemy_Creat();
	c_camera->Camera_Control(c_stage);

	//最初にBボタンを押してゲーム開始
	if (c_ready == true) {

		//c_stage->Stage_Make(c_enemy, c_player);

		if (!Collision_Player) {
			for (int i = 0; i < ENEMY_MAX; i++) {
				c_enemy->Enemy_State(i, c_player, c_camera);
			}
			//c_enemy->Enemy_Creat();
		}

		//プレイヤーの表示と動きの制御
		//c_player->Player_Controller();
		c_player->Player_Move(c_camera, c_enemy);

		//c_camera->Camera_Control(c_stage);

		WIN_Text();
		judge_count = 0;
		player_win = false;
		enemy_win = false;
		/*check_1 = 0;
		check_2 = 0;*/
		if (c_player->CheckHit(c_player->c_Position, LightPos)) {
			judge_count++;
			player_win = true;

		}

		if (c_enemy->EnemyCheckHit(c_enemy->c_ObjPos, LightPos)) {
			judge_count++;
			enemy_win = true;
		}
		/*if (c_enemy->EnemyCheckHit2(c_enemy->c_ObjPos)) {
			check_1 = 1;
		}
		if (c_enemy->EnemyCheckHit3(c_enemy->c_ObjPos, c_player->c_Position)) {
			check_2 = 1;
		}*/
		if (judge_count == 1) {
			if (CheckSoundMem(win_sound) == 0) {
				PlaySoundMem(win_sound, DX_PLAYTYPE_LOOP);
			}
			if (player_win) {
				if (judge_win == false)
				{
					PLAYER_WIN_COUNT++;
					judge_win = true;
				}

				win_timer = (win_timer + 1) % 121;
				if (win_timer < 119) {
					SetFontSize(100);
					DrawString(360, 120, "PLAYER_WIN", GetColor(0xff, 0x00, 0x00));
				}
				if (win_timer == 120) {
					StopSoundMem(win_sound);
					time = 600;
					win_timer = 0;
				}
			}
			if (enemy_win) {
				if (ENEMY_WIN == 1) {
					Key_Look = true;
					if (judge_win == false)
					{
						ENEMY_WIN_COUNT1++;
						judge_win = true;
					}

					win_timer = (win_timer + 1) % 121;
					if (win_timer < 119) {
						SetFontSize(100);
						DrawString(360, 120, "enemy0_WIN", GetColor(0x00, 0x00, 0xff));
					}
				}
				if (ENEMY_WIN == 2) {
					Key_Look = true;
					if (judge_win == false)
					{
						ENEMY_WIN_COUNT2++;
						judge_win = true;
					}

					win_timer = (win_timer + 1) % 121;
					if (win_timer < 119) {
						SetFontSize(100);
						DrawString(360, 120, "enemy1_WIN", GetColor(0x00, 0x00, 0xff));
					}
				}
				if (ENEMY_WIN == 3) {
					Key_Look = true;
					if (judge_win == false)
					{
						ENEMY_WIN_COUNT3++;
						judge_win = true;
					}

					win_timer = (win_timer + 1) % 121;
					if (win_timer < 119) {
						SetFontSize(100);
						DrawString(360, 120, "enemy2_WIN", GetColor(0x00, 0x00, 0xff));
					}
				}
				if (win_timer == 120) {
					StopSoundMem(win_sound);
					time = 600;
					win_timer = 0;
				}
			}
		}

		if (finish == false) GameState = 3;	//決着ついたらタイトルへ戻る

		//if (!Collision_Player) {
		//	MV1DrawModel(c_player->c_PlayerModel);
		//}
		if (Build_bool) {
			Build_Time();
		}
		if (GameJudge) {
			SetFontSize(50);
			DrawString(570, 5, "Judge", GetColor(0x00, 0x00, 0x00));
			SetFontSize(20);
			DrawFormatString(20, 40, 0xFFFFFF, "win_timer:%d", win_timer);
			/*	DrawFormatString(20, 60, 0xFFFFFF, "check_1:%d", check_1);
				DrawFormatString(20, 80, 0xFFFFFF, "check_2:%d", check_2);*/
			DrawFormatString(20, 100, 0xFFFFFF, "ENEMYWIN:%d", ENEMY_WIN);
			DrawFormatString(20, 120, 0xFFFFFF, "judge:%d", judge_count);
			Game_Judge();

			if (((g_NowKey & PAD_INPUT_1) != 0)) {
				GameState = 0;
			}
		}

		Light();

		//開始時にGO!を表示
		if (--c_dispTime >= 0)DrawFormatString(525, 250, 0x0000FF, "GO!");

	}
	//3秒立ったら始める
	else {
	    StopSoundMem(bgm_title);
		SetFontSize(100);
		DrawFormatString(470, 250, 0xFF0000, "READY?");
		DrawFormatString(580, 350, 0xFF0000, "%d", c_dispTime / 60);
	}

	//ボタン押したらゲーム開始
	if (--c_dispTime <= 60 && c_ready == false) {
		c_ready = true;
		c_dispTime = c_dispTimeMax;	//GOの表示時間を代入
	}
}

void MAIN::Game_Title() {
	if (CheckSoundMem(bgm_title) == 0) {
		PlaySoundMem(bgm_title, DX_PLAYTYPE_LOOP);
	}
	DrawGraph(0, 0, maku[imgC], TRUE);      // 画像を表示
	DrawGraph(500, 400, menu[1], TRUE);
	DrawGraph(500, 500, menu[2], TRUE);
	
	// 描画する文字列の文字セットを変更します
	ChangeFont("Pokemon Solid");
	SetFontSize(150);
	DrawFormatString(250, 100, 0xffff00, "SpotLight");
	if (((g_KeyFlg & PAD_INPUT_DOWN) != 0)) {
		state += 1;
		if (state >= 2) {
			state = 0;
		}
	}
	else if (((g_KeyFlg & PAD_INPUT_UP) != 0)) {
		state -= 1;
		if (state < 0) {
			state = 1;
		}
	}	
	if (state == 0) {
		DrawGraph(500, 405, menu2[1], TRUE);
	}
	else if (state == 1) {
		DrawGraph(500, 505, menu2[2], TRUE);
	}
	if (((g_KeyFlg & PAD_INPUT_2) != 0) || CheckHitKey(KEY_INPUT_I)) {
		if (state == 0) {
			g_play = true;
		}
		else if (state == 1) {
			g_exit = true;
		}
		//LightFlg = false;
				//Key_Look = false;
				//Win = false;
				//Lose = false;
				//GameJudge = false;
				//judge_win = false;
				//PLAYER_WIN_COUNT = 0;
				//ENEMY_WIN = 0;
				//ENEMY_WIN_COUNT1 = 0;
				//ENEMY_WIN_COUNT2 = 0;
				//ENEMY_WIN_COUNT3 = 0;
				//check_1 = 0;
				//check_2 = 0;
	}
	if (g_play == true) {
		static int c = 0;
		c++;
		if (c % 3 == 0) {
			imgC--;
		}
	}
	else if (g_exit == true) {
		DxLib_End();
	}
	if (imgC < 0) {
		ChangeFont("MS Pゴシック");
		g_play = false;
		GameState = 1;
	}
}

void MAIN::Game_Result() {
	StopSoundMem(drum);
	StopSoundMem(bgm_main);

	if (PLAYER_WIN_COUNT > ENEMY_WIN_COUNT1) {
		if (PLAYER_WIN_COUNT > ENEMY_WIN_COUNT2) {
			if (PLAYER_WIN_COUNT > ENEMY_WIN_COUNT3) {
				if (CheckSoundMem(player_win_sound) == 0) {
					PlaySoundMem(player_win_sound, DX_PLAYTYPE_BACK);
				}
			}
		}
	}
	else {
		if (CheckSoundMem(enemy_win_sound) == 0) {
			PlaySoundMem(enemy_win_sound, DX_PLAYTYPE_BACK);
		}
	}
	int score[4];	//スコア格納用の変数　０はプレイヤー用　１～３は適用
	
	score[0] = PLAYER_WIN_COUNT * c_pointcal;
	score[1] = ENEMY_WIN_COUNT1 * c_pointcal;
	score[2] = ENEMY_WIN_COUNT2 * c_pointcal;
	score[3] = ENEMY_WIN_COUNT3 * c_pointcal;


	SetFontSize(20);
	DrawFormatString(100, 100, 0xFFFFFF, "PLAYER_WIN_NUM:%d", PLAYER_WIN_COUNT);
	DrawFormatString(100, 120, 0xFFFFFF, "PLAYER_POINT:%d", score[0]);
	DrawFormatString(500, 100, 0xFFFFFF, "ENEMY1_WIN_NUM:%d", ENEMY_WIN_COUNT1);
	DrawFormatString(500, 120, 0xFFFFFF, "ENEMY1_POINT:%d", score[1]);
	DrawFormatString(120, 140, 0xFFFFFF, "ENEMY2_WIN_NUM:%d", ENEMY_WIN_COUNT2);
	DrawFormatString(120, 160, 0xFFFFFF, "ENEMY2_POINT:%d", score[2]);
	DrawFormatString(520, 140, 0xFFFFFF, "ENEMY3_WIN_NUM:%d", ENEMY_WIN_COUNT3);
	DrawFormatString(520, 160, 0xFFFFFF, "ENEMY3_POINT:%d", score[3]);

	if ((g_KeyFlg & PAD_INPUT_2) != 0) GameState = 0;
}

void WIN_Text() {
	SetFontSize(20);
	DrawFormatString(20, 140, 0xFFFFFF, "PLAYER_WIN:%d", PLAYER_WIN_COUNT);
	DrawFormatString(20, 160, 0xFFFFFF, "ENEMY_WIN_1:%d", ENEMY_WIN_COUNT1);
	DrawFormatString(20, 180, 0xFFFFFF, "ENEMY_WIN_2:%d", ENEMY_WIN_COUNT2);
	DrawFormatString(20, 200, 0xFFFFFF, "ENEMY_WIN_3:%d", ENEMY_WIN_COUNT3);

}

int MAIN::LoadSound() {
	//ゲーム音読み込み
	if ((bgm_title = LoadSoundMem("GameSound/GameTitle.mp3")) == -1)return -1;
	if ((bgm_main = LoadSoundMem("GameSound/CandyCrush.mp3")) == -1)return -1;
	if ((drum = LoadSoundMem("GameSound/drum.mp3")) == -1)return -1;
	if ((drum_finish = LoadSoundMem("GameSound/drum_finish.mp3")) == -1)return -1;
	if ((win_sound = LoadSoundMem("GameSound/win_sound.mp3")) == -1)return -1;
	if ((player_win_sound = LoadSoundMem("GameSound/player_win.mp3")) == -1)return-1;
	if ((enemy_win_sound = LoadSoundMem("GameSound/enemy_win.mp3")) == -1)return-1;
	if ((player_attack_sound = LoadSoundMem("GameSound/player_attack.mp3")) == -1)return -1;
	//音量調整
	// BGM
	ChangeVolumeSoundMem(100, bgm_title);
	ChangeVolumeSoundMem(60, bgm_main);
	ChangeVolumeSoundMem(80, drum);
	ChangeVolumeSoundMem(80, drum_finish);
	ChangeVolumeSoundMem(100, player_win_sound);
	ChangeVolumeSoundMem(100, enemy_win_sound);
	// SE
	ChangeVolumeSoundMem(80, win_sound);
	ChangeVolumeSoundMem(80, player_attack_sound);

	return 0;
}