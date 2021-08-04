#include "DxLib.h"
#include <math.h>

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

VECTOR dis;
VECTOR dis1;
VECTOR dis2;
VECTOR dis3;
VECTOR dis4;
VECTOR dis5;
VECTOR dis6;
VECTOR dis7;
VECTOR dis8;
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

	//ポイントライトの初期値を設定
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 1000.0f, 0.0f));
	
	//// ディレクショナルライトを作成する
	//DirLightHandle = CreateDirLightHandle(VGet(-1.0f, 0.0f, 0.0f));

	//// ディレクショナルライトのアンビエントカラーを抑える
	//SetLightAmbColorHandle(DirLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	//// ディレクショナルライトのディフューズカラーを緑にする
	//SetLightDifColorHandle(DirLightHandle, GetColorF(5.0f, 5.0f, 10.0f, 0.0f));
	
	// グローバルアンビエントライト( 大域環境光 )を２０％の明るさにする
	SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	count = GetRand(8);
	cntFlg = count;

	dis = VGet(-distance, 0.0f, distance);
	dis1 = VGet(0.0f, 0.0f, distance);
	dis2 = VGet(distance, 0.0f, distance);
	dis3 = VGet(-distance, 0.0f, 0.0f);
	dis4 = VGet(0.0f, 0.0f, 0.0f);
	dis5 = VGet(distance, 0.0f, 0.0f);
	dis6 = VGet(-distance, 0.0f, -distance);
	dis7 = VGet(0.0f, 0.0f, -distance);
	dis8 = VGet(distance, 0.0f, -distance);
}
void Light()
{
	//10秒経過したら方向転換
	if (time < 600) {
		time++;
	}
	else if (time >= 600) {
		while (cntFlg == count) {
				count = GetRand(8);
			}
		cntFlg = count;
		time = 0;
		//10秒間処理を止める
		WaitTimer(10000);
	}
	if (count == 0) {
		if (LightPos.x > dis.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z > dis.z) {
			LightRotateAngle2 += 0.01f;
		}
	}
	else if (count == 1) {
		if (LightPos.x < dis1.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.x > dis1.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z < dis1.z) {
			LightRotateAngle2 += 0.01f;
		}
	}
	else if (count == 2) {
		if (LightPos.x < dis2.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z < dis2.z) {
			LightRotateAngle2 += 0.01f;
		}
	}
	else if (count == 3) {
		if (LightPos.x > dis3.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z > dis3.z) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z < dis3.z) {
			LightRotateAngle += 0.01f;
		}
	}
	else if (count == 4) {
		if (LightPos.x > dis4.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.x < dis4.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z > dis4.z) {
			LightRotateAngle2 -= 0.01f;
		}
		if (LightPos.z < dis4.z) {
			LightRotateAngle2 += 0.01f;
		}
	}
	else if (count == 5) {
		if (LightPos.x < dis5.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z < dis5.z) {
			LightRotateAngle2 += 0.01f;
		}
		if (LightPos.z > dis5.z) {
			LightRotateAngle2 -= 0.01f;
		}
	}
	else if (count == 6) {
		if (LightPos.x > dis6.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z > dis6.z) {
			LightRotateAngle2 -= 0.01f;
		}
	}
	else if (count == 7) {
		if (LightPos.x < dis7.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.x > dis7.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z > dis7.z) {
			LightRotateAngle -= 0.01f;
		}
	}
	else if (count == 8) {
		if (LightPos.x < dis8.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z > dis8.z) {
			LightRotateAngle2 -= 0.01f;
		}
	}
	// ライトの位置の回転値を加算
	LightPos = VGet(LightRotateAngle * 200.0f, 800.0f, LightRotateAngle2 * 200.0f);

	//10カウント表示
	SetFontSize(100);
	DrawFormatString(500, 10, 0x25525000, "%d秒",time/60);
	
	// スポットライトの位置の更新
	SetLightPositionHandle(SpotLightHandle, LightPos);
}