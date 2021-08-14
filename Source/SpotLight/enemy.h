#pragma once
#include "Character.h"

#define ENEMY_MAX 3
#define ENEMY_IDLE 0//スタミナを回復している状態
#define ENEMY_MOVE 1//移動している状態
#define ENEMY_ATTACK 2//攻撃している状態
//#define ENEMY_ATTACK 3


class PLAYER;
class CAMERA;

class ENEMY:public CHARACTER
{
public:
	ENEMY();
	~ENEMY();

	VECTOR c_AddPosEnemy[ENEMY_MAX];	//エネミーの大きさ
	VECTOR c_ObjPos[ENEMY_MAX];		//オブジェクトの位置
	VECTOR c_Rotation[ENEMY_MAX];		//エネミーの回転
	int c_EnemyAng[ENEMY_MAX];		//エネミーの角度をM_PI込みでいれる変数
	int c_Enemy_MoveAng[ENEMY_MAX];		//エネミーの現在の角度をいれる変数
	int c_EnemyModel[ENEMY_MAX];	//エネミーのインポート用変数



	VECTOR c_SpotPos;//スポットライトの場所
	float c_SpotRadius = 30.0f;//スポットライトの半径

	void Enemy_Creat();
	void Enemy_Move(int num, PLAYER* player, CAMERA* camera);
	bool Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec);

	//ゲッター＆セッター
	bool GetEnemyMoveKey(int i) { return c_MoveKey[i]; }
	//敵に攻撃を当てた際に止める処理
	void SetEnemyMoveFalseKey(int num) {
		c_MoveKey[num] = false;
	}
	void SetEnemyMoveTrueKey(int num) {
		c_MoveKey[num] = false;
	}
	bool c_MoveKey[ENEMY_MAX];//敵の動きを管理 true:動いている false:止まっている
	
	int c_EnemyState[ENEMY_MAX];//敵の状態を制御#defineに書いてます。
	void Enemy_State(int num, PLAYER* player, CAMERA* camera);//敵の状態を制御関数
	bool EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos);//enemyの判定
	void debug();		//デバッグ用、用がなくなったら消します
private:
	bool c_MoveFlag;//エネミーが移動しているのか判定
	int c_StmCount[ENEMY_MAX];	//敵の体力
	const int c_StmMax = 300;	//体力の最大値

	VECTOR c_MoveVector;	//移動変数

	float c_EnemySpeed[ENEMY_MAX];//現在のスピード
	const float c_movespeed = 5.0f;	//エネミー最大移動スピード
	float Coefficient;//エネミーの移動係数（ななめ移動用）

};

bool Collision_Cube(VECTOR MyCol, VECTOR YouCol, float MyScale, float YouScale);
