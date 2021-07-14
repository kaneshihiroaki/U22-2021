#include "DxLib.h"
#include <math.h>
#include <list>
#include"Camera.h"
#include "Player.h"
#include "Stage.h"
#include "enemy.h"
#include "Main.h"
//�Q�[���̏��
int GameState = 0;

int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];

MAIN::MAIN()
{

}

MAIN::~MAIN()
{
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �w�i�̐F
	SetBackgroundColor(255, 255, 255);

	SetMainWindowText("�R�c");
	ChangeWindowMode(TRUE);

	if (DxLib_Init() < 0) return -1;

	SetDrawScreen(DX_SCREEN_BACK);

	SetCameraNearFar(100.0f, 50000.0f);

	//	 �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	MAIN *c_main = new MAIN();

	// ���C�����[�v(�����L�[�������ꂽ�烋�[�v�𔲂���)
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ��ʂ̃N���A
		ClearDrawScreen();

		//���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		switch (c_main->GameState)
		{
		case 0:
			c_main->Game_Main();
			break;

		default:
			break;
		} 

		ScreenFlip();
	}
	// �L�[���͑҂�������
	WaitKey();

	// �c�w���C�u�����̌�n��
	DxLib_End();

	return 0;
}

void MAIN::Game_Main() {
	c_stage->Stage_Make();

	c_enemy->Enemy_Creat();

	c_player->Player_Move();

	c_camera->Camera_Control(c_player->c_Position);



	MV1DrawModel(c_player->c_PlayerModel);
}
