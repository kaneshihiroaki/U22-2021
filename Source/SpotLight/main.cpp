#include "DxLib.h"
// EffekseerForDXLib.hをインクルードします。
#include "EffekseerForDXLib.h"

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
#include "GameSound.h"


//ゲームの状態
//int GameState = 0;


int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];

//勝敗関係
int Number_count = 0;//スポットライトに入っている人数
int win_timer = 0;//勝利テキストを見せる秒数
bool player_win = false;//playerがスポットライトに入った時のflg
bool enemy_win = false;//敵がスポットライトに入った時のflg
bool judge_win = false;

bool DrawFlg;//drawcountをカウントするときのflg
int draw_timer = 0;//drawを表示するタイマー
int draw_count = 0;//drawを表示していい時に使う

int Time_IN_count;//敵がスポットライトに入ったら数える
bool player_judge;//プレイヤーがスポットライトに入ったときのflg
bool enemy_judge;//敵がスポットライトに入ったら入ったときのflg
int Win_NameOld = NO_NAME;//誰がスポットライトに入っていたか#defineで数字管理
int Win_NameNow = NO_NAME;//誰がスポットライトに入っていたか#defineで数字管理

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
int player_attack_false_sound;//playerが攻撃できなかったとき（スタミナが足りなかったとき）のSE
int enemy1_attack_sound;//enemy1が攻撃するときのSE
int enemy2_attack_sound;//enemy2が攻撃するときのSE
int enemy3_attack_sound;//enemy3が攻撃するときのSE
int damage_sound;//被弾した時のSE
int cursor_sound;//カーソルのSE
int draw_sound;//引き分けのSE
int breath_sound;  //息切れのSE

int BGM_flg;//BGMをとめるflg;
int Enemy_Sound_flg;//enemyの攻撃音をとめるflg;//true:止める false:止めない

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

bool g_loopFlg = false;

