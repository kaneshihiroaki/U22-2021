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
	////オブジェクトの座標初期化
	//c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	//c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	//c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// ３Ｄモデルの読み込み
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == 0) {
			c_EnemyModel[i] = MV1LoadModel("Model/EnMe.mv1");
		}
		else {
			c_EnemyModel[i] = MV1LoadModel("Model/obj.mv1");
		}
		
		//c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		//c_MoveKey[i] = true;
		//c_StmCount[i] = 300;	//エネミーの体力の最大
		//c_Rotation[i] = VGet(0.0f, 0.0f /*(c_PlayerAng * (M_PI / 180))*/, 0.0f);//エネミーの回転
		//c_Enemy_MoveAng[i] = 0;//エネミーの角度
		//c_EnemySpeed[i] = 0.0f;//エネミーのスピード
		//c_EnemyState[i] = ENEMY_IDLE;//エネミーの初期状態
		//MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//エネミーのスケールをいれている

		//c_EnemyAddVect[i] = VGet(0.0f, 0.0f, 0.0f);//追い越す処理のときに加算するベクトルを保存
		//c_EnemyFrameCount[i] = 0;//追い越す処理のときにフレを数える
	}

	//c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//スポットライトの座標
	//Coefficient = 1.0f;
	//c_MoveFlag = FALSE;
	//c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
}

ENEMY::~ENEMY()
{
}

void ENEMY::init() {
	//オブジェクトの座標初期化
	c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// ３Ｄモデルの読み込み
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		c_StmCount[i] = 300;	//エネミーの体力の最大
		c_Rotation[i] = VGet(0.0f, 0.0f /*(c_PlayerAng * (M_PI / 180))*/, 0.0f);//エネミーの回転
		c_Enemy_MoveAng[i] = 0;//エネミーの角度
		c_EnemySpeed[i] = 0.0f;//エネミーのスピード
		c_EnemyState[i] = ENEMY_IDLE;//エネミーの初期状態
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//エネミーのスケールをいれている

		c_EnemyAddVect[i] = VGet(0.0f, 0.0f, 0.0f);//追い越す処理のときに加算するベクトルを保存
		c_EnemyFrameCount[i] = 0;//追い越す処理のときにフレを数える
	}

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//スポットライトの座標
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
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

	/****************
	ここから
	*****************/
	//敵が追い越す処理(敵)
	for (int i = 0; i < ENEMY_MAX; i++) {
		//if (num != 0)continue;//０のみ検証
		if (i == num)continue;
		VECTOR Check_Future_Pos = c_ObjPos[num];//変更してもいいようにローカルVEC変数
		Check_Future_Pos.x += (c_MoveVector.x * 15);//１～３０フレーム後のポジション（仮） speed×30フレーム
		Check_Future_Pos.z += (c_MoveVector.z * 15);//１～３０フレーム後のポジション（仮）
		if (i == 1)DrawSphere3D(Check_Future_Pos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		if (c_EnemyFrameCount[num] == 0) {



			
			//if(Collision_Cube())　//角度を参照していないので変更をする
			if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], c_ObjPos[i], 30, 150, 105, 55) == true) {

				float rad = c_Rotation[num].y + (M_PI / 2);
				c_EnemyAddVect[num].x = c_MoveVector.x * cos(rad) - c_MoveVector.z * sin(rad);
				c_EnemyAddVect[num].z = c_MoveVector.x * sin(rad) + c_MoveVector.z * cos(rad);

				c_MoveVector.x += c_EnemyAddVect[num].x;
				c_MoveVector.z += c_EnemyAddVect[num].z;

				c_EnemyFrameCount[num] = 1;

				//c_MoveVector.x += 5.0f;

				SetFontSize(20);
				DrawFormatString(1100, 600, 0xFFFFFF, "いるぜ\n");

			}
		}
		else if (c_EnemyFrameCount[num] < 30*(ENEMY_MAX-1)) {
			c_MoveVector.x += c_EnemyAddVect[num].x;
			c_MoveVector.z += c_EnemyAddVect[num].z;
			c_EnemyFrameCount[num]++;
		}
		else {
			c_EnemyFrameCount[num] = 0;
		}
	}
	//敵が追い越す処理（プレイヤー）
	/****************
	ここまで
	*****************/

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

	if (Damage[num].s_paralyzeKey == true) Enemy_Paralyze(num);//しびれているならカウントと移動フラグをoffにする
	if (((g_KeyFlg & PAD_INPUT_5) != 0) && Att[num].s_AttackStartKey == false)Att[num].s_AttackStartKey = true;//今のところR1をおすと敵が攻撃
	if (Att[num].s_AttackStartKey == true) Enemy_Attack(player, num);
	
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
			if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
				if (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false) {//falseなら動かせなかった
					VECTOR Reserve_Vect = TempMoveVector;//X座標を0にしてみる

					float Reserve = Reserve_Vect.x;//X座標を0にしてみる
					Reserve_Vect.x = 0.0f;//
					
					if (Coefficient!=1.0f) {
						if ((Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) && (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false)) {
							Reserve_Vect.x = Reserve;//
							Reserve = Reserve_Vect.z;//
							Reserve_Vect.z = 0.0f;//
							if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
								if (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false) {//falseなら動かせなかった
									c_MoveFlag = false;
								}
							}
						}
					}
					else {
						c_MoveFlag = false;
					}
					
					

					if (c_MoveFlag) {//TRUEなら移動先を変更
						TempMoveVector = Reserve_Vect;
					}
					
				}
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
			if (player->Player_Push(camera, c_ObjPos, TempMoveVector) == false) {//falseなら動かせなかった
				VECTOR Reserve_Vect = TempMoveVector;//X座標を0にしてみる

				float Reserve = Reserve_Vect.x;//X座標を0にしてみる
				Reserve_Vect.x = 0.0f;//
				if (Coefficient != 1.0) {
					if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true && player->Player_Push(camera, c_ObjPos, Reserve_Vect) == false) {//falseなら動かせなかった

						Reserve_Vect.x = Reserve;//
						Reserve = Reserve_Vect.z;//
						Reserve_Vect.z = 0.0f;//
						if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
							if (player->Player_Push(camera, c_ObjPos, Reserve_Vect) == false) {//falseなら動かせなかった
								c_MoveFlag = false;
							}
						}
					}
				}
				else {
					c_MoveFlag = false;
				}

				if (c_MoveFlag) {//TRUEなら移動先を変更
					TempMoveVector = Reserve_Vect;
				}
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


