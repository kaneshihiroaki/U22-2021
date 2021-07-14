#pragma once
#include "Main.h"
#include "Player.h"
#include "Camera.h"
//ゲームの状態
int GameState = 0;

int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];

VECTOR player1;
VECTOR player2;
VECTOR player3;
VECTOR player4;
//敵
VECTOR enemy1;
VECTOR enemy2;

float Cap1R;
float Cap2R;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

    // ウインドウモードで起動
    ChangeWindowMode(TRUE);

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // Ｚバッファを有効にする
    SetUseZBuffer3D(TRUE);

    // Ｚバッファへの書き込みを有効にする
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && GetHitKeyStateAll(key) == 0) {

        //入力キー取得
        g_OldKey = g_NowKey;
        g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
        g_KeyFlg = g_NowKey & ~g_OldKey;

        // 画面をクリアする
        ClearDrawScreen();
        switch (GameState) {
        case 0:
            GameInit();
            break;
        case 1:
            GameMain();
            break;
        }

        // 裏画面の内容を表画面に反映する
        ScreenFlip();
    }
    // ＤＸライブラリの後始末
    DxLib_End();

    // ソフトの終了
    return 0;
}

void GameInit() {

    //// 軸の座標を初期化

    ////プレイヤー
    player1 = VGet(120.0f, 100.0f, 0.0f);
    player2 = VGet(120.0f, 150.0f, 0.0f);

    ////敵
    enemy1 = VGet(320.0f, 100.0f, 0.0f);
    enemy2 = VGet(320.0f, 150.0f, 0.0f);

    Cap1R = 30.0f;
    Cap2R = 30.0f;


    GameState = 1;
}


void GameMain() {

    //カメラ
    Camera();

    // 地面モデル
    {
        DrawCube3D(VGet(-500.0f, 0.0f, -1000.0f), VGet(1200.0f, 10.0f, 1000.0f),
            GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
    }
   
    //プレイヤー
    PlayerMove();

}
