#include <DxLib.h>
#include "enemy.h"

ENEMY::ENEMY()
{
	//オブジェクトの座標初期化
	c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	c_ObjPos[1] = VGet(300.0f, 50.0f, 50.0f);
	c_ObjPos[2] = VGet(50.0f, 50.0f, 170.0f);
}

ENEMY::~ENEMY()
{
}

void ENEMY::Enemy_Creat() {
	//オブジェクト描画
	DrawSphere3D(c_ObjPos[0], 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	DrawCube3D(c_ObjPos[1], VAdd(c_ObjPos[1], VECTOR{ 50,50,50 }), GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
	DrawCube3D(c_ObjPos[2], VAdd(c_ObjPos[2], VECTOR{ 50,50,50 }), GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}