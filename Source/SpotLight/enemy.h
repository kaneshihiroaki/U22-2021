#pragma once

#define ENEMY_MAX 3

class PLAYER;

class ENEMY
{
public:
	ENEMY();
	~ENEMY();

	VECTOR c_AddPosEnemy[ENEMY_MAX];	//エネミーの大きさ
	VECTOR c_ObjPos[ENEMY_MAX];		//オブジェクトの位置
	int c_EnemyModel[ENEMY_MAX];	//エネミーのインポート用変数

	VECTOR c_SpotPos;//スポットライトの場所
	float c_SpotRadius = 30.0f;//スポットライトの半径

	void Enemy_Creat();
	void Enemy_Move(int num, VECTOR PlayerCol);

	//ゲッター＆セッター
	bool GetEnemyMoveKey(int i) { return c_MoveKey[i]; }
	void SetEnemyMoveKey(bool key, int num) {
		//printfDx("%d \n", GetEnemyMoveKey(2));
		c_MoveKey[num] = key;
	}
	bool c_MoveKey[ENEMY_MAX];//敵の動きを管理 true:動いている false:止まっている

	void debug();		//デバッグ用、用がなくなったら消します
private:
	bool c_MoveFlag;//エネミーが移動しているのか判定

	VECTOR c_MoveVector;	//移動変数

	const float c_movespeed = 5.0f;	//エネミー移動スピード
	float Coefficient;//エネミーの移動係数（ななめ移動用）

};

bool Collision_Cube(VECTOR MyCol, VECTOR YouCol, float MyScale, float YouScale);
