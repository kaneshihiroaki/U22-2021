#pragma once
#include "DxLib.h"
#include "enemy.h"
#include "Character.h"

#define CHAR_SIZE_X		55.0f		// キャラのサイズ
#define CHAR_SIZE_Y		55.0f		// キャラのサイズ
#define CHAR_SIZE_Z		55.0f		// キャラのサイズ

class CAMERA;
class ENEMY;
class CHARACTER;

extern int PLAYER_WIN_COUNT;//playerが勝った数を入れる変数


class PLAYER : public CHARACTER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//プレイヤーのインポート用変数
	int c_WinPlayerModel;	//プレイヤーのインポート用変数
	VECTOR c_AddPosPlay;	//プレイヤーの大きさ
	VECTOR c_Rotation;		//プレイヤーの回転
	VECTOR c_Position;	//プレイヤーの位置

	//プレイヤーの被弾判定
	void SetPlayerParalyze(){
		Damage.s_paralyzeKey = true;//trueしか使ってないので書き換えます
	}

	void Player_Controller();
	void Player_Move( PLAYER* player, ENEMY* ene);
	bool Player_Push(PLAYER* player, ENEMY* enemy,  VECTOR PushVec, int count);
	bool CheckHit(VECTOR Player, VECTOR LightPos);
	void init();	//初期化

	void Player_Paralyze();	//主人公がしびれる（止まる）←しびれているときに入る関数。しびれのカウントをして直すのもここ


	bool CheckPara();//調べたいエネミーがしびれているかどうかの判定
	////痺れ（ダメージ関連）
	//struct Damage
	//{
	//	int s_ParaTime = 0;					//プレイヤーが痺れる時間をカウント
	//	bool s_paralyzeKey = false;		//プレイヤーがしびれているか判定する（true:痺れてる false:痺れていない）
	//	const int s_MaxTimeParalyze = 30;		//プレイヤーが痺れている時間
	//}; Damage Damage;

	//プレイヤーを痺れさせるセッター
	void SetParalyzeKey() {
		Damage.s_paralyzeKey = true;
	}

	//プレイヤーがステージにいるかどうか
	void SetPlayerOutStage() {
		c_StageIn = false;
	}
	void SetPlayerInStage() {
		c_StageIn = true;
	}
	VECTOR GetFuturePos() { return VAdd(c_Position, c_TempMoveVector); };

private:
	float c_PlayerAng;		//プレイヤーの角度

	bool c_RotFlag;		//プレイヤーが回転している
	bool c_MoveFlag;	//プレイヤーが移動しているのか判定
	bool c_StageIn;		//ステージ内にいるかどうか判定
	int c_StmCount;		//プレイヤーの体力
	int c_StmMax;	//スタミナの最大値
	bool c_Slide;	//プレイヤーを滑らせる判定変数
	
	int c_GearStm;	//スタミナが切れた後の処理を選択
	bool c_StmStop;	//スタミナが切れたことを知らせる変数 true:切れてない false:切れた


	VECTOR c_MoveVector;	//移動変数
	VECTOR c_TempMoveVector; //移動先を計算する変数

	bool c_Player_win = false;//プレイヤーがスポットライトに入っているときモデルを変更するようの変数

	float c_movespeed = 7.0f;	//プレイヤー移動スピード
	float c_Acc;	//加速を制御

		//痺れ（ダメージ関連）
	struct Damage
	{
		int s_ParaTime = 0;					//プレイヤーが痺れる時間をカウント
		bool s_paralyzeKey = false;		//プレイヤーがしびれているか判定する（true:痺れてる false:痺れていない）
		const int s_MaxTimeParalyze = 60;		//プレイヤーが痺れている時間
	}; Damage Damage;

	struct Attack {
		//攻撃を行うかどうか判定変数
		bool s_AttackStartKey = false;
		int s_AttackCons;		//プレイヤーの攻撃時消費体力
		bool s_GetOneRot = false;
		float s_Rang = 0.0f;	//攻撃時間(範囲)

		//攻撃の開始地点を決める変数
		float s_RotSin = 0.0f;
		float s_RotCos = 0.0f;
		float s_Posx = 0.0f;
		float s_Posz = 0.0f;
		const float s_width = 100.0f;
		const float s_heigt = 100.0f;

		//攻撃速度(終了地点)
		const float s_AttackSpeed = 10.0f;
		const float s_RangMax = 500.0f;

		int s_Memo=0;
		int s_TimePara = 0;
		const int s_TimeMaxPara = 50;
	}; Attack Att;
	
	void Collision_Draw(VECTOR EnemyPos[ENEMY_MAX]);//デバックモードで使用
	
	void Player_Attack(ENEMY* ene,VECTOR Player_rot);		//攻撃
	bool Player_AttackCol(VECTOR AttPosRU, VECTOR AttPosLU, VECTOR AttPosRD, VECTOR AttPosLD, ENEMY* enepos, int num, float ang);

	//ENEMY* c_enemyCol;		//敵の座標を取得するために取得
};


