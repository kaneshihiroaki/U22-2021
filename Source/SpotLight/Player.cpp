#include <DxLib.h>
#include "Player.h"
#include <math.h>

PLAYER::PLAYER()
{
	// プレイヤー座標初期化
	c_Position = VGet(100.0f, 100.0f, 0.0f);
	//プレイヤーの大きさ初期化
	c_AddPosPlay = { 0.5f,0.5f,0.5f };

	c_MoveFlag = FALSE;	//プレイヤーが移動しているのか判定

	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	// ３Ｄモデルの読み込み
	c_PlayerModel = MV1LoadModel("Model/MyPlayer.mv1");

	//カメラの起動の取得
	Sin = 0.0f;
	Cos = 0.0f;
}

PLAYER::~PLAYER()
{
}

void PLAYER::Player_Creat() {

}

// プレイヤーとオブジェクトのあたり判定
bool Collision_Cube(VECTOR PlayerCol, VECTOR ObjCol, float MyScale) {
	// 各座標を取得する
	VECTOR pos = PlayerCol;
	VECTOR posObj = ObjCol;

	//当たってたら止める
	if ((pos.x > posObj.x - MyScale &&
		pos.z > posObj.z) &&
		(pos.x <= posObj.x + (MyScale * 2) &&
			pos.z <= posObj.z + (MyScale * 2))) {
		return true;
	}

	return false;
}
bool Collision_Sphere(VECTOR PlayerCol, VECTOR ObjCol, float MyScale, float YourScale) {
	// 各座標を取得する
	VECTOR pos = PlayerCol;
	VECTOR posObj = ObjCol;

	//当たったら止める(今回はy座標いらない）
	if (HitCheck_Sphere_Sphere(pos, MyScale, posObj, YourScale)) {
		return true;
	}
	return false;
}

void PLAYER::Player_Move()
{
	//プレイヤー
// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(c_PlayerModel, c_Position);
	MV1SetScale(c_PlayerModel, c_AddPosPlay);

	//移動してるかどうか
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	// プレイヤー移動
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


	//移動フラグがたってたら移動
	if (c_MoveFlag == TRUE)
	{
		//移動場所の確認
		VECTOR TempMoveVector;

		c_cameraAng->c_SinParam = sin(c_cameraAng->c_CameraHAngle / 180.0f * DX_PI_F);
		c_cameraAng->c_CosParam = cos(c_cameraAng->c_CameraHAngle / 180.0f * DX_PI_F);

		//TempMoveVector.x = c_MoveVector.x;
		//TempMoveVector.y = 0.0f;
		//TempMoveVector.z = c_MoveVector.z;

		printfDx("%lf \n", c_MoveVector.x * c_cameraAng->c_CosParam - c_MoveVector.z * c_cameraAng->c_SinParam);

		TempMoveVector.x = c_MoveVector.x * c_cameraAng->c_CosParam - c_MoveVector.z * c_cameraAng->c_SinParam;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.x * c_cameraAng->c_SinParam + c_MoveVector.z * c_cameraAng->c_CosParam;

		//当たり判定の確認
		if (Collision_Sphere(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[0], 50, 32 * 2) == false &&
			Collision_Cube(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[1], 50) == false &&
			Collision_Cube(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[2], 50) == false) {
			c_Position = VAdd(c_Position, TempMoveVector);		//移動
		}
	}
}