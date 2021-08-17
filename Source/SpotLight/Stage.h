#pragma once
#include "DxLib.h"

class ENEMY;
class PLAYER;
class CHARACTER;

class STAGE
{
public:
	STAGE();
	~STAGE();

	int c_StageModel;	//ステージのインポート用変数
	VECTOR c_StageScale;	//ステージの大きさ
	VECTOR c_StagePosition;	//ステージの位置

	void Stage_Make(ENEMY* enemy, PLAYER* player);	//ステージ作成
	void Stage_Col(ENEMY* enemy,PLAYER* player);		//当たり判定
	void init();	//初期化

private:
	//横幅と奥行き
	float c_width;
	float c_depth;

};