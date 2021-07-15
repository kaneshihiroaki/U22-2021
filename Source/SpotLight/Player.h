//#pragma once
#include "DxLib.h"
#include "Camera.h"
#include "enemy.h"

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

	ENEMY* c_enemyCol = new ENEMY();		//敵の座標を取得するために取得;
	CAMERA* c_cameraAng = new CAMERA();		//カメラの角度を取得するために取得;
private:
	int c_MoveFlag;	//プレイヤーが移動しているのか判定
	float Sin;		//カメラの方向に移動するよう角度を取得
	float Cos;		//カメラの方向に移動するよう角度を取得
	VECTOR c_MoveVector;	//移動変数

	const float c_movespeed = 10.0f;	//プレイヤー移動スピード
};


