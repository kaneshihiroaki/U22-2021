//#pragma once
#include "DxLib.h"
#include "enemy.h"

#define CHAR_SIZE_X		55.0f		// �L�����̃T�C�Y
#define CHAR_SIZE_Y		55.0f		// �L�����̃T�C�Y
#define CHAR_SIZE_Z		55.0f		// �L�����̃T�C�Y

class PLAYER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//�v���C���[�̃C���|�[�g�p�ϐ�
	VECTOR c_AddPosPlay;	//�v���C���[�̑傫��
	VECTOR c_Position;	//�v���C���[�̈ʒu

	void Player_Controller(float Sin, float Cos);

private:
	bool c_MoveFlag;	//�v���C���[���ړ����Ă���̂�����
	VECTOR c_MoveVector;	//�ړ��ϐ�

	const float c_movespeed = 5.0f;	//�v���C���[�ړ��X�s�[�h

	//Ⴢ�i�_���[�W�֘A�j
	struct Damage
	{
		int s_ParaTime = 0;					//�v���C���[��Ⴢ�鎞�Ԃ��J�E���g
		bool s_paralyzeKey = false;		//�v���C���[�����т�Ă��邩���肷��itrue:Ⴢ�Ă� false:Ⴢ�Ă��Ȃ��j
		const int s_MaxTimeParalyze = 30;		//�v���C���[��Ⴢ�Ă��鎞��
	}; Damage Damage;

	//�X�^�~�i�֘A
	struct Stamina
	{
		int s_Count = 300;		//�����Ă��鎞�Ԃ��J�E���g
		const int s_StaminaMax = 300;		//�X�^�~�i�̍ő�l
	}; Stamina Stamina;

	struct Attack {
		bool s_AttackStartKey = false;
		float s_Rang = 0.0f;
		const float s_AttackSpeed = 10.0f;
		const float s_RangMax = 200.0f;
	}; Attack Att;

	void Player_Move(float Sin, float Cos);
	void Collision_Draw();//�f�o�b�N���[�h�Ŏg�p
	void Player_Paralyze();	//��l�������т��i�~�܂�j
	void Player_StaminaCount();	//�v���C���[�X�^�~�i�J�E���g
	void Player_Attack();		//�U��

	ENEMY* c_enemyCol = new ENEMY();		//�G�̍��W���擾���邽�߂Ɏ擾
};


