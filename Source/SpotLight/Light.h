#pragma once

extern int ModelHandle;
extern int PixelShaderHandle;
extern int VertexShaderHandle;
extern float LightRotateAngle;
extern int SpotLightHandle;
extern int PointLightHandle;
extern int i, j;
extern float DrawX, DrawZ;
extern VECTOR LightPos;

void Light();
void Light_init();