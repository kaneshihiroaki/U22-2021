#pragma once

#define ENEMY_MAX 3

class ENEMY
{
public:
	ENEMY();
	~ENEMY();

	VECTOR c_AddPosEnemy[ENEMY_MAX];	//エネミーの大きさ
	VECTOR c_ObjPos[ENEMY_MAX];		//オブジェクトの位置
	int c_EnemyModel[ENEMY_MAX];	//エネミーのインポート用変数

	void Enemy_Creat();
private:
};

