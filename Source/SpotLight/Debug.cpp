#include "Debug.h"
#include "DxLib.h"

//extern変数
int DebugNum = 1;
bool DebugMode = false;
bool Collision_Player = false;


//ビルド時の日付や時間
const char data[] = __DATE__;
const char time[] = __TIME__;

//ローカル変数（private変数）



int DebugCom() {
	//デバックモードじゃないなら帰る
	if (DebugMode == false) {
		
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

	DebugDrawing();
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
	DrawString(50, 21, "FreeCamera", GetColor(0x00, 0xff, 0xff));
	DrawString(50, 41, "Player_collision", GetColor(0x00, 0xff, 0xff));
	
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
	DrawFormatString(500, 10, 0x000000, "最終ビルド日時\n %c%c%c%c %c%c%c %c%c\n  %s",
		data[7], data[8], data[9], data[10],
		data[0], data[1], data[2],
		data[4], data[5],
		time);
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