MAIN::MAIN()
{
	GameState = 0;
	LoadSound();
	LoadDivGraph("Image/pipo-curtain2.png", 18, 1, 18, 1280, 960, maku); // 画像の分割読み込み
	LoadDivGraph("Image/mes01_f01_d03_c10_05.png", 64, 4, 17, 240, 60, menu); // 画像の分割読み込み
	LoadDivGraph("Image/mes01_f01_d03_c09_05.png", 64, 4, 17, 240, 60, menu2); // 画像の分割読み込み

	LPCSTR font_path = "Fonts/rampart-one/RampartOne-Regular.ttf"; // 読み込むフォントファイルのパス
	LPCSTR font_main = "Fonts/alumni-sans/AlumniSans-Black.ttf";	//メイン等で使うファイルパス

	//タイトルフォント読込み
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "タイトルフォント読込失敗", "", MB_OK);
	}

	//メインフォント読込み
	if (AddFontResourceEx(font_main, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "メインフォント読込失敗", "", MB_OK);
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

	//タイトルで使う変数初期化
	imgC = 17;
	g_play = false;
	g_exit = false;
	state = 0;

	//勝敗判定初期化
	finish = true;
	judgefinish = false;
	win_timer = 0;
	WaitTime = 0;
	round_count = 0;



	//ゲーム開始の演出関連変数初期化
	c_ready = false;
	c_dispTime = c_readyMaxTime;
	c_resultdispTime = 0;
	c_PressBDispTime = 0;

	//ライト・リザルト用変数初期化
	LightFlg = false;
	Key_Look = false;
	Win = false;
	Lose = false;
	GameJudge = false;
	judge_win = false;

	DrawFlg = false;
	draw_timer = 0;
	draw_count = 0;

	PLAYER_WIN_COUNT = 0;
	ENEMY_WIN = 0;
	ENEMY_WIN_COUNT1 = 0;
	ENEMY_WIN_COUNT2 = 0;
	ENEMY_WIN_COUNT3 = 0;
	c_OnePass = false;
	c_ResultBack = false;
	/*check_1 = 0;
	check_2 = 0;*/

	BGM_flg = false;//BGMをとめるflg;
	Enemy_Sound_flg = false;//enemyの攻撃音をとめるflg;//true:止める false:止めない

	//初期化したらゲームメインへ
	GameState = 2;

}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 背景の色
	SetBackgroundColor(35, 35, 35);

	SetMainWindowText("３Ｄ");
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);


	if (DxLib_Init() < 0) return -1;

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}


	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	

	Light_SetUp();


	SetDrawScreen(DX_SCREEN_BACK);

	SetCameraNearFar(100.0f, 50000.0f);

	//	 Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	MAIN* c_main = new MAIN();

	// エフェクトリソースを読み込む。
	// 読み込む時に大きさを指定する。
	//int effectResourceHandle = LoadEffekseerEffect("Laser01.efkefc", 1.0f);
	//下のEffectSeekImportで読み込みを行う
	c_main->EffectSeekImport();

	//ゲームステータスをタイトルへ
	c_main->GameState = 0;

	// メインループ(何かキーが押されたらループを抜ける)
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && g_loopFlg == false)
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
			// 背景の色
			c_main->Game_Main();
			break;

		case 3:
			c_main->Game_Result(c_main);
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
	//WaitKey();

	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(c_main->effectResourceHandle[0]);

	// Effekseerを終了する。
	Effkseer_End();

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
	c_camera->Camera_Control(c_stage);

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	

	c_stage->Stage_Make(c_enemy, c_player);
	if (!Collision_Player)c_enemy->Enemy_Creat();
	c_player->Player_Controller();

	if (Debug_Camera == true) {
		SetFontSize(50);
		DrawFormatString(300, 110, 0xFFFFFF, "CameraPos：%f", c_camera->cko);
		DrawFormatString(300, 150, 0xFFFFFF, "CameraAngV%f", c_camera->c_CameraVAngle);
		DrawFormatString(300, 190, 0xFFFFFF, "CameraAngD%f", c_camera->c_CameraHAngle);
	}

	//最初にBボタンを押してゲーム開始
	if (c_ready == true) {

		//c_stage->Stage_Make(c_enemy, c_player);

		if (!Collision_Player) {
			for (int i = 0; i < ENEMY_MAX; i++) {
				c_enemy->Enemy_State(i, c_player, c_enemy);
			}
		}

		//プレイヤーの表示と動きの制御
		c_player->Player_Move(c_player, c_enemy);


		WIN_Text();

		//DrawFormatString(100, 220 + 20, 0xFFFFFF, "%d\n", Time_IN_count);
		if (LightFlg == true) {
			Number_count = 0;//スポットライトに入っている人数
			win_timer = 0;
			draw_timer = 0;
			judge_win = false;
			player_judge = false;
			enemy_judge = false;
			DrawFlg = false;
			Time_IN_count = 0;//1人がスポットライトに何秒入っているかどうか
			Win_NameOld = NO_NAME;
			
		}

		player_win = false;//プレイヤーがスポットライトに入っているかどうか
		enemy_win = false;//敵がスポットライトに入っているかどうか

		//サドンデスなら入る。主にタイムを固定する予定
		if (Sadondes_flg && LightFlg == false && round_count > 0) {
			time_All = 100;
		}
		//ここはドロー判定
		if (LightFlg == false && time_All >= 598) {
			if (DrawFlg == false) {
				draw_count++;
				DrawFlg = true;
			}
			if (draw_count >= 2) {
				draw_timer = (draw_timer + 1) % 121;
				time_All = 599;
				if (draw_timer < 119) {
					if (CheckSoundMem(draw_sound) == 0) {
						PlaySoundMem(draw_sound, DX_PLAYTYPE_BACK);
					}
					Key_Look = true;
					SetFontSize(100);
					DrawString(520, 140, "Draw", GetColor(0xff, 0xff, 0x00));
				}
				else if (draw_timer >= 120) {
					time_All = 600;
					draw_timer = 0;
				}
			}
		}


		Number_count = 0;//スポットライトに入っている人数


		//敵がスポットライトに入っているかどうか判定
		Number_count += c_enemy->EnemyCheckHit(c_enemy->c_ObjPos, LightPos);
		if (Number_count > 0) {//1人以上入っているならば
			enemy_win = true;
		}
		//プレイヤーがスポットライトに入っているかどうか判定
		if (c_player->CheckHit(c_player->c_Position, LightPos)) {
			Number_count++;
			player_win = true;
		}

		if (time_All <= 597) {
			//スポットライトが止まっているなら勝敗判定を行う
			if (LightFlg == false) {

				c_player->SetStopMoveFlg();		//勝敗判定時にプレイヤーが動かないようにフラグをfalseにしておく

				if (Number_count == 1) {//1人だけになったときにカウント60フレームくらい
					//1人なっているのがだれかを判定
					if (player_win) {
						Win_NameNow = PLAYER_NAME;
					}
					else {
						Win_NameNow = ENEMY_WIN;
					}

					//入り続けているのが同じ人かどうかを調べる。
					if (Win_NameOld == NO_NAME) {//最初のカウント時
						Win_NameOld = Win_NameNow;
						Time_IN_count++;
					}
					else if (Win_NameOld == Win_NameNow) {//同じ人が入っています。
						Time_IN_count++;
					}
					else {//違う人だけが入っています。
						Win_NameOld = Win_NameNow;
						Time_IN_count = 1;
					}
				}
				else {//それ以外だと0にする
					Time_IN_count = 0;
					Win_NameOld = NO_NAME;
				}


				if (Number_count == 1 && Time_IN_count > 60) {
					if (player_win) {
						if (CheckSoundMem(win_sound) == 0) {
							PlaySoundMem(win_sound, DX_PLAYTYPE_LOOP);
						}
						if (judge_win == false)
						{
							PLAYER_WIN_COUNT++;
							judge_win = true;
						}

						win_timer = (win_timer + 1) % 121;
						if (win_timer < 119) {
							time_All = 496;
							Key_Look = true;
							SetFontSize(100);
							DrawString(470, 120, "YOU_WIN", GetColor(0xff, 0x00, 0x00));
						}
						else if (win_timer >= 120) {
							StopSoundMem(win_sound);
							time_All = 600;
							win_timer = 0;

						}
					}
				}
				if (Number_count == 1 && Time_IN_count > 60) {
					if (enemy_win) {
						if (CheckSoundMem(win_sound) == 0) {
							PlaySoundMem(win_sound, DX_PLAYTYPE_LOOP);
						}

						if (ENEMY_WIN == 1) {
							Key_Look = true;
							if (judge_win == false)
							{
								ENEMY_WIN_COUNT1++;
								judge_win = true;
							}

							win_timer = (win_timer + 1) % 121;
							if (win_timer < 119) {
								time_All = 496;
								Key_Look = true;
								SetFontSize(100);
								DrawString(420, 120, "CPU1_WIN", GetColor(0x00, 0x00, 0xff));
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
								time_All = 496;
								Key_Look = true;
								SetFontSize(100);
								DrawString(420, 120, "CPU2_WIN", GetColor(0x00, 0x00, 0xff));
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
								time_All = 496;
								Key_Look = true;
								SetFontSize(100);
								DrawString(420, 120, "CPU3_WIN", GetColor(0x00, 0x00, 0xff));
							}
						}
						if (win_timer >= 120) {
							StopSoundMem(win_sound);
							time_All = 600;
							win_timer = 0;

						}
					}
				}
			}
		}


		//決着ついたらリザルトへ行くこれをサドンデスかどうか調べてから
		if (finish == false) {
			Sadondes_check();
			if (Sadondes_flg == true) {//サドンデスにいってほしいなら
				Sadondes_Init();
				return;
			}
			else {
				GameState = 3;	//決着ついたらリザルト画面へ
			}
			
		}

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
			DrawFormatString(20, 40, 0xFFFFFF, "win_timer:%d", time);
			DrawFormatString(20, 60, 0xFFFFFF, "judge_count2:%d", Time_IN_count);
			DrawFormatString(20, 80, 0xFFFFFF, "judge_count3:%d", Time_IN_count);
			DrawFormatString(20, 100, 0xFFFFFF, "ENEMYWIN:%d", ENEMY_WIN);
			DrawFormatString(20, 120, 0xFFFFFF, "judge:%d", Number_count);
			Game_Judge();

			if (((g_NowKey & PAD_INPUT_1) != 0)) {
				GameState = 0;
			}
		}

		Light();

		//ラウンド表示
		if (Sadondes_flg==false) {
			DrawFormatString(500, 10, 0xffff00, "ROUND %d", round_count);
		}
		else {
			DrawFormatString(410, 10, 0xffff00, "EXTRA ROUND");
		}
		
		//開始時にGO!を表示
		if (--c_dispTime >= 0)DrawFormatString(580, 230, 0x0000FF, "GO!");

	}
	//3秒立ったら始める
	else {
		StopSoundMem(bgm_title);
		SetFontSize(100);
		if (Sadondes_flg == false) {//サドンデス前なのでタイトルからとんだとき
			DrawFormatString(520, 140, 0xFF0000, "READY?");
			DrawFormatString(620, 240, 0xFF0000, "%d", c_dispTime / 60);
		}
		else {//サドンデス用の表示
			DrawFormatString(410, 140, 0xFF0000, "EXTRA ROUND");
			StopSoundMem(drum);
			DrawFormatString(620, 240, 0xFF0000, "%d", c_dispTime / 60);
		}
	}

	//ボタン押したらゲーム開始
	if (--c_dispTime <= 60 && c_ready == false) {
		c_ready = true;
		c_dispTime = c_dispTimeMax;	//GOの表示時間を代入
	}

	Effect_Draw();
}

