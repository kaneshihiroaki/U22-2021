//#pragma once
#include "DxLib.h"

extern void PlayerMove();
extern void GameInit();


struct Player {

	//cˆÚ“®
	float x = 0.0f;

	//‰¡ˆÚ“®
	float z = 0.0f;

	//ƒXƒs[ƒh
	float speed = 3.0f;

	
};

extern VECTOR player1;
extern VECTOR player2;
extern VECTOR player3;
extern VECTOR player4;
//“G
extern VECTOR enemy1;
extern VECTOR enemy2;

//”¼Œa
extern float Cap1R;
//”¼Œa
extern float Cap2R;

extern int g_NowKey;

extern char key[256];
