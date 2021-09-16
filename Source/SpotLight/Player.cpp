#define _USE_MATH_DEFINES
#include <DxLib.h>
#include "Player.h"
#include "enemy.h"
#include "Camera.h"
#include <math.h>
//#include "Main.h"
#include "Debug.h"
#include "Light.h"
#include "GameSound.h"
#include "EffekseerForDXLib.h"

int PLAYER_WIN_COUNT = 0;

PLAYER::PLAYER()
{
	//// �v���C���[���W������
	//c_Position = VGet(100.0f, 100.0f, 0.0f);
	//c_PlayerAng = 0;	//�v���C���[�̊p�x
	////�v���C���[��]�i���W�A���ϊ��j
	//c_Rotation = VGet(0.0f, (c_PlayerAng *(M_PI/180)), 0.0f);
	////�v���C���[�̑傫��������
	//c_AddPosPlay = { 0.5f,0.5f,0.5f };

	//c_MoveFlag = FALSE;	//�v���C���[���ړ����Ă���̂�����

	//c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	//c_StmCount = 300;		//�v���C���[�̗̑�

	//c_Acc = 0.0f;

	c_EffPara = LoadEffekseerEffect("Effect/Numb/Sibire.efk", 50.0f);//MV1LoadModel("image/Ⴢ�.efk");
	if ((c_EffSmoke = LoadEffekseerEffect("Effect/Smook.efkefc", 5.0f)) == -1) {
		int ff = 0;
		ff++;
	}
	//int effectResourceHandle = LoadEffekseerEffect("image/�d��2.efkefc", 1.0f);

	// �R�c���f���̓ǂݍ���
	c_PlayerModel = MV1LoadModel("Model/Player3.mv1");
	c_WinPlayerModel = MV1LoadModel("Model/Player4.mv1");


	//�U���G�t�F�N�g
	Att.s_AttackPara = LoadEffekseerEffect("Effect/kougeki.efkefc", 50.0f);

	//�U���G�t�F�N�gflg
	Att.c_onePlayAttackEffect = false;

	//c_PlayerModel = MV1LoadModel("Model/player_debug.mv1");

	//c_enemyCol = new ENEMY();
}

PLAYER::~PLAYER()
{
}

void PLAYER::init() {
	// �v���C���[���W������
	c_Position = VGet(-450.0f, 100.0f, 0.0f);
	c_StringPos = VGet(0.0f, 0.0f, 0.0f);
	c_PlayerAng = 180;	//�v���C���[�̊p�x
	//�v���C���[��]�i���W�A���ϊ��j
	c_Rotation = VGet(0.0f, (180.0f * (M_PI / 180)), 0.0f);
	//�v���C���[�̑傫��������
	c_AddPosPlay = { 0.5f,0.5f,0.5f };

	c_MoveFlag = false;	//�v���C���[���ړ����Ă���̂�����
	c_Slide = false;
	c_StmStop = true;  //�X�^�~�i���؂ꂽ���Ƃ�m�点��ϐ� true:�؂�ĂȂ� false:�؂ꂽ
	c_StageIn = true;	//�X�e�[�W���ɂ��邩�ǂ�������

	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
	c_TempMoveVector = VGet(0.0f, 0.0f, 0.0f);

	c_StmCount = 300;		//�v���C���[�̗̑�
	c_StmMax = 300;		//�v���C���[�̗͍̑ő�l
	if (pattern_blue == 0 || pattern_blue == 1) {
		Att.s_AttackCons = 45;	//�v���C���[�̍U��������̗�
	}
	else {
		Att.s_AttackCons = 0;	//�v���C���[�̍U��������̗�
	}

	Damage.s_paralyzeKey = false;	//�v���C���[����Ⴢ��Ă���ϐ�������

	c_Acc = 0.0f;		//�����E��������ϐ�������

	c_Player_win = false;

	c_movespeed = c_MoveMax;	//�v���C���[�̑����ݒ�

	c_EnemyTuchFlg = false;	//�G�ɓ����������ǂ�����m�点��t���O

	//Ⴢ�G�t�F�N�g����x�����o��������ϐ�������
	Damage.c_onePlayEffect = false;
	//����������
	for (int i = 0; i < 3; i++) {
		c_SlotEffSmoke[i] = -1;		//�ړ����̉��G�t�F�N�g�i�[�p
	}
	c_SmokeCount = 0;//���̃J�E���g�p

	//���f���̑傫����ݒ�
	MV1SetScale(c_PlayerModel, c_AddPosPlay);
	MV1SetScale(c_WinPlayerModel, c_AddPosPlay);

	if (Sadondes_flg == false)c_DrowYouCount = 180;

}

