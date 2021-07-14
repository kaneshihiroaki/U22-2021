//#pragma once
#include "DxLib.h"

extern void PlayerMove();
extern void GameInit();


struct Player {

	//�c�ړ�
	float x = 0.0f;

	//���ړ�
	float z = 0.0f;

	//�X�s�[�h
	float speed = 3.0f;

	
};

extern VECTOR player1;
extern VECTOR player2;
extern VECTOR player3;
extern VECTOR player4;
//�G
extern VECTOR enemy1;
extern VECTOR enemy2;

//���a
extern float Cap1R;
//���a
extern float Cap2R;



class PLAYER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//�v���C���[�̃C���|�[�g�p�ϐ�
	VECTOR c_AddPosPlay;	//�v���C���[�̑傫��
	VECTOR c_Position;	//�v���C���[�̈ʒu
	void Player_Creat();
	void Player_Move();


private:
	int    c_MoveFlag;	//�v���C���[���ړ����Ă���̂�����

	VECTOR c_MoveVector;	//�ړ��ϐ�

	const float c_movespeed = 10.0f;	//�v���C���[�ړ��X�s�[�h
};


