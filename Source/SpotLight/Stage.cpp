#include <math.h>
#include "Stage.h"
#include "enemy.h"
#include "Player.h"

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

	//�����Ɖ��s��
	c_width = 2600;
	c_depth = 1300;

	MV1SetPosition(c_StageModel, c_StagePosition);
	MV1SetScale(c_StageModel, c_StageScale);
}

void STAGE::Stage_Make(ENEMY* enemy, PLAYER* player) {
	//�X�e�[�W�̓����蔻��
	Stage_Col(enemy, player);

	//���̕`��
	MV1DrawModel(c_StageModel);
	//DrawCube3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1500.0f, 50.0f, 1200.0f), GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

void STAGE::Stage_Col(ENEMY* enemy, PLAYER* player) {
	//��
	DrawLine3D(VGet(c_StagePosition.x - (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) + (c_depth / 2)),
		VGet(c_StagePosition.x + (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) + (c_depth / 2)), 0xFFFFFF);
	//��
	DrawLine3D(VGet(c_StagePosition.x - (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) - (c_depth / 2)),
		VGet(c_StagePosition.x + (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) - (c_depth / 2)), 0xFFFFFF);
	//��
	DrawLine3D(VGet(c_StagePosition.x - (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) + (c_depth / 2)),
		VGet(c_StagePosition.x - (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) - (c_depth / 2)), 0xFFFFFF);
	//�E
	DrawLine3D(VGet(c_StagePosition.x + (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) + (c_depth / 2)),
		VGet(c_StagePosition.x + (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) - (c_depth / 2)), 0xFFFFFF);

	//�E��̓_�FVGet(c_StagePosition.x + 2000.0f, c_StagePosition.y + 50.0f, c_StagePosition.z + 2000.0f);
	//����̓_�FVGet(c_StagePosition.x - 2000.0f, c_StagePosition.y + 50.0f, c_StagePosition.z + 2000.0f);
	//�E���̓_�FVGet(c_StagePosition.x + 2000.0f, c_StagePosition.y + 50.0f, c_StagePosition.z - 2000.0f);
	//�����̓_�FVGet(c_StagePosition.x - 2000.0f, c_StagePosition.y + 50.0f, c_StagePosition.z - 2000.0f);

	/****************************************
	//�v���C���[�̓����蔻���ݒ�
	*****************************************/

	//���S�_����o��
	float halfx = (c_StagePosition.x + 2000.0f + c_StagePosition.x + 2000.0f +
		c_StagePosition.x - 2000.0f + c_StagePosition.x - 2000.0f) / 4;
	float halfz = (c_StagePosition.z + 2000.0f + (250) + c_StagePosition.z - 2000.0f + (250) +
		c_StagePosition.z + 2000.0f + (250) + c_StagePosition.z - 2000.0f + (250)) / 4;

	//���S�_�ƃv���C���[�̍��W�̋���
	float playerdistx = player->GetFuturePos().x - halfx;
	float playerdistz = player->GetFuturePos().z - halfz;
	float enemydistx;
	float enemydistz;

	//�v���C���[�Ƃ̓����蔻��̌v�Z
	float posx = cos(0) * playerdistx + sin(0) * playerdistz;
	float posz = -sin(0) * playerdistx + cos(0) * playerdistz;

	//�v���C���[�̓����蔻��
	if (-c_width / 2.0f <= posx && c_width / 2.0f >= posx &&
		-c_depth / 2.0f <= posz && c_depth / 2.0f >= posz) {
		//return true;
		player->SetPlayerInStage();
	}
	else {
		player->SetPlayerOutStage();
	}

	/****************************************
	//�G�̓����蔻���ݒ�
	*****************************************/
	for (int i = 0; i < ENEMY_MAX; i++) {
		//���S�_����o��
		float enehalfx = (c_StagePosition.x + 2000.0f + c_StagePosition.x + 2000.0f +
			c_StagePosition.x - 2000.0f + c_StagePosition.x - 2000.0f) / 4;
		float enehalfz = (c_StagePosition.z + 2000.0f + c_StagePosition.z - 2000.0f +
			c_StagePosition.z + 2000.0f + c_StagePosition.z - 2000.0f) / 4;

		//���S�_�ƓG�̍��W�̋���
		float enedistx = enemy->GetEnemyMoveKey(i).x - enehalfx;
		float enedistz = enemy->GetEnemyMoveKey(i).z - enehalfz;

		//�G�Ƃ̓����蔻��̌v�Z
		float posx = cos(0) * enedistx + sin(0) * enedistz;
		float posz = -sin(0) * enedistx + cos(0) * enedistz;

		//�G�̓����蔻��
		if (-c_width / 2.0f <= posx && c_width / 2.0f >= posx &&
			-c_depth / 2.0f <= posz && c_depth / 2.0f >= posz) {
			enemy->SetEnemyStageInKey(i);
		}
		else {
			enemy->SetEnemyStageOutKey(i);
		}
	}
}

