#pragma once
#include "Main.h"
#include "Player.h"
#include "Camera.h"
//�Q�[���̏��
int GameState = 0;

int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];

VECTOR player1;
VECTOR player2;
VECTOR player3;
VECTOR player4;
//�G
VECTOR enemy1;
VECTOR enemy2;

float Cap1R;
float Cap2R;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

    // �E�C���h�E���[�h�ŋN��
    ChangeWindowMode(TRUE);

    // �`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    // �y�o�b�t�@��L���ɂ���
    SetUseZBuffer3D(TRUE);

    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
    SetWriteZBuffer3D(TRUE);

    while (ProcessMessage() == 0 && GetHitKeyStateAll(key) == 0) {

        //���̓L�[�擾
        g_OldKey = g_NowKey;
        g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
        g_KeyFlg = g_NowKey & ~g_OldKey;

        // ��ʂ��N���A����
        ClearDrawScreen();
        switch (GameState) {
        case 0:
            GameInit();
            break;
        case 1:
            GameMain();
            break;
        }

        // ����ʂ̓��e��\��ʂɔ��f����
        ScreenFlip();
    }
    // �c�w���C�u�����̌�n��
    DxLib_End();

    // �\�t�g�̏I��
    return 0;
}

void GameInit() {

    //// ���̍��W��������

    ////�v���C���[
    player1 = VGet(120.0f, 100.0f, 0.0f);
    player2 = VGet(120.0f, 150.0f, 0.0f);

    ////�G
    enemy1 = VGet(320.0f, 100.0f, 0.0f);
    enemy2 = VGet(320.0f, 150.0f, 0.0f);

    Cap1R = 30.0f;
    Cap2R = 30.0f;


    GameState = 1;
}


void GameMain() {

    //�J����
    Camera();

    // �n�ʃ��f��
    {
        DrawCube3D(VGet(-500.0f, 0.0f, -1000.0f), VGet(1200.0f, 10.0f, 1000.0f),
            GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
    }
   
    //�v���C���[
    PlayerMove();

}