void PLAYER::Player_Controller() {
	//�v���C���[
	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	if (!Collision_Player) {
		if (Damage.s_ParaTime % 20 < 10 || Key_Look) {//0~9�܂ł͕`��10~19�܂ł͕`�悵�Ȃ�
			if (c_Player_win) {
				MV1SetPosition(c_WinPlayerModel, c_Position);
				MV1SetRotationXYZ(c_WinPlayerModel, c_Rotation);
				MV1DrawModel(c_WinPlayerModel);			 //�v���C���[�̃��f���`��
			}
			else {
				MV1SetPosition(c_PlayerModel, c_Position);
				MV1SetRotationXYZ(c_PlayerModel, c_Rotation);
				MV1DrawModel(c_PlayerModel);			 //�v���C���[�̃��f���`��
			}

		}
	}

	//int PlayParaEff;

	//// ����I�ɃG�t�F�N�g���Đ�����
	//if (time_All % 120 == 3)
	//{
	//	int PlayParaEff;

	//	PlayParaEff = PlayEffekseer3DEffect(c_EffPara);

	//	// �Đ����̃G�t�F�N�g���ړ�����B
	//	SetPosPlayingEffekseer3DEffect(PlayParaEff, c_Position.x, c_Position.y+10, c_Position.z);

	//	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	//	DrawEffekseer3D();

	//	// �G�t�F�N�g�̈ʒu�����Z�b�g����B
	//	//position_x = 0.0f;
	//}

	//PlayParaEff = PlayEffekseer3DEffect(c_EffPara);

	//// �Đ����̃G�t�F�N�g���ړ�����B
	//SetPosPlayingEffekseer3DEffect(PlayParaEff, c_Position.x, c_Position.y, c_Position.z);

	//// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	//DrawEffekseer3D();

	//YOU��\�������鏈��
	SetFontSize(30);
	c_StringPos = ConvWorldPosToScreenPos(c_Position);
	if (c_DrowYouCount > 2) {
		c_DrowYouCount--;
		DrawFormatString(c_StringPos.x - 20, c_StringPos.y - 85, 0xFF0000, "YOU");
	}
}

// �v���C���[�ƃI�u�W�F�N�g�̂����蔻��
bool Collision_Cube(VECTOR PlayerCol, VECTOR ObjCol, float EnemyScaleX, float EnemyScaleZ) {
	// �e���W���擾����
	VECTOR pos = PlayerCol;
	VECTOR posObj = ObjCol;

	//����������true
	if ((pos.x + CHAR_SIZE_X > posObj.x - EnemyScaleX &&
		pos.z + CHAR_SIZE_Z > posObj.z - EnemyScaleZ) &&
		(pos.x - CHAR_SIZE_X < posObj.x + EnemyScaleX &&
			pos.z - CHAR_SIZE_Z < posObj.z + EnemyScaleZ)) {
		return true;
	}

	return false;
}

bool Collision_Sphere(VECTOR PlayerCol, VECTOR ObjCol, float EnemyScale) {
	// �e���W���擾����
	VECTOR pos = PlayerCol;
	VECTOR posObj = ObjCol;


	//����������true�B�̈�A�A������
	if ((pos.x + CHAR_SIZE_X > posObj.x &&
		pos.z + CHAR_SIZE_Z > posObj.z - EnemyScale) &&
		(pos.x - CHAR_SIZE_X < posObj.x &&
			pos.z - CHAR_SIZE_Z < posObj.z + EnemyScale)) {
		return true;
	}

	//����������true�B�̈�B�A������
	if ((pos.x + CHAR_SIZE_X > posObj.x - EnemyScale &&
		pos.z + CHAR_SIZE_Z > posObj.z) &&
		(pos.x - CHAR_SIZE_X < posObj.x + EnemyScale &&
			pos.z - CHAR_SIZE_Z < posObj.z)) {
		return true;
	}
	//����������true�B�̈�CDEF�A�~����
	if (pow((pos.x + CHAR_SIZE_X - posObj.x), 2) + pow((pos.z + CHAR_SIZE_Z - posObj.z), 2) < pow(EnemyScale, 2) ||
		pow((pos.x + CHAR_SIZE_X - posObj.x), 2) + pow((pos.z - CHAR_SIZE_Z - posObj.z), 2) < pow(EnemyScale, 2) ||
		pow((pos.x - CHAR_SIZE_X - posObj.x), 2) + pow((pos.z + CHAR_SIZE_Z - posObj.z), 2) < pow(EnemyScale, 2) ||
		pow((pos.x - CHAR_SIZE_X - posObj.x), 2) + pow((pos.z - CHAR_SIZE_Z - posObj.z), 2) < pow(EnemyScale, 2)) {
		return true;
	}

	return false;
}

