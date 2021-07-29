#include "Debug.h"
#include "DxLib.h"

//extern変数
int DebugNum = 1;
bool DebugMode = false;
bool Collision_Player = false;
bool GamePadIn_bool = false;

bool GameJudge = false;//勝敗変数
bool Win = false;
bool Lose = false;

//Keyを制御する変数
bool Key_Look = false;

bool Build_bool = true;//ビルドの日付をけす用にする。

const char data[] = __DATE__;//ビルド時の日付や時間
const char time[] = __TIME__;

//ローカル変数（private変数）
float version;



int DebugCom() {
	//デバックモードじゃないなら帰る
	if (DebugMode == false) {
		GamePadIn_bool = false;
		return 0;
	}
	if (((g_NowKey & PAD_INPUT_DOWN) != 0) && ((g_NowKey & g_OldKey) == 0)) {
		if (++DebugNum >10) {
			DebugNum = 1;
		}
	}
	if (((g_NowKey & PAD_INPUT_UP) != 0) && ((g_NowKey & g_OldKey) == 0)) {
		if (--DebugNum < 1) {
			DebugNum = 10;
		}
	}

	if (GamePadIn_bool) {
		GamePadIn();
	}
	else {
		DebugDrawing();
	}
	
	if (((g_NowKey & PAD_INPUT_2) != 0) && ((g_NowKey & g_OldKey) == 0)) {
		//操作
		switch (DebugNum)
		{
		case 1:
			CameraFree();
			break;
		case 2:
			Collision_player();
			break;
		case 3:
			if (GamePadIn_bool) {
				GamePadIn_bool = false;
			}
			else {
				GamePadIn_bool = true;
			}
			break;
		case 4:
			Build_In();
			break;
		case 5:
			Game_Judge_In();
			break;
		default:
			break;
		}
	}

	
	return -1;
}


void DebugDrawing() {
	for (int i = 0; i < 10; i++) {
		DrawBox(40, 20 + (i * 20), 200, 40 + (i * 20), GetColor(0xbb, 0xbb, 0xbb), true);
		DrawBox(40, 20 + (i * 20), 200, 40 + (i * 20), GetColor(0x00, 0x00, 0x00), false);
	}

	DrawBox(40, 20 + ((DebugNum - 1) * 20), 200, 40 + ((DebugNum - 1) * 20), GetColor(0x00, 0x00, 0x00), true);

	// 文字列の描画
	SetFontSize(16);
	DrawString(50, 21, "FreeCamera", GetColor(0x00, 0xff, 0xff));
	DrawString(50, 41, "Player_collision", GetColor(0x00, 0xff, 0xff));
	DrawString(50, 61, "GamePad_State", GetColor(0x00, 0xff, 0xff));
	DrawString(50, 81, "Build_Time", GetColor(0x00, 0xff, 0xff));
	DrawString(50, 101, "Game_Judge", GetColor(0x00, 0xff, 0xff));
}


void CameraFree() {
	DebugMode = false;
}

void Build_Time() {

	static int month = 0;	//月
	switch (data[0]) {
	case 'J':
		if (data[2] == 'a') month = 1;
		if (data[2] == 'u') {
			if (data[3] == 'n') month = 6;
			if (data[3] == 'l') month = 7;
		}
		break;
	case 'F': month = 2; break;
	case 'M':
		if (data[2] == 'r') month = 2;
		if (data[2] == 'y') month = 5;
		break;
	case 'A':
		if (data[2] == 'r') month = 4;
		if (data[2] == 'g') month = 8;
		break;
	case 'S': month = 9; break;
	case 'O': month = 10; break;
	case 'N': month = 11; break;
	case 'D': month = 12; break;
	}

	SetFontSize(18);
	DrawFormatString(1000, 10, 0x000000, "最終ビルド日時\n %c%c%c%c %c%c%c %c%c\n  %s",
		data[7], data[8], data[9], data[10],
		data[0], data[1], data[2],
		data[4], data[5],
		time);

	version = 0.02f;		//ビルドのバージョン、金曜日がくるたびに数値を上げて更新すること
	//printfDx("ver%.2f", version);

	DrawFormatString(10, 10, 0x000000, "ver%.2f",version);

}

void Collision_player() {
	if (Collision_Player) {
		Collision_Player = false;
	}
	else {
		Collision_Player = true;
	}

	DebugMode = false;
}

void GamePadIn() {

	DINPUT_JOYSTATE input;

	// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
	int num;
	int Color;

	// 画面に構造体の中身を描画
	Color = GetColor(0, 255, 255);
	DrawFormatString(0, 0, Color, "X:%d Y:%d Z:%d",
		input.X, input.Y, input.Z);
	DrawFormatString(0, 16, Color, "Rx:%d Ry:%d Rz:%d",
		input.Rx, input.Ry, input.Rz);
	DrawFormatString(0, 32, Color, "Slider 0:%d 1:%d",
		input.Slider[0], input.Slider[1]);
	DrawFormatString(0, 48, Color, "POV 0:%d 1:%d 2:%d 3:%d",
		input.POV[0], input.POV[1],
		input.POV[2], input.POV[3]);
	DrawString(0, 64, "Button", Color);
	for (num = 0; num < 32; num++)
	{
		DrawFormatString(64 + num % 8 * 64, 64 + num / 8 * 16, Color,
			"%2d:%d", num, input.Buttons[num]);
	}

	
}

void Build_In() {
	if (Build_bool) {
		Build_bool = false;
	}
	else {
		Build_bool = true;
	}
	DebugMode = false;
}

void Game_Judge_In() {
	if (GameJudge) {

		GameJudge = false;
		Key_Look = false;
		Win = false;
		Lose = false;
	}
	else {

		GameJudge = true;
	}
	DebugMode = false;
}

void Game_Judge() {


	if (((g_NowKey & PAD_INPUT_4) != 0)) {
		Win = true;
		Lose = false;
	}
	if (((g_NowKey & PAD_INPUT_3) != 0)) {
		Win = false;
		Lose = true;
	}

	if (Win == true && Lose == false) {
		Key_Look = true;
		SetFontSize(200);
		DrawString(490, 120, "Win", GetColor(0xff, 0x00, 0x00));
	}
	if (Lose == true && Win == false) {
		Key_Look = true;
		SetFontSize(200);
		DrawString(440, 120, "Lose", GetColor(0x00, 0x00, 0xff));
	}


}
