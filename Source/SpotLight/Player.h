//#pragma once
#include "DxLib.h"
#include "enemy.h"
#include "Camera.h"
#include "Math.h"

#define CHAR_SIZE_X		55.0f		// キャラのサイズ
#define CHAR_SIZE_Y		55.0f		// キャラのサイズ
#define CHAR_SIZE_Z		55.0f		// キャラのサイズ

class PLAYER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//プレイヤーのインポート用変数
	VECTOR c_AddPosPlay;	//プレイヤーの大きさ
	VECTOR c_Position;	//プレイヤーの位置

	void Player_Controller(float Sin, float Cos);

private:
	int c_MoveFlag;	//プレイヤーが移動しているのか判定
	bool c_paralyzeKey = false;		//プレイヤーがしびれているか判定する（true:痺れてる false:痺れていない）
	int c_ParaTime = 0;					//プレイヤーが痺れる時間をカウント
	VECTOR c_MoveVector;	//移動変数

	const float c_movespeed = 5.0f;	//プレイヤー移動スピード
	const int c_TimeParalyze = 6;		//プレイヤーが痺れている時間

	ENEMY* c_enemyCol = new ENEMY();		//敵の座標を取得するために取得;
	CAMERA* c_cameraAng = new CAMERA();		//カメラの角度を取得するために取得;;

	//スタミナ関連
	struct Stamina
	{
		int s_Count = 300;		//動いている時間をカウント
		bool s_Key = true;		//動いているかどうか判定
		const int s_StaminaMax = 300;		//スタミナの最大値
	}; Stamina Stamina;

	void Player_Move(float Sin, float Cos);
	void Collision_Draw();//デバックモードで使用
	void Player_Paralyze();	//主人公がしびれる（止まる）
	void Player_StaminaCount();

	CAMERA* c_camera = new CAMERA();
};


