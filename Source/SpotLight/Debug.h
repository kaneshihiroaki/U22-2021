#include"DxLib.h"

using namespace std;


extern int DebugNum; //デバックの数字
extern bool DebugMode;//デバックモードのオンオフ

extern bool Collision_Player;
extern bool GamePadIn_bool;

extern bool Build_bool;//ビルドを表示消すよう

extern bool GameJudge;//勝敗判定
extern bool Win;
extern bool Lose;

extern int g_KeyFlg;
extern int g_NowKey;
extern int g_OldKey;


extern int DebugCom();
extern void DebugDrawing();;
extern void CameraFree();
extern void Collision_player();
extern void GamePadIn();
extern void Build_In();
extern void Game_Judge_In();


extern void Build_Time();//ビルドスタンプ関数
extern void Game_Judge();//勝敗関数


