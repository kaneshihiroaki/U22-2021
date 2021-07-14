//#pragma once
#include "DxLib.h"
#include "enemy.h"
#include "Camera.h"

class PLAYER:public CAMERA
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
	float Sin;		//カメラの方向に移動するよう角度を取得
	float Cos;		//カメラの方向に移動するよう角度を取得
	VECTOR c_MoveVector;	//移動変数

	const float c_movespeed = 10.0f;	//プレイヤー移動スピード

	ENEMY* c_enemyCol = new ENEMY();		//敵の座標を取得するために取得
	CAMERA c_cameraAng = CAMERA();		//カメラの角度を取得するために取得
};