void MAIN::Game_Title() {

	if (CheckSoundMem(bgm_title) == 0) {
		PlaySoundMem(bgm_title, DX_PLAYTYPE_LOOP);
	}
	DrawGraph(0, 0, maku[imgC], TRUE);      // 画像を表示
	DrawGraph(500, 400, menu[1], TRUE);
	DrawGraph(500, 500, menu[2], TRUE);

	// 描画する文字列の文字セットを変更します
	ChangeFont("Rampart One");
	SetFontSize(150);
	//DrawFormatString(255, 100, 0x000000, "SpotLight");
	//SetFontSize(150);
	DrawFormatString(250, 100, 0xffff00, "SpotLight");
	if (((g_KeyFlg & PAD_INPUT_DOWN && g_play == false) != 0)) {
		if (CheckSoundMem(cursor_sound) == 0) {
			PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK);
		}
		state += 1;
		if (state >= 2) {
			state = 0;
		}
	}
	else if (((g_KeyFlg & PAD_INPUT_UP && g_play == false) != 0)) {
		if (CheckSoundMem(cursor_sound) == 0) {
			PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK);
		}
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
	}
	if (g_play == true) {
		static int c = 0;
		c++;
		if (c % 3 == 0) {
			imgC--;
		}
	}
	else if (g_exit == true) {
		g_loopFlg = true;
	}
	if (imgC < 0) {
		ChangeFont("Alumni Sans Black");
		g_play = false;
		GameState = 1;
	}
}

