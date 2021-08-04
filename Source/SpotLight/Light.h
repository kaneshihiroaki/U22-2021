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
extern VECTOR dis;
extern VECTOR dis1;
extern VECTOR dis2;
extern VECTOR dis3;
extern VECTOR dis4;
extern VECTOR dis5;
extern VECTOR dis6;
extern VECTOR dis7;
extern VECTOR dis8;

void Light();
void Light_init();