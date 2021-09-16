#include "DxLib.h"
#include <math.h>
#include"Camera.h"
#include "Player.h"
#include "Debug.h"
#include "Stage.h"
#include "Main.h"

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
	c_CameraVAngle = 33.0f;

	// 向きを初期化
	c_SinParam = 0.0f;
	c_CosParam = 0.0f;

	//リザルトでのカメラ位置初期化
	c_RPosX = 0;
	c_RPosY = 569;
	c_RPosZ = -530;
	c_RAngX = -0.41;
	c_RAngY = 3.15;
	c_RAngZ = 0;
}

void CAMERA::Camera_Control(STAGE* stage) {

	if (Debug_Camera == true) {
		DINPUT_JOYSTATE inputGet;

		// 入力状態を取得
		GetJoypadDirectInputState(DX_INPUT_PAD1, &inputGet);
		if (CameraLR_bool == false) {
			// カメラ左右移動
			if (inputGet.Rx > 0)
			{
				c_CameraHAngle += c_CameraSpeed;
				if (c_CameraHAngle >= 180.0f)
				{
					c_CameraHAngle -= 360.0f;
				}
			}
			if (inputGet.Rx < 0)
			{
				c_CameraHAngle -= c_CameraSpeed;
				if (c_CameraHAngle <= -180.0f)
				{
					c_CameraHAngle += 360.0f;
				}
			}
		}
		else {
			// カメラ左右移動
			if (inputGet.Rx < 0)
			{
				c_CameraHAngle += c_CameraSpeed;
				if (c_CameraHAngle >= 180.0f)
				{
					c_CameraHAngle -= 360.0f;
				}
			}
			if (inputGet.Rx > 0)
			{
				c_CameraHAngle -= c_CameraSpeed;
				if (c_CameraHAngle <= -180.0f)
				{
					c_CameraHAngle += 360.0f;
				}
			}
		}

		if (CameraUp_bool == false) {
			//カメラの上下移動
			if (inputGet.Ry > 0)
			{
				c_CameraVAngle += c_CameraSpeed;
				if (c_CameraVAngle >= 80.0f)
				{
					c_CameraVAngle = 80.0f;
				}
			}
			if (inputGet.Ry < 0)
			{
				c_CameraVAngle -= c_CameraSpeed;
				if (c_CameraVAngle <= 0.0f)
				{
					c_CameraVAngle = 0.0f;
				}
			}
		}
		else {
			//カメラの上下移動
			if (inputGet.Ry < 0)
			{
				c_CameraVAngle += c_CameraSpeed;
				if (c_CameraVAngle >= 80.0f)
				{
					c_CameraVAngle = 80.0f;
				}
			}
			if (inputGet.Ry > 0)
			{
				c_CameraVAngle -= c_CameraSpeed;
				if (c_CameraVAngle <= 0.0f)
				{
					c_CameraVAngle = 0.0f;
				}
			}
		}



		//カメラとプレイヤーの距離
		if ((g_NowKey & PAD_INPUT_3))
		{
			//if (cko >= 350.0f)
			//{
			cko -= 10.0f;
			//}
		}
		if ((g_NowKey & PAD_INPUT_4))
		{
			//if (cko <= 4000.0f)
			//{
			cko += 10.0f;
			//}
		}
	}

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

void CAMERA::Camera_Result(MAIN* main) {
	//if (CheckHitKey(KEY_INPUT_Z))c_RPosX = c_RPosX + 1;
	//if (CheckHitKey(KEY_INPUT_A))c_RPosX = c_RPosX - 1;
	//if (CheckHitKey(KEY_INPUT_X))c_RPosY = c_RPosY + 1;
	//if (CheckHitKey(KEY_INPUT_S))c_RPosY = c_RPosY - 1;
	//if (CheckHitKey(KEY_INPUT_C))c_RPosZ = c_RPosZ + 1;
	//if (CheckHitKey(KEY_INPUT_D))c_RPosZ = c_RPosZ - 1;
	//if (CheckHitKey(KEY_INPUT_V))c_RAngX = c_RAngX + 0.01;
	//if (CheckHitKey(KEY_INPUT_F))c_RAngX = c_RAngX - 0.01;
	//if (CheckHitKey(KEY_INPUT_B))c_RAngY = c_RAngY + 0.01;
	//if (CheckHitKey(KEY_INPUT_G))c_RAngY = c_RAngY - 0.01;
	//if (CheckHitKey(KEY_INPUT_N))c_RAngZ = c_RAngZ + 0.01;
	//if (CheckHitKey(KEY_INPUT_H))c_RAngZ = c_RAngZ - 0.01;

	//SetFontSize(20);
	//DrawFormatString(10, 10, 0xFFFFFF, "%f", c_RPosX);
	//DrawFormatString(10, 30, 0xFFFFFF, "%f", c_RPosY);
	//DrawFormatString(10, 50, 0xFFFFFF, "%f", c_RPosZ);
	//DrawFormatString(10, 70, 0xFFFFFF, "%f", c_RAngX);
	//DrawFormatString(10, 90, 0xFFFFFF, "%f", c_RAngY);
	//DrawFormatString(10, 110, 0xFFFFFF, "%f", c_RAngZ);


	//SetCameraPositionAndTarget_UpVecY(VGet(x, y, z), /*main->c_ResultPos[0]*/VGet(x1, y2, z1));
	SetCameraPositionAndAngle(VGet(c_RPosX, c_RPosY, c_RPosZ), c_RAngX, c_RAngY, c_RAngZ);

	if (main->GetResult() == true) {
		VECTOR CameraPos = VGet(c_RPosX, c_RPosY, c_RPosZ);
		switch (main->GetWinner())
		{
		case 0:
			if(c_RPosX <= 585) c_RPosX = c_RPosX + 20;
			if(c_RPosY >= 593) c_RPosY = c_RPosY - 1;
			if(c_RPosZ >= -651) c_RPosZ = c_RPosZ - 5;
			break;
		case 1:
			if (c_RPosX <= 195) c_RPosX = c_RPosX + 20;
			if (c_RPosY >= 593) c_RPosY = c_RPosY - 1;
			if (c_RPosZ >= -651) c_RPosZ = c_RPosZ - 8;
			break;
		case 2:
			if (c_RPosX >= -185) c_RPosX = c_RPosX - 20;
			if (c_RPosY >= 593) c_RPosY = c_RPosY - 1;
			if (c_RPosZ >= -651) c_RPosZ = c_RPosZ - 8;
			break;
		case 3:
			if (c_RPosX >= -592) c_RPosX = c_RPosX - 20;
			if (c_RPosY >= 593) c_RPosY = c_RPosY - 1;
			if (c_RPosZ >= -651) c_RPosZ = c_RPosZ - 5;
			break;
		default:
			break;
		}
	}
}
