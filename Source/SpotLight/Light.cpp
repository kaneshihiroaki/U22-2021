#include "DxLib.h"
#include <math.h>
#include "Debug.h"
#include "Light.h"

#define DRAW_NUM	(3)
#define SPACE		(512.0f)


int PixelShaderHandle;
int VertexShaderHandle;
float LightRotateAngle;
float LightRotateAngle2;
int SpotLightHandle;
int PointLightHandle;
int DirLightHandle;
int i, j;
float DrawX, DrawZ;

int time = 600;
int count;
int cntFlg;
float distance = 1200.0f;
int WaitTime = 0;

bool LightFlg;

VECTOR dis[9];
VECTOR LightPos;
VECTOR LightPos2;

void Light_init() {

	//頂点シェーダーを読み込む
	VertexShaderHandle = LoadVertexShader("Shader/NormalMesh_SpotPointLightVS.vso");

	//ピクセルシェーダーを読み込む
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
	SetLightAmbColorHandle(PointLightHandle, GetColorF(10.0f, 10.0f, 10.0f, 0.0f));

	// ポイントライトのディフューズカラーを強い色にする
	SetLightDifColorHandle(PointLightHandle, GetColorF(9.0f, 9.0f, 9.0f, 0.0f));

	//ポイントライトの初期値を設定
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 1500.0f, 0.0f));

	LightFlg = true;

	count = 1;

	dis[0] = VGet(-distance, 0.0f, distance);
	dis[1] = VGet(0.0f, 0.0f, distance);
	dis[2] = VGet(distance, 0.0f, distance);
	dis[3] = VGet(-distance, 0.0f, 0.0f);
	dis[4] = VGet(0.0f, 0.0f, 0.0f);
	dis[5] = VGet(distance, 0.0f, 0.0f);
	dis[6] = VGet(-distance, 0.0f, -distance);
	dis[7] = VGet(0.0f, 0.0f, -distance);
	dis[8] = VGet(distance, 0.0f, -distance);
}
void Light()
{
	//10秒経過したら方向転換
	if (time < 600) {
		time++;
	}
	else if (time >= 600 && WaitTime == 0) {
		while (cntFlg == count || cntFlg + 2 == count || cntFlg - 2 == count || cntFlg + 4 == count || cntFlg - 4 == count || cntFlg + 5 == count || cntFlg - 5 == count|| cntFlg + 6 == count || cntFlg - 6 == count 
			|| cntFlg + 7 == count || cntFlg - 7 == count || cntFlg + 8 == count || cntFlg - 8 == count || (cntFlg == 2) && (count == 3) || (cntFlg == 3) && (count == 2) || (cntFlg == 5) && (count == 6) || (cntFlg == 6) && (count == 5))
		{
			count = GetRand(8);
		}
		cntFlg = count;
		time = 0;
		WaitTime = 1;
		Key_Look = false;
		LightFlg = true;
	}
	else if (WaitTime == 1) {
		WaitTime = 0;
		time = 0;
		LightFlg = false;
	}
	if (WaitTime == 1 && count < 9) {
		if (LightPos.x > dis[count].x) {
			LightRotateAngle -= 0.01f;
		}
		else if (LightPos.x < dis[count].x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z > dis[count].z) {
			LightRotateAngle2 -= 0.01f;
		}
		else if (LightPos.z < dis[count].z) {
			LightRotateAngle2 += 0.01f;
		}
	}

	// ライトの位置の回転値を加算
	LightPos = VGet(LightRotateAngle * 200.0f, 800.0f, LightRotateAngle2 * 200.0f);
	LightPos2 = VGet(LightRotateAngle * 200.0f, 1100.0f, LightRotateAngle2 * 200.0f);

	//10カウント表示
	SetFontSize(100);
	DrawFormatString(500, 10, 0x25525000, "%d秒", time / 60);

	//ポイントライトの初期値を設定
	SetLightPositionHandle(PointLightHandle,LightPos2);

	// スポットライトの位置の更新
	SetLightPositionHandle(SpotLightHandle, LightPos);
}