void MAIN::Game_Result(MAIN* main) {
	
	StopSoundMem(drum);
	StopSoundMem(bgm_main);
	StopSoundMem(damage_sound);

	//エネミーを描画するために存在させる
	for (int i = 0; i < 3; i++) {
		c_enemy->c_AliveEnemy[i] = true;
	}

	//プレイヤーと敵の点数を調べて、プレイヤーの点数が敵の点数以上ならはいる。
	if (PLAYER_WIN_COUNT >= ENEMY_WIN_COUNT1 &&
		PLAYER_WIN_COUNT >= ENEMY_WIN_COUNT2 &&
		PLAYER_WIN_COUNT >= ENEMY_WIN_COUNT3) {
				if (CheckSoundMem(player_win_sound) == 0) {
					if (BGM_flg == false) {
						PlaySoundMem(player_win_sound, DX_PLAYTYPE_BACK);
						BGM_flg = true;
					}
				}
			
		
	}
	else {
		if (CheckSoundMem(enemy_win_sound) == 0) {
			if (BGM_flg == false) {
				PlaySoundMem(enemy_win_sound, DX_PLAYTYPE_BACK);
				BGM_flg = true;
			}

		}
	}

	//スコアの表示（リザルト画面の描画）
	int score[4];	//スコア格納用の変数　０はプレイヤー用　１～３は適用

	score[0] = PLAYER_WIN_COUNT;
	score[1] = ENEMY_WIN_COUNT1;
	score[2] = ENEMY_WIN_COUNT2;
	score[3] = ENEMY_WIN_COUNT3;

	c_ResultPos[0] = VGet(600.0f, 750.0f, -1200.0f);
	c_ResultPos[1] = VGet(200.0f, 750.0f, -1200.0f);
	c_ResultPos[2] = VGet(-200.0f, 750.0f, -1200.0f);
	c_ResultPos[3] = VGet(-600.0f, 750.0f, -1200.0f);

	//ステージの描画
	MV1SetPosition(c_stage->c_StageModel, VGet(80.0f, 650.0f, -1200.0f));
	MV1SetRotationXYZ(c_stage->c_StageModel, VGet((-30.0f * (DX_PI / 180)), (180.0f * (DX_PI / 180)), 0.0f));
	MV1SetScale(c_stage->c_StageModel, c_stage->c_StageScale);
	MV1DrawModel(c_stage->c_StageModel);

	//キャラクターの描画
	//プレイヤー
	MV1SetPosition(c_player->c_PlayerModel, c_ResultPos[0]);
	MV1SetRotationXYZ(c_player->c_PlayerModel, VGet((30.0f * (DX_PI / 180)), (0.0f * (DX_PI / 180)), 0.0f));
	MV1SetPosition(c_player->c_WinPlayerModel, c_ResultPos[0]);
	MV1SetRotationXYZ(c_player->c_WinPlayerModel, VGet((30.0f * (DX_PI / 180)), (0.0f * (DX_PI / 180)), 0.0f));
	//MV1SetScale(c_player->c_WinPlayerModel, c_player->c_AddPosPlay);

	//敵１の描画
	MV1SetPosition(c_enemy->c_EnemyModel[0], c_ResultPos[1]);
	MV1SetRotationXYZ(c_enemy->c_EnemyModel[0], VGet((30.0f * (DX_PI / 180)), (0.0f * (DX_PI / 180)), 0.0f));
	MV1SetPosition(c_enemy->c_WinEnemyModel[0], c_ResultPos[1]);
	MV1SetRotationXYZ(c_enemy->c_WinEnemyModel[0], VGet((30.0f * (DX_PI / 180)), (0.0f * (DX_PI / 180)), 0.0f));
	//MV1SetScale(c_enemy->c_WinEnemyModel[0], c_player->c_AddPosPlay);

	//敵２の描画
	MV1SetPosition(c_enemy->c_EnemyModel[1], c_ResultPos[2]);
	MV1SetRotationXYZ(c_enemy->c_EnemyModel[1], VGet((30.0f * (DX_PI / 180)), (0.0f * (DX_PI / 180)), 0.0f));
	MV1SetPosition(c_enemy->c_WinEnemyModel[1], c_ResultPos[2]);
	MV1SetRotationXYZ(c_enemy->c_WinEnemyModel[1], VGet((30.0f * (DX_PI / 180)), (0.0f * (DX_PI / 180)), 0.0f));
	//MV1SetScale(c_enemy->c_WinEnemyModel[1], c_player->c_AddPosPlay);

	//敵３の描画
	MV1SetPosition(c_enemy->c_EnemyModel[2], c_ResultPos[3]);
	MV1SetRotationXYZ(c_enemy->c_EnemyModel[2], VGet((30.0f * (DX_PI / 180)), (0.0f * (DX_PI / 180)), 0.0f));
	MV1SetPosition(c_enemy->c_WinEnemyModel[2], c_ResultPos[3]);
	MV1SetRotationXYZ(c_enemy->c_WinEnemyModel[2], VGet((30.0f * (DX_PI / 180)), (0.0f * (DX_PI / 180)), 0.0f));
	//MV1SetScale(c_enemy->c_WinEnemyModel[2], c_player->c_AddPosPlay);


	SetFontSize(150);
	DrawFormatString(400, 50, 0xFF0000, "WINNER IS");

	c_camera->Camera_Result(main);

	//c_camera->Camera_Control(c_stage);

	//if (onecheck == false) {
	//	c_player->c_PlayerModel = MV1LoadModel("Model/Player2.mv1");
	//	onecheck = true;
	//}

	SetFontSize(80);

	//ポイントライトの初期値を設定
	//SetLightPositionHandle(PointLightHandle, VGet(80.0f, 1550.0f, -1200.0f));
	//2秒待って勝者を映す
	if (c_resultdispTime++ >= c_resultdispMaxTime) {
		if (c_OnePass == false) {
			c_VictorNum = CountMaxPoint(score);	//勝者を判定
			c_OnePass = true;
		}

		/*キャラの描画*/
		if (c_VictorNum == 0) {
			MV1DrawModel(c_player->c_WinPlayerModel);//ここは勝者のみ写す
		}
		else {
			MV1DrawModel(c_player->c_PlayerModel);//ここは敗者
		}
		for (int i = 1; i < 4; i++) {
			if (c_VictorNum == i) {
				MV1DrawModel(c_enemy->c_WinEnemyModel[i - 1]);//ここは勝者のみ写す
			}
			else {
				MV1DrawModel(c_enemy->c_EnemyModel[i - 1]);//ここは敗者
			}
		}
		/**/

		//// スポットライトの位置の更新
		//SetLightPositionHandle(SpotLightHandle, VGet(80.0f, 1450.0f, -1200.0f));

		//ポイントライトの初期値を設定
		//SetLightPositionHandle(PointLightHandle, VGet(80.0f, 1550.0f, -1200.0f));
		switch (c_VictorNum)
		{
		case 0:
			DrawFormatString(540, 220, 0xFF0000, "PLAYER!");
			SetLightPositionHandle(SpotLightHandle, VGet(600.0f, 1450.0f, -1250.0f));
			//MV1SetPosition(c_player->c_PlayerModel, VGet(80.0f, 750.0f, -1200.0f));
			//MV1SetRotationXYZ(c_player->c_PlayerModel, VGet((-30.0f * (DX_PI / 180)), (180.0f * (DX_PI / 180)), 0.0f));
			//MV1SetScale(c_player->c_PlayerModel, c_player->c_AddPosPlay);

			//MV1DrawModel(c_player->c_PlayerModel);
			break;
		case 1:
			DrawFormatString(540, 200, 0x0000FF, "ENEMY1!");
			SetLightPositionHandle(SpotLightHandle, VGet(200.0f, 1450.0f, -1250.0f));
			//MV1SetPosition(c_enemy->c_EnemyModel[c_VictorNum - 1], VGet(80.0f, 750.0f, -1200.0f));
			//MV1SetRotationXYZ(c_enemy->c_EnemyModel[c_VictorNum - 1], VGet((-30.0f * (DX_PI / 180)), (180.0f * (DX_PI / 180)), 0.0f));
			//MV1SetScale(c_enemy->c_EnemyModel[c_VictorNum - 1], c_player->c_AddPosPlay);

			//MV1DrawModel(c_enemy->c_EnemyModel[c_VictorNum - 1]);
			break;
		case 2:
			DrawFormatString(540, 200, 0x0000FF, "ENEMY2!");
			SetLightPositionHandle(SpotLightHandle, VGet(-200.0f, 1450.0f, -1250.0f));
			//MV1SetPosition(c_enemy->c_EnemyModel[c_VictorNum - 1], VGet(80.0f, 750.0f, -1200.0f));
			//MV1SetRotationXYZ(c_enemy->c_EnemyModel[c_VictorNum - 1], VGet((-30.0f * (DX_PI / 180)), (180.0f * (DX_PI / 180)), 0.0f));
			//MV1SetScale(c_enemy->c_EnemyModel[c_VictorNum - 1], c_player->c_AddPosPlay);

			//MV1DrawModel(c_enemy->c_EnemyModel[c_VictorNum - 1]);
			break;
		case 3:
			DrawFormatString(540, 200, 0x0000FF, "ENEMY3!");
			SetLightPositionHandle(SpotLightHandle, VGet(-600.0f, 1450.0f, -1250.0f));
			//MV1SetPosition(c_enemy->c_EnemyModel[c_VictorNum - 1], VGet(80.0f, 750.0f, -1200.0f));
			//MV1SetRotationXYZ(c_enemy->c_EnemyModel[c_VictorNum - 1], VGet((-30.0f * (DX_PI / 180)), (180.0f * (DX_PI / 180)), 0.0f));
			//MV1SetScale(c_enemy->c_EnemyModel[c_VictorNum - 1], c_player->c_AddPosPlay);

			//MV1DrawModel(c_enemy->c_EnemyModel[c_VictorNum - 1]);
			break;
		default:
			break;
		}

		if (c_PressBDispTime++ >= c_resultdispMaxTime)
		{
			c_ResultBack = true;
		}
		if (c_ResultBack == true) {
			if (c_PressBDispTime % 100 < 50)DrawFormatString(530, 550, 0x880000, "Press B");
		}

		if ((g_KeyFlg & PAD_INPUT_2) != 0 && c_ResultBack == true) GameState = 0;
	}
	else {//ほぼ常にうつす
		MV1DrawModel(c_player->c_PlayerModel);//
		MV1DrawModel(c_enemy->c_EnemyModel[0]);//
		MV1DrawModel(c_enemy->c_EnemyModel[1]);//
		MV1DrawModel(c_enemy->c_EnemyModel[2]);
	}

	//DrawFormatString(100, 100, 0xFFFFFF, "PLAYER_WIN_NUM:%d", PLAYER_WIN_COUNT);
	//DrawFormatString(100, 120, 0xFFFFFF, "PLAYER_POINT:%d", score[0]);
	//DrawFormatString(500, 100, 0xFFFFFF, "ENEMY1_WIN_NUM:%d", ENEMY_WIN_COUNT1);
	//DrawFormatString(500, 120, 0xFFFFFF, "ENEMY1_POINT:%d", score[1]);
	//DrawFormatString(120, 140, 0xFFFFFF, "ENEMY2_WIN_NUM:%d", ENEMY_WIN_COUNT2);
	//DrawFormatString(120, 160, 0xFFFFFF, "ENEMY2_POINT:%d", score[2]);
	//DrawFormatString(520, 140, 0xFFFFFF, "ENEMY3_WIN_NUM:%d", ENEMY_WIN_COUNT3);
	//DrawFormatString(520, 160, 0xFFFFFF, "ENEMY3_POINT:%d", score[3]);

}

