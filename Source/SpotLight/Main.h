#pragma once
#include"Dxlib.h"

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1280


void GameInit();
void GameMain();
void WIN_Text();


class CAMERA;
class PLAYER;
class STAGE;
class ENEMY;

extern int judge_count;
extern int win_timer;//������\����������J�E���g
extern bool player_win;
extern bool enemy_win;

class MAIN 
{
public:
	MAIN();
	~MAIN();

	int GameState;		//�Q�[���̏��

	void Game_init();	//�Q�[���̏�����
	void Game_Main();
	void Game_Title();
	void Game_Result();

private:
	bool c_ready;		//�{�^���������ă��C�����J�n����ϐ�
	int c_dispTime;		//GO�̕\�����ԃJ�E���g
	const int c_dispTimeOver = 30;	//�\����
	const int c_pointcal = 10;		//�|�C���g�v�Z

	CAMERA* c_camera;
	PLAYER* c_player;
	STAGE* c_stage;
	ENEMY* c_enemy;
	CHARACTER* c_chara;
};

//extern int g_NowKey;

extern char key[256];
