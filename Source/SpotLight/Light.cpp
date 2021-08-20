#include "DxLib.h"
#include <math.h>
#include "Debug.h"
#include "Light.h"
#include <cmath>

#define DRAW_NUM	(3)
#define SPACE		(512.0f)
#define PI 3.141592654f

int PixelShaderHandle;
int VertexShaderHandle;
float LightRotateAngle;
float LightRotateAngle2;
int SpotLightHandle;
int PointLightHandle;
int DirLightHandle;
float DrawX = 0.0f;
float DrawZ = 0.0f;

int time = 600;
int count;
int cntFlg = 4;
int rc = 4;
float distance = 1200.0f;
int WaitTime = 1;

bool LightFlg;

VECTOR dis[9];
VECTOR LightPos;
VECTOR LightPos2;

typedef struct {
	float x, z;    //座標
	float ox, oz;//回転の中心
	float T;    //周期
	float Range;//半径
}Point_t;

void Light_SetUp() {
	//頂点シェーダーを読み込む
	VertexShaderHandle = LoadVertexShader("Shader/NormalMesh_SpotPointLightVS.vso");

	//ピクセルシェーダーを読み込む
	PixelShaderHandle = LoadPixelShader("Shader/NormalMesh_SpotPointLightPS.pso");

	// 使用する頂点シェーダーをセット
	SetUseVertexShader(VertexShaderHandle);

	// 使用するピクセルシェーダーをセット
	SetUsePixelShader(PixelShaderHandle);

	// 標準ライトを無効にする
	SetLightEnable(FALSE);

	//ライトの処理を1ピクセルごとに行う（処理が重くなる）
	SetUsePixelLighting(TRUE);
	
	// スポットライトを作成する
	SpotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.28f, 0.0f, 2000.0f, 0.0f, 0.006f, 0.0f);

	// スポットライトのアンビエントカラーを黄色にする
	SetLightAmbColorHandle(SpotLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	// スポットライトのディフューズカラーを黄色にする
	SetLightDifColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	// ポイントライトを作成する
	PointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 7000.0f, 1.016523f, 0.0001f, 0.00001f);

	// ポイントライトのアンビエントカラーを無効にする
	SetLightAmbColorHandle(PointLightHandle, GetColorF(10.0f, 10.0f, 10.0f, 0.0f));

	// ポイントライトのディフューズカラーを強い色にする
	SetLightDifColorHandle(PointLightHandle, GetColorF(9.0f, 9.0f, 9.0f, 0.0f));
}