int MAIN::CountMaxPoint(int* point)
{
	int max_score = 0;
	int win_num = 0;

	for (int i = 0; i < 4; i++) {
		if (max_score < point[i]) {
			max_score = point[i];
			win_num = i;
		}
	}

	return win_num;
}

void WIN_Text() {
	int teto = 130;
	DrawBox(955+teto, 30, 1265, 210, 0xFFFFFF, false);

	DrawCircle(990+teto, 61, 15, 0xffffff, true);//player
	DrawCircle(990+teto, 101, 15, 0xec1c24, true);//enemy1
	DrawCircle(990+teto, 141, 15, 0x0ed145, true);//enemy2
	DrawCircle(990+teto, 181, 15, 0xfff200, true);//enemy3
	SetFontSize(40);
	DrawFormatString(1020+teto, 40, 0xFFFFFF,  "YOU　 :%d", PLAYER_WIN_COUNT);
	DrawFormatString(1020+teto, 80, 0xFFFFFF,  "CPU1  :%d", ENEMY_WIN_COUNT1);
	DrawFormatString(1020+teto, 120, 0xFFFFFF, "CPU2 :%d", ENEMY_WIN_COUNT2);
	DrawFormatString(1020+teto, 160, 0xFFFFFF, "CPU3 :%d", ENEMY_WIN_COUNT3);
	
	
}

