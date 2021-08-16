#pragma once

extern int PixelShaderHandle;
extern int VertexShaderHandle;
extern float LightRotateAngle;
extern float LightRotateAngle2;
extern int SpotLightHandle;
extern int PointLightHandle;
extern int DirLightHandle;
extern int i, j;
extern float DrawX, DrawZ;
extern int count;
extern int cntFlg;
extern bool finish;		//ゲームが終わったか判定（true:ゲーム再開 false:タイトルへ戻る)
extern bool judgefinish;	//決着ついたか判定	true:終了 false:続ける
extern int WaitTime;

extern VECTOR LightPos;
extern bool LightFlg;//止まっているか調べる( TRUE:動く FALSE:止まっている )


void Light();
void Light_init();
void Light_SetUp();