bool PLAYER::CheckPara() {
	return Damage.s_paralyzeKey;
}//�v���C���[�����т�Ă��邩�ǂ����G�l�~�[�ɕԂ�

void PLAYER::Player_Paralyze() {
	c_MoveFlag = false;
	c_Slide = false;

	//int PlayParaEff;


	// ����I�ɃG�t�F�N�g���Đ�����
	if (Damage.c_onePlayEffect == false)
	{
		//�G�t�F�N�g���Đ����i�[
		Damage.c_SlotEffect = PlayEffekseer3DEffect(c_EffPara);
		//c_SlotEffect = PlayEffekseer3DEffect(c_EffPara);

		//�G�t�F�N�g����x�����Đ�
		Damage.c_onePlayEffect = true;
	}

	// �Đ����̃G�t�F�N�g���ړ�����B
	SetPosPlayingEffekseer3DEffect(Damage.c_SlotEffect, c_Position.x, c_Position.y + 10, c_Position.z);

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();

	//�I�����ɑS�ď�����
	if (Damage.s_ParaTime++ == Damage.s_MaxTimeParalyze) {
		Damage.s_paralyzeKey = false;
		Damage.c_onePlayEffect = false;
		Damage.s_ParaTime = 0;
		StopEffekseer3DEffect(Damage.c_SlotEffect);
	}
}

bool PLAYER::Player_AttackCol(VECTOR AttPosRU, VECTOR AttPosLU, VECTOR AttPosRD, VECTOR AttPosLD, ENEMY* enepos, int num, float ang) {
	//���S�_����o��
	float halfx = (AttPosRU.x + AttPosRD.x + AttPosLU.x + AttPosLD.x) / 4;
	float halfz = (AttPosRU.z + AttPosRD.z + AttPosLU.z + AttPosLD.z) / 4;

	//���S�_�ƓG�̍��W�̋���
	float distx = enepos->c_ObjPos[num].x - halfx;
	float distz = enepos->c_ObjPos[num].z - halfz;

	//�����蔻��̌v�Z
	float posz = cos(ang) * distz + sin(ang) * distx;
	float posx = -sin(ang) * distz + cos(ang) * distx;

	//��`�Ɠ_�̓����蔻����s��
	if (-Att.s_heigt /*/ 2.0f*/ <= posz && Att.s_heigt/* / 2.0f*/ >= posz) {
		if (-Att.s_width/* / 2.0f*/ <= posx && Att.s_width /*/ 2.0f*/ >= posx) {
			return true;
		}
	}

	return false;
}

void PLAYER::Player_Attack(ENEMY* ene, VECTOR Player_rot) {

	//��x�����擾
	if (Att.s_GetOneRot == false) {
		//�ړ��ꏊ�̊m�F
		Att.s_RotSin = sin(Player_rot.y);
		Att.s_RotCos = cos(Player_rot.y);
		Att.s_Posx = c_Position.x;
		Att.s_Posz = c_Position.z;
		Att.s_GetOneRot = true;
		//c_StmCount -= Att.s_AttackCons;		//�v���C���[�̗̑�
	}

	//�v���C���[�̑O�������擾
	float x = Att.s_Posx + (Att.s_RotSin * Att.s_Rang);
	float z = Att.s_Posz + (Att.s_RotCos * Att.s_Rang);

	//�U�����O���ɐi��
	Att.s_Rang += Att.s_AttackSpeed;

	//����
	DrawLine3D(VGet(x + (Att.s_RotCos * Att.s_width), c_Position.y, z - (Att.s_RotSin * Att.s_width)),
		VGet(x - (Att.s_RotCos * Att.s_width), c_Position.y, z + (Att.s_RotSin * Att.s_width)), 0x880000);

	//�E�c
	DrawLine3D(VGet(x + (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z - (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
		VGet(x + (Att.s_RotCos * Att.s_width), c_Position.y, z - (Att.s_RotSin * Att.s_width)), 0x880000);

	//���c
	DrawLine3D(VGet(x - (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z + (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
		VGet(x - (Att.s_RotCos * Att.s_width), c_Position.y, z + (Att.s_RotSin * Att.s_width)), 0x880000);

	//�㉡
	DrawLine3D(VGet(x - (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z + (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
		VGet(x + (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z - (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)), 0x880000);

	//�E��� x + (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z - (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)
	//����� x - (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z + (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)
	//�E���� x + (Att.s_RotCos * Att.s_width), c_Position.y, z - (Att.s_RotSin * Att.s_width)
	//������ x - (Att.s_RotCos * Att.s_width), c_Position.y, z + (Att.s_RotSin * Att.s_width)

	//�U������
	if (Att.s_Rang >= Att.s_RangMax) {
		Att.s_AttackStartKey = false;
		Att.s_GetOneRot = false;
		Att.s_Rang = 0.0f;
	}

	//�����蔻��
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (Player_AttackCol(VGet(x + (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z - (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
			VGet(x - (Att.s_RotCos * Att.s_width) + (Att.s_RotSin * Att.s_heigt), c_Position.y, z + (Att.s_RotSin * Att.s_width) + (Att.s_RotCos * Att.s_heigt)),
			VGet(x + (Att.s_RotCos * Att.s_width), c_Position.y, z - (Att.s_RotSin * Att.s_width)),
			VGet(x - (Att.s_RotCos * Att.s_width), c_Position.y, z + (Att.s_RotSin * Att.s_width)),
			ene, i, Player_rot.y) == true) {
			ene->SetEnemyParaKey(i);

		}
	}

	if (Att.c_onePlayAttackEffect == false)
	{


		Att.s_PlayAttackEff = PlayEffekseer3DEffect(Att.s_AttackPara);


		SetRotationPlayingEffekseer3DEffect(Att.s_PlayAttackEff, 0, Player_rot.y, 0);
		// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
		DrawEffekseer3D();

		Att.c_onePlayAttackEffect = true;
	}

	// �Đ����̃G�t�F�N�g���ړ�����B
	SetPosPlayingEffekseer3DEffect(Att.s_PlayAttackEff, x, c_Position.y + 90, z);
}

void PLAYER::Player_Move(PLAYER* player, ENEMY* ene)
{
	//�ړ��ꏊ�̊m�F
	VECTOR TempRotVector;

	//�ړ����Ă邩�ǂ���
	//c_MoveFlag = false;
	c_Slide = false;
	//c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	if (Key_Look == false) {
		// �v���C���[�ړ�
		//����ړ�
		if (((g_NowKey & PAD_INPUT_LEFT) != 0) && ((g_NowKey & PAD_INPUT_UP) != 0))
		{
			c_MoveFlag = true;
			c_Slide = true;
			c_MoveVector.x = c_movespeed;
			c_MoveVector.z = c_movespeed;

			//�p�x���
			c_PlayerAng = 315.0f;
		}
		//�����ړ�
		else if (((g_NowKey & PAD_INPUT_LEFT) != 0) && ((g_NowKey & PAD_INPUT_DOWN) != 0))
		{
			c_MoveFlag = true;
			c_Slide = true;
			c_MoveVector.x = c_movespeed;
			c_MoveVector.z = c_movespeed;
			//�p�x���
			c_PlayerAng = 225.0f;
		}
		//�E���ړ�
		else if (((g_NowKey & PAD_INPUT_RIGHT) != 0) && ((g_NowKey & PAD_INPUT_DOWN) != 0))
		{
			c_MoveFlag = true;
			c_Slide = true;

			c_MoveVector.x = c_movespeed;
			c_MoveVector.z = c_movespeed;
			//�p�x���
			c_PlayerAng = 135.0f;
		}
		//�E��ړ�
		else if (((g_NowKey & PAD_INPUT_RIGHT) != 0) && ((g_NowKey & PAD_INPUT_UP) != 0))
		{
			c_MoveFlag = true;
			c_Slide = true;

			c_MoveVector.x = c_movespeed;
			c_MoveVector.z = c_movespeed;
			//�p�x���
			c_PlayerAng = 45.0f;
		}
		//�E�ړ�
		else if ((g_NowKey & PAD_INPUT_RIGHT) != 0)
		{
			c_MoveFlag = true;
			c_Slide = true;

			c_MoveVector.x = c_movespeed;

			//�p�x���
			c_PlayerAng = 90.0f;
		}
		//������
		else if ((g_NowKey & PAD_INPUT_LEFT) != 0)
		{
			c_MoveFlag = true;
			c_Slide = true;

			c_MoveVector.x = c_movespeed;

			//�p�x���
			c_PlayerAng = 270.0f;
		}
		//������
		else if ((g_NowKey & PAD_INPUT_DOWN) != 0)
		{
			c_MoveFlag = true;
			c_Slide = true;

			c_MoveVector.z = c_movespeed;

			//�p�x���
			c_PlayerAng = 180.0f;
		}
		//�����
		else if ((g_NowKey & PAD_INPUT_UP) != 0)
		{
			c_MoveFlag = true;
			c_Slide = true;

			c_MoveVector.z = c_movespeed;


			//�p�x���
			c_PlayerAng = 0.0f;
		}
	}

	//�v���C���[����莞�Ԏ~�܂�
	if (Damage.s_paralyzeKey == true) {
		if (CheckSoundMem(damage_sound) == 0) {
			PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
		}
		Player_Paralyze();
	}

	if (Key_Look == false)c_StmCount = PlayerStaminaCount(c_Slide, c_EnemyTuchFlg/*, c_StmStop*/, c_StmCount, c_StmMax);//�X�^�~�i�Ǘ�

	//�X�^�~�i�̌�����̏���
	if (c_StmCount <= 0) { c_movespeed = 1.0f; }
	else { c_movespeed = c_MoveMax; }

	//�ړ��t���O�������Ă���ړ�
	if (c_MoveFlag == true && c_StmStop == true)
	{
		if (c_Slide == true) {
			if (c_Acc == 0.0f) {//����
				c_Acc = 0.9f;
			}
			else if (c_Acc == 1.0f) {
			}
			else if (c_Acc > 1.0f) {
				c_Acc = 1.0f;
			}
			else {//�����x
				c_Acc += 0.01f;
			}
		}
		else {
			c_Acc -= 0.1f;

			if (c_Acc <= 0) {
				c_MoveFlag = false;
				c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
			}
		}


		//�ړ��ꏊ�̊m�F
		//VECTOR TempMoveVector;
		float Sin1 = sin(c_PlayerAng * (M_PI / 180));
		float Cos1 = cos(c_PlayerAng * (M_PI / 180));

		c_TempMoveVector.x = c_MoveVector.x * Sin1 * c_Acc;
		c_TempMoveVector.y = 0.0f;
		c_TempMoveVector.z = c_MoveVector.z * Cos1 * c_Acc;

		//�����蔻��̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (Collision_Cube(VAdd(c_Position, c_TempMoveVector), ene->c_ObjPos[i], CHAR_SIZE_X, CHAR_SIZE_Z) == true) {
				if (ene->CheckPara(i) == false) {
					c_MoveFlag = false;
				}
				else if ((ene->Enemy_Push(i, player, ene, c_TempMoveVector, 0)) == false) {//false�Ȃ瓮�����Ȃ������B
					c_MoveFlag = false;
				}
				c_EnemyTuchFlg = true;
			}
		}
		if (c_MoveFlag && c_StageIn == true) {//�ړ��ł���Ƃ��ɂ݂̂Ƃ���
			c_Position = VAdd(c_Position, c_TempMoveVector);		//�ړ�
			c_EnemyTuchFlg = false;
		}
		////�p�x���
		//c_Rotation.x = 0.0f;
		//c_Rotation.y = c_PlayerAng * (M_PI / 180);
		//c_Rotation.z = 0.0f;
	}
	else {
		c_Acc = 0.0f;
	}

	//�p�x���
	c_Rotation.x = 0.0f;
	c_Rotation.y = c_PlayerAng * (M_PI / 180);
	c_Rotation.z = 0.0f;

	//�U��
	if (((g_KeyFlg & PAD_INPUT_2) != 0 && Key_Look == false &&
		Att.s_AttackStartKey == false && c_StmCount >= Att.s_AttackCons && Damage.s_paralyzeKey == false)) {
		if (CheckSoundMem(player_attack_sound) == 0) {
			PlaySoundMem(player_attack_sound, DX_PLAYTYPE_BACK);
		}
		Att.s_AttackStartKey = true;
		Att.c_onePlayAttackEffect = false;
	}
	else if (((g_KeyFlg & PAD_INPUT_2) != 0 && Key_Look == false &&
		Att.s_AttackStartKey == false && c_StmCount < Att.s_AttackCons && Damage.s_paralyzeKey == false)) {
		if (CheckSoundMem(player_attack_false_sound) == 0) {
			PlaySoundMem(player_attack_false_sound, DX_PLAYTYPE_BACK);
		}

	}
	else if (((g_KeyFlg & PAD_INPUT_2) != 0 && Key_Look == false &&
		Att.s_AttackStartKey == false && Damage.s_paralyzeKey == true)) {
		if (CheckSoundMem(player_attack_false_sound) == 0) {
			PlaySoundMem(player_attack_false_sound, DX_PLAYTYPE_BACK);
		}
	}

	//�v���C���[�̍U��
	if (Att.s_AttackStartKey == true) Player_Attack(ene, c_Rotation);

	//�v���C���[�̃X�^�~�i��UI
	SetFontSize(30);
	DrawBox(49, 69, 51 + 200, 91, 0xFFFFFF, FALSE);

	//�X�^�~�i��100�ȏ�Ȃ�΃Q�[�W�E�ȉ��Ȃ�ԃQ�[�W
	DrawFormatString(50, 35, 0xFF0000, "ST");
	if (c_StmCount >= (c_StmMax * 0.3f)) {
		StopSoundMem(breath_sound);
		//DrawBox(c_StringPos.x - 29, c_StringPos.y - 54, c_StringPos.x + 39 * c_StmCount / c_StmMax, c_StringPos.y - 41, 0x008000, TRUE);
		DrawBox(50, 70, 50 + 200 * c_StmCount / c_StmMax, 90, 0x008000, TRUE);
	}
	else {
		if (CheckSoundMem(breath_sound) == 0)PlaySoundMem(breath_sound, DX_PLAYTYPE_BACK);
		//DrawBox(c_StringPos.x - 29, c_StringPos.y - 54, c_StringPos.x + 9 * c_StmCount / c_StmMax, c_StringPos.y - 41, 0xff4500, TRUE);
		DrawBox(50, 70, 50 + 200 * c_StmCount / c_StmMax, 90, 0xff4500, TRUE);
	}

	c_SmokeCount++;
	if (c_MoveFlag) {//�ړ��ł���Ƃ��ɂ݂̂Ƃ���.���G�t�F�N�g
		if (c_SmokeCount % 20 == 0) {//60�t���[�����Ƃɂ͂���
			// �G�t�F�N�g���Đ�����B
			c_SlotEffSmoke[(c_SmokeCount / 20) % 3] = PlayEffekseer3DEffect(c_EffSmoke);
			// �Đ����̃G�t�F�N�g���ړ�����B
			SetPosPlayingEffekseer3DEffect(c_SlotEffSmoke[(c_SmokeCount / 20) % 3], c_Position.x, 50.0f, c_Position.z);
		}
	}

	if (Collision_Player) {
		Collision_Draw(ene->c_ObjPos);//�f�o�b�N�p
	}
}

bool PLAYER::Player_Push(PLAYER* player, ENEMY* enemy, VECTOR PushVec, int count)
{
	//���т�Ă��邩�ǂ����B���т�Ă��Ȃ��Ȃ�false�ŋA��
	if (Damage.s_paralyzeKey == false || count > 2) {
		return false;
	}

	//�ړ����Ă邩�ǂ���
	bool r_MoveFlag = true;
	VECTOR r_MoveVector = PushVec;

	//�ړ��t���O�������Ă���ړ�
	if (r_MoveFlag == true)
	{

		c_TempMoveVector.x = r_MoveVector.x;
		c_TempMoveVector.y = 0.0f;
		c_TempMoveVector.z = r_MoveVector.z;


		//�����蔻��̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (Collision_Cube(VAdd(c_Position, c_TempMoveVector), enemy->c_ObjPos[i], CHAR_SIZE_X, CHAR_SIZE_Z) == true) {
				r_MoveFlag = false;
				if (enemy->Enemy_Push(i, player, enemy, c_TempMoveVector, count + 1) == false) {//false�Ȃ瓮�����Ȃ�����
					r_MoveFlag = false;
				}
			}
		}

		if (c_StageIn == false) {
			r_MoveFlag = false;
		}

		if (r_MoveFlag) {//�ړ��ł���Ƃ��ɂ݂̂Ƃ���
			c_Position = VAdd(c_Position, c_TempMoveVector);		//�ړ�
			//c_Rotation = VAdd(c_Rotation, TempRotVector);
		}
	}

	return r_MoveFlag;
}

void PLAYER::Collision_Draw(VECTOR EnemyPos[ENEMY_MAX]) {

	VECTOR Copy_Vect1;//�I�u�W�F�N�g�̃R�s�[
	VECTOR Copy_Vect2;//�I�u�W�F�N�g�̃R�s�[

	//�v���C���[�̃R���W����
	Copy_Vect1 = c_Position; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
	Copy_Vect2 = c_Position; Copy_Vect2.x += CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
	DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
	Copy_Vect1 = c_Position; Copy_Vect1.x -= CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
	Copy_Vect2 = c_Position; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
	DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
	Copy_Vect1 = c_Position; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z -= CHAR_SIZE_Z;
	Copy_Vect2 = c_Position; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
	DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
	Copy_Vect1 = c_Position; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
	Copy_Vect2 = c_Position; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z += CHAR_SIZE_Z;
	DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);





	//�I�u�W�F�N�g�̃R���W����
	for (int i = 0; i < 3; i++) {
		Copy_Vect1 = EnemyPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = EnemyPos[i]; Copy_Vect2.x += CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = EnemyPos[i]; Copy_Vect1.x -= CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = EnemyPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = EnemyPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z -= CHAR_SIZE_Z;
		Copy_Vect2 = EnemyPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = EnemyPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = EnemyPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z += CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);

		/*Copy_Vect1 = c_enemyCol->c_ObjPos[i];	Copy_Vect1.x += 55.0f;
		Copy_Vect2 = c_enemyCol->c_ObjPos[i];	Copy_Vect2.z += 55.0f;
		Copy_Vect3 = c_enemyCol->c_ObjPos[i];	Copy_Vect3.x += 55.0f;	Copy_Vect3.z += 55.0f;
		DrawLine3D(c_enemyCol->c_ObjPos[i], Copy_Vect1, 0xffffff);
		DrawLine3D(c_enemyCol->c_ObjPos[i], Copy_Vect2, 0xffffff);
		DrawLine3D(Copy_Vect1, Copy_Vect3, 0xffffff);
		DrawLine3D(Copy_Vect2, Copy_Vect3, 0xffffff);*/
	}

	//���a���T�T�ɓ��ꂵ�Ă���
	//DrawSphere3D(EnemyPos[0], 55.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

}

bool PLAYER::CheckHit(VECTOR c_Position, VECTOR LightPos) {

	VECTOR Player = c_Position;

	VECTOR Light = LightPos;

	/*SetFontSize(20);
	DrawFormatString(10, 100, 0x888888, "x:%f", Player.x);
	DrawFormatString(10, 130, 0x888888, "y:%f", Player.y);
	DrawFormatString(10, 160, 0x888888, "z:%f", Player.z);
	DrawFormatString(10, 190, 0x888888, "x:%f", Light.x);
	DrawFormatString(10, 220, 0x888888, "y:%f", Light.y);
	DrawFormatString(10, 250, 0x888888, "z:%f", Light.z);*/
	float cx = Light.x - Player.x;
	float cz = Light.z - Player.z;

	float cr = (cx * cx) + (cz * cz);
	float lr = (70.0f);
	float lr2 = (lr * lr);

	/*DrawSphere3D(Player,10.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	DrawSphere3D(Light,70.0f, 32, GetColor(255,0, 255), GetColor(255, 255, 255), TRUE);*/
	c_Player_win = false;
	// player��light�̓����蔻��( TRUE:�������Ă��� FALSE:�������Ă��Ȃ� )
	if (cr <= lr2) {
		c_Player_win = true;
		if (LightFlg == false) {
			c_MoveFlag = false;
		}
		return true;
	}

	return false;
}