int MAIN::LoadSound() {
	//ゲーム音読み込み
	if ((bgm_title = LoadSoundMem("GameSound/GameTitle.mp3")) == -1)return -1;
	if ((bgm_main = LoadSoundMem("GameSound/CandyCrush.mp3")) == -1)return -1;
	if ((drum = LoadSoundMem("GameSound/drum1.mp3")) == -1)return -1;
	if ((drum_finish = LoadSoundMem("GameSound/drum_finish.mp3")) == -1)return -1;
	if ((win_sound = LoadSoundMem("GameSound/win_sound.mp3")) == -1)return -1;
	if ((player_win_sound = LoadSoundMem("GameSound/player_win.mp3")) == -1)return-1;
	if ((enemy_win_sound = LoadSoundMem("GameSound/enemy_win.mp3")) == -1)return-1;
	if ((player_attack_sound = LoadSoundMem("GameSound/player_attack.mp3")) == -1)return -1;
	if ((player_attack_false_sound = LoadSoundMem("GameSound/player_attack_false.mp3")) == -1)return -1;
	if ((enemy1_attack_sound = LoadSoundMem("GameSound/enemy1.mp3")) == -1)return -1;
	if ((enemy2_attack_sound = LoadSoundMem("GameSound/enemy2.mp3")) == -1)return -1;
	if ((enemy3_attack_sound = LoadSoundMem("GameSound/enemy3.mp3")) == -1)return -1;
	if ((damage_sound = LoadSoundMem("GameSound/damage.mp3")) == -1)return-1;
	if ((cursor_sound = LoadSoundMem("GameSound/cursor.mp3")) == -1)return-1;
	if ((draw_sound = LoadSoundMem("GameSound/draw.mp3")) == -1)return-1;
	if ((breath_sound = LoadSoundMem("GameSound/ikigire.m4a")) == -1)return-1;
	
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
	ChangeVolumeSoundMem(80, enemy1_attack_sound);
	ChangeVolumeSoundMem(80, enemy2_attack_sound);
	ChangeVolumeSoundMem(80, enemy3_attack_sound);
	ChangeVolumeSoundMem(80, damage_sound);
	ChangeVolumeSoundMem(80, cursor_sound);
	ChangeVolumeSoundMem(80, draw_sound);
	ChangeVolumeSoundMem(80, breath_sound);
	ChangeVolumeSoundMem(80, player_attack_false_sound);

	return 0;
}