//numは押される側
bool ENEMY::Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec)
{
	//しびれているかどうか。しびれていないならfalseで帰る
	if (Damage[num].s_paralyzeKey == false) {
		return false;
	}

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
			if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector),c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
				c_MoveFlag = false;
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_Rotation[num], PlayerCol, ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
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


// プレイヤーとオブジェクトのあたり判定//角度を参照できるようにする（未実装）
//MyColが自分の中心座標、YouColが相手の中心座標、MyScaleが自分の大きさだったが、縦と横も追加する
bool Collision_Cube(VECTOR MyCol,VECTOR MyRot, VECTOR YouCol, float MyScale_X,float MyScale_Z, float YouScale_X, float YouScale_Z) {
	// 各座標を取得する
	VECTOR pos = MyCol;
	VECTOR rot = MyRot;
	VECTOR posYou = YouCol;

	/*********************************************************************************
	

	// 矩形の中心を原点とした相対座標を作成する
	VECTOR relative_position = VGet(posYou.x - pos.x,0.0f, posYou.z - pos.z);

	// 相対座標に対して矩形の回転を打ち消す逆行列を掛ける
	VECTOR transform_pos = VGet(
		cosf(rot.y) * relative_position.x + sinf(rot.y) * relative_position.z,
		0.0f,
		-sinf(rot.y) * relative_position.x + cosf(rot.y) * relative_position.z
	);

	// 矩形と点の当たり判定を行う
	if (-MyScale_X / 2.0f <= transform_pos.x && MyScale_X / 2.0f >= transform_pos.x &&
		-MyScale_Z / 2.0f <= transform_pos.z && MyScale_Z / 2.0f >= transform_pos.z)
	{
		return true;
	}
	***********************************************************************/

	//当たったらtrue
	if ((pos.x + MyScale_X > posYou.x - YouScale_X &&
	 	 pos.z + MyScale_Z > posYou.z - YouScale_Z) &&
		(pos.x - MyScale_X < posYou.x + YouScale_X &&
		 pos.z - MyScale_Z < posYou.z + YouScale_Z)) {
		return true;
	}

	return false;
}