void Light_init() {
	// Direct3D9Ex を使用する
	SetUseDirect3DVersion(DX_DIRECT3D_9EX);

	// ライトの位置を回転する値を初期化
	//LightRotateAngle = 0.0f;

	//// 標準ライトを無効にする
	//SetLightEnable(FALSE);

	////ライトの処理を1ピクセルごとに行う（処理が重くなる）
	//SetUsePixelLighting(TRUE);

	//// スポットライトを作成する
	//SpotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.18f, 0.15f, 1000.0f, 0.4f, 0.001662f, 0.000001f);

	//// スポットライトのアンビエントカラーを黄色にする
	//SetLightAmbColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	//// スポットライトのディフューズカラーを黄色にする
	//SetLightDifColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	//// ポイントライトを作成する
	//PointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 7000.0f, 1.016523f, 0.000100f, 0.000010f);

	//// ポイントライトのアンビエントカラーを無効にする
	//SetLightAmbColorHandle(PointLightHandle, GetColorF(10.0f, 10.0f, 10.0f, 0.0f));

	//// ポイントライトのディフューズカラーを強い色にする
	//SetLightDifColorHandle(PointLightHandle, GetColorF(9.0f, 9.0f, 9.0f, 0.0f));

	//ポイントライトの初期値を設定
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 1200.0f, 0.0f));

	LightFlg = true;

	// ライトの位置の回転値を加算
	LightPos = VGet(0.0f, 800.0f, 0.0f);
	LightPos2 = VGet(0.0f, 1100.0f, 0.0f);

	dis[0] = VGet(-distance, 0.0f, distance);
	dis[1] = VGet(0.0f, 0.0f, distance);
	dis[2] = VGet(distance, 0.0f, distance);
	dis[3] = VGet(-distance, 0.0f, 0.0f);
	dis[4] = VGet(0.0f, 0.0f, 0.0f);
	dis[5] = VGet(distance, 0.0f, 0.0f);
	dis[6] = VGet(-distance, 0.0f, -distance);
	dis[7] = VGet(0.0f, 0.0f, -distance);
	dis[8] = VGet(distance, 0.0f, -distance);

	//角度を初期化
	LightRotateAngle = 0;
	LightRotateAngle2 = 0;

	//ポイントライトの初期値
	SetLightPositionHandle(PointLightHandle, LightPos2);

	// スポットライトの初期値
	SetLightPositionHandle(SpotLightHandle, LightPos);

	//時間初期化
	time = 600;

	WaitTime = 0;
	cntFlg = 4;
	rc = 4;
	while (count == 0 || count == 2 || count == 4 || count == 6 || count == 8)
	{
		count = GetRand(8);
	}
}
void Light()
{
	Point_t
		cp1 = { 0, 0, 0, distance / 2, -180, distance / 2 },
		cp2 = { 0, 0, 0, -distance / 2, -180, distance / 2 },
		cp3 = { 0, 0, distance / 2, 0, -180, distance / 2 },
		cp4 = { 0, 0, -distance / 2, 0, -180, distance / 2 };

	//10秒経過したら方向転換
	if (time < 600) {
		time++;
	}
	else if (WaitTime == 1) {
		WaitTime = 0;
		time = 0;
		LightFlg = false;
		//finish = false;
		round_count++;
	}
	else if (time >= 600 && WaitTime == 0) {
		while (cntFlg == count || cntFlg + 2 == count || cntFlg - 2 == count || cntFlg + 4 == count || cntFlg - 4 == count || cntFlg + 5 == count || cntFlg - 5 == count || cntFlg + 6 == count || cntFlg - 6 == count
			|| cntFlg + 7 == count || cntFlg - 7 == count || cntFlg + 8 == count || cntFlg - 8 == count || (cntFlg == 2) && (count == 3) || (cntFlg == 3) && (count == 2) || (cntFlg == 5) && (count == 6) || (cntFlg == 6) && (count == 5))
		{
			count = GetRand(8);
			rc = cntFlg;
		}
		cntFlg = count;
		time = 0;
		WaitTime = 1;
		Key_Look = false;
		LightFlg = true;
		judge_win = false;
		if (round_count >= 6) finish = false;		//6ラウンドやったら終わる
	}

	if (WaitTime == 1 && count < 9) {
		if (count == rc - 3 && LightPos.z < dis[count].z) {
			cp1.x += cp1.ox + sin(PI / cp1.T * LightRotateAngle) * cp1.Range;
			cp1.z += cp1.oz + -cos(PI / cp1.T * LightRotateAngle2) * cp1.Range;
			LightRotateAngle += 0.6f;
			LightRotateAngle2 += 0.3f;
			DrawX = cp1.x;
			DrawZ = cp1.z;
		}
		else if (count == rc + 3 && LightPos.z > dis[count].z) {
			cp2.x += cp2.ox + sin(PI / cp2.T * LightRotateAngle) * cp2.Range;
			cp2.z += cp2.oz + cos(PI / cp2.T * LightRotateAngle2) * cp2.Range;
			LightRotateAngle += 0.6f;
			LightRotateAngle2 += 0.3f;
			DrawX = cp2.x;
			DrawZ = cp2.z;
		}
		if (count == rc + 1 && LightPos.x < dis[count].x) {
			cp3.x += cp3.ox + -cos(PI / cp1.T * LightRotateAngle) * cp3.Range;
			cp3.z += cp3.oz + sin(PI / cp1.T * LightRotateAngle2) * cp3.Range;
			LightRotateAngle += 0.3f;
			LightRotateAngle2 += 0.6f;
			DrawX = cp3.x;
			DrawZ = cp3.z;
		}
		else if (count == rc - 1 && LightPos.x > dis[count].x) {
			cp4.x += cp4.ox + cos(PI / cp4.T * LightRotateAngle) * cp4.Range;
			cp4.z += cp4.oz + sin(PI / cp4.T * LightRotateAngle2) * cp4.Range;
			LightRotateAngle += 0.3f;
			LightRotateAngle2 += 0.6f;
			DrawX = cp4.x;
			DrawZ = cp4.z;
		}
	}

	//ライトの位置の回転値を加算
	LightPos = VGet(DrawX, 600.0f, DrawZ);
	LightPos2 = VGet(DrawX, 1200.0f, DrawZ);

	// スポットライトの位置の更新
	SetLightPositionHandle(SpotLightHandle, LightPos);

	//ポイントライトの初期値を設定
	SetLightPositionHandle(PointLightHandle, LightPos2);

	//10カウント表示
	SetFontSize(100);
	DrawFormatString(500, 10, 0x25525000, "%d秒", time / 60);
}