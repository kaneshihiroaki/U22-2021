#define _USE_MATH_DEFINES

#include <DxLib.h>
#include <math.h>

#include "enemy.h"
#include "Light.h"
#include "Player.h"
#include "Camera.h"
#include "debug.h"

ENEMY::ENEMY()
{
	//オブジェクトの座標初期化
	c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// ３Ｄモデルの読み込み
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_EnemyModel[i] = MV1LoadModel("Model/obj.mv1");
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		c_StmCount[i] = 300;	//エネミーの体力の最大
		c_Rotation[i] = VGet(0.0f, 0.0f /*(c_PlayerAng * (M_PI / 180))*/, 0.0f);//エネミーの回転
		c_EnemyAng[i] = 0;//エネミーの角度
		c_Enemy_MoveAng[i] = 0;//エネミーの角度
		c_EnemySpeed[i] = 0.0f;//エネミーのスピード
		c_EnemyState[i] = ENEMY_IDLE;//エネミーの初期状態
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//エネミーのスケールをいれている
	}

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//スポットライトの座標
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
}

ENEMY::~ENEMY()
{
}

void ENEMY::Enemy_Creat() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		MV1SetPosition(c_EnemyModel[i], c_ObjPos[i]);//エネミーの移動後位置をいれてる
		MV1SetRotationXYZ(c_EnemyModel[i], c_Rotation[i]);//エネミーの角度をいれている
		MV1DrawModel(c_EnemyModel[i]);				 //エネミーのモデル描画
	}
	//オブジェクト描画
	//DrawSphere3D(c_ObjPos[0], 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[1], VAdd(c_ObjPos[1], VECTOR{ 50,50,50 }), GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[2], VAdd(c_ObjPos[2], VECTOR{ 50,50,50 }), GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

void ENEMY::debug() {
	printfDx("%d\n", GetEnemyMoveKey(2));
}

void ENEMY::Enemy_State(int num, PLAYER* player, CAMERA* camera) {
	
	

	
	switch (c_EnemyState[num])
	{
	case ENEMY_IDLE:
		c_StmCount[num] = StaminaCount(false,num);		//スタミナ回復
		if (c_StmCount[num] >= 300) {//スタミナがマックスになったら移動する。
			c_EnemyState[num] = ENEMY_MOVE;
		}
		break;
	case ENEMY_MOVE:
		Enemy_Move(num, player, camera);
		if (c_StmCount[num] == 0) {//スタミナ０になったらアイドルになって回復する。
			c_EnemyState[num] = ENEMY_IDLE;
		}
		break;
	case ENEMY_ATTACK:
		break;
	}

	SetFontSize(20);
	DrawFormatString(1100, 620 + 20 * num, 0xFFFFFF, "%dの敵体力 %d\n", num, c_StmCount[num]);

}

