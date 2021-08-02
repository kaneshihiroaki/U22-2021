#pragma once
class CHARACTER
{
public:
	CHARACTER();
	~CHARACTER();

protected:
	int StaminaCount(bool MoveFlag);	//プレイヤースタミナカウント

private:
	//スタミナ関連
	struct Stamina
	{
		//bool s_MoveFlag;	//移動しているのか判定
		int s_Count = 300;		//動いている時間をカウント
		const int s_StaminaMax = 300;		//スタミナの最大値
	}; Stamina Stamina;
};
