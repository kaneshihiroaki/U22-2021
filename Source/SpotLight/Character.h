#pragma once
class CHARACTER
{
public:
	CHARACTER();
	~CHARACTER();
	void Character_Init();

protected:
	int StaminaCount(bool MoveFlag,int num);	//エネミースタミナカウント
	int PlayerStaminaCount(bool MoveFlag,int count,const int countMAX);//プレイヤースタミナカウント
	int AttackStaminaCount( int num);	//エネミー攻撃によるスタミナカウント

private:
	//スタミナ関連
	struct Stamina
	{
		//bool s_MoveFlag;	//移動しているのか判定
		int s_Count[3];		//動いている時間をカウント
		int s_PlayerCount;
		int s_RecoveryCount[3];//回復するまでのインターバル
		const int s_StaminaMax = 300;		//敵のスタミナの最大値
		//const int s_PlayStaminaMax = 600;		//プレイヤーのスタミナの最大値
	}; Stamina Stamina;
};
