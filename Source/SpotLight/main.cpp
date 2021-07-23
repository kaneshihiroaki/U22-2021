#include "DxLib.h"
#include <math.h>
#include <list>
#include"Camera.h"
#include "Player.h"
#include "Stage.h"
#include "enemy.h"
#include "Main.h"
#include "Debug.h"
//�Q�[���̏��
int GameState = 0;

int g_KeyFlg;
int g_NowKey;
int g_OldKey;
char key[256];

float version;

MAIN::MAIN()
{
	GameState = 0;
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

	version = 0.01f;		//�r���h�̃o�[�W�����A���j�������邽�тɐ��l���グ�čX�V���邱��
	printfDx("ver%.2f", version);

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

		if (((g_NowKey & PAD_INPUT_7) != 0) && ((g_NowKey & g_OldKey) == 0)) {
			if (DebugMode) {
				DebugMode = false;
				DebugNum = 1;
			}
			else {
				DebugMode = true;
			}

		}

		switch (c_main->GameState)
		{
		case 0:
			c_main->Game_Main();
			break;

		default:
			break;
		} 

		//�f�o�b�N�R�}���h�\��
		if (DebugCom() == -1) {
			//�f�o�b�N����Ȃ����
		}

		// ����ʂ̓��e��\��ʂɔ��f����
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

	if (!Collision_Player) {
		c_enemy->Enemy_Creat();
	}
	
	c_player->Player_Move(c_camera->c_SinParam,c_camera->c_CosParam);
	
	c_camera->Camera_Control(c_player->c_Position);


	if (!Collision_Player) {
		MV1DrawModel(c_player->c_PlayerModel);
	}
	Build_Time();
}
