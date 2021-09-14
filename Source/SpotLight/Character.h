#pragma once
class CHARACTER
{
public:
	CHARACTER();
	~CHARACTER();

protected:
	int StaminaCount(bool MoveFlag,int num);	//�G�l�~�[�X�^�~�i�J�E���g
	int PlayerStaminaCount(bool SliderFlg, bool EnemyFlg/*,bool StmOver*/,int count,const int countMAX);//�v���C���[�X�^�~�i�J�E���g
	int AttackStaminaCount( int num);	//�G�l�~�[�U���ɂ��X�^�~�i�J�E���g
	void Character_Init();

private:
	//�X�^�~�i�֘A
	struct Stamina
	{
		//bool s_MoveFlag;	//�ړ����Ă���̂�����
		int s_Count[3];		//�����Ă��鎞�Ԃ��J�E���g
		int s_PlayerCount;
		int s_RecoveryCount[3];//�񕜂���܂ł̃C���^�[�o��
		const int s_StaminaMax = 300;		//�G�̃X�^�~�i�̍ő�l
		//const int s_PlayStaminaMax = 600;		//�v���C���[�̃X�^�~�i�̍ő�l
	}; Stamina Stamina;
};

extern int pattern_blue;
