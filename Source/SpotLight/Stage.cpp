#include "Stage.h"
#include <DxLib.h>

STAGE::STAGE()
{
}

STAGE::~STAGE()
{
}

void STAGE::Stage_Make() {
	//è∞ÇÃï`âÊ
	DrawCube3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1500.0f, 50.0f, 1200.0f), GetColor(0, 0, 0), GetColor(255, 255, 255), TRUE);
}