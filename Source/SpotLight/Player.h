#pragma once
#include "DxLib.h"
#include "enemy.h"
#include "Character.h"

#define CHAR_SIZE_X		55.0f		// キャラのサイズ
#define CHAR_SIZE_Y		55.0f		// キャラのサイズ
#define CHAR_SIZE_Z		55.0f		// キャラのサイズ

class CAMERA;
class ENEMY;
class CHARACTER;

class PLAYER : public CHARACTER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//プレイヤーのインポート用変数
	VECTOR c_AddPosPlay;	//プレイヤーの大きさ
	VECTOR c_Rotation;		//プレイヤーの回転
	VECTOR c_Position;	//プレイヤーの位置

	//プレイヤーの被弾判定
	void SetPlayerParalyze(){
		Damage.s_paralyzeKey = !Damage.s_paralyzeKey;
	}

	void Player_Controller();
	void Player_Move(CAMERA* camera, ENEMY* ene);
	bool Player_Push(CAMERA* camera, VECTOR EnemyCol[ENEMY_MAX], VECTOR PushVec);
	bool CheckHit(VECTOR Player, VECTOR LightPos);

private:
	float c_PlayerAng;		//プレイヤーの角度

	bool c_RotFlag;		//プレイヤーが回転している
	bool c_MoveFlag;	//プレイヤーが移動しているのか判定
	int c_StmCount;		//プレイヤーの体力
	const int c_StmMax = 300;	//体力の最大値
	VECTOR c_MoveVector;	//移動変数

	const float c_movespeed = 5.0f;	//プレイヤー移動スピード

	//痺れ（ダメージ関連）
	struct Damage
	{
		int s_ParaTime = 0;					//プレイヤーが痺れる時間をカウント
		bool s_paralyzeKey = false;		//プレイヤーがしびれているか判定する（true:痺れてる false:痺れていない）
		const int s_MaxTimeParalyze = 30;		//プレイヤーが痺れている時間
	}; Damage Damage;

	struct Attack {
		bool s_AttackStartKey = false;
		float s_Rang = 0.0f;
		const float s_AttackSpeed = 10.0f;
		const float s_RangMax = 500.0f;

		int s_Memo=0;
		bool s_ParaKey[ENEMY_MAX];
		int s_TimePara = 0;
		const int s_TimeMaxPara = 50;
	}; Attack Att;
	
	void Collision_Draw(VECTOR EnemyPos[ENEMY_MAX]);//デバックモードで使用
	void Player_Paralyze();	//主人公がしびれる（止まる）
	void Player_Attack(ENEMY* ene,VECTOR Player_rot);		//攻撃

	ENEMY* c_enemyCol;		//敵の座標を取得するために取得
};


