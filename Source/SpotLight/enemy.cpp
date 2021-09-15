#define _USE_MATH_DEFINES

#include <DxLib.h>
#include <math.h>

#include "enemy.h"
#include "Light.h"
#include "Player.h"
#include "Camera.h"
#include "debug.h"
#include "GameSound.h"


int ENEMY_WIN;//どの敵が勝ったか調べる変数
int ENEMY_WIN_COUNT1;//敵１の勝利数
int ENEMY_WIN_COUNT2;//敵２の勝利数
int ENEMY_WIN_COUNT3;//敵３の勝利数


ENEMY::ENEMY()
{
	////オブジェクトの座標初期化
	//c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	//c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	//c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// ３Ｄモデルの読み込み
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == 0) {//赤
			c_EnemyModel[i] = MV1LoadModel("Model/EnMe3.mv1");
			c_WinEnemyModel[i] = MV1LoadModel("Model/EnMe4.mv1");
		}
		else if (i == 1) {//緑
			//			c_EnemyModel[i] = MV1LoadModel("Model/obj.mv1");
			c_EnemyModel[i] = MV1LoadModel("Model/EnMe5.mv1");
			c_WinEnemyModel[i] = MV1LoadModel("Model/EnMe6.mv1");
		}
		else {//オレンジ
			//			c_EnemyModel[i] = MV1LoadModel("Model/obj.mv1");
			c_EnemyModel[i] = MV1LoadModel("Model/EnMe7.mv1");
			c_WinEnemyModel[i] = MV1LoadModel("Model/EnMe8.mv1");
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
	c_ObjPos[0] = VGet(-150.0f, 100.0f, 0.0f);
	c_ObjPos[1] = VGet(150.0f, 100.0f, 0.0f);
	c_ObjPos[2] = VGet(450.0f, 100.0f, 0.0f);

	// ３Ｄモデルの読み込み
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		c_StmCount[i] = c_StmMax;	//エネミーの体力の最大
		c_Rotation[i] = VGet(0.0f, (180.0f * (M_PI / 180)), 0.0f);//エネミーの回転
		c_Enemy_MoveAng[i] = 180;//エネミーの角度
		c_EnemySpeed[i] = 0.0f;//エネミーのスピード
		c_EnemyState[i] = ENEMY_IDLE;//エネミーの初期状態
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//エネミーのスケールをいれている
		MV1SetScale(c_WinEnemyModel[i], c_AddPosEnemy[i]);//エネミーのスケールをいれている

		c_EnemyAddVect[i] = VGet(0.0f, 0.0f, 0.0f);//追い越す処理のときに加算するベクトルを保存
		c_EnemyFrameCount[i] = 0;//追い越す処理のときにフレを数える
		Damage[i].s_paralyzeKey = false;//しびれた時の変数初期化
		c_AliveEnemy[i] = true;
		Damage[i].s_ParaTime = 0;
		c_EnemyWin[i] = false;
		//攻撃しているフラグを初期化
		Att[i].s_AttackStartKey = false;
		Att[i].s_GetOneRot = false;
		Att[i].s_Rang = 0.0f;
	}

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//スポットライトの座標
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
	Character_Init();
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_TempMoveVector[i] = VGet(0.0f, 0.0f, 0.0f);
	}
}

