//#include "DxLib.h"
//#include <math.h>
//#include <list>
//#include"camera.h"
//
//#define MOVESPEED					10.0f
//
//#define CAMERA_ANGLE_SPEED			3.0f
//// �J�����̒����_�̍���
//#define CAMERA_LOOK_AT_HEIGHT		0.0f
//// �J�����ƒ����_�̋���
//#define CAMERA_LOOK_AT_DISTANCE		350.0f
//
//// �v���C���[�ƃI�u�W�F�N�g�̂����蔻��
//bool Collision_Cube(VECTOR PlayerCol, VECTOR ObjCol, float MyScale) {
//	// �e���W���擾����
//	VECTOR pos = PlayerCol;
//	VECTOR posObj = ObjCol;
//
//	//�������Ă���~�߂�
//	if ((pos.x > posObj.x - MyScale &&
//		pos.z > posObj.z) &&
//		(pos.x <= posObj.x + (MyScale * 2) &&
//			pos.z <= posObj.z + (MyScale * 2))) {
//		return true;
//	}
//
//	return false;
//}
//bool Collision_Sphere(VECTOR PlayerCol, VECTOR ObjCol, float MyScale, float YourScale) {
//	// �e���W���擾����
//	VECTOR pos = PlayerCol;
//	VECTOR posObj = ObjCol;
//
//	//����������~�߂�(�����y���W����Ȃ��j
//	if (HitCheck_Sphere_Sphere(pos, MyScale, posObj, YourScale)) {
//		return true;
//	}
//	return false;
//}

#include <DxLib.h>
#include "Player.h"
#include <math.h>

PLAYER::PLAYER()
{
	// �v���C���[���W������
	c_Position = VGet(100.0f, 100.0f, 0.0f);
	//�v���C���[�̑傫��������
	c_AddPosPlay = { 0.5f,0.5f,0.5f };

	c_MoveFlag = FALSE;	//�v���C���[���ړ����Ă���̂�����

	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	// �R�c���f���̓ǂݍ���
	c_PlayerModel = MV1LoadModel("Model/MyPlayer.mv1");
}

PLAYER::~PLAYER()
{
}

void PLAYER::Player_Creat() {

}

void PLAYER::Player_Move()
{
	//�v���C���[
// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(c_PlayerModel, c_Position);
	MV1SetScale(c_PlayerModel, c_AddPosPlay);

	//�ړ����Ă邩�ǂ���
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	// �v���C���[�ړ�
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		//FrontAngle = 90.0f - CameraHAngle;
		c_MoveFlag = TRUE;
		c_MoveVector.x = -c_movespeed;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		//FrontAngle = -90.0f - CameraHAngle;
		c_MoveFlag = TRUE;
		c_MoveVector.x = c_movespeed;
	}

	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		//FrontAngle = 0.0f - CameraHAngle;
		c_MoveFlag = TRUE;
		c_MoveVector.z = -c_movespeed;
	}

	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		//FrontAngle = 180.0f - CameraHAngle;
		c_MoveFlag = TRUE;
		c_MoveVector.z = c_movespeed;
	}


	//�ړ��t���O�������Ă���ړ�
	if (c_MoveFlag == TRUE)
	{
		//�ړ��ꏊ�̊m�F
		VECTOR TempMoveVector;

		//SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
		//CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);

		TempMoveVector.x = c_MoveVector.x;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z;

		//printfDx("%lf \n", c_MoveVector.x * c_camera->c_CosParam - MoveVector.z * c_camera->c_SinParam);

		//TempMoveVector.x = c_MoveVector.x * CosParam - MoveVector.z * SinParam;
		//TempMoveVector.y = 0.0f;
		//TempMoveVector.z = c_MoveVector.x * SinParam + MoveVector.z * CosParam;

		//�����蔻��̊m�F
		//if (Collision_Sphere(VAdd(c_Position, TempMoveVector), ObjPos[0], 50, 32 * 2) == false &&
		//	Collision_Cube(VAdd(c_Position, TempMoveVector), ObjPos[1], 50) == false &&
		//	Collision_Cube(VAdd(c_Position, TempMoveVector), ObjPos[2], 50) == false) {
			c_Position = VAdd(c_Position, TempMoveVector);		//�ړ�
		//}
	}
}