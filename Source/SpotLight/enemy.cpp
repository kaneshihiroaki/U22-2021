#include <DxLib.h>
#include "enemy.h"

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
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//エネミーのスケールをいれている
	}
	
}

ENEMY::~ENEMY()
{
}

void ENEMY::Enemy_Creat() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		MV1SetPosition(c_EnemyModel[i], c_ObjPos[i]);//エネミーの移動後位置をいれてる
		
		MV1DrawModel(c_EnemyModel[i]);				 //エネミーのモデル描画
	}
	//オブジェクト描画
	//DrawSphere3D(c_ObjPos[0], 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[1], VAdd(c_ObjPos[1], VECTOR{ 50,50,50 }), GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[2], VAdd(c_ObjPos[2], VECTOR{ 50,50,50 }), GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}



void ENEMY::Enemy_Move(int num)
{
	//移動してるかどうか
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//スポットライトの座標
	Coefficient = 1.0f;

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

	//移動フラグがたってたら移動
	if (c_MoveFlag == true)
	{
		//移動場所の確認
		VECTOR TempMoveVector;

		TempMoveVector.x = c_MoveVector.x * Coefficient;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z * Coefficient;

		//当たりl判定の確認
		//if (Colision_Sphere(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[0], 55) == false &&
		//	Collision_Cube(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[1], 55) == false &&
		//	Collision_Cube(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[2], 55) == false) {
		//	c_Position = VAdd(c_Position, TempMoveVector);		//移動
		//}
		c_ObjPos[num] = VAdd(c_ObjPos[num], TempMoveVector);;
	}
	DrawSphere3D(c_SpotPos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//if (Collision_Player) {
	//	Collision_Draw();//デバック用
	//}
}