void ENEMY::Sadon_init() {
	

	// ３Ｄモデルの読み込み
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (c_AliveEnemy[i] == true) {
			c_ObjPos[i] = VGet(-150.0f + (300.0f * i), 100.0f, 0.0f);
		}
		else {//エネミーが存在しない。ので遠くに飛ばす
			c_ObjPos[i] = VGet(-5000.0f, 100.0f, 0.0f);
		}
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		c_StmCount[i] = c_StmMax;	//エネミーの体力の最大
		c_Rotation[i] = VGet(0.0f, 0.0f /*(c_PlayerAng * (M_PI / 180))*/, 0.0f);//エネミーの回転
		c_Enemy_MoveAng[i] = 0;//エネミーの角度
		c_EnemySpeed[i] = 0.0f;//エネミーのスピード
		c_EnemyState[i] = ENEMY_IDLE;//エネミーの初期状態
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//エネミーのスケールをいれている
		MV1SetScale(c_WinEnemyModel[i], c_AddPosEnemy[i]);//エネミーのスケールをいれている

		c_EnemyAddVect[i] = VGet(0.0f, 0.0f, 0.0f);//追い越す処理のときに加算するベクトルを保存
		c_EnemyFrameCount[i] = 0;//追い越す処理のときにフレを数える
		Damage[i].s_paralyzeKey = false;//しびれた時の変数初期化
		//c_AliveEnemy[i] = true;
		Damage[i].s_ParaTime = 0;
		c_EnemyWin[i] = false;
		//攻撃しているフラグを初期化
		Att[i].s_AttackStartKey = false;
		Att[i].s_GetOneRot = false;
		Att[i].s_Rang = 0.0f;
	}

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//スポットライトの座標
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
	Character_Init();
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_TempMoveVector[i] = VGet(0.0f, 0.0f, 0.0f);
	}
}

void ENEMY::Enemy_Creat() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (c_AliveEnemy[i] == false)continue;//存在しないとき
		if (Damage[i].s_ParaTime%20<10 || Key_Look) {//0~9までは描画10~19までは描画しない。決着後消えるのはおかしいので表示する
			if (c_EnemyWin[i]) {//勝利判定しているとき
				MV1SetPosition(c_WinEnemyModel[i], c_ObjPos[i]);//エネミーの移動後位置をいれてる
				MV1SetRotationXYZ(c_WinEnemyModel[i], c_Rotation[i]);//エネミーの角度をいれている
				MV1DrawModel(c_WinEnemyModel[i]);				 //エネミーのモデル描画
			}
			else {
				MV1SetPosition(c_EnemyModel[i], c_ObjPos[i]);//エネミーの移動後位置をいれてる
				MV1SetRotationXYZ(c_EnemyModel[i], c_Rotation[i]);//エネミーの角度をいれている
				MV1DrawModel(c_EnemyModel[i]);				 //エネミーのモデル描画
			}
		}
	}
	//オブジェクト描画
	//DrawSphere3D(c_ObjPos[0], 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[1], VAdd(c_ObjPos[1], VECTOR{ 50,50,50 }), GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[2], VAdd(c_ObjPos[2], VECTOR{ 50,50,50 }), GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

void ENEMY::debug() {
	//printfDx("%d\n", GetEnemyMoveKey(2));
}

void ENEMY::Enemy_State(int num, PLAYER* player, ENEMY* enemy) {
	if (Key_Look)return;//勝敗が決したときなどに入らないようにするフラグ
	if (c_AliveEnemy[num] == false)return;//エネミーが存在していないとき
	if (num == 0) {//タイプがっきー
		Ga_Move(num, player);
		Ga_Attack(num, player);
	}
	else if (num == 1) {//タイプサングラス
		San_Move(num);
		San_Attack(num, player);
	}
	else if (num == 2) {//タイプアスカ
		A_Move(num);
		A_Attack(num, player);
	}
	else {//それ以外
		Bot_Normal(num, player);
	}
	
	
	if (Damage[num].s_paralyzeKey == true) {
		if (CheckSoundMem(damage_sound) == 0) {
			PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
		}
		Enemy_Paralyze(num);//しびれているならカウントしないといけない
	}
	
	SetFontSize(20);
	switch (c_EnemyState[num])
	{
	case ENEMY_IDLE:
		c_StmCount[num] = StaminaCount(false, num);		//スタミナ回復
		if (Debug_Enemy) {
			DrawFormatString(1100, 420 + 20 * num, 0xFFFFFF, "%d IDLE\n", num);
		}
		break;
	case ENEMY_MOVE:
		Enemy_Move(num, player, enemy);
		if (Debug_Enemy) {
			DrawFormatString(1100, 420 + 20 * num, 0xFFFFFF, "%d MOVE\n", num);
		}
		break;
	case ENEMY_ATTACK:
		break;
	}

	if (Debug_Enemy) {
		DrawFormatString(1100, 620 + 20 * num, 0xFFFFFF, "%d %d\n", num, c_StmCount[num]);
		if (Damage[num].s_paralyzeKey) {
			DrawFormatString(1100, 520 + 20 * num, 0xFFFFFF, "%d True\n", num);
		}
		else {
			DrawFormatString(1100, 520 + 20 * num, 0xFFFFFF, "%d False\n", num);
		}
		DrawFormatString(500, 520 + 20 * num, 0xFFFFFF, "x:%lf y:%lf z:%lf\n", c_ObjPos[num].x, c_ObjPos[num].y, c_ObjPos[num].z);
		if (c_EnemyWin[num]) {
			DrawFormatString(100, 520 + 20 * num, 0xFFFFFF, "true\n");
		}
		else {
			DrawFormatString(100, 520 + 20 * num, 0xFFFFFF, "false\n");
		}
		
	}
	
}

