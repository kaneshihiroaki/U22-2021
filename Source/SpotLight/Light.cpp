#include "DxLib.h"
#include <math.h>
#include "Debug.h"
#include "Light.h"
#include "GameSound.h"
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
float DrawX2 = 0.0f;
float DrawZ2 = 0.0f;

int time = 600;
int count;
int cntFlg = 4;
int rc = 4;
float distance = 600.0f;
int WaitTime = 0;

bool LightFlg;

VECTOR dis[6];
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
	SpotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.375f, 0.75f, 2000.0f, 0.0f, 0.007f, 0.0f);

	// スポットライトのアンビエントカラーを黄色にする
	SetLightAmbColorHandle(SpotLightHandle, GetColorF(15.0f, 15.0f, 0.0f, 0.0f));

	// スポットライトのディフューズカラーを黄色にする
	SetLightDifColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	// ポイントライトを作成する
	PointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 7000.0f, 1.016523f, 0.0f, 0.000015f);

	// ポイントライトのアンビエントカラーを無効にする
	SetLightAmbColorHandle(PointLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	// ポイントライトのディフューズカラーを強い色にする
	SetLightDifColorHandle(PointLightHandle, GetColorF(10.0f, 10.0f, 10.0f, 0.0f));
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
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 0.0f, 0.0f));

	LightFlg = true;

	// ライトの位置の回転値を加算
	LightPos = VGet(0.0f, 600.0f, -300.0f);
	LightPos2 = VGet(0.0f, 1000.0f, 0.0f);

	dis[0] = VGet(-distance, 0.0f, distance);
	dis[1] = VGet(0.0f, 0.0f, distance);
	dis[2] = VGet(distance, 0.0f, distance);
	dis[3] = VGet(-distance, 0.0f, 0.0f);
	dis[4] = VGet(0.0f, 0.0f, 0.0f);
	dis[5] = VGet(distance, 0.0f, 0.0f);

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
	while (count == 0 || count == 2 || count == 4)
	{
		count = GetRand(5);
	}
}
void Light()
{
	Point_t
		cp1 = { 0,dis[rc].z, 0, distance, -180, distance / 2 },
		cp2 = { 0,dis[rc].z, 0, -distance, -180, distance / 2 },
		cp3 = { dis[rc].x,0, distance, 0, -180, distance / 2 },
		cp4 = { dis[rc].x,0, -distance, 0, -180, distance / 2 };

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
		StopSoundMem(drum);
		PlaySoundMem(drum_finish, DX_PLAYTYPE_BACK);
	}
	else if (time >= 600 && WaitTime == 0) {
		while (cntFlg == count || cntFlg + 2 == count || cntFlg - 2 == count || cntFlg + 4 == count || cntFlg - 4 == count ||
			cntFlg + 5 == count || cntFlg - 5 == count || (cntFlg == 2) && (count == 3) || (cntFlg == 3) && (count == 2))
		{
			count = GetRand(5);
			rc = cntFlg;
		}

		PlaySoundMem(drum, DX_PLAYTYPE_LOOP);

		cntFlg = count;
		time = 0;
		WaitTime = 1;
		Key_Look = false;
		LightFlg = true;
		judge_win = false;
		if (round_count >= 6) finish = false;		//6ラウンドやったら終わる
	}

	if (WaitTime == 1 && count < 6) {
		if (count == rc - 3) {
			LightRotateAngle += 0.9f;
			LightRotateAngle2 += 1.5f;
			DrawX = cp1.x+ sin(PI / cp1.T * LightRotateAngle) * cp1.Range;
			DrawZ = cp1.z+ -cos(PI / cp1.T * LightRotateAngle2) * cp1.Range;
		}
		else if (count == rc + 3) {
			LightRotateAngle += 0.9f;
			LightRotateAngle2 += 1.5f;
			DrawX = cp2.x + sin(PI / cp2.T * LightRotateAngle) * cp2.Range;
			DrawZ = cp2.z + cos(PI / cp2.T * LightRotateAngle2) * cp2.Range;
		}
		if (count == rc + 1) {
			LightRotateAngle += 1.5f;
			LightRotateAngle2 += 0.9f;
			DrawX = cp3.x + -cos(PI / cp1.T * LightRotateAngle) * cp3.Range;
			DrawZ = cp3.z + sin(PI / cp1.T * LightRotateAngle2) * cp3.Range;
		}
		else if (count == rc - 1) {
			LightRotateAngle += 1.5f;
			LightRotateAngle2 += 0.9f;
			DrawX = cp4.x + cos(PI / cp4.T * LightRotateAngle) * cp4.Range;
			DrawZ = cp4.z + sin(PI / cp4.T * LightRotateAngle2) * cp4.Range;
		}
	}

	//ライトの位置の回転値を加算
	LightPos = VGet(DrawX, 600.0f, DrawZ - 300);

	// スポットライトの位置の更新
	SetLightPositionHandle(SpotLightHandle, LightPos);

	//ポイントライトの初期値を設定
	SetLightPositionHandle(PointLightHandle, LightPos2);

	//10カウント表示
	SetFontSize(100);
	DrawFormatString(500, 10, 0x25525000, "%d", time / 60);
}