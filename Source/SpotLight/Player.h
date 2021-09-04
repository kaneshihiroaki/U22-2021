#pragma once
#include "DxLib.h"
#include "enemy.h"
#include "Character.h"

#define CHAR_SIZE_X		55.0f		// �L�����̃T�C�Y
#define CHAR_SIZE_Y		55.0f		// �L�����̃T�C�Y
#define CHAR_SIZE_Z		55.0f		// �L�����̃T�C�Y

class CAMERA;
class ENEMY;
class CHARACTER;

extern int PLAYER_WIN_COUNT;//player����������������ϐ�


class PLAYER : public CHARACTER
{
public:
	PLAYER();
	~PLAYER();

	int c_PlayerModel;	//�v���C���[�̃C���|�[�g�p�ϐ�
	int c_WinPlayerModel;	//�v���C���[�̃C���|�[�g�p�ϐ�
	VECTOR c_AddPosPlay;	//�v���C���[�̑傫��
	VECTOR c_Rotation;		//�v���C���[�̉�]
	VECTOR c_Position;	//�v���C���[�̈ʒu

	//�v���C���[�̔�e����
	void SetPlayerParalyze(){
		Damage.s_paralyzeKey = true;//true�����g���ĂȂ��̂ŏ��������܂�
	}

	void Player_Controller();
	void Player_Move( PLAYER* player, ENEMY* ene);
	bool Player_Push(PLAYER* player, ENEMY* enemy,  VECTOR PushVec, int count);
	bool CheckHit(VECTOR Player, VECTOR LightPos);
	void init();	//������

	void Player_Paralyze();	//��l�������т��i�~�܂�j�����т�Ă���Ƃ��ɓ���֐��B���т�̃J�E���g�����Ē����̂�����


	bool CheckPara();//���ׂ����G�l�~�[�����т�Ă��邩�ǂ����̔���
	////Ⴢ�i�_���[�W�֘A�j
	//struct Damage
	//{
	//	int s_ParaTime = 0;					//�v���C���[��Ⴢ�鎞�Ԃ��J�E���g
	//	bool s_paralyzeKey = false;		//�v���C���[�����т�Ă��邩���肷��itrue:Ⴢ�Ă� false:Ⴢ�Ă��Ȃ��j
	//	const int s_MaxTimeParalyze = 30;		//�v���C���[��Ⴢ�Ă��鎞��
	//}; Damage Damage;

	//�v���C���[��Ⴢꂳ����Z�b�^�[
	void SetParalyzeKey() {
		Damage.s_paralyzeKey = true;
	}

	//�v���C���[���X�e�[�W�ɂ��邩�ǂ���
	void SetPlayerOutStage() {
		c_StageIn = false;
	}
	void SetPlayerInStage() {
		c_StageIn = true;
	}
	VECTOR GetFuturePos() { return VAdd(c_Position, c_TempMoveVector); };

private:
	float c_PlayerAng;		//�v���C���[�̊p�x

	bool c_RotFlag;		//�v���C���[����]���Ă���
	bool c_MoveFlag;	//�v���C���[���ړ����Ă���̂�����
	bool c_StageIn;		//�X�e�[�W���ɂ��邩�ǂ�������
	int c_StmCount;		//�v���C���[�̗̑�
	int c_StmMax;	//�X�^�~�i�̍ő�l
	bool c_Slide;	//�v���C���[�����点�锻��ϐ�
	
	int c_GearStm;	//�X�^�~�i���؂ꂽ��̏�����I��
	bool c_StmStop;	//�X�^�~�i���؂ꂽ���Ƃ�m�点��ϐ� true:�؂�ĂȂ� false:�؂ꂽ


	VECTOR c_MoveVector;	//�ړ��ϐ�
	VECTOR c_TempMoveVector; //�ړ�����v�Z����ϐ�

	bool c_Player_win = false;//�v���C���[���X�|�b�g���C�g�ɓ����Ă���Ƃ����f����ύX����悤�̕ϐ�

	float c_movespeed = 7.0f;	//�v���C���[�ړ��X�s�[�h
	float c_Acc;	//�����𐧌�

		//Ⴢ�i�_���[�W�֘A�j
	struct Damage
	{
		int s_ParaTime = 0;					//�v���C���[��Ⴢ�鎞�Ԃ��J�E���g
		bool s_paralyzeKey = false;		//�v���C���[�����т�Ă��邩���肷��itrue:Ⴢ�Ă� false:Ⴢ�Ă��Ȃ��j
		const int s_MaxTimeParalyze = 60;		//�v���C���[��Ⴢ�Ă��鎞��
	}; Damage Damage;

	struct Attack {
		//�U�����s�����ǂ�������ϐ�
		bool s_AttackStartKey = false;
		int s_AttackCons;		//�v���C���[�̍U��������̗�
		bool s_GetOneRot = false;
		float s_Rang = 0.0f;	//�U������(�͈�)

		//�U���̊J�n�n�_�����߂�ϐ�
		float s_RotSin = 0.0f;
		float s_RotCos = 0.0f;
		float s_Posx = 0.0f;
		float s_Posz = 0.0f;
		const float s_width = 100.0f;
		const float s_heigt = 100.0f;

		//�U�����x(�I���n�_)
		const float s_AttackSpeed = 10.0f;
		const float s_RangMax = 500.0f;

		int s_Memo=0;
		int s_TimePara = 0;
		const int s_TimeMaxPara = 50;
	}; Attack Att;
	
	void Collision_Draw(VECTOR EnemyPos[ENEMY_MAX]);//�f�o�b�N���[�h�Ŏg�p
	
	void Player_Attack(ENEMY* ene,VECTOR Player_rot);		//�U��
	bool Player_AttackCol(VECTOR AttPosRU, VECTOR AttPosLU, VECTOR AttPosRD, VECTOR AttPosLD, ENEMY* enepos, int num, float ang);

	//ENEMY* c_enemyCol;		//�G�̍��W���擾���邽�߂Ɏ擾
};


