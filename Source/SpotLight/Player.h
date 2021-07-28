//#pragma once
#include "DxLib.h"
#include "enemy.h"

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
	bool c_MoveFlag;	//プレイヤーが移動しているのか判定
	VECTOR c_MoveVector;	//移動変数

	const float c_movespeed = 5.0f;	//プレイヤー移動スピード

	//痺れ（ダメージ関連）
	struct Damage
	{
		int s_ParaTime = 0;					//プレイヤーが痺れる時間をカウント
		bool s_paralyzeKey = false;		//プレイヤーがしびれているか判定する（true:痺れてる false:痺れていない）
		const int s_MaxTimeParalyze = 30;		//プレイヤーが痺れている時間
	}; Damage Damage;

	//スタミナ関連
	struct Stamina
	{
		int s_Count = 300;		//動いている時間をカウント
		const int s_StaminaMax = 300;		//スタミナの最大値
	}; Stamina Stamina;

	struct Attack {
		bool s_AttackStartKey = false;
		float s_Rang = 0.0f;
		const float s_AttackSpeed = 10.0f;
		const float s_RangMax = 200.0f;
	}; Attack Att;

	void Player_Move(float Sin, float Cos);
	void Collision_Draw();//デバックモードで使用
	void Player_Paralyze();	//主人公がしびれる（止まる）
	void Player_StaminaCount();	//プレイヤースタミナカウント
	void Player_Attack();		//攻撃

	ENEMY* c_enemyCol = new ENEMY();		//敵の座標を取得するために取得
};


