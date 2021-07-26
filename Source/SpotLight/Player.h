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

	void Player_Creat();
	void Player_Move(float Sin, float Cos);


private:
	int c_MoveFlag;	//�v���C���[���ړ����Ă���̂�����
	//float Sin;		//�J�����̕����Ɉړ�����悤�p�x���擾
	//float Cos;		//�J�����̕����Ɉړ�����悤�p�x���擾
	VECTOR c_MoveVector;	//�ړ��ϐ�

	const float c_movespeed = 5.0f;	//�v���C���[�ړ��X�s�[�h

	ENEMY* c_enemyCol = new ENEMY();		//�G�̍��W���擾���邽�߂Ɏ擾;
	CAMERA* c_cameraAng = new CAMERA();		//�J�����̊p�x���擾���邽�߂Ɏ擾;;

	void Collision_Draw();//�f�o�b�N���[�h�Ŏg�p
};


