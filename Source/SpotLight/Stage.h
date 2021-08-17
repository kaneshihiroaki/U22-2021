#pragma once
#include "DxLib.h"

class ENEMY;
class PLAYER;
class CHARACTER;

class STAGE
{
public:
	STAGE();
	~STAGE();

	int c_StageModel;	//�X�e�[�W�̃C���|�[�g�p�ϐ�
	VECTOR c_StageScale;	//�X�e�[�W�̑傫��
	VECTOR c_StagePosition;	//�X�e�[�W�̈ʒu

	void Stage_Make(ENEMY* enemy, PLAYER* player);	//�X�e�[�W�쐬
	void Stage_Col(ENEMY* enemy,PLAYER* player);		//�����蔻��
	void init();	//������

private:
	//�����Ɖ��s��
	float c_width;
	float c_depth;

};