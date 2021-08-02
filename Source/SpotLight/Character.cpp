#include "DxLib.h"
#include "Character.h"

CHARACTER::CHARACTER()
{
}

CHARACTER::~CHARACTER()
{
}

int CHARACTER::StaminaCount(bool MoveFlag) {
	if (MoveFlag == false) {
		if (Stamina.s_Count < Stamina.s_StaminaMax) {
			Stamina.s_Count++;
		}
	}
	else {
		if (Stamina.s_Count > 0) {
			Stamina.s_Count--;
		}
	}

	return Stamina.s_Count;
}