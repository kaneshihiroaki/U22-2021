#pragma once
class CHARACTER
{
public:
	CHARACTER();
	~CHARACTER();

protected:
	int StaminaCount(bool MoveFlag);	//�v���C���[�X�^�~�i�J�E���g

private:
	//�X�^�~�i�֘A
	struct Stamina
	{
		//bool s_MoveFlag;	//�ړ����Ă���̂�����
		int s_Count = 300;		//�����Ă��鎞�Ԃ��J�E���g
		const int s_StaminaMax = 300;		//�X�^�~�i�̍ő�l
	}; Stamina Stamina;
};
