//#pragma once
#include "DxLib.h"
#include "enemy.h"

#define CHAR_SIZE_X		55.0f		// キャラのサイズ
#define CHAR_SIZE_Y		55.0f		// キャラのサイズ
#define CHAR_SIZE_Z		55.0f		// キャラのサイズ

class CAMERA;
class ENEMY;

class PLAYER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//プレイヤーのインポート用変数
	VECTOR c_AddPosPlay;	//プレイヤーの大きさ
	VECTOR c_Position;	//プレイヤーの位置

	void Player_Controller();
	void Player_Move(CAMERA* camera, ENEMY* ene);

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

		int s_Memo=0;
		bool s_ParaKey[ENEMY_MAX];
		int s_TimePara = 0;
		const int s_TimeMaxPara = 50;
	}; Attack Att;
	
	void Collision_Draw(VECTOR EnemyPos[ENEMY_MAX]);//デバックモードで使用
	void Player_Paralyze();	//主人公がしびれる（止まる）
	void Player_StaminaCount();	//プレイヤースタミナカウント
	void Player_Attack(ENEMY* ene);		//攻撃

	ENEMY* c_enemyCol;		//敵の座標を取得するために取得
};


