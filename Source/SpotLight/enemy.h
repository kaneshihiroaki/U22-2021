#pragma once
#include "Character.h"

#define ENEMY_MAX 3
#define ENEMY_IDLE 0//�X�^�~�i���񕜂��Ă�����
#define ENEMY_MOVE 1//�ړ����Ă�����
#define ENEMY_ATTACK 2//�U�����Ă�����
//#define ENEMY_ATTACK 3


class PLAYER;
class CAMERA;

class ENEMY:public CHARACTER
{
public:
	ENEMY();
	~ENEMY();

	VECTOR c_AddPosEnemy[ENEMY_MAX];	//�G�l�~�[�̑傫��
	VECTOR c_ObjPos[ENEMY_MAX];		//�I�u�W�F�N�g�̈ʒu
	VECTOR c_Rotation[ENEMY_MAX];		//�G�l�~�[�̉�]
	int c_EnemyAng[ENEMY_MAX];		//�G�l�~�[�̊p�x��M_PI���݂ł����ϐ�
	int c_Enemy_MoveAng[ENEMY_MAX];		//�G�l�~�[�̌��݂̊p�x�������ϐ�
	int c_EnemyModel[ENEMY_MAX];	//�G�l�~�[�̃C���|�[�g�p�ϐ�



	VECTOR c_SpotPos;//�X�|�b�g���C�g�̏ꏊ
	float c_SpotRadius = 30.0f;//�X�|�b�g���C�g�̔��a

	void Enemy_Creat();
	void Enemy_Move(int num, PLAYER* player, CAMERA* camera);
	bool Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec);

	//�Q�b�^�[���Z�b�^�[
	bool GetEnemyMoveKey(int i) { return c_MoveKey[i]; }
	//�G�ɍU���𓖂Ă��ۂɎ~�߂鏈��
	void SetEnemyMoveFalseKey(int num) {
		c_MoveKey[num] = false;
	}
	void SetEnemyMoveTrueKey(int num) {
		c_MoveKey[num] = false;
	}
	bool c_MoveKey[ENEMY_MAX];//�G�̓������Ǘ� true:�����Ă��� false:�~�܂��Ă���
	
	int c_EnemyState[ENEMY_MAX];//�G�̏�Ԃ𐧌�#define�ɏ����Ă܂��B
	void Enemy_State(int num, PLAYER* player, CAMERA* camera);//�G�̏�Ԃ𐧌�֐�
	bool EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos);//enemy�̔���
	void debug();		//�f�o�b�O�p�A�p���Ȃ��Ȃ���������܂�
private:
	bool c_MoveFlag;//�G�l�~�[���ړ����Ă���̂�����
	int c_StmCount[ENEMY_MAX];	//�G�̗̑�
	const int c_StmMax = 300;	//�̗͂̍ő�l

	VECTOR c_MoveVector;	//�ړ��ϐ�

	float c_EnemySpeed[ENEMY_MAX];//���݂̃X�s�[�h
	const float c_movespeed = 5.0f;	//�G�l�~�[�ő�ړ��X�s�[�h
	float Coefficient;//�G�l�~�[�̈ړ��W���i�ȂȂ߈ړ��p�j

};

bool Collision_Cube(VECTOR MyCol, VECTOR YouCol, float MyScale, float YouScale);