//サドンデス用メモ
void MAIN::Sadondes() {
	/*必要なこと
	・敵キャラを存在する敵と存在しない敵にわける
	・タイムが10秒経過後、その後10秒たってもドローしないようにする。
	・Sadondesuフラグを作る
	・ライトはinitでほぼオッケー
	・メインは点数はそのままにするgameStateもそのまま
	・敵のinitもほぼ同じ。存在フラグのみかな
	・charactor.cppは普通にinit
	*/
}

void MAIN::Sadondes_check() {
	//サドンデス後も入ってもらうので一度falseにします。
	Sadondes_flg = false;
	/*ここはデバッグ用です。*/
	//return;
	/*ここはデバッグ用です。*/
	
	//プレイヤーと敵の点数を調べて、プレイヤーの点数が敵の点数以上ならはいる。
	if (PLAYER_WIN_COUNT >= ENEMY_WIN_COUNT1 && 
		PLAYER_WIN_COUNT >= ENEMY_WIN_COUNT2 && 
		PLAYER_WIN_COUNT >= ENEMY_WIN_COUNT3) {

		//その後敵の点数とプレイヤーの点数が同じならサドンデス
		if (PLAYER_WIN_COUNT == ENEMY_WIN_COUNT1) {
			Sadondes_flg = true;
		}
		else {
			//エネミーが存在しないフラグ
			c_enemy->c_AliveEnemy[0] = false;
		}
		if (PLAYER_WIN_COUNT == ENEMY_WIN_COUNT2) {
			Sadondes_flg = true;
		}
		else {
			//エネミーが存在しないフラグ
			c_enemy->c_AliveEnemy[1] = false;
		}
		if (PLAYER_WIN_COUNT == ENEMY_WIN_COUNT3) {
			Sadondes_flg = true;
		}
		else {
			//エネミーが存在しないフラグ
			c_enemy->c_AliveEnemy[2] = false;
		}
	}
	
	
}


void MAIN::Sadondes_Init() {
	//initを新しくつくる
	c_player->init();
	c_enemy->Sadon_init();
	c_stage->init();
	c_camera->init();
	Light_init();

	//タイトルで使う変数初期化
	/*imgC = 17;
	g_play = false;
	g_exit = false;
	state = 0;*/

	//勝敗判定初期化
	finish = true;
	judgefinish = false;
	win_timer = 0;
	WaitTime = 0;
	round_count = 0;



	//ゲーム開始の演出関連変数初期化
	c_ready = false;
	c_dispTime = c_readyMaxTime;
	c_resultdispTime = 0;
	c_PressBDispTime = 0;

	//ライト・リザルト用変数初期化
	LightFlg = false;
	Key_Look = false;
	Win = false;
	Lose = false;
	GameJudge = false;
	judge_win = false;

	//引き分け用変数
	DrawFlg = false;
	draw_timer = 0;
	draw_count = 0;
	//得点は初期化しない
	//PLAYER_WIN_COUNT = 0;
	ENEMY_WIN = 0;
	//ENEMY_WIN_COUNT1 = 0;
	//ENEMY_WIN_COUNT2 = 0;
	//ENEMY_WIN_COUNT3 = 0;

	//スコア計算用リザルトで使用かな？
	c_OnePass = false;
	c_ResultBack = false;
	/*check_1 = 0;
	check_2 = 0;*/

	//BGM_flg = false;//BGMをとめるflg;
	//Enemy_Sound_flg = false;//enemyの攻撃音をとめるflg;//true:止める false:止めない

	//初期化したらゲームメインへ
	//GameState = 2;
}

void MAIN::EffectSeekImport() {
	if ((effectResourceHandle[0] = LoadEffekseerEffect("Effect/Laser01.efkefc", 10.0f)) == -1) {
		int er = 0;
		er = -1;
	}
	// 再生中のエフェクトのハンドルを初期化する。
	playingEffectHandle[0] = -1;
}

void MAIN::Effect_Draw() {
	//// 定期的にエフェクトを再生する
	//if (time_All % 120 == 3)
	//{
	//	// エフェクトを再生する。
	//	playingEffectHandle[0] = PlayEffekseer3DEffect(effectResourceHandle[0]);
	//	// 再生中のエフェクトを移動する。
	//	SetPosPlayingEffekseer3DEffect(playingEffectHandle[0], 100, 100, 0);

	//	// エフェクトの位置をリセットする。
	//	//position_x = 0.0f;
	//}

	//
	///*position_x += 0.2f; */

	//// Effekseerにより再生中のエフェクトを更新する。
	//UpdateEffekseer3D();

	//// Effekseerにより再生中のエフェクトを描画する。
	//DrawEffekseer3D();
}
