#include "DxLib.h"
#include <math.h>
#include"Camera.h"
#include "Player.h"

CAMERA::CAMERA()
{
	// �J�����̌�����������
	c_CameraHAngle = 0.0f;
	c_CameraVAngle = 30.0f;

	// ������������
	c_SinParam = 0.0f;
	c_CosParam = 0.0f;
}

CAMERA::~CAMERA()
{
}

void CAMERA::Camera_Control(PLAYER* play) {

	// �J�������E�ړ�
	if (CheckHitKey(KEY_INPUT_C) == 1)
	{
		c_CameraHAngle += c_CameraSpeed;
		if (c_CameraHAngle >= 180.0f)
		{
			c_CameraHAngle -= 360.0f;
		}
	}
	if (CheckHitKey(KEY_INPUT_Z) == 1)
	{
		c_CameraHAngle -= c_CameraSpeed;
		if (c_CameraHAngle <= -180.0f)
		{
			c_CameraHAngle += 360.0f;
		}
	}

	//�J�����̏㉺�ړ�
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		c_CameraVAngle += c_CameraSpeed;
		if (c_CameraVAngle >= 80.0f)
		{
			c_CameraVAngle = 80.0f;
		}
	}
	if (CheckHitKey(KEY_INPUT_X) == 1)
	{
		c_CameraVAngle -= c_CameraSpeed;
		if (c_CameraVAngle <= 0.0f)
		{
			c_CameraVAngle = 0.0f;
		}
	}

	////�J�����ƃv���C���[�̋���
	//if (CheckHitKey(KEY_INPUT_A) == 1)
	//{
	//	if (c_CameraPosDist >= 350.0f)
	//	{
	//		c_CameraPosDist -= 10.0f;
	//	}
	//}
	//if (CheckHitKey(KEY_INPUT_D) == 1)
	//{
	//	if (c_CameraPosDist <= 4000.0f)
	//	{
	//		c_CameraPosDist += 10.0f;
	//	}
	//}

	//�J�����̌v�Z�̂��߂̕ϐ��錾
	VECTOR TempPosition1;
	VECTOR TempPosition2;
	VECTOR CameraPosition;
	VECTOR CameraLookAtPosition;
	CameraLookAtPosition = play->c_Position;
	//CameraLookAtPosition.y += c_CameraPosHeight;
	//printfDx("%lf \n", c_SinParam);

	//�J�����̏㉺�ړ�
	c_SinParam = sin(c_CameraVAngle / 180.0f * DX_PI_F);
	c_CosParam = cos(c_CameraVAngle / 180.0f * DX_PI_F);
	TempPosition1.x = 0.0f;
	TempPosition1.y = c_SinParam * c_CameraPosDist;
	TempPosition1.z = -c_CosParam * c_CameraPosDist;

	//�J�����̍��E�ړ�
	c_SinParam = sin(c_CameraHAngle / 180.0f * DX_PI_F);
	c_CosParam = cos(c_CameraHAngle / 180.0f * DX_PI_F);
	TempPosition2.x = c_CosParam * TempPosition1.x - c_SinParam * TempPosition1.z;
	TempPosition2.y = TempPosition1.y;
	TempPosition2.z = c_SinParam * TempPosition1.x + c_CosParam * TempPosition1.z;

	CameraPosition = VAdd(TempPosition2, CameraLookAtPosition);

	SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
}
