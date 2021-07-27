//#pragma once
#include "DxLib.h"
#include "enemy.h"
#include "Camera.h"
#include "Math.h"

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
	int c_MoveFlag;	//�v���C���[���ړ����Ă���̂�����
	bool c_paralyzeKey = false;		//�v���C���[�����т�Ă��邩���肷��itrue:Ⴢ�Ă� false:Ⴢ�Ă��Ȃ��j
	int c_ParaTime = 0;					//�v���C���[��Ⴢ�鎞�Ԃ��J�E���g
	VECTOR c_MoveVector;	//�ړ��ϐ�

	const float c_movespeed = 5.0f;	//�v���C���[�ړ��X�s�[�h
	const int c_TimeParalyze = 6;		//�v���C���[��Ⴢ�Ă��鎞��

	ENEMY* c_enemyCol = new ENEMY();		//�G�̍��W���擾���邽�߂Ɏ擾;
	CAMERA* c_cameraAng = new CAMERA();		//�J�����̊p�x���擾���邽�߂Ɏ擾;;

	//�X�^�~�i�֘A
	struct Stamina
	{
		int s_Count = 300;		//�����Ă��鎞�Ԃ��J�E���g
		bool s_Key = true;		//�����Ă��邩�ǂ�������
		const int s_StaminaMax = 300;		//�X�^�~�i�̍ő�l
	}; Stamina Stamina;

	void Player_Move(float Sin, float Cos);
	void Collision_Draw();//�f�o�b�N���[�h�Ŏg�p
	void Player_Paralyze();	//��l�������т��i�~�܂�j
	void Player_StaminaCount();

	CAMERA* c_camera = new CAMERA();
};