void ENEMY::Enemy_Move(int num, PLAYER* player, CAMERA* camera)
{
	int p_Enemy_MoveAng = 0;//エネミーの向かう角度
	//移動してるかどうか
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);


	Coefficient = 1.0f;

	c_SpotPos = LightPos;

	// スポットライトを追跡用
	if (c_SpotPos.x - c_SpotRadius > c_ObjPos[num].x) {
		c_MoveFlag = true;
		if (c_MoveKey[num] == true && c_StmCount[num] > 0)c_MoveVector.x = c_movespeed;
		p_Enemy_MoveAng = 90;//右

	}

	if (c_SpotPos.x + c_SpotRadius < c_ObjPos[num].x) {
		c_MoveFlag = true;
		if (c_MoveKey[num] == true && c_StmCount[num] > 0)c_MoveVector.x = -c_movespeed;
		p_Enemy_MoveAng = 270;//左

	}

	if (c_SpotPos.z - c_SpotRadius > c_ObjPos[num].z) {
		c_MoveFlag = true;
		if (c_MoveKey[num] == true && c_StmCount[num] > 0)c_MoveVector.z = c_movespeed;
		p_Enemy_MoveAng = 0;//上

	}

	if (c_SpotPos.z + c_SpotRadius < c_ObjPos[num].z) {
		c_MoveFlag = true;
		if (c_MoveKey[num] == true && c_StmCount[num] > 0)c_MoveVector.z = -c_movespeed;
		p_Enemy_MoveAng = 180;//下
	}

	if ((c_MoveVector.x != 0.0f) && (c_MoveVector.z != 0.0f)) {
		Coefficient = 0.7f;
		if ((c_MoveVector.x > 0.0f) && (c_MoveVector.z > 0.0f))p_Enemy_MoveAng = 45;//右上
		if ((c_MoveVector.x > 0.0f) && (c_MoveVector.z < 0.0f))p_Enemy_MoveAng = 135;//右下
		if ((c_MoveVector.x < 0.0f) && (c_MoveVector.z < 0.0f))p_Enemy_MoveAng = 225;//左下
		if ((c_MoveVector.x < 0.0f) && (c_MoveVector.z > 0.0f))p_Enemy_MoveAng = 315;//左上
	}

	//エネミーの角度を決定
	if (c_Enemy_MoveAng[num] >= 180) {//現在の角度が180~359
		if (c_Enemy_MoveAng[num] < p_Enemy_MoveAng || c_Enemy_MoveAng[num] - 180 > p_Enemy_MoveAng) {//185以上で5未満
			if ((c_Enemy_MoveAng[num] < p_Enemy_MoveAng && c_Enemy_MoveAng[num] + 6 > p_Enemy_MoveAng) || (c_Enemy_MoveAng[num] + 6 - 360 > p_Enemy_MoveAng)) {
				c_Enemy_MoveAng[num] = p_Enemy_MoveAng;
			}
			else {
				c_Enemy_MoveAng[num] += 6;
				if (c_Enemy_MoveAng[num] >= 360) {
					c_Enemy_MoveAng[num] -= 360;
				}
			}
		}
		else {//現在の角度が185として、目指す角度が185以下で5以上なら
			if (c_Enemy_MoveAng[num] - 6 < p_Enemy_MoveAng) {
				c_Enemy_MoveAng[num] = p_Enemy_MoveAng;
			}
			else {
				c_Enemy_MoveAng[num] -= 6;
			}
		}
	}
	else {//現在の角度が0~179
		if (c_Enemy_MoveAng[num] > p_Enemy_MoveAng || c_Enemy_MoveAng[num] + 180 < p_Enemy_MoveAng) {//
			if ((c_Enemy_MoveAng[num] > p_Enemy_MoveAng && c_Enemy_MoveAng[num] - 6 < p_Enemy_MoveAng) || c_Enemy_MoveAng[num] - 6 + 360 < p_Enemy_MoveAng) {
				c_Enemy_MoveAng[num] = p_Enemy_MoveAng;
			}
			else {
				c_Enemy_MoveAng[num] -= 6;
				if (c_Enemy_MoveAng[num] < 0) {
					c_Enemy_MoveAng[num] += 360;
				}
			}


		}
		else {//現在の角度が5として、目指す角度が185以下で5以上なら
			if (c_Enemy_MoveAng[num] + 6 > p_Enemy_MoveAng) {
				c_Enemy_MoveAng[num] = p_Enemy_MoveAng;
			}
			else {
				c_Enemy_MoveAng[num] += 6;
			}
		}
	}
	c_Rotation[num].y = c_Enemy_MoveAng[num] * (M_PI / 180);


	
	//移動フラグがたってたら移動
	if (c_MoveFlag == true)
	{
		if (c_EnemySpeed[num] == 0.0f) {//初速
			c_EnemySpeed[num] = 0.9f;
		}
		else if (c_EnemySpeed[num] == 1.0f) {
		}
		else if (c_EnemySpeed[num] > 1.0f) {
			c_EnemySpeed[num] = 1.0f;
		}
		else {//加速度
			c_EnemySpeed[num] += 0.01f;
		}
		//移動場所の確認
		VECTOR TempMoveVector;

		TempMoveVector.x = c_MoveVector.x * Coefficient * c_EnemySpeed[num];
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z * Coefficient * c_EnemySpeed[num];


		//当たりl判定の確認
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_ObjPos[i], 55, 55) == true) {
				if (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false) {//falseなら動かせなかった
					c_MoveFlag = false;
				}
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), player->c_Position, 55, 55) == true) {
			if (player->Player_Push(camera, c_ObjPos, TempMoveVector) == false) {//falseなら動かせなかった
				c_MoveFlag = false;
			}
		}

		if (c_MoveFlag == true)
		{
			c_ObjPos[num] = VAdd(c_ObjPos[num], TempMoveVector);
		}
		
	}

	if(c_MoveFlag == false) {//移動失敗
		c_EnemySpeed[num] = 0.0f;
	}
	c_StmCount[num] = StaminaCount(c_MoveFlag,num);		//スタミナ管理


	
	//DrawSphere3D(c_SpotPos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	
	//if (Collision_Player) {
	//	Collision_Draw();//デバック用
	//}
}

bool ENEMY::Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec)
{
	//しびれているかどうか
	/*if()*/

	//移動してるかどうか
	c_MoveFlag = FALSE;
	c_MoveVector = PushVec;

	Coefficient = 1.0f;

	c_SpotPos = LightPos;

	c_MoveFlag = true;




	//移動フラグがたってたら移動
	if (c_MoveFlag == true)
	{
		//移動場所の確認
		VECTOR TempMoveVector;

		TempMoveVector.x = c_MoveVector.x * Coefficient;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z * Coefficient;


		//当たりl判定の確認
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
	//if (Collision_Player) {
	//	Collision_Draw();//デバック用
	//}
	return c_MoveFlag;
}


// プレイヤーとオブジェクトのあたり判定
bool Collision_Cube(VECTOR MyCol, VECTOR YouCol, float MyScale, float YouScale) {
	// 各座標を取得する
	VECTOR pos = MyCol;
	VECTOR posYou = YouCol;

	//当たったらtrue
	if ((pos.x + MyScale > posYou.x - YouScale &&
		pos.z + MyScale > posYou.z - YouScale) &&
		(pos.x - MyScale < posYou.x + YouScale &&
			pos.z - MyScale < posYou.z + YouScale)) {
		return true;
	}

	return false;
}
bool ENEMY::EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos) {
	VECTOR Light = LightPos;
	LightPos.y = 0.0f;
	for (int i = 0; i < ENEMY_MAX; i++) {

		float ex = Light.x - c_ObjPos[i].x;
		float ez = Light.z - c_ObjPos[i].z;

		float er = (ex * ex) + (ez * ez);
		float elr = (80.0f+70.0f);
		float elr2 = (elr * elr);

		// enemyとlightの当たり判定( TRUE:当たっている FALSE:当たっていない )
		if (er <= elr2&&LightFlg==false) {
			
			return true;
		}

	}
	return false;

	/*SetFontSize(20);
	DrawFormatString(10, 100, 0x888888, "x:%f", Player.x);
	DrawFormatString(10, 130, 0x888888, "y:%f", Player.y);
	DrawFormatString(10, 160, 0x888888, "z:%f", Player.z);
	DrawFormatString(10, 190, 0x888888, "x:%f", Enemy.x);
	DrawFormatString(10, 220, 0x888888, "y:%f", Enemy.y);
	DrawFormatString(10, 250, 0x888888, "z:%f", Enemy.z);*/

}