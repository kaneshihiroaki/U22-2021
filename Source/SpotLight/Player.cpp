#include <DxLib.h>
#include "Player.h"
#include "enemy.h"
#include "Camera.h"
#include <math.h>
//#include "Main.h"
#include "Debug.h"


PLAYER::PLAYER()
{
	// プレイヤー座標初期化
	c_Position = VGet(100.0f, 100.0f, 0.0f);
	//プレイヤー回転
	c_Rotation = VGet(0.0f, 0.0f, 0.0f);
	//プレイヤーの大きさ初期化
	c_AddPosPlay = { 0.5f,0.5f,0.5f };

	c_MoveFlag = FALSE;	//プレイヤーが移動しているのか判定

	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	c_StmCount = 300;		//プレイヤーの体力

	// ３Ｄモデルの読み込み
	//c_PlayerModel = MV1LoadModel("Model/MyPlayer.mv1");
	c_PlayerModel = MV1LoadModel("Model/obj.mv1");

	c_enemyCol = new ENEMY();
}

PLAYER::~PLAYER()
{
}

void PLAYER::Player_Controller() {
	//プレイヤー
	// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(c_PlayerModel, c_Position);
	MV1SetRotationXYZ(c_PlayerModel, c_Rotation);
	MV1SetScale(c_PlayerModel, c_AddPosPlay);
	SetFontSize(18);
	DrawFormatString(10, 670, 0xFFFFFF, "スタミナ：%d / %d", c_StmCount, c_StmMax);

	//Player_Move(Sin, Cos);
}

// プレイヤーとオブジェクトのあたり判定
bool Collision_Cube(VECTOR PlayerCol, VECTOR ObjCol, float EnemyScale) {
	// 各座標を取得する
	VECTOR pos = PlayerCol;
	VECTOR posObj = ObjCol;

	//当たったらtrue
	if ((pos.x + CHAR_SIZE_X > posObj.x - EnemyScale &&
		pos.z + CHAR_SIZE_Z > posObj.z - EnemyScale) &&
		(pos.x - CHAR_SIZE_X < posObj.x + EnemyScale &&
			pos.z - CHAR_SIZE_Z < posObj.z + EnemyScale)) {
		return true;
	}

	return false;
}

bool Collision_Sphere(VECTOR PlayerCol, VECTOR ObjCol, float EnemyScale) {
	// 各座標を取得する
	VECTOR pos = PlayerCol;
	VECTOR posObj = ObjCol;


	//当たったらtrue。領域A、ｙ部分
	if ((pos.x + CHAR_SIZE_X > posObj.x &&
		pos.z + CHAR_SIZE_Z > posObj.z - EnemyScale) &&
		(pos.x - CHAR_SIZE_X < posObj.x &&
			pos.z - CHAR_SIZE_Z < posObj.z + EnemyScale)) {
		return true;
	}

	//当たったらtrue。領域B、ｘ部分
	if ((pos.x + CHAR_SIZE_X > posObj.x - EnemyScale &&
		pos.z + CHAR_SIZE_Z > posObj.z) &&
		(pos.x - CHAR_SIZE_X < posObj.x + EnemyScale &&
			pos.z - CHAR_SIZE_Z < posObj.z)) {
		return true;
	}
	//当たったらtrue。領域CDEF、円部分
	if (pow((pos.x + CHAR_SIZE_X - posObj.x), 2) + pow((pos.z + CHAR_SIZE_Z - posObj.z), 2) < pow(EnemyScale, 2) ||
		pow((pos.x + CHAR_SIZE_X - posObj.x), 2) + pow((pos.z - CHAR_SIZE_Z - posObj.z), 2) < pow(EnemyScale, 2) ||
		pow((pos.x - CHAR_SIZE_X - posObj.x), 2) + pow((pos.z + CHAR_SIZE_Z - posObj.z), 2) < pow(EnemyScale, 2) ||
		pow((pos.x - CHAR_SIZE_X - posObj.x), 2) + pow((pos.z - CHAR_SIZE_Z - posObj.z), 2) < pow(EnemyScale, 2)) {
		return true;
	}

	return false;
}

