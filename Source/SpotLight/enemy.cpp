#include <DxLib.h>
#include "enemy.h"

ENEMY::ENEMY()
{
	//�I�u�W�F�N�g�̍��W������
	c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// �R�c���f���̓ǂݍ���
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_EnemyModel[i] = MV1LoadModel("Model/obj.mv1");
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//�G�l�~�[�̃X�P�[��������Ă���
	}
	
	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//�X�|�b�g���C�g�̍��W
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
}

ENEMY::~ENEMY()
{
}

void ENEMY::Enemy_Creat() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		MV1SetPosition(c_EnemyModel[i], c_ObjPos[i]);//�G�l�~�[�̈ړ���ʒu������Ă�
		
		MV1DrawModel(c_EnemyModel[i]);				 //�G�l�~�[�̃��f���`��
	}
	//�I�u�W�F�N�g�`��
	//DrawSphere3D(c_ObjPos[0], 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[1], VAdd(c_ObjPos[1], VECTOR{ 50,50,50 }), GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[2], VAdd(c_ObjPos[2], VECTOR{ 50,50,50 }), GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

void ENEMY::debug() {
	printfDx("%d\n", GetEnemyMoveKey(2));
}

void ENEMY::Enemy_Move(int num, VECTOR PlayerCol, VECTOR LightPos)
{
	//�ړ����Ă邩�ǂ���
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	
	Coefficient = 1.0f;

	c_SpotPos = LightPos;

	// 
	if (c_SpotPos.x - c_SpotRadius > c_ObjPos[num].x) {
		c_MoveFlag = true;
		c_MoveVector.x = c_movespeed;
	}

	if (c_SpotPos.x + c_SpotRadius < c_ObjPos[num].x) {
		c_MoveFlag = true;
		c_MoveVector.x = -c_movespeed;
	}

	if (c_SpotPos.z - c_SpotRadius > c_ObjPos[num].z) {
		c_MoveFlag = true;
		c_MoveVector.z = c_movespeed;
	}

	if (c_SpotPos.z + c_SpotRadius < c_ObjPos[num].z) {
		c_MoveFlag = true;
		c_MoveVector.z = -c_movespeed;
	}

	if ((c_MoveVector.x != 0.0f) && (c_MoveVector.z != 0.0f)) {
		Coefficient = 0.7f;
	}

	//�ړ��t���O�������Ă���ړ�
	if (c_MoveFlag == true)
	{
		//�ړ��ꏊ�̊m�F
		VECTOR TempMoveVector;

		TempMoveVector.x = c_MoveVector.x * Coefficient;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z * Coefficient;

		
		//������l����̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_ObjPos[i], 55, 55) == true) {
				c_MoveFlag = false;
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), PlayerCol, 55, 55) == true) {
			c_MoveFlag = false;
		}

		if (c_MoveFlag == true)
		{
			c_ObjPos[num] = VAdd(c_ObjPos[num], TempMoveVector);
		}
	}
	DrawSphere3D(c_SpotPos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//if (Collision_Player) {
	//	Collision_Draw();//�f�o�b�N�p
	//}
}


// �v���C���[�ƃI�u�W�F�N�g�̂����蔻��
bool Collision_Cube(VECTOR MyCol, VECTOR YouCol, float MyScale, float YouScale) {
	// �e���W���擾����
	VECTOR pos = MyCol;
	VECTOR posYou = YouCol;

	//����������true
	if ((pos.x + MyScale > posYou.x - YouScale &&
		pos.z + MyScale > posYou.z - YouScale) &&
		(pos.x - MyScale < posYou.x + YouScale &&
			pos.z - MyScale < posYou.z + YouScale)) {
		return true;
	}

	return false;
}