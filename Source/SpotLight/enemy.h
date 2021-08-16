#pragma once
#include "Character.h"

#define ENEMY_MAX 3
#define ENEMY_WIDTH 55
#define ENEMY_HEIGHT 55
#define ENEMY_IDLE 0//スタミナを回復している状態
#define ENEMY_MOVE 1//移動している状態
#define ENEMY_ATTACK 2//攻撃している状態
//#define ENEMY_ATTACK 3

extern int ENEMY_WIN;//どの敵が勝ったか調べる変数
extern int ENEMY_WIN_COUNT1;//敵１の勝利数
extern int ENEMY_WIN_COUNT2;//敵２の勝利数
extern int ENEMY_WIN_COUNT3;//敵３の勝利数

class PLAYER;
class CAMERA;

class ENEMY:public CHARACTER
{
public:
	ENEMY();
	~ENEMY();

	VECTOR c_AddPosEnemy[ENEMY_MAX];	//エネミーの大きさ
	VECTOR c_ObjPos[ENEMY_MAX];		//オブジェクトの位置
	VECTOR c_Rotation[ENEMY_MAX];		//エネミーの回転rad = 度*π/180
	int c_Enemy_MoveAng[ENEMY_MAX];		//エネミーの現在の角度をいれる変数0~359
	int c_EnemyModel[ENEMY_MAX];	//エネミーのインポート用変数


	VECTOR c_EnemyAddVect[ENEMY_MAX];//15フレの間横にベクトルを加えるようにする
	int c_EnemyFrameCount[ENEMY_MAX];//15フレ数える



	VECTOR c_SpotPos;//スポットライトの場所
	float c_SpotRadius = 30.0f;//スポットライトの半径

	void Enemy_Creat();
	void Enemy_Move(int num, PLAYER* player, CAMERA* camera);
	bool Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec);

	//ゲッター＆セッター
	bool GetEnemyMoveKey(int i) { return c_MoveKey[i]; }
	//敵に攻撃を当てた際に止める処理
	void SetEnemyMoveFalseKey(int num) {
		//c_MoveKey[num] = false;

		Damage[num].s_paralyzeKey = true;//しびれた時に呼ばれる

	}
	void SetEnemyMoveTrueKey(int num) {
		c_MoveKey[num] = true;
	}
	bool c_MoveKey[ENEMY_MAX];//敵の動きを管理 true:動いている false:止まっている
	
	int c_EnemyState[ENEMY_MAX];//敵の状態を制御#defineに書いてます。
	void Enemy_State(int num, PLAYER* player, CAMERA* camera);//敵の状態を制御関数
	bool EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos);//enemyの判定
	void debug();		//デバッグ用、用がなくなったら消します
	void init();		//初期化

	void Enemy_Attack(PLAYER* player, int num);//エネミーの攻撃用
	bool CheckPara(int num);//調べたいエネミーがしびれているかどうかの判定

	//痺れ（ダメージ関連）
	struct Damage
	{
		int s_ParaTime = 0;					//プレイヤーが痺れる時間をカウント
		bool s_paralyzeKey = false;		//プレイヤーがしびれているか判定する（true:痺れてる false:痺れていない）
		const int s_MaxTimeParalyze = 30;		//プレイヤーが痺れている時間
	}; Damage Damage[ENEMY_MAX];

private:
	bool c_MoveFlag;//エネミーが移動しているのか判定
	int c_StmCount[ENEMY_MAX];	//敵の体力
	const int c_StmMax = 300;	//体力の最大値

	VECTOR c_MoveVector;	//移動変数

	float c_EnemySpeed[ENEMY_MAX];//現在のスピード
	const float c_movespeed = 5.0f;	//エネミー最大移動スピード
	float Coefficient;//エネミーの移動係数（ななめ移動用）
	bool Collision_Cube2(VECTOR MyCol, VECTOR MyRot, VECTOR YouCol, float MyScale_X, float MyScale_Z, float YouScale_X, float YouScale_Z);
	
	struct Attack {
		//攻撃を行うかどうか判定変数
		bool s_AttackStartKey = false;
		bool s_GetOneRot = false;
		float s_Rang = 0.0f;	//攻撃時間(範囲)

		//攻撃の開始地点を決める変数
		float s_RotSin = 0.0f;
		float s_RotCos = 0.0f;
		float s_Posx = 0.0f;
		float s_Posz = 0.0f;
		const float s_width = 200.0f;
		const float s_heigt = 100.0f;

		//攻撃速度(終了地点)
		const float s_AttackSpeed = 10.0f;
		const float s_RangMax = 500.0f;

		int s_Memo = 0;
		bool s_ParaKey[ENEMY_MAX];
		int s_TimePara = 0;
		const int s_TimeMaxPara = 50;
	}; 
	Attack Att[ENEMY_MAX];

	bool Enemy_AttackCol(VECTOR AttPosRU, VECTOR AttPosLU, VECTOR AttPosRD, VECTOR AttPosLD, VECTOR YouPos, int num, float ang);
	void Enemy_Paralyze(int num);//しびれているときに入る。移動不可にする
};

bool Collision_Cube(VECTOR MyCol, VECTOR MyRot, VECTOR YouCol, float MyScale_X, float MyScale_Z, float YouScale_X, float YouScale_Z);
