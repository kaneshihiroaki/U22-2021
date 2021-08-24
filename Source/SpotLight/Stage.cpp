#include <math.h>
#include "Stage.h"
#include "enemy.h"
#include "Player.h"

STAGE::STAGE()
{
	//// 座標初期化
	//c_StagePosition = VGet(100.0f, 0.0f, 0.0f);
	////大きさ初期化
	//c_StageScale = { 0.5f,0.5f,0.5f };

	// ３Ｄモデルの読み込み
	c_StageModel = MV1LoadModel("Model/Stage3.mv1");

	//MV1SetPosition(c_StageModel, c_StagePosition);
	//MV1SetScale(c_StageModel, c_StageScale);

}

STAGE::~STAGE()
{
}

void STAGE::init() {
	// 座標初期化
	c_StagePosition = VGet(100.0f, 0.0f, 0.0f);
	//大きさ初期化
	c_StageScale = { 1.0f,1.0f,1.0f };

	//横幅と奥行き
	c_width = 2600;
	c_depth = 1300;

	MV1SetPosition(c_StageModel, c_StagePosition);
	MV1SetScale(c_StageModel, c_StageScale);
}

void STAGE::Stage_Make(ENEMY* enemy, PLAYER* player) {
	//ステージの当たり判定
	Stage_Col(enemy, player);

	//床の描画
	MV1DrawModel(c_StageModel);
	//DrawCube3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1500.0f, 50.0f, 1200.0f), GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

void STAGE::Stage_Col(ENEMY* enemy, PLAYER* player) {
	//上
	DrawLine3D(VGet(c_StagePosition.x - (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) + (c_depth / 2)),
		VGet(c_StagePosition.x + (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) + (c_depth / 2)), 0xFFFFFF);
	//下
	DrawLine3D(VGet(c_StagePosition.x - (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) - (c_depth / 2)),
		VGet(c_StagePosition.x + (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) - (c_depth / 2)), 0xFFFFFF);
	//左
	DrawLine3D(VGet(c_StagePosition.x - (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) + (c_depth / 2)),
		VGet(c_StagePosition.x - (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) - (c_depth / 2)), 0xFFFFFF);
	//右
	DrawLine3D(VGet(c_StagePosition.x + (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) + (c_depth / 2)),
		VGet(c_StagePosition.x + (c_width / 2), c_StagePosition.y + 50.0f, c_StagePosition.z + (250) - (c_depth / 2)), 0xFFFFFF);

	//右上の点：VGet(c_StagePosition.x + 2000.0f, c_StagePosition.y + 50.0f, c_StagePosition.z + 2000.0f);
	//左上の点：VGet(c_StagePosition.x - 2000.0f, c_StagePosition.y + 50.0f, c_StagePosition.z + 2000.0f);
	//右下の点：VGet(c_StagePosition.x + 2000.0f, c_StagePosition.y + 50.0f, c_StagePosition.z - 2000.0f);
	//左下の点：VGet(c_StagePosition.x - 2000.0f, c_StagePosition.y + 50.0f, c_StagePosition.z - 2000.0f);

	/****************************************
	//プレイヤーの当たり判定を設定
	*****************************************/

	//中心点割り出し
	float halfx = (c_StagePosition.x + 2000.0f + c_StagePosition.x + 2000.0f +
		c_StagePosition.x - 2000.0f + c_StagePosition.x - 2000.0f) / 4;
	float halfz = (c_StagePosition.z + 2000.0f + (250) + c_StagePosition.z - 2000.0f + (250) +
		c_StagePosition.z + 2000.0f + (250) + c_StagePosition.z - 2000.0f + (250)) / 4;

	//中心点とプレイヤーの座標の距離
	float playerdistx = player->GetFuturePos().x - halfx;
	float playerdistz = player->GetFuturePos().z - halfz;
	float enemydistx;
	float enemydistz;

	//プレイヤーとの当たり判定の計算
	float posx = cos(0) * playerdistx + sin(0) * playerdistz;
	float posz = -sin(0) * playerdistx + cos(0) * playerdistz;

	//プレイヤーの当たり判定
	if (-c_width / 2.0f <= posx && c_width / 2.0f >= posx &&
		-c_depth / 2.0f <= posz && c_depth / 2.0f >= posz) {
		//return true;
		player->SetPlayerInStage();
	}
	else {
		player->SetPlayerOutStage();
	}

	/****************************************
	//敵の当たり判定を設定
	*****************************************/
	for (int i = 0; i < ENEMY_MAX; i++) {
		//中心点割り出し
		float enehalfx = (c_StagePosition.x + 2000.0f + c_StagePosition.x + 2000.0f +
			c_StagePosition.x - 2000.0f + c_StagePosition.x - 2000.0f) / 4;
		float enehalfz = (c_StagePosition.z + 2000.0f + c_StagePosition.z - 2000.0f +
			c_StagePosition.z + 2000.0f + c_StagePosition.z - 2000.0f) / 4;

		//中心点と敵の座標の距離
		float enedistx = enemy->GetEnemyMoveKey(i).x - enehalfx;
		float enedistz = enemy->GetEnemyMoveKey(i).z - enehalfz;

		//敵との当たり判定の計算
		float posx = cos(0) * enedistx + sin(0) * enedistz;
		float posz = -sin(0) * enedistx + cos(0) * enedistz;

		//敵の当たり判定
		if (-c_width / 2.0f <= posx && c_width / 2.0f >= posx &&
			-c_depth / 2.0f <= posz && c_depth / 2.0f >= posz) {
			enemy->SetEnemyStageInKey(i);
		}
		else {
			enemy->SetEnemyStageOutKey(i);
		}
	}
}

