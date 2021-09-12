#include "DxLib.h"
#include "Character.h"

int pattern_blue = 0;//０は通常。１は移動が減らない。２は攻撃が減らない。３はどっちも減らない

CHARACTER::CHARACTER()
{
	for (int i = 0; i < 3; i++) {
		Stamina.s_Count[i] = Stamina.s_StaminaMax;
	}
}

CHARACTER::~CHARACTER()
{
}

void CHARACTER::Character_Init() {
	for (int i = 0; i < 3; i++) {
		Stamina.s_Count[i] = Stamina.s_StaminaMax;
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
			if (pattern_blue == 0 || pattern_blue == 2) {
				Stamina.s_Count[num]--;
			}
			Stamina.s_RecoveryCount[num] = 30;//移動などでスタミナを消費したら30フレーム回復しないようにする
		}
	}

	return Stamina.s_Count[num];
}

int CHARACTER::PlayerStaminaCount(bool MoveFlag,bool StmOver, int count, const int countMAX) {
	if (StmOver == true) {
		if (MoveFlag == false) {
			if (count < countMAX) {
				count++;
			}
		}
		else {
			if (count > 0) {
				if (pattern_blue == 0 || pattern_blue == 2) {
					count--;
				}
				
			}
		}
	}
	else {
		if (count < countMAX) {
			count++;
		}
	}

	return count;
}

int CHARACTER::AttackStaminaCount(int num) {
	
	if (pattern_blue == 0 || pattern_blue == 1) {
		Stamina.s_Count[num] -= 45;
	}
	
	Stamina.s_RecoveryCount[num] = 30;//移動などでスタミナを消費したら30フレーム回復しないようにする

	return Stamina.s_Count[num];
}//エネミー攻撃によるスタミナカウント