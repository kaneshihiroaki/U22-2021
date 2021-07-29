#include "DxLib.h"
#include <math.h>
#include"Camera.h"
#include "Player.h"

CAMERA::CAMERA()
{
	// カメラの向きを初期化
	c_CameraHAngle = 0.0f;
	c_CameraVAngle = 30.0f;

	// 向きを初期化
	c_SinParam = 0.0f;
	c_CosParam = 0.0f;
}

CAMERA::~CAMERA()
{
}

void CAMERA::Camera_Control(PLAYER* play) {

	// カメラ左右移動
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

	//カメラの上下移動
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

	////カメラとプレイヤーの距離
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

	//カメラの計算のための変数宣言
	VECTOR TempPosition1;
	VECTOR TempPosition2;
	VECTOR CameraPosition;
	VECTOR CameraLookAtPosition;
	CameraLookAtPosition = play->c_Position;
	//CameraLookAtPosition.y += c_CameraPosHeight;
	//printfDx("%lf \n", c_SinParam);

	//カメラの上下移動
	c_SinParam = sin(c_CameraVAngle / 180.0f * DX_PI_F);
	c_CosParam = cos(c_CameraVAngle / 180.0f * DX_PI_F);
	TempPosition1.x = 0.0f;
	TempPosition1.y = c_SinParam * c_CameraPosDist;
	TempPosition1.z = -c_CosParam * c_CameraPosDist;

	//カメラの左右移動
	c_SinParam = sin(c_CameraHAngle / 180.0f * DX_PI_F);
	c_CosParam = cos(c_CameraHAngle / 180.0f * DX_PI_F);
	TempPosition2.x = c_CosParam * TempPosition1.x - c_SinParam * TempPosition1.z;
	TempPosition2.y = TempPosition1.y;
	TempPosition2.z = c_SinParam * TempPosition1.x + c_CosParam * TempPosition1.z;

	CameraPosition = VAdd(TempPosition2, CameraLookAtPosition);

	SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);
}
