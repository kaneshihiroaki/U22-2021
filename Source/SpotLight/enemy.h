#pragma once

#define ENEMY_MAX 3

class ENEMY
{
public:
	ENEMY();
	~ENEMY();

	VECTOR c_AddPosEnemy[ENEMY_MAX];	//�G�l�~�[�̑傫��
	VECTOR c_ObjPos[ENEMY_MAX];		//�I�u�W�F�N�g�̈ʒu
	int c_EnemyModel[ENEMY_MAX];	//�G�l�~�[�̃C���|�[�g�p�ϐ�

	void Enemy_Creat();
private:
};

