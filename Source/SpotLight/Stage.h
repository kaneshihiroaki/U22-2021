#pragma once
#include "DxLib.h"

#define SphereAmount 40

class ENEMY;
class PLAYER;

class STAGE
{
public:
	STAGE();
	~STAGE();

	int c_StageModel;	//�X�e�[�W�̃C���|�[�g�p�ϐ�
	VECTOR c_StageScale;	//�X�e�[�W�̑傫��
	VECTOR c_StagePosition;	//�X�e�[�W�̈ʒu

	
	int c_SphereModel[SphereAmount];	//���鋅�̃C���|�[�g�p�ϐ�
	VECTOR c_SpherePosition[SphereAmount];	//���鋅�̂̈ʒu
	VECTOR c_SphereScale;	//���鋅�̂̑傫��
	

	void Stage_Make(ENEMY* enemy, PLAYER* player);	//�X�e�[�W�쐬
	void Stage_Col(ENEMY* enemy,PLAYER* player);		//�����蔻��
	void init();	//������

private:
	//�����Ɖ��s��
	float c_width;
	float c_depth;

};