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

extern VECTOR LightPos;
extern bool LightFlg;//�~�܂��Ă��邩���ׂ�( TRUE:���� FALSE:�~�܂��Ă��� )


void Light();
void Light_init();
void Light_SetUp();