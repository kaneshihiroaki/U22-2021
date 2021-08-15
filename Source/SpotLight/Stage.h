#pragma once
#include "DxLib.h"

class STAGE
{
public:
	STAGE();
	~STAGE();

	int c_StageModel;	//ステージのインポート用変数
	VECTOR c_StageScale;	//ステージの大きさ
	VECTOR c_StagePosition;	//ステージの位置

	void Stage_Make();	//ステージ作成
	void init();	//初期化

private:

};