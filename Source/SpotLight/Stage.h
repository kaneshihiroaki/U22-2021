#pragma once
#include "DxLib.h"

#define SphereAmount 40

class ENEMY;
class PLAYER;

class STAGE
{
public:
	STAGE();
	~STAGE();

	int c_StageModel;	//ステージのインポート用変数
	VECTOR c_StageScale;	//ステージの大きさ
	VECTOR c_StagePosition;	//ステージの位置

	
	int c_SphereModel[SphereAmount];	//光る球体インポート用変数
	VECTOR c_SpherePosition[SphereAmount];	//光る球体の位置
	VECTOR c_SphereScale;	//光る球体の大きさ
	

	void Stage_Make(ENEMY* enemy, PLAYER* player);	//ステージ作成
	void Stage_Col(ENEMY* enemy,PLAYER* player);		//当たり判定
	void init();	//初期化

private:
	//横幅と奥行き
	float c_width;
	float c_depth;

};