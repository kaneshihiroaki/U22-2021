#pragma once
#include "Character.h"

#define ENEMY_MAX 3
#define ENEMY_WIDTH 55
#define ENEMY_HEIGHT 55
#define ENEMY_IDLE 0//�X�^�~�i���񕜂��Ă�����
#define ENEMY_MOVE 1//�ړ����Ă�����
#define ENEMY_ATTACK 2//�U�����Ă�����
//#define ENEMY_ATTACK 3

extern int ENEMY_WIN;//�ǂ̓G�������������ׂ�ϐ�
extern int ENEMY_WIN_COUNT1;//�G�P�̏�����
extern int ENEMY_WIN_COUNT2;//�G�Q�̏�����
extern int ENEMY_WIN_COUNT3;//�G�R�̏�����

class PLAYER;
class CAMERA;

class ENEMY:public CHARACTER
{
public:
	ENEMY();
	~ENEMY();

	VECTOR c_AddPosEnemy[ENEMY_MAX];	//�G�l�~�[�̑傫��
	VECTOR c_ObjPos[ENEMY_MAX];		//�I�u�W�F�N�g�̈ʒu
	VECTOR c_Rotation[ENEMY_MAX];		//�G�l�~�[�̉�]rad = �x*��/180
	int c_Enemy_MoveAng[ENEMY_MAX];		//�G�l�~�[�̌��݂̊p�x�������ϐ�0~359
	int c_EnemyModel[ENEMY_MAX];	//�G�l�~�[�̃C���|�[�g�p�ϐ�


	VECTOR c_EnemyAddVect[ENEMY_MAX];//15�t���̊ԉ��Ƀx�N�g����������悤�ɂ���
	int c_EnemyFrameCount[ENEMY_MAX];//15�t��������



	VECTOR c_SpotPos;//�X�|�b�g���C�g�̏ꏊ
	float c_SpotRadius = 30.0f;//�X�|�b�g���C�g�̔��a

	void Enemy_Creat();
	void Enemy_Move(int num, PLAYER* player, CAMERA* camera);
	bool Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec);

	//�Q�b�^�[���Z�b�^�[
	bool GetEnemyMoveKey(int i) { return c_MoveKey[i]; }
	//�G�ɍU���𓖂Ă��ۂɎ~�߂鏈��
	void SetEnemyMoveFalseKey(int num) {
		//c_MoveKey[num] = false;

		Damage[num].s_paralyzeKey = true;//���тꂽ���ɌĂ΂��

	}
	void SetEnemyMoveTrueKey(int num) {
		c_MoveKey[num] = true;
	}
	bool c_MoveKey[ENEMY_MAX];//�G�̓������Ǘ� true:�����Ă��� false:�~�܂��Ă���
	
	int c_EnemyState[ENEMY_MAX];//�G�̏�Ԃ𐧌�#define�ɏ����Ă܂��B
	void Enemy_State(int num, PLAYER* player, CAMERA* camera);//�G�̏�Ԃ𐧌�֐�
	bool EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos);//enemy�̔���
	void debug();		//�f�o�b�O�p�A�p���Ȃ��Ȃ���������܂�
	void init();		//������

	void Enemy_Attack(PLAYER* player, int num);//�G�l�~�[�̍U���p
	bool CheckPara(int num);//���ׂ����G�l�~�[�����т�Ă��邩�ǂ����̔���

	//Ⴢ�i�_���[�W�֘A�j
	struct Damage
	{
		int s_ParaTime = 0;					//�v���C���[��Ⴢ�鎞�Ԃ��J�E���g
		bool s_paralyzeKey = false;		//�v���C���[�����т�Ă��邩���肷��itrue:Ⴢ�Ă� false:Ⴢ�Ă��Ȃ��j
		const int s_MaxTimeParalyze = 30;		//�v���C���[��Ⴢ�Ă��鎞��
	}; Damage Damage[ENEMY_MAX];

private:
	bool c_MoveFlag;//�G�l�~�[���ړ����Ă���̂�����
	int c_StmCount[ENEMY_MAX];	//�G�̗̑�
	const int c_StmMax = 300;	//�̗͂̍ő�l

	VECTOR c_MoveVector;	//�ړ��ϐ�

	float c_EnemySpeed[ENEMY_MAX];//���݂̃X�s�[�h
	const float c_movespeed = 5.0f;	//�G�l�~�[�ő�ړ��X�s�[�h
	float Coefficient;//�G�l�~�[�̈ړ��W���i�ȂȂ߈ړ��p�j
	bool Collision_Cube2(VECTOR MyCol, VECTOR MyRot, VECTOR YouCol, float MyScale_X, float MyScale_Z, float YouScale_X, float YouScale_Z);
	
	struct Attack {
		//�U�����s�����ǂ�������ϐ�
		bool s_AttackStartKey = false;
		bool s_GetOneRot = false;
		float s_Rang = 0.0f;	//�U������(�͈�)

		//�U���̊J�n�n�_�����߂�ϐ�
		float s_RotSin = 0.0f;
		float s_RotCos = 0.0f;
		float s_Posx = 0.0f;
		float s_Posz = 0.0f;
		const float s_width = 200.0f;
		const float s_heigt = 100.0f;

		//�U�����x(�I���n�_)
		const float s_AttackSpeed = 10.0f;
		const float s_RangMax = 500.0f;

		int s_Memo = 0;
		bool s_ParaKey[ENEMY_MAX];
		int s_TimePara = 0;
		const int s_TimeMaxPara = 50;
	}; 
	Attack Att[ENEMY_MAX];

	bool Enemy_AttackCol(VECTOR AttPosRU, VECTOR AttPosLU, VECTOR AttPosRD, VECTOR AttPosLD, VECTOR YouPos, int num, float ang);
	void Enemy_Paralyze(int num);//���т�Ă���Ƃ��ɓ���B�ړ��s�ɂ���
};

bool Collision_Cube(VECTOR MyCol, VECTOR MyRot, VECTOR YouCol, float MyScale_X, float MyScale_Z, float YouScale_X, float YouScale_Z);
