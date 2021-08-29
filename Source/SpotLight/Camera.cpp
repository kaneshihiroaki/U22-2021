#include "DxLib.h"
#include <math.h>
#include"Camera.h"
#include "Player.h"
#include "Debug.h"
#include "Stage.h"

CAMERA::CAMERA()
{
	//// カメラの向きを初期化
	//c_CameraHAngle = 0.0f;
	//c_CameraVAngle = 35.0f;

	//// 向きを初期化
	//c_SinParam = 0.0f;
	//c_CosParam = 0.0f;
}

CAMERA::~CAMERA()
{
}

void CAMERA::init() {
	// カメラの向きを初期化
	c_CameraHAngle = 0.0f;
	c_CameraVAngle = 35.0f;

	// 向きを初期化
	c_SinParam = 0.0f;
	c_CosParam = 0.0f;
}

void CAMERA::Camera_Control(STAGE* stage) {

	//DINPUT_JOYSTATE inputGet;

	//// 入力状態を取得
	//GetJoypadDirectInputState(DX_INPUT_PAD1, &inputGet);
	//if (CameraLR_bool == false) {
	//	// カメラ左右移動
	//	if (inputGet.Rx > 0)
	//	{
	//		c_CameraHAngle += c_CameraSpeed;
	//		if (c_CameraHAngle >= 180.0f)
	//		{
	//			c_CameraHAngle -= 360.0f;
	//		}
	//	}
	//	if (inputGet.Rx < 0)
	//	{
	//		c_CameraHAngle -= c_CameraSpeed;
	//		if (c_CameraHAngle <= -180.0f)
	//		{
	//			c_CameraHAngle += 360.0f;
	//		}
	//	}
	//}else{
	//	// カメラ左右移動
	//	if (inputGet.Rx < 0)
	//	{
	//		c_CameraHAngle += c_CameraSpeed;
	//		if (c_CameraHAngle >= 180.0f)
	//		{
	//			c_CameraHAngle -= 360.0f;
	//		}
	//	}
	//	if (inputGet.Rx > 0)
	//	{
	//		c_CameraHAngle -= c_CameraSpeed;
	//		if (c_CameraHAngle <= -180.0f)
	//		{
	//			c_CameraHAngle += 360.0f;
	//		}
	//	}
	//}

	//if (CameraUp_bool == false) {
	//	//カメラの上下移動
	//	if (inputGet.Ry > 0)
	//	{
	//		c_CameraVAngle += c_CameraSpeed;
	//		if (c_CameraVAngle >= 80.0f)
	//		{
	//			c_CameraVAngle = 80.0f;
	//		}
	//	}
	//	if (inputGet.Ry < 0)
	//	{
	//		c_CameraVAngle -= c_CameraSpeed;
	//		if (c_CameraVAngle <= 0.0f)
	//		{
	//			c_CameraVAngle = 0.0f;
	//		}
	//	}
	//}
	//else {
	//	//カメラの上下移動
	//	if (inputGet.Ry < 0)
	//	{
	//		c_CameraVAngle += c_CameraSpeed;
	//		if (c_CameraVAngle >= 80.0f)
	//		{
	//			c_CameraVAngle = 80.0f;
	//		}
	//	}
	//	if (inputGet.Ry > 0)
	//	{
	//		c_CameraVAngle -= c_CameraSpeed;
	//		if (c_CameraVAngle <= 0.0f)
	//		{
	//			c_CameraVAngle = 0.0f;
	//		}
	//	}
	//}

	//

	////カメラとプレイヤーの距離
	//if (CheckHitKey(KEY_INPUT_A) == 1)
	//{
	//	//if (cko >= 350.0f)
	//	//{
	//		cko -= 10.0f;
	//	//}
	//}
	//if (CheckHitKey(KEY_INPUT_D) == 1)
	//{
	//	//if (cko <= 4000.0f)
	//	//{
	//		cko += 10.0f;
	//	//}
	//}

	//DrawFormatString(300, 110, 0xFFFFFF, "%f", cko);
	//DrawFormatString(300, 130, 0xFFFFFF, "%f", c_CameraVAngle);

	//カメラの計算のための変数宣言
	VECTOR TempPosition1;
	VECTOR TempPosition2;
	VECTOR CameraPosition;
	VECTOR CameraLookAtPosition;
	CameraLookAtPosition = stage->c_StagePosition;
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

	SetCameraPositionAndTarget_UpVecY(VGet(CameraPosition.x,CameraPosition.y+50,CameraPosition.z+ cko), CameraLookAtPosition);
}
