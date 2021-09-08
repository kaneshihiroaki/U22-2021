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
extern bool judge_win;//勝利数をカウントするときに使うflg
extern int round_count;//ラウンド数
extern int WaitTime;

extern VECTOR LightPos;
extern bool LightFlg;//止まっているか調べる( TRUE:動く FALSE:止まっている )

extern int time;//エネミーの方で今何秒なのか検知するよう
extern int WaitTime;//上に同じ

/*サドンデス用変数*/
extern bool Sadondes_flg;//サドンデスを行うかどうかtrueなら行っている。
/*サドンデス用変数*/

void Light();
void Light_init();
void Light_SetUp();