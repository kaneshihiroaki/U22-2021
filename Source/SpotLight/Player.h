//#pragma once
#include "DxLib.h"

extern void PlayerMove();
extern void GameInit();


struct Player {

	//縦移動
	float x = 0.0f;

	//横移動
	float z = 0.0f;

	//スピード
	float speed = 3.0f;

	
};

extern VECTOR player1;
extern VECTOR player2;
extern VECTOR player3;
extern VECTOR player4;
//敵
extern VECTOR enemy1;
extern VECTOR enemy2;

//半径
extern float Cap1R;
//半径
extern float Cap2R;



class PLAYER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//プレイヤーのインポート用変数
	VECTOR c_AddPosPlay;	//プレイヤーの大きさ
	VECTOR c_Position;	//プレイヤーの位置
	void Player_Creat();
	void Player_Move();


private:
	int    c_MoveFlag;	//プレイヤーが移動しているのか判定

	VECTOR c_MoveVector;	//移動変数

	const float c_movespeed = 10.0f;	//プレイヤー移動スピード
};


