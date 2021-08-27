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

extern int judge_count2;//�v���C���[���X�|�b�g���C�g�ɓ������琔����
extern int judge_count3;//�G���X�|�b�g���C�g�ɓ������琔����
extern bool player_judge;//�v���C���[���X�|�b�g���C�g�ɓ������Ƃ���flg
extern bool enemy_judge;//�G���X�|�b�g���C�g�ɓ�������������Ƃ���flg

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
	int c_dispTime;		//READY��GO�̕\�����ԃJ�E���g
	int c_resultdispTime;	//���U���g�ŕ����̕\���Ɏg�p����J�E���g
	bool OnePass;
	bool onecheck = false;
	int c_VictorNum = 0;	//���Ҋi�[�悤�ϐ�

	const int c_dispTimeMax = 60;	//GO�\������
	const int c_readyMaxTime = 240;		//READY�̕\�����Ԃ����ς�
	const int c_resultdispMaxTime = 180;	//���U���g�̕\������
	//const int c_pointcal = 10;		//���U���g�̃|�C���g�v�Z

	int LoadSound();
	int CountMaxPoint(int* point);	//���U���g�ł��ꂪ��ԃ|�C���g���擾�����̂��v�Z

	CAMERA* c_camera;
	PLAYER* c_player;
	STAGE* c_stage;
	ENEMY* c_enemy;
	CHARACTER* c_chara;
};

//extern int g_NowKey;

extern char key[256];
