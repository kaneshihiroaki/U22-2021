#pragma once
#include "DxLib.h"

class STAGE
{
public:
	STAGE();
	~STAGE();

	int c_StageModel;	//�X�e�[�W�̃C���|�[�g�p�ϐ�
	VECTOR c_StageScale;	//�X�e�[�W�̑傫��
	VECTOR c_StagePosition;	//�X�e�[�W�̈ʒu

	void Stage_Make();	//�X�e�[�W�쐬
	void init();	//������

private:

};