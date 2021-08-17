#include "DxLib.h"
#include "Character.h"

CHARACTER::CHARACTER()
{
	for (int i = 0; i < 3; i++) {
		Stamina.s_Count[i] = 300;
	}
}

CHARACTER::~CHARACTER()
{
}

void CHARACTER::Character_Init() {
	for (int i = 0; i < 3; i++) {
		Stamina.s_Count[i] = 300;
		Stamina.s_RecoveryCount[i] = 0;
	}
}

int CHARACTER::StaminaCount(bool MoveFlag,int num) {
	if (MoveFlag == false) {
		if (Stamina.s_RecoveryCount[num] == 0 && Stamina.s_Count[num] < Stamina.s_StaminaMax) {
			Stamina.s_Count[num]++;
		}
		else {
			Stamina.s_RecoveryCount[num]--;//回復できない状態
		}
	}
	else {
		if (Stamina.s_Count > 0) {
			Stamina.s_Count[num]--;
			Stamina.s_RecoveryCount[num] = 30;//移動などでスタミナを消費したら30フレーム回復しないようにする
		}
	}

	return Stamina.s_Count[num];
}

int CHARACTER::PlayerStaminaCount(bool MoveFlag, int count) {
	if (MoveFlag == false) {
		if (count < Stamina.s_StaminaMax) {
			count++;
		}
	}
	else {
		if (count > 0) {
			count--;
		}
	}

	return count;
}

int CHARACTER::AttackStaminaCount(int num) {
	
	Stamina.s_Count[num] -= 15;
	Stamina.s_RecoveryCount[num] = 30;//移動などでスタミナを消費したら30フレーム回復しないようにする

	return Stamina.s_Count[num];
}//エネミー攻撃によるスタミナカウント