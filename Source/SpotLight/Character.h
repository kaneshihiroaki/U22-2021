#pragma once
class CHARACTER
{
public:
	CHARACTER();
	~CHARACTER();

protected:
	int StaminaCount(bool MoveFlag,int num);	//エネミースタミナカウント
	int PlayerStaminaCount(bool MoveFlag,int count);//プレイヤースタミナカウント
	void Character_Init();

private:
	//スタミナ関連
	struct Stamina
	{
		//bool s_MoveFlag;	//移動しているのか判定
		int s_Count[3];		//動いている時間をカウント
		int s_PlayerCount;
		int s_RecoveryCount[3];//回復するまでのインターバル
		const int s_StaminaMax = 300;		//スタミナの最大値
	}; Stamina Stamina;
};
