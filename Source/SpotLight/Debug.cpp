#include "Debug.h"
#include "DxLib.h"

//extern変数
int DebugNum = 1;
bool DebugMode = false;

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
	
}


void CameraFree() {
	DebugMode = false;
}