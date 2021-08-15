#define _USE_MATH_DEFINES
#include <DxLib.h>
#include "Player.h"
#include "enemy.h"
#include "Camera.h"
#include <math.h>
//#include "Main.h"
#include "Debug.h"
#include "Light.h"


PLAYER::PLAYER()
{
	//// プレイヤー座標初期化
	//c_Position = VGet(100.0f, 100.0f, 0.0f);
	//c_PlayerAng = 0;	//プレイヤーの角度
	////プレイヤー回転（ラジアン変換）
	//c_Rotation = VGet(0.0f, (c_PlayerAng *(M_PI/180)), 0.0f);
	////プレイヤーの大きさ初期化
	//c_AddPosPlay = { 0.5f,0.5f,0.5f };

	//c_MoveFlag = FALSE;	//プレイヤーが移動しているのか判定

	//c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	//c_StmCount = 300;		//プレイヤーの体力

	//c_Acc = 0.0f;

	// ３Ｄモデルの読み込み
	c_PlayerModel = MV1LoadModel("Model/MyPlayer.mv1");
	//c_PlayerModel = MV1LoadModel("Model/player_debug.mv1");

	//c_enemyCol = new ENEMY();
}

PLAYER::~PLAYER()
{
}

void PLAYER::init() {
	// プレイヤー座標初期化
	c_Position = VGet(100.0f, 100.0f, 0.0f);
	c_PlayerAng = 0;	//プレイヤーの角度
	//プレイヤー回転（ラジアン変換）
	c_Rotation = VGet(0.0f, (c_PlayerAng * (M_PI / 180)), 0.0f);
	//プレイヤーの大きさ初期化
	c_AddPosPlay = { 0.5f,0.5f,0.5f };

	c_MoveFlag = FALSE;	//プレイヤーが移動しているのか判定

	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	c_StmCount = 300;		//プレイヤーの体力

	c_Acc = 0.0f;
}

