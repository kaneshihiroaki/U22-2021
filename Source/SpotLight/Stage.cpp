#include "Stage.h"


STAGE::STAGE()
{
	//// ���W������
	//c_StagePosition = VGet(100.0f, 0.0f, 0.0f);
	////�傫��������
	//c_StageScale = { 0.5f,0.5f,0.5f };

	// �R�c���f���̓ǂݍ���
	c_StageModel = MV1LoadModel("Model/Stage3.mv1");

	//MV1SetPosition(c_StageModel, c_StagePosition);
	//MV1SetScale(c_StageModel, c_StageScale);

}

STAGE::~STAGE()
{
}

void STAGE::init() {
	// ���W������
	c_StagePosition = VGet(100.0f, 0.0f, 0.0f);
	//�傫��������
	c_StageScale = { 1.0f,1.0f,1.0f };

	MV1SetPosition(c_StageModel, c_StagePosition);
	MV1SetScale(c_StageModel, c_StageScale);
}

void STAGE::Stage_Make() {
	//���̕`��
	MV1DrawModel(c_StageModel);
	//DrawCube3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1500.0f, 50.0f, 1200.0f), GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}