void ENEMY::Enemy_Move(int num, PLAYER* player, ENEMY* enemy)
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
		if (c_StmCount[num] > 0)c_MoveVector.x = c_movespeed;
		p_Enemy_MoveAng = 90;//右

	}

	if (c_SpotPos.x + c_SpotRadius < c_ObjPos[num].x) {
		c_MoveFlag = true;
		if (c_StmCount[num] > 0)c_MoveVector.x = -c_movespeed;
		p_Enemy_MoveAng = 270;//左

	}

	if (c_SpotPos.z - c_SpotRadius > c_ObjPos[num].z) {
		c_MoveFlag = true;
		if (c_StmCount[num] > 0)c_MoveVector.z = c_movespeed;
		p_Enemy_MoveAng = 0;//上

	}

	if (c_SpotPos.z + c_SpotRadius < c_ObjPos[num].z) {
		c_MoveFlag = true;
		if (c_StmCount[num] > 0)c_MoveVector.z = -c_movespeed;
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
		//if (i == 1)DrawSphere3D(Check_Future_Pos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		if (c_EnemyFrameCount[num] == 0) {



			
			//if(Collision_Cube())　//角度を参照していないので変更をする
			if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], c_ObjPos[i], 30, 150, 105, 55) == true) {

				float rad = c_Rotation[num].y + (M_PI / 2);
				c_EnemyAddVect[num].x = 5.0f * sinf(rad)/* - c_MoveVector.z * sin(rad)*/;
				c_EnemyAddVect[num].z = 5.0f * cosf(rad) /*+ c_MoveVector.z * cos(rad)*/;

				c_MoveVector.x += c_EnemyAddVect[num].x;
				c_MoveVector.z += c_EnemyAddVect[num].z;

				c_EnemyFrameCount[num] = 1;

				//c_MoveVector.x += 5.0f;

				SetFontSize(20);
				//DrawFormatString(1100, 600, 0xFFFFFF, "いるぜ\n");

			}
			//1回だけ通る
			if (i == 0 || (num == 0 && i == 1)) {
				if (Collision_Cube2(Check_Future_Pos, c_Rotation[num],player->c_Position, 30, 150, 105, 55) == true) {

					float rad = c_Rotation[num].y + (M_PI / 2);
					c_EnemyAddVect[num].x = 5.0f * sinf(rad)/* - c_MoveVector.z * sin(rad)*/;
					c_EnemyAddVect[num].z = 5.0f * cosf(rad) /*+ c_MoveVector.z * cos(rad)*/;

					c_MoveVector.x += c_EnemyAddVect[num].x;
					c_MoveVector.z += c_EnemyAddVect[num].z;

					c_EnemyFrameCount[num] = 1;

					//c_MoveVector.x += 5.0f;

					SetFontSize(20);
					//DrawFormatString(1100, 600, 0xFFFFFF, "いるぜ\n");

				}
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

	if (Damage[num].s_paralyzeKey == true) c_MoveFlag = false; //しびれているなら移動フラグをoffにする
	
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
		//VECTOR TempMoveVector;

		c_TempMoveVector[num].x = c_MoveVector.x * Coefficient * c_EnemySpeed[num];
		c_TempMoveVector[num].y = 0.0f;
		c_TempMoveVector[num].z = c_MoveVector.z * Coefficient * c_EnemySpeed[num];


		//当たりl判定の確認
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], c_TempMoveVector[num]), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT ) == true) {
				if (Enemy_Push(i, player,enemy, c_TempMoveVector[num], 0) == false) {//falseなら動かせなかった
					VECTOR Reserve_Vect = c_TempMoveVector[num];//X座標を0にしてみる

					float Reserve = Reserve_Vect.x;//X座標を0にしてみる
					Reserve_Vect.x = 0.0f;//
					
					if (Coefficient!=1.0f) {
						if ((Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) && (Enemy_Push(i, player, enemy,  Reserve_Vect,0) == false)) {
							Reserve_Vect.x = Reserve;//
							Reserve = Reserve_Vect.z;//
							Reserve_Vect.z = 0.0f;//
							if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
								if (Enemy_Push(i, player,enemy, Reserve_Vect, 0) == false) {//falseなら動かせなかった
									c_MoveFlag = false;
								}
							}
						}
					}
					else {
						c_MoveFlag = false;
					}
					
					

					if (c_MoveFlag) {//TRUEなら移動先を変更
						c_TempMoveVector[num] = Reserve_Vect;
					}
					
				}
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], c_TempMoveVector[num]), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
			if (player->Player_Push(player,enemy,c_TempMoveVector[num], 0) == false) {//falseなら動かせなかった
				VECTOR Reserve_Vect = c_TempMoveVector[num];//X座標を0にしてみる

				float Reserve = Reserve_Vect.x;//X座標を0にしてみる
				Reserve_Vect.x = 0.0f;//
				if (Coefficient != 1.0) {
					if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true && player->Player_Push(player, enemy,  Reserve_Vect, 0) == false) {//falseなら動かせなかった

						Reserve_Vect.x = Reserve;//
						Reserve = Reserve_Vect.z;//
						Reserve_Vect.z = 0.0f;//
						if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
							if (player->Player_Push(player, enemy, Reserve_Vect, 0) == false) {//falseなら動かせなかった
								c_MoveFlag = false;
							}
						}
					}
				}
				else {
					c_MoveFlag = false;
				}

				if (c_MoveFlag) {//TRUEなら移動先を変更
					c_TempMoveVector[num] = Reserve_Vect;
				}
			}
		}
		//c_MoveKeyがtrueだったらステージないにいる＝動く
		if (c_MoveFlag == true && c_MoveKey[num] == true)
		{
			c_ObjPos[num] = VAdd(c_ObjPos[num], c_TempMoveVector[num]);
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
bool ENEMY::Enemy_Push(int num, PLAYER* player, ENEMY* enemy, VECTOR PushVec, int count)
{
	//しびれているかどうか。しびれていないならfalseで帰るまたはカウントが3回目以上ならfalseでかえるオーバーフロー対策
	if (Damage[num].s_paralyzeKey == false || count > 2) {
		return false;
	}
	//ここで新しくローカル変数を作成
	//移動してるかどうか
	bool r_MoveFlag = true;
	VECTOR r_MoveVector = PushVec;

	float r_Coefficient = 1.0f;







	//移動フラグがたってたら移動
	if (r_MoveFlag == true)
	{
		//移動場所の確認
		c_TempMoveVector[num].x = r_MoveVector.x * r_Coefficient;
		c_TempMoveVector[num].y = 0.0f;
		c_TempMoveVector[num].z = r_MoveVector.z * r_Coefficient;


		//当たりl判定の確認
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], c_TempMoveVector[num]), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
				if (Enemy_Push(i, player, enemy, c_TempMoveVector[num], count + 1) == false) {//falseなら動かせなかった
					r_MoveFlag = false;
				}
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], c_TempMoveVector[num]), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
			if (player->Player_Push(player, enemy, c_TempMoveVector[num], count + 1) == false) {//falseなら動かせなかった
				r_MoveFlag = false;
			}
		}
		if (c_MoveKey[num] == false) {
			r_MoveFlag = false;
		}

		if (r_MoveFlag == true)
		{
			c_ObjPos[num] = VAdd(c_ObjPos[num], c_TempMoveVector[num]);
		}
	}
	//if (Collision_Player) {
	//	Collision_Draw();//デバック用
	//}

	return r_MoveFlag;
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
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)), 0x880000);

	//右縦
	DrawLine3D(VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)), 0x880000);

	//左縦
	DrawLine3D(VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)), 0x880000);

	//上横
	DrawLine3D(VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)), 0x880000);

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
			/*SetEnemyMoveFalseKey(i);*/SetEnemyParaKey(i);		//SetEnemyMoveFalseKeyはステージの判定に使うので変えました（名称以外は前のものと同じです）
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
	float posz = cos(ang) * distz + sin(ang) * distx;
	float posx = -sin(ang) * distz + cos(ang) * distx;


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
	
	if (Damage[num].s_ParaTime++ == Damage[num].s_MaxTimeParalyze) {
		Damage[num].s_paralyzeKey = false;
		Damage[num].s_ParaTime = 0;
	}
}


int ENEMY::EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos) {
	int Win_Count = 0;

	for (int i = 0; i < ENEMY_MAX; i++) {
		c_EnemyWin[i] = false;
		float ex = LightPos.x - c_ObjPos[i].x;
		float ez = LightPos.z - c_ObjPos[i].z;
		if (c_AliveEnemy[i] == false)continue;//存在していない
		float er = (ex * ex) + (ez * ez);
		float elr = ( 70.0f);
		float elr2 = (elr * elr);
		//DrawSphere3D(c_ObjPos[i], 10.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
		// enemyとlightの当たり判定
		if (er <= elr2) {
			c_EnemyWin[i] = true;
			Win_Count++;
			if (LightFlg == false) {
				if (i == 0) {
					ENEMY_WIN = 1;
				}
				else if (i == 1) {
					ENEMY_WIN = 2;
				}
				else if (i == 2) {
					ENEMY_WIN = 3;
				}
			}
		}

	}

	return Win_Count;
	

	/*SetFontSize(20);
	DrawFormatString(10, 100, 0x888888, "x:%f", Player.x);
	DrawFormatString(10, 130, 0x888888, "y:%f", Player.y);
	DrawFormatString(10, 160, 0x888888, "z:%f", Player.z);
	DrawFormatString(10, 190, 0x888888, "x:%f", Enemy.x);
	DrawFormatString(10, 220, 0x888888, "y:%f", Enemy.y);
	DrawFormatString(10, 250, 0x888888, "z:%f", Enemy.z);*/

}