void PLAYER::Player_Controller() {
	//プレイヤー
	// 画面に映る位置に３Ｄモデルを移動
	MV1SetPosition(c_PlayerModel, c_Position);
	MV1SetRotationXYZ(c_PlayerModel, c_Rotation);
	MV1SetScale(c_PlayerModel, c_AddPosPlay);
	SetFontSize(18);
	DrawFormatString(10, 670, 0x888888, "スタミナ：%d / %d", c_StmCount, c_StmMax);

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

bool PLAYER::Player_AttackCol(VECTOR AttPosRU, VECTOR AttPosLU, VECTOR AttPosRD, VECTOR AttPosLD, ENEMY* enepos,int num, float ang) {
	//中心点割り出し
	float halfx = (AttPosRU.x + AttPosRD.x + AttPosLU.x + AttPosLD.x) / 4;
	float halfz = (AttPosRU.z + AttPosRD.z + AttPosLU.z + AttPosLD.z) / 4;

	//中心点と敵の座標の距離
	float distx = enepos->c_ObjPos[num].x - halfx;
	float distz = enepos->c_ObjPos[num].z - halfz;

	//当たり判定の計算
	float posx = cos(ang) * distx + sin(ang) * distz;
	float posz = -sin(ang) * distx + cos(ang) * distz;

	//矩形と点の当たり判定を行う
	if (-Att.s_width /*/ 2.0f*/ <= posx && Att.s_width /*/ 2.0f*/ >= posx &&
		-Att.s_heigt / 2.0f <= posz && Att.s_heigt / 2.0f >= posz) {
		return true;
	}

	return false;
}

void PLAYER::Player_Attack(ENEMY* ene, VECTOR Player_rot) {

	//一度だけ取得
	if (Att.s_GetOneRot == false) {
		//移動場所の確認
		Att.s_RotSin = sin(Player_rot.y);
		Att.s_RotCos = cos(Player_rot.y);
		Att.s_Posx = c_Position.x;
		Att.s_Posz = c_Position.z;
		Att.s_GetOneRot = true;
	}

	//プレイヤーの前方方向取得
	float x = Att.s_Posx + (Att.s_RotSin * Att.s_Rang);
	float z = Att.s_Posz + (Att.s_RotCos * Att.s_Rang);

	//攻撃が前方に進む
	Att.s_Rang += Att.s_AttackSpeed;
	
	//下横
	DrawLine3D(VGet(x + (Att.s_RotCos * Att.s_width), c_Position.y, z - (Att.s_RotSin * Att.s_width)),
		VGet(x - (Att.s_RotCos * Att.s_width), c_Position.y, z + (Att.s_RotSin * Att.s_width)), 0x888888);

	//右縦
	DrawLine3D(VGet(x + (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z - (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
		VGet(x + (Att.s_RotCos * Att.s_width), c_Position.y, z - (Att.s_RotSin * Att.s_width)), 0x888888);

	//左縦
	DrawLine3D(VGet(x - (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z + (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
		VGet(x - (Att.s_RotCos * Att.s_width), c_Position.y, z + (Att.s_RotSin * Att.s_width)), 0x888888);

	//上横
	DrawLine3D(VGet(x - (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z + (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
		VGet(x + (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z - (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)), 0x888888);

	//右上は x + (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z - (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)
	//左上は x - (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z + (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)
	//右下は x + (Att.s_RotCos * Att.s_width), c_Position.y, z - (Att.s_RotSin * Att.s_width)
	//左下は x - (Att.s_RotCos * Att.s_width), c_Position.y, z + (Att.s_RotSin * Att.s_width)

	//攻撃時間
	if (Att.s_Rang >= Att.s_RangMax) {
		Att.s_AttackStartKey = false;
		Att.s_GetOneRot = false;
		Att.s_Rang = 0.0f;
	}
	
	//当たり判定
	for (int i = 0; i < ENEMY_MAX; i++) {
		if(Player_AttackCol(VGet(x + (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z - (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
			VGet(x - (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z + (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
			VGet(x + (Att.s_RotCos * Att.s_width), c_Position.y, z - (Att.s_RotSin * Att.s_width)),
			VGet(x - (Att.s_RotCos * Att.s_width), c_Position.y, z + (Att.s_RotSin * Att.s_width)),
			ene,i, Player_rot.y) == true){
			ene->SetEnemyMoveFalseKey(i);
			Att.s_ParaKey[i] = true;
		}
	}
}

void PLAYER::Player_Move(CAMERA* camera, ENEMY* ene)
{
	//移動場所の確認
	VECTOR TempRotVector;

	//移動してるかどうか
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	if (Key_Look == false) {
		// プレイヤー移動
		//左上移動
		if (((g_NowKey & PAD_INPUT_LEFT) != 0) && ((g_NowKey & PAD_INPUT_UP) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.x = c_movespeed;
				c_MoveVector.z = c_movespeed;
			}

			//角度代入
			c_PlayerAng = 315.0f;
		}
		//左下移動
		else if (((g_NowKey & PAD_INPUT_LEFT) != 0) && ((g_NowKey & PAD_INPUT_DOWN) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.x = c_movespeed;
				c_MoveVector.z = c_movespeed;
			}
			//角度代入
			c_PlayerAng = 225.0f;
		}
		//右下移動
		else if (((g_NowKey & PAD_INPUT_RIGHT) != 0) && ((g_NowKey & PAD_INPUT_DOWN) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.x = c_movespeed;
				c_MoveVector.z = c_movespeed;
			}
			//角度代入
			c_PlayerAng = 135.0f;
		}
		//右上移動
		else if (((g_NowKey & PAD_INPUT_RIGHT) != 0) && ((g_NowKey & PAD_INPUT_UP) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.x = c_movespeed;
				c_MoveVector.z = c_movespeed;
			}
			//角度代入
			c_PlayerAng = 45.0f;
		}
		//右移動
		else if ((g_NowKey & PAD_INPUT_RIGHT) != 0)
		{
			c_MoveFlag = true;
			if (c_StmCount > 0)c_MoveVector.x = c_movespeed;

			//角度代入
			c_PlayerAng = 90.0f;
		}
		//左方向
		else if ((g_NowKey & PAD_INPUT_LEFT) != 0)
		{
			c_MoveFlag = true;
			if (c_StmCount > 0)c_MoveVector.x = c_movespeed;

			//角度代入
			c_PlayerAng = 270.0f;
		}
		//下方向
		else if ((g_NowKey & PAD_INPUT_DOWN) != 0)
		{
			c_MoveFlag = true;
			if (c_StmCount > 0)c_MoveVector.z = c_movespeed;

			//角度代入
			c_PlayerAng = 180.0f;
		}
		//上方向
		else if ((g_NowKey & PAD_INPUT_UP) != 0)
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.z = c_movespeed;
			}

			//角度代入
			c_PlayerAng = 0.0f;
		}
	}

	//Gキーを押したらプレイヤーが一定時間止まる
	if (CheckHitKey(KEY_INPUT_G)) Damage.s_paralyzeKey = true;
	if (Damage.s_paralyzeKey == true) Player_Paralyze();

	c_StmCount = PlayerStaminaCount(c_MoveFlag, c_StmCount);        //スタミナ管理

	//移動フラグがたってたら移動
	if (c_MoveFlag == true)
	{
		if (c_Acc == 0.0f) {//初速
			c_Acc = 0.9f;
		}
		else if (c_Acc == 1.0f) {
		}
		else if (c_Acc > 1.0f) {
			c_Acc = 1.0f;
		}
		else {//加速度
			c_Acc += 0.01f;
		}

		//移動場所の確認
		VECTOR TempMoveVector;
		float Sin1 = sin(c_PlayerAng * (M_PI / 180));
		float Cos1 = cos(c_PlayerAng * (M_PI / 180));

		TempMoveVector.x = c_MoveVector.x * Sin1 * c_Acc;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z * Cos1 * c_Acc;

		//当たり判定の確認
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (Collision_Sphere(VAdd(c_Position, TempMoveVector), ene->c_ObjPos[i], 55) == true) {
				if (Att.s_ParaKey[i] == false) {
					c_MoveFlag = false;
				}
				else if ((ene->Enemy_Push(i, c_Position, TempMoveVector)) == false) {//falseなら動かせなかった。
					c_MoveFlag = false;
				}
			}
		}
		if (c_MoveFlag) {//移動できるときにのみとおる
			c_Position = VAdd(c_Position, TempMoveVector);		//移動

			//角度代入
			c_Rotation.x = 0.0f;
			c_Rotation.y = c_PlayerAng * (M_PI / 180);
			c_Rotation.z = 0.0f;
		}
	}
	else {
		c_Acc = 0.0f;
	}


	//攻撃
	if (((g_KeyFlg & PAD_INPUT_2) != 0) && Att.s_AttackStartKey == false)Att.s_AttackStartKey = true;
	if (Att.s_AttackStartKey == true) Player_Attack(ene, c_Rotation);
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (Att.s_ParaKey[i] == true) {
			if (Att.s_TimePara++ >= Att.s_TimeMaxPara) {
				Att.s_TimePara = 0;
				ene->SetEnemyMoveTrueKey(i);
			}
		}
	}


	if (Collision_Player) {
		Collision_Draw(ene->c_ObjPos);//デバック用
	}
}

bool PLAYER::Player_Push(CAMERA* camera, VECTOR EnemyCol[ENEMY_MAX], VECTOR PushVec)
{
	//しびれているかどうか。しびれていないならfalseで帰る
	if (Damage.s_paralyzeKey == false) {
		return false;
	}

	//移動場所の確認
	VECTOR TempMoveVector;
	//VECTOR TempRotVector;




	//移動してるかどうか
	c_MoveFlag = true;
	c_MoveVector = PushVec;

	//float Sin = sin(camera->GetCameraAngle() / 180.0f * DX_PI_F);
	//float Cos = cos(camera->GetCameraAngle() / 180.0f * DX_PI_F);

	//TempMoveVector.x = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
	//TempMoveVector.y = 0.0f;
	//TempMoveVector.z = c_MoveVector.x * Sin + c_MoveVector.z * Cos;

	//TempRotVector.x = 0.0f;
	//TempRotVector.y = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
	//TempRotVector.z = 0.0f;

	//移動フラグがたってたら移動
	if (c_MoveFlag == true)
	{

		TempMoveVector.x = c_MoveVector.x;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z;


		//当たり判定の確認
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (Collision_Sphere(VAdd(c_Position, TempMoveVector), EnemyCol[i], 55) == true) {
				c_MoveFlag = false;
			}
		}
		if (c_MoveFlag) {//移動できるときにのみとおる
			c_Position = VAdd(c_Position, TempMoveVector);		//移動
			//c_Rotation = VAdd(c_Rotation, TempRotVector);
		}
	}

	return c_MoveFlag;
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

bool PLAYER::CheckHit(VECTOR c_Position, VECTOR LightPos) {

	VECTOR Player = c_Position;

	VECTOR Light = LightPos;

	/*SetFontSize(20);
	DrawFormatString(10, 100, 0x888888, "x:%f", Player.x);
	DrawFormatString(10, 130, 0x888888, "y:%f", Player.y);
	DrawFormatString(10, 160, 0x888888, "z:%f", Player.z);
	DrawFormatString(10, 190, 0x888888, "x:%f", Light.x);
	DrawFormatString(10, 220, 0x888888, "y:%f", Light.y);
	DrawFormatString(10, 250, 0x888888, "z:%f", Light.z);*/
	float cx = Light.x - Player.x;
	float cz = Light.z - Player.z;

	float cr = (cx * cx) + (cz * cz);
	float lr = (10.0f + 70.0f);
	float lr2 = (lr * lr);

	/*DrawSphere3D(Player,10.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	DrawSphere3D(Light,70.0f, 32, GetColor(255,0, 255), GetColor(255, 255, 255), TRUE);*/

	// playerとlightの当たり判定( TRUE:当たっている FALSE:当たっていない )
	if (cr <= lr2&&LightFlg == false){
		Key_Look = true;
		c_MoveFlag = false;
		return true;
	}

	return false;
}
