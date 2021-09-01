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

//extern int check_1;//����m�F�̂��߂̕ϐ�
//extern int check_2;

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
	int c_WinEnemyModel[ENEMY_MAX];	//�����G�l�~�[�̃C���|�[�g�p�ϐ�


	VECTOR c_EnemyAddVect[ENEMY_MAX];//15�t���̊ԉ��Ƀx�N�g����������悤�ɂ���
	int c_EnemyFrameCount[ENEMY_MAX];//15�t��������



	VECTOR c_SpotPos;//�X�|�b�g���C�g�̏ꏊ
	float c_SpotRadius = 30.0f;//�X�|�b�g���C�g�̔��a
	bool c_EnemyWin[ENEMY_MAX] = { false,false,false };//�G�l�~�[���������肳��Ă��邩�ǂ���

	void Enemy_Creat();
	void Enemy_Move(int num, PLAYER* player, ENEMY* enemy);
	bool Enemy_Push(int num, PLAYER* player, ENEMY* enemy,  VECTOR PushVec,int count);

	//�G��Ⴢꂳ����Z�b�^�[
	void SetEnemyParaKey(int num) {
		Damage[num].s_paralyzeKey = true;//���тꂽ���ɌĂ΂��
	}

	//�G���X�e�[�W�̊O�ɍs���Ȃ��悤�ɂ���
	void SetEnemyStageOutKey(int num) {
		c_MoveKey[num] = false;
	}
	void SetEnemyStageInKey(int num) {
		c_MoveKey[num] = true;
	}
	VECTOR GetEnemyMoveKey(int i) { return VAdd(c_ObjPos[i], c_TempMoveVector[i]); }
	bool c_MoveKey[ENEMY_MAX];//�X�e�[�W���̓G�̓������Ǘ� true:�����Ă��� false:�~�܂��Ă���
	
	int c_EnemyState[ENEMY_MAX];//�G�̏�Ԃ𐧌�#define�ɏ����Ă܂��B
	void Enemy_State(int num, PLAYER* player, ENEMY* enemy);//�G�̏�Ԃ𐧌�֐�
	int EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos);//enemy�̔���

	void debug();		//�f�o�b�O�p�A�p���Ȃ��Ȃ���������܂�
	void init();		//������

	void Enemy_Attack(PLAYER* player, int num);//�G�l�~�[�̍U���p
	int c_AttackStm = 60;//�U���ɂ�����X�^�~�i
	bool CheckPara(int num);//���ׂ����G�l�~�[�����т�Ă��邩�ǂ����̔���

	//Ⴢ�i�_���[�W�֘A�j
	struct Damage
	{
		int s_ParaTime = 0;					//�v���C���[��Ⴢ�鎞�Ԃ��J�E���g
		bool s_paralyzeKey = false;		//�v���C���[�����т�Ă��邩���肷��itrue:Ⴢ�Ă� false:Ⴢ�Ă��Ȃ��j
		const int s_MaxTimeParalyze = 60;		//�v���C���[��Ⴢ�Ă��鎞��
	}; Damage Damage[ENEMY_MAX];

	
	void Ga_Attack(int num, PLAYER* player);//�������[�̍U���֐�
	void Ga_Move(int num, PLAYER* player);//�ړ��֐�
	int Ga_Interval[ENEMY_MAX] = { 0,0,0 };//�U���̃C���^�[�o��
	int Ga_Debug_Interval = 90;//�������[�̃C���^�[�o����

	void A_Move(int num);//�A�X�J�̈ړ��֐�
	void A_Attack(int num, PLAYER* player);//�A�X�J�̍U���֐�
	int A_Debug_Interval = 90;//�A�X�J�̃C���^�[�o����
	//�U���̃C���^�[�o���͂������[��Ga_Interval���g���܂�

	void San_Move(int num);//�T���O���X�̈ړ��֐�
	void San_Attack(int num, PLAYER* player);//�T���O���X�̍U���֐�
	int San_Debug_Interval = 40;//�T���O���X�̃C���^�[�o����
	//�U���̃C���^�[�o���͂������[��Ga_Interval���g���܂�

	void Bot_Normal(int num, PLAYER* player);//�]���̓G�W���j�[�Y�N

private:
	bool c_MoveFlag;//�G�l�~�[���ړ����Ă���̂�����
	int c_StmCount[ENEMY_MAX];	//�G�̗̑�
	const int c_StmMax = 300;	//�̗͂̍ő�l

	VECTOR c_MoveVector;	//�ړ��ϐ�
	VECTOR c_TempMoveVector[ENEMY_MAX];	//�ړ���v�Z�p�ϐ�

	float c_EnemySpeed[ENEMY_MAX];//���݂̃X�s�[�h
	const float c_movespeed = 10.0f;	//�G�l�~�[�ő�ړ��X�s�[�h
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
		const float s_width = 80.0f;
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