//矩形と点の当たり判定（角度を考慮に入れている）
//これはまだ編集できそう（点のほうの大きさなどを考慮にいれることができそう）
bool ENEMY::Collision_Cube2(VECTOR MyCol, VECTOR MyRot, VECTOR YouCol, float MyScale_X, float MyScale_Z, float YouScale_X, float YouScale_Z) {
	// 各座標を取得する
	VECTOR pos = MyCol;
	VECTOR rot = MyRot;
	VECTOR posYou = YouCol;


	// 矩形の中心を原点とした相対座標を作成する
	VECTOR relative_position = VGet(posYou.x - pos.x, 0.0f, posYou.z - pos.z);

	// 相対座標に対して矩形の回転を打ち消す逆行列を掛ける
	VECTOR transform_pos = VGet(
		cosf(rot.y) * relative_position.x + sinf(rot.y) * relative_position.z,
		0.0f,
		-sinf(rot.y) * relative_position.x + cosf(rot.y) * relative_position.z
	);

	// 矩形と点の当たり判定を行う
	if (-MyScale_X / 2.0f <= transform_pos.x && MyScale_X / 2.0f >= transform_pos.x &&
		-MyScale_Z / 2.0f <= transform_pos.z && MyScale_Z / 2.0f >= transform_pos.z)
	{
		return true;
	}

	return false;
}


void ENEMY::Enemy_Attack(PLAYER* player, int num) {

	//一度だけ取得
	if (Att[num].s_GetOneRot == false) {
		//移動場所の確認
		Att[num].s_RotSin = sin(c_Rotation[num].y);
		Att[num].s_RotCos = cos(c_Rotation[num].y);
		Att[num].s_Posx = c_ObjPos[num].x;
		Att[num].s_Posz = c_ObjPos[num].z;
		Att[num].s_GetOneRot = true;
	}

	//エネミーの前方方向取得
	float x = Att[num].s_Posx + (Att[num].s_RotSin * Att[num].s_Rang);
	float z = Att[num].s_Posz + (Att[num].s_RotCos * Att[num].s_Rang);

	//攻撃が前方に進む
	Att[num].s_Rang += Att[num].s_AttackSpeed;

	//下横
	DrawLine3D(VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)), 0x888888);

	//右縦
	DrawLine3D(VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)), 0x888888);

	//左縦
	DrawLine3D(VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)), 0x888888);

	//上横
	DrawLine3D(VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)), 0x888888);

	//右上は x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_Position.y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)
	//左上は x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_Position.y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)
	//右下は x + (Att[num].s_RotCos * Att[num].s_width), c_Position.y, z - (Att[num].s_RotSin * Att[num].s_width)
	//左下は x - (Att[num].s_RotCos * Att[num].s_width), c_Position.y, z + (Att[num].s_RotSin * Att[num].s_width)

	//攻撃時間
	if (Att[num].s_Rang >= Att[num].s_RangMax) {
		Att[num].s_AttackStartKey = false;
		Att[num].s_GetOneRot = false;
		Att[num].s_Rang = 0.0f;
	}

	//エネミーの当たり判定
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;
		if (Enemy_AttackCol(VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
			VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
			VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)),
			VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)),
			c_ObjPos[i],num, c_Rotation[num].y) == true) {
			SetEnemyMoveFalseKey(i);
		}
	}

	//プレイヤーの当たり判定
	if (Enemy_AttackCol(VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)),
		player->c_Position, num, c_Rotation[num].y) == true) {
		player->SetPlayerParalyze();
		
	}
}

bool ENEMY::Enemy_AttackCol(VECTOR AttPosRU, VECTOR AttPosLU, VECTOR AttPosRD, VECTOR AttPosLD,VECTOR YouPos, int num, float ang) {
	//中心点割り出し
	float halfx = (AttPosRU.x + AttPosRD.x + AttPosLU.x + AttPosLD.x) / 4;
	float halfz = (AttPosRU.z + AttPosRD.z + AttPosLU.z + AttPosLD.z) / 4;

	//中心点と敵の座標の距離
	float distx = YouPos.x - halfx;
	float distz = YouPos.z - halfz;

	//当たり判定の計算
	float posx = cos(ang) * distx + sin(ang) * distz;
	float posz = -sin(ang) * distx + cos(ang) * distz;

	//矩形と点の当たり判定を行う
	if (-Att[num].s_width /*/ 2.0f*/ <= posx && Att[num].s_width /*/ 2.0f*/ >= posx &&
		-Att[num].s_heigt / 2.0f <= posz && Att[num].s_heigt / 2.0f >= posz) {
		return true;
	}

	return false;
}

bool ENEMY::CheckPara(int num) {
	return Damage[num].s_paralyzeKey;
}//調べたいエネミーがしびれているかどうかの判定


void ENEMY::Enemy_Paralyze(int num) {
	c_MoveFlag = false;

	if (Damage[num].s_ParaTime++ == Damage[num].s_MaxTimeParalyze) {
		Damage[num].s_paralyzeKey = false;
		Damage[num].s_ParaTime = 0;
	}
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