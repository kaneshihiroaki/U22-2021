#include"DxLib.h"

using namespace std;


extern int DebugNum; //デバックの数字
extern bool DebugMode;//デバックモードのオンオフ

extern bool Collision_Player;//当たり判定を見るよう
extern bool GamePadIn_bool;//ゲームパッドを見るよう
extern bool CameraUp_bool;//カメラ移動上下を反転
extern bool CameraLR_bool;//カメラ移動左右を反転

extern bool Build_bool;//ビルドを表示消すよう

extern bool GameJudge;//勝敗判定
extern bool Win;
extern bool Lose;

extern int g_KeyFlg;
extern int g_NowKey;
extern int g_OldKey;

extern bool Key_Look;//プレイヤーの入力を制御する変数

extern bool Debug_Enemy;//デバック用フラグtrueで確認可能にする
extern bool Debug_Camera;	//カメラ用デバック用フラグtrueで確認可能にする


extern int DebugCom();
extern void DebugDrawing();;
extern void CameraState();
extern void CameraReverse();
extern void Collision_player();
extern void GamePadIn();
extern void Build_In();
extern void Game_Judge_In();
extern void Enemy_State();
extern void FreeCamera();


extern void Build_Time();//ビルドスタンプ関数
extern void Game_Judge();//勝敗関数

extern void Player_Enemy(VECTOR player, VECTOR Ene[3]);
