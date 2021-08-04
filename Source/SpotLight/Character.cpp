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
	}
}

int CHARACTER::StaminaCount(bool MoveFlag,int num) {
	if (MoveFlag == false) {
		if (Stamina.s_Count[num] < Stamina.s_StaminaMax) {
			Stamina.s_Count[num]++;
		}
	}
	else {
		if (Stamina.s_Count > 0) {
			Stamina.s_Count[num]--;
		}
	}

	return Stamina.s_Count[num];
}

