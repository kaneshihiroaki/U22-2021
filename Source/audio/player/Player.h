//#pragma once
#include "DxLib.h"

extern void PlayerMove();
extern void GameInit();


struct Player {

	//�c�ړ�
	float x = 0.0f;

	//���ړ�
	float z = 0.0f;

	//�X�s�[�h
	float speed = 3.0f;

	
};

extern VECTOR player1;
extern VECTOR player2;
extern VECTOR player3;
extern VECTOR player4;
//�G
extern VECTOR enemy1;
extern VECTOR enemy2;

//���a
extern float Cap1R;
//���a
extern float Cap2R;

extern int g_NowKey;

extern char key[256];
