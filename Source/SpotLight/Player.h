#pragma once
#include "DxLib.h"
#include "enemy.h"
#include "Character.h"

#define CHAR_SIZE_X		55.0f		// �L�����̃T�C�Y
#define CHAR_SIZE_Y		55.0f		// �L�����̃T�C�Y
#define CHAR_SIZE_Z		55.0f		// �L�����̃T�C�Y

class CAMERA;
class ENEMY;
class CHARACTER;

class PLAYER : public CHARACTER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//�v���C���[�̃C���|�[�g�p�ϐ�
	VECTOR c_AddPosPlay;	//�v���C���[�̑傫��
	VECTOR c_Rotation;		//�v���C���[�̉�]
	VECTOR c_Position;	//�v���C���[�̈ʒu

	//�v���C���[�̔�e����
	void SetPlayerParalyze(){
		Damage.s_paralyzeKey = !Damage.s_paralyzeKey;
	}

	void Player_Controller();
	void Player_Move(CAMERA* camera, ENEMY* ene);
	bool Player_Push(CAMERA* camera, VECTOR EnemyCol[ENEMY_MAX], VECTOR PushVec);
	bool CheckHit(VECTOR Player, VECTOR LightPos);

private:
	float c_PlayerAng;		//�v���C���[�̊p�x

	bool c_RotFlag;		//�v���C���[����]���Ă���
	bool c_MoveFlag;	//�v���C���[���ړ����Ă���̂�����
	int c_StmCount;		//�v���C���[�̗̑�
	const int c_StmMax = 300;	//�̗͂̍ő�l
	VECTOR c_MoveVector;	//�ړ��ϐ�

	const float c_movespeed = 5.0f;	//�v���C���[�ړ��X�s�[�h

	//Ⴢ�i�_���[�W�֘A�j
	struct Damage
	{
		int s_ParaTime = 0;					//�v���C���[��Ⴢ�鎞�Ԃ��J�E���g
		bool s_paralyzeKey = false;		//�v���C���[�����т�Ă��邩���肷��itrue:Ⴢ�Ă� false:Ⴢ�Ă��Ȃ��j
		const int s_MaxTimeParalyze = 30;		//�v���C���[��Ⴢ�Ă��鎞��
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
	
	void Collision_Draw(VECTOR EnemyPos[ENEMY_MAX]);//�f�o�b�N���[�h�Ŏg�p
	void Player_Paralyze();	//��l�������т��i�~�܂�j
	void Player_Attack(ENEMY* ene,VECTOR Player_rot);		//�U��

	ENEMY* c_enemyCol;		//�G�̍��W���擾���邽�߂Ɏ擾
};