void ENEMY::Ga_Attack(int num, PLAYER* player) {
	if (Att[num].s_AttackStartKey == true) {
		
		return; //攻撃中だと帰る
	}
	if (Ga_Interval[num] > 0) {//攻撃のインターバル
		Ga_Interval[num]--;
		return;
	}
	if (c_StmCount[num] < c_AttackStm + 1 || Damage[num].s_paralyzeKey == true) {
		
		return;
	}//スタミナが15以下または、しびれていたら攻撃できないので帰る

	VECTOR Check_Future_Pos = c_ObjPos[num];//前方に座標をうつすため。長さ９６
	Check_Future_Pos.x += 96.0f * sinf(c_Rotation[num].y)/* - c_MoveVector.z * sin(rad)*/;
	Check_Future_Pos.z += 96.0f * cosf(c_Rotation[num].y) /*+ c_MoveVector.z * cos(rad)*/;
	//DrawSphere3D(Check_Future_Pos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	if (((g_KeyFlg & PAD_INPUT_5) != 0)) {
		Att[num].s_AttackStartKey = true;//今のところR1をおすと敵が攻撃
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}

	//他のエネミーが自分の周りにいるかどうか判定
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;

		//自分の前方をみる
		if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], c_Rotation[i], 30, 96, 105, 55) == true) {

			Ga_Interval[num] = Ga_Debug_Interval;//攻撃のインターバル60フレーム
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy1_attack_sound) == 0) {
					PlaySoundMem(enemy1_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
		//自分の後ろや周りをみる
		if (Collision_Cube(c_ObjPos[num], c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH * 2, ENEMY_HEIGHT * 2, 55, 55) == true) {
			float PosX = c_ObjPos[i].x - c_ObjPos[num].x;
			float PosZ = c_ObjPos[i].z - c_ObjPos[num].z;
			float rad = atan2f(c_ObjPos[i].z - c_ObjPos[num].z, c_ObjPos[i].x - c_ObjPos[num].x) * 180 / M_PI;
			//向いている角度の調整
			if ((rad >= -180 && rad < -135) || (rad >= 135)) {//左
				c_Rotation[num].y = 270.0f;
			}
			else if (rad >= -135 && rad < -45) {//下
				c_Rotation[num].y = 180.0f;
			}
			else if (rad >= -45 && rad < 45) {//右
				c_Rotation[num].y = 90.0f;
			}
			else if (rad >= 45 && rad < 135) {//上
				c_Rotation[num].y = 0.0f;
			}

			Ga_Interval[num] = Ga_Debug_Interval;//攻撃のインターバル60フレーム
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy1_attack_sound) == 0) {
					PlaySoundMem(enemy1_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
	}
	//プレイヤーが自分の周りにいるかどうか判定
	//自分の前方をみる
	if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], player->c_Position, 30, 150, 105, 55) == true) {
		Ga_Interval[num] = Ga_Debug_Interval;//攻撃のインターバル60フレー
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy1_attack_sound) == 0) {
				PlaySoundMem(enemy1_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
	//自分の後ろや周りをみる
	if (Collision_Cube(c_ObjPos[num], c_Rotation[num], player->c_Position, ENEMY_WIDTH * 2, ENEMY_HEIGHT * 2, 55, 55) == true) {
		float PosX = player->c_Position.x - c_ObjPos[num].x;
		float PosZ = player->c_Position.z - c_ObjPos[num].z;
		float rad = atan2f(player->c_Position.z - c_ObjPos[num].z, player->c_Position.x - c_ObjPos[num].x) * 180 / M_PI;
		//向いている角度の調整
		if ((rad >= -180 && rad < -135) || (rad >= 135)) {//左
			c_Rotation[num].y = 270.0f;
		}
		else if (rad >= -135 && rad < -45) {//下
			c_Rotation[num].y = 180.0f;
		}
		else if (rad >= -45 && rad < 45) {//右
			c_Rotation[num].y = 90.0f;
		}
		else if (rad >= 45 && rad < 135) {//上
			c_Rotation[num].y = 0.0f;
		}

		Ga_Interval[num] = Ga_Debug_Interval;//攻撃のインターバル60フレー
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy1_attack_sound) == 0) {
				PlaySoundMem(enemy1_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
}

void ENEMY::Ga_Move(int num, PLAYER* player) {
	if (WaitTime == 0 || time_All >= 480) {//スポットライトの動きが止まっているまたは、8秒以上になっている
		if (c_StmCount[num] >= (int)(c_StmMax * 0.5)) {//スタミナが50%以上なら勝ちを取りに行こうと動く
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < 10) {//スタミナが10以下なら回復に専念
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}
	else {//スタートして0~8秒までの間は普通に動く
		if (c_StmCount[num] >= c_StmMax-10) {//スタミナが最大－10以上ならほぼ全回復と判断して移動に移る
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < (int)(c_StmMax * 0.3)) {//スタミナが30%以下なら回復に専念
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}
	
}
void ENEMY::A_Move(int num) {
	if (WaitTime == 0 || time_All >= 480) {//スポットライトの動きが止まっているまたは、8秒以上になっている
		if (c_StmCount[num] >= (int)(c_StmMax * 0.4)) {//スタミナが40%以上なら勝ちを取りに行こうと動く
			//if (check_1 == 0 && check_2 == 0) {//敵と味方両方とも範囲にいない場合行動に移る
				c_EnemyState[num] = ENEMY_MOVE;
			//}
		}
		else if (c_StmCount[num] < 10) {//スタミナが10以下なら回復に専念
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}
	else {//スタートして0~8秒までの間は普通に動く
		if (c_StmCount[num] >= (int)(c_StmMax * 0.8)) {//スタミナが80%以上ならほぼ全回復と判断して移動に移る
			//if (check_1 == 0 && check_2 == 0) {//敵と味方両方とも範囲にいない場合行動に移る
			//	
			//}
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < (int)(c_StmMax * 0.3)) {//スタミナが30%以下なら回復に専念
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}

}
void ENEMY::A_Attack(int num, PLAYER* player) {
	if (Att[num].s_AttackStartKey == true) {
		
		return; //攻撃中だと帰る
	}
	if (Ga_Interval[num] > 0) {//攻撃のインターバル
		Ga_Interval[num]--;
		return;
	}
	if (c_StmCount[num] < c_AttackStm + 1 || Damage[num].s_paralyzeKey == true) {
		
		return; 
	}//スタミナが15以下だと帰る

	
	if (((g_KeyFlg & PAD_INPUT_5) != 0)) {
		Att[num].s_AttackStartKey = true;//今のところR1をおすと敵が攻撃
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}

	//他のエネミーが自分の周りにいるかどうか判定
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;

		
		//自分の後ろや周りをみる
		if (Collision_Cube(c_ObjPos[num], c_Rotation[num], c_ObjPos[i], 200,200, 55, 55) == true) {
			float PosX = c_ObjPos[i].x - c_ObjPos[num].x;
			float PosZ = c_ObjPos[i].z - c_ObjPos[num].z;
			float rad = atan2f(c_ObjPos[i].z - c_ObjPos[num].z, c_ObjPos[i].x - c_ObjPos[num].x) * 180 / M_PI;
			//向いている角度の調整
			if ((rad >= -180 && rad < -135) || (rad >= 135)) {//左
				c_Rotation[num].y = 270.0f;
			}
			else if (rad >= -135 && rad < -45) {//下
				c_Rotation[num].y = 180.0f;
			}
			else if (rad >= -45 && rad < 45) {//右
				c_Rotation[num].y = 90.0f;
			}
			else if (rad >= 45 && rad < 135) {//上
				c_Rotation[num].y = 0.0f;
			}

			Ga_Interval[num] = A_Debug_Interval;//攻撃のインターバル60フレーム
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy3_attack_sound) == 0) {
					PlaySoundMem(enemy3_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
	}
	//プレイヤーが自分の周りにいるかどうか判定
	//自分の後ろや周りをみる
	if (Collision_Cube(c_ObjPos[num], c_Rotation[num], player->c_Position, 200,200, 55, 55) == true) {
		float PosX = player->c_Position.x - c_ObjPos[num].x;
		float PosZ = player->c_Position.z - c_ObjPos[num].z;
		float rad = atan2f(player->c_Position.z - c_ObjPos[num].z, player->c_Position.x - c_ObjPos[num].x) * 180 / M_PI;
		//向いている角度の調整
		if ((rad >= -180 && rad < -135) || (rad >= 135)) {//左
			c_Rotation[num].y = 270.0f;
		}
		else if (rad >= -135 && rad < -45) {//下
			c_Rotation[num].y = 180.0f;
		}
		else if (rad >= -45 && rad < 45) {//右
			c_Rotation[num].y = 90.0f;
		}
		else if (rad >= 45 && rad < 135) {//上
			c_Rotation[num].y = 0.0f;
		}

		Ga_Interval[num] = A_Debug_Interval;//攻撃のインターバル60フレー
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy3_attack_sound) == 0) {
				PlaySoundMem(enemy3_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
}

void ENEMY::San_Attack(int num, PLAYER* player) {
	if (Att[num].s_AttackStartKey == true) {
		

		return; //攻撃中だと帰る
	}
	if (Ga_Interval[num] > 0) {//攻撃のインターバル
		Ga_Interval[num]--;
		return;
	}
	if (c_StmCount[num] < c_AttackStm + 1 || Damage[num].s_paralyzeKey == true) {
		
		return;//スタミナが15以下だと帰る
	}
	VECTOR Check_Future_Pos = c_ObjPos[num];//前方に座標をうつすため。長さ123
	Check_Future_Pos.x += 123.0f * sinf(c_Rotation[num].y)/* - c_MoveVector.z * sin(rad)*/;
	Check_Future_Pos.z += 123.0f * cosf(c_Rotation[num].y) /*+ c_MoveVector.z * cos(rad)*/;
	//DrawSphere3D(Check_Future_Pos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	if (((g_KeyFlg & PAD_INPUT_5) != 0)) {
		Att[num].s_AttackStartKey = true;//今のところR1をおすと敵が攻撃
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}

	//他のエネミーが自分の周りにいるかどうか判定
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;

		//自分の前方をみる
		if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], c_Rotation[i], 30, 96, 105, 55) == true) {

			Ga_Interval[num] = San_Debug_Interval;//攻撃のインターバル10フレーム
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy2_attack_sound) == 0) {
					PlaySoundMem(enemy2_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
		//自分の後ろや周りをみる
		if (Collision_Cube(c_ObjPos[num], c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH * 2, ENEMY_HEIGHT * 2, 55, 55) == true) {
			float PosX = c_ObjPos[i].x - c_ObjPos[num].x;
			float PosZ = c_ObjPos[i].z - c_ObjPos[num].z;
			float rad = atan2f(c_ObjPos[i].z - c_ObjPos[num].z, c_ObjPos[i].x - c_ObjPos[num].x) * 180 / M_PI;
			//向いている角度の調整
			if ((rad >= -180 && rad < -135) || (rad >= 135)) {//左
				c_Rotation[num].y = 270.0f;
			}
			else if (rad >= -135 && rad < -45) {//下
				c_Rotation[num].y = 180.0f;
			}
			else if (rad >= -45 && rad < 45) {//右
				c_Rotation[num].y = 90.0f;
			}
			else if (rad >= 45 && rad < 135) {//上
				c_Rotation[num].y = 0.0f;
			}

			Ga_Interval[num] = San_Debug_Interval;//攻撃のインターバル10フレーム
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy2_attack_sound) == 0) {
					PlaySoundMem(enemy2_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
	}
	//プレイヤーが自分の周りにいるかどうか判定
	//自分の前方をみる
	if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], player->c_Position, 30, 150, 105, 55) == true) {
		Ga_Interval[num] = San_Debug_Interval;//攻撃のインターバル10フレー
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy2_attack_sound) == 0) {
				PlaySoundMem(enemy2_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
	//自分の後ろや周りをみる
	if (Collision_Cube(c_ObjPos[num], c_Rotation[num], player->c_Position, ENEMY_WIDTH * 2, ENEMY_HEIGHT * 2, 55, 55) == true) {
		float PosX = player->c_Position.x - c_ObjPos[num].x;
		float PosZ = player->c_Position.z - c_ObjPos[num].z;
		float rad = atan2f(player->c_Position.z - c_ObjPos[num].z, player->c_Position.x - c_ObjPos[num].x) * 180 / M_PI;
		//向いている角度の調整
		if ((rad >= -180 && rad < -135) || (rad >= 135)) {//左
			c_Rotation[num].y = 270.0f;
		}
		else if (rad >= -135 && rad < -45) {//下
			c_Rotation[num].y = 180.0f;
		}
		else if (rad >= -45 && rad < 45) {//右
			c_Rotation[num].y = 90.0f;
		}
		else if (rad >= 45 && rad < 135) {//上
			c_Rotation[num].y = 0.0f;
		}

		Ga_Interval[num] = San_Debug_Interval;//攻撃のインターバル10フレー
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy2_attack_sound) == 0) {
				PlaySoundMem(enemy2_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
}

void ENEMY::San_Move(int num) {
	
	if (WaitTime == 0 || time_All >= 540) {//スポットライトの動きが止まっているまたは、9秒以上になっている
		if (c_StmCount[num] >= (int)(c_StmMax*0.15)) {//スタミナが15%以上なら勝ちを取りに行こうと動く
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < 10) {//スタミナが10以下なら回復に専念
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}
	else {//スタートして0~8秒までの間は普通に動く
		if (c_StmCount[num] >= c_StmMax-10) {//スタミナが最大－10以上ならほぼ全回復と判断して移動に移る
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < 10) {//スタミナが10以下なら回復に専念
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}

}

void ENEMY::Bot_Normal(int num, PLAYER* player) {

	if (c_StmCount[num] >= c_StmMax - 10) {//スタミナがマックスになったら移動する。
		c_EnemyState[num] = ENEMY_MOVE;
	}
	if (c_StmCount[num] == 10) {//スタミナ０になったらアイドルになって回復する。
		c_EnemyState[num] = ENEMY_IDLE;
	}
}

