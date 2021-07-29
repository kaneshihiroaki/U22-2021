#include "DxLib.h"
#include <math.h>

#define DRAW_NUM	(3)
#define SPACE		(512.0f)

int PixelShaderHandle;
int VertexShaderHandle;
float LightRotateAngle;
int SpotLightHandle;
int PointLightHandle;
int i, j;
float DrawX, DrawZ;
VECTOR LightPos;

void Light_init() {

	// 頂点シェーダーを読み込む
	VertexShaderHandle = LoadVertexShader("Shader/NormalMesh_SpotPointLightVS.vso");

	// ピクセルシェーダーを読み込む
	PixelShaderHandle = LoadPixelShader("Shader/NormalMesh_SpotPointLightPS.pso");

	// 使用する頂点シェーダーをセット
	SetUseVertexShader(VertexShaderHandle);

	// 使用するピクセルシェーダーをセット
	SetUsePixelShader(PixelShaderHandle);

	// ライトの位置を回転する値を初期化
	LightRotateAngle = 0.0f;

	// 標準ライトを無効にする
	SetLightEnable(FALSE);

	//ライトの処理を1ピクセルごとに行う（処理が重くなる）
	SetUsePixelLighting(TRUE);

	// スポットライトを作成する
	SpotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.18f, 0.15f, 1000.0f, 0.4f, 0.001662f, 0.000001f);

	// スポットライトのアンビエントカラーを黄色にする
	SetLightAmbColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	// スポットライトのディフューズカラーを黄色にする
	SetLightDifColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	// ポイントライトを作成する
	PointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 7000.0f, 1.016523f, 0.000100f, 0.000010f);
	
	// ポイントライトのアンビエントカラーを無効にする
	SetLightAmbColorHandle(PointLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	// ポイントライトのディフューズカラーを強い色にする
	SetLightDifColorHandle(PointLightHandle, GetColorF(5.0f, 5.0f, 10.0f, 0.0f));

	// グローバルアンビエントライト( 大域環境光 )を２０％の明るさにする
	SetGlobalAmbientLight(GetColorF(0.2f, 0.2f, 0.2f, 0.0f));
	
	//ポイントライトの位置の更新
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 1000.0f, 0.0f));
}
void Light() 
{
	// ライトの位置の回転値を加算
	LightRotateAngle += 0.01f;

	LightPos = VGet(sin(-LightRotateAngle) * 200.0f, 800.0f, sin(-LightRotateAngle * 2) * 150.0f);

	// スポットライトの位置の更新
	SetLightPositionHandle(SpotLightHandle, LightPos);
}