void PLAYER::Player_Paralyze() {
	c_MoveFlag = false;

	if (Damage.s_ParaTime++ == Damage.s_MaxTimeParalyze) {
		Damage.s_paralyzeKey = false;
		Damage.s_ParaTime = 0;
	}
}

void PLAYER::Player_Attack(ENEMY* ene/*, VECTOR Player_rot*/) {
	//移動場所の確認
	//VECTOR plus;
	//plus.x = Player_rot.x;
	//plus.y = 0.0f;
	//plus.z = Player_rot.y;
	//plus = VAdd(c_Position, Player_rot);

	Att.s_Rang += Att.s_AttackSpeed;
	DrawSphere3D(c_Position, Att.s_Rang, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

	//DrawCube3D(VGet(plus.x - 100.0f, plus.y, plus.z + Att.s_Rang),
	//	VGet(plus.x+100.0f,plus.y+100.0f,plus.z+200.0f + Att.s_Rang),
	//	GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	
	if (Att.s_Rang >= Att.s_RangMax) {
		Att.s_AttackStartKey = false;
		Att.s_Rang = 0.0f;
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (HitCheck_Sphere_Sphere(c_Position, Att.s_Rang, c_enemyCol->c_ObjPos[i], 55)) {
			ene->SetEnemyMoveKey(i);
			//EneMoveFlag[i] = false;
			Att.s_ParaKey[i] = true;
		}
	}
}

void PLAYER::Player_Move(CAMERA* camera, ENEMY* ene)
{
	////移動場所の確認
	//VECTOR TempMoveVector;
	//VECTOR TempRotVector;

	//TempRotVector.y = 0.0f;

	//float Sin = sin(camera->GetCameraAngle() / 180.0f * DX_PI_F);
	//float Cos = cos(camera->GetCameraAngle() / 180.0f * DX_PI_F);

	//TempMoveVector.x = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
	//TempMoveVector.y = 0.0f;
	//TempMoveVector.z = c_MoveVector.x * Sin + c_MoveVector.z * Cos;

	//TempRotVector.x = 0.0f;
	//TempRotVector.y += 0.001f;
	//TempRotVector.z = 0.0f;

	//移動してるかどうか
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	if (Key_Look == false) {
		// プレイヤー移動
		if (((g_NowKey & PAD_INPUT_LEFT) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0)c_MoveVector.x = -c_movespeed;

			//TempRotVector.x = 0.0f;
			//TempRotVector.y += -270.0f;
			//TempRotVector.z = 0.0f;
		}

		if (((g_NowKey & PAD_INPUT_RIGHT) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0)c_MoveVector.x = c_movespeed;

			//TempRotVector.x = 0.0f;
			//TempRotVector.y += 270.0f;
			//TempRotVector.z = 0.0f;
		}

		if (((g_NowKey & PAD_INPUT_DOWN) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0)c_MoveVector.z = -c_movespeed;

			//TempRotVector.x = 0.0f;
			//TempRotVector.y += -90.0f;
			//TempRotVector.z = 0.0f;
		}

		if (((g_NowKey & PAD_INPUT_UP) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0)c_MoveVector.z = c_movespeed;

			//TempRotVector.x = 0.0f;
			//TempRotVector.y += 90.0f;
			//TempRotVector.z = 0.0f;
		}
	}
	//Gキーを押したらプレイヤーが一定時間止まる
	if (CheckHitKey(KEY_INPUT_G)) Damage.s_paralyzeKey = true;
	if (Damage.s_paralyzeKey == true) Player_Paralyze();

	c_StmCount = StaminaCount(c_MoveFlag);		//スタミナ管理

	if (((g_NowKey & PAD_INPUT_2) != 0) && ((g_NowKey & g_OldKey) == 0) && Att.s_AttackStartKey == false)Att.s_AttackStartKey = true;
	if (Att.s_AttackStartKey == true) Player_Attack(ene/*, TempRotVector*/);
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (Att.s_ParaKey[i] == true) {
			if (Att.s_TimePara++ >= Att.s_TimeMaxPara) {
				Att.s_TimePara = 0;
				ene->SetEnemyMoveKey(i);
			}
		}
	}

	//printfDx("%f\n", c_Rotation.y);
	//c_Rotation = VAdd(c_Rotation, TempRotVector);

	//VECTOR c_plus;

	//DrawCube3D(VGet(c_Position.x + c_Rotation.y - 100.0f, c_Position.y, c_Position.z + c_Rotation.y),
	//	VGet(c_Position.x + c_Rotation.y + 100.0f, c_Position.y + 100.0f, c_Position.z + c_Rotation.y + 200.0f),
	//	GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

	//移動フラグがたってたら移動
	if (c_MoveFlag == true)
	{
		//移動場所の確認
		VECTOR TempMoveVector;
		
		float Sin = sin(camera->GetCameraAngle() / 180.0f * DX_PI_F);
		float Cos = cos(camera->GetCameraAngle() / 180.0f * DX_PI_F);

		TempMoveVector.x = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.x * Sin + c_MoveVector.z * Cos;

		//当たり判定の確認
		if (Collision_Sphere(VAdd(c_Position, TempMoveVector), ene->c_ObjPos[0], 55) == false &&
			Collision_Cube(VAdd(c_Position, TempMoveVector), ene->c_ObjPos[1], 55) == false &&
			Collision_Cube(VAdd(c_Position, TempMoveVector), ene->c_ObjPos[2], 55) == false) {
			c_Position = VAdd(c_Position, TempMoveVector);		//移動
			//c_Rotation = VAdd(c_Rotation, TempRotVector);
			//c_Rotation = TempRotVector;
		}
	}

	if (Collision_Player) {
		Collision_Draw(ene->c_ObjPos);//デバック用
	}
}

void PLAYER::Collision_Draw(VECTOR EnemyPos[ENEMY_MAX]) {

	VECTOR Copy_Vect1;//オブジェクトのコピー
	VECTOR Copy_Vect2;//オブジェクトのコピー

	//プレイヤーのコリジョン
	Copy_Vect1 = c_Position; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
	Copy_Vect2 = c_Position; Copy_Vect2.x += CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
	DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
	Copy_Vect1 = c_Position; Copy_Vect1.x -= CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
	Copy_Vect2 = c_Position; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
	DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
	Copy_Vect1 = c_Position; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z -= CHAR_SIZE_Z;
	Copy_Vect2 = c_Position; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
	DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
	Copy_Vect1 = c_Position; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
	Copy_Vect2 = c_Position; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z += CHAR_SIZE_Z;
	DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);





	//オブジェクトのコリジョン
	for (int i = 1; i < 3; i++) {
		Copy_Vect1 = EnemyPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = EnemyPos[i]; Copy_Vect2.x += CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = EnemyPos[i]; Copy_Vect1.x -= CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = EnemyPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = EnemyPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z -= CHAR_SIZE_Z;
		Copy_Vect2 = EnemyPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = EnemyPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = EnemyPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z += CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);

		/*Copy_Vect1 = c_enemyCol->c_ObjPos[i];	Copy_Vect1.x += 55.0f;
		Copy_Vect2 = c_enemyCol->c_ObjPos[i];	Copy_Vect2.z += 55.0f;
		Copy_Vect3 = c_enemyCol->c_ObjPos[i];	Copy_Vect3.x += 55.0f;	Copy_Vect3.z += 55.0f;
		DrawLine3D(c_enemyCol->c_ObjPos[i], Copy_Vect1, 0xffffff);
		DrawLine3D(c_enemyCol->c_ObjPos[i], Copy_Vect2, 0xffffff);
		DrawLine3D(Copy_Vect1, Copy_Vect3, 0xffffff);
		DrawLine3D(Copy_Vect2, Copy_Vect3, 0xffffff);*/
	}

	//半径を５５に統一している
	DrawSphere3D(EnemyPos[0], 55.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

}