#pragma once
#include "Character.h"

#define ENEMY_MAX 3

class PLAYER;
class CAMERA;

class ENEMY:public CHARACTER
{
public:
	ENEMY();
	~ENEMY();

	VECTOR c_AddPosEnemy[ENEMY_MAX];	//�G�l�~�[�̑傫��
	VECTOR c_ObjPos[ENEMY_MAX];		//�I�u�W�F�N�g�̈ʒu
	int c_EnemyModel[ENEMY_MAX];	//�G�l�~�[�̃C���|�[�g�p�ϐ�

	VECTOR c_SpotPos;//�X�|�b�g���C�g�̏ꏊ
	float c_SpotRadius = 30.0f;//�X�|�b�g���C�g�̔��a

	void Enemy_Creat();
	void Enemy_Move(int num, PLAYER* player, CAMERA* camera);
	bool Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec);

	//�Q�b�^�[���Z�b�^�[
	bool GetEnemyMoveKey(int i) { return c_MoveKey[i]; }
	void SetEnemyMoveKey(int num) {
		c_MoveKey[num] = !c_MoveKey[num];
	}
	bool c_MoveKey[ENEMY_MAX];//�G�̓������Ǘ� true:�����Ă��� false:�~�܂��Ă���

	void debug();		//�f�o�b�O�p�A�p���Ȃ��Ȃ���������܂�
private:
	bool c_MoveFlag;//�G�l�~�[���ړ����Ă���̂�����
	int c_StmCount[ENEMY_MAX];	//�G�̗̑�

	VECTOR c_MoveVector;	//�ړ��ϐ�

	const float c_movespeed = 5.0f;	//�G�l�~�[�ړ��X�s�[�h
	float Coefficient;//�G�l�~�[�̈ړ��W���i�ȂȂ߈ړ��p�j

};

bool Collision_Cube(VECTOR MyCol, VECTOR YouCol, float MyScale, float YouScale);
