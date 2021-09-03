#pragma once
#include"Dxlib.h"

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1280

#define NO_NAME 0

#define ENEMY1_NAME 1
#define ENEMY2_NAME 2
#define ENEMY3_NAME 3

#define PLAYER_NAME 4

void GameInit();
void GameMain();
void WIN_Text();


class CAMERA;
class PLAYER;
class STAGE;
class ENEMY;

extern int Number_count;
extern int win_timer;//������\����������J�E���g
extern bool player_win;
extern bool enemy_win;

extern bool DrawFlg;//drawcount���J�E���g����Ƃ���flg
extern int draw_timer;//draw��\����������b��
extern int draw_count;//draw��\�����Ă������Ɏg���J�E���g


extern int Time_IN_count;//�G���X�|�b�g���C�g�ɓ������琔����
extern bool player_judge;//�v���C���[���X�|�b�g���C�g�ɓ������Ƃ���flg
extern bool enemy_judge;//�G���X�|�b�g���C�g�ɓ�������������Ƃ���flg
extern int Win_NameOld;//�N���X�|�b�g���C�g�ɓ����Ă�����#define�Ő����Ǘ�
extern int Win_NameNow;//�N���X�|�b�g���C�g�ɓ����Ă�����#define�Ő����Ǘ�

/*�T�h���f�X�p�ϐ�*/
extern bool Sadondes_flg;//�T�h���f�X���s�����ǂ���true�Ȃ�s���Ă���B
/*�T�h���f�X�p�ϐ�*/

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

	//�T�h���f�X�p�֐�
	void Sadondes();
	void Sadondes_check();
	void Sadondes_Init();

private:
	bool c_ready;		//�{�^���������ă��C�����J�n����ϐ�
	int c_dispTime;		//READY��GO�̕\�����ԃJ�E���g
	int c_resultdispTime;	//���U���g�ŕ����̕\���Ɏg�p����J�E���g
	int c_PressBDispTime;	//Press B��\���E�_�ł�����ϐ�
	bool c_OnePass;			//�X�R�A�v�Z����񂾂��Q��
	bool c_ResultBack;		//���U���g�Ń^�C�g���ɖ߂�Ƃ����\�L��\��������
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
