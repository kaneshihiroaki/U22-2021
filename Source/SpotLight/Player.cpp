#include <DxLib.h>
#include "Player.h"
#include <math.h>

#include "Debug.h"


PLAYER::PLAYER()
{
	// �v���C���[���W������
	c_Position = VGet(100.0f, 100.0f, 0.0f);
	//�v���C���[�̑傫��������
	c_AddPosPlay = { 0.5f,0.5f,0.5f };

	c_MoveFlag = FALSE;	//�v���C���[���ړ����Ă���̂�����

	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	// �R�c���f���̓ǂݍ���
	c_PlayerModel = MV1LoadModel("Model/MyPlayer.mv1");
}

PLAYER::~PLAYER()
{
}

void PLAYER::Player_Controller(float Sin, float Cos) {
	//�v���C���[
	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(c_PlayerModel, c_Position);
	MV1SetScale(c_PlayerModel, c_AddPosPlay);

	DrawFormatString(10, 450, 0xFFFFFF, "�X�^�~�i�F%d / %d", Stamina.s_Count, Stamina.s_StaminaMax);

	Player_Move(Sin, Cos);
}

// �v���C���[�ƃI�u�W�F�N�g�̂����蔻��
bool Collision_Cube(VECTOR PlayerCol, VECTOR ObjCol, float EnemyScale) {
	// �e���W���擾����
	VECTOR pos = PlayerCol;
	VECTOR posObj = ObjCol;

	//����������true
	if ((pos.x + CHAR_SIZE_X > posObj.x - EnemyScale &&
		pos.z + CHAR_SIZE_Z > posObj.z - EnemyScale) &&
		(pos.x - CHAR_SIZE_X < posObj.x + EnemyScale &&
			pos.z - CHAR_SIZE_Z < posObj.z + EnemyScale)) {
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

void PLAYER::Player_Paralyze() {
	c_MoveFlag = false;

	if (Damage.s_ParaTime++ == Damage.s_MaxTimeParalyze) {
		Damage.s_paralyzeKey = false;
		Damage.s_ParaTime = 0;
	}
}

void PLAYER::Player_StaminaCount() {
	if (c_MoveFlag == false) {
		if (Stamina.s_Count < Stamina.s_StaminaMax) {
			Stamina.s_Count++;
		}
	}
	else {
		if (Stamina.s_Count > 0) {
			Stamina.s_Count--;
		}
	}
}

void PLAYER::Player_Attack() {
	Att.s_Rang += Att.s_AttackSpeed;
	DrawSphere3D(c_Position, Att.s_Rang, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

	if (Att.s_Rang >= Att.s_RangMax) {
		Att.s_AttackStartKey = false;
		Att.s_Rang = 0.0f;
	}
}

void PLAYER::Player_Move(float Sin, float Cos)
{
	//�ړ����Ă邩�ǂ���
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	// �v���C���[�ړ�
	if (((g_NowKey & PAD_INPUT_LEFT) != 0))
	{
		c_MoveFlag = true;
		if (Stamina.s_Count > 0)c_MoveVector.x = -c_movespeed;
	}

	if (((g_NowKey & PAD_INPUT_RIGHT) != 0))
	{
		c_MoveFlag = true;
		if (Stamina.s_Count > 0)c_MoveVector.x = c_movespeed;
	}

	if (((g_NowKey & PAD_INPUT_DOWN) != 0))
	{
		c_MoveFlag = true;
		if (Stamina.s_Count > 0)c_MoveVector.z = -c_movespeed;
	}

	if (((g_NowKey & PAD_INPUT_UP) != 0))
	{
		c_MoveFlag = true;
		if (Stamina.s_Count > 0)c_MoveVector.z = c_movespeed;
	}

	//G�L�[����������v���C���[����莞�Ԏ~�܂�
	if (CheckHitKey(KEY_INPUT_G)) Damage.s_paralyzeKey = true;
	if (Damage.s_paralyzeKey == true) Player_Paralyze();

	Player_StaminaCount();		//�X�^�~�i�Ǘ�

	if (CheckHitKey(KEY_INPUT_A) && Att.s_AttackStartKey == false)Att.s_AttackStartKey = true;
	if(Att.s_AttackStartKey == true) Player_Attack();

	//�ړ��t���O�������Ă���ړ�
	if (c_MoveFlag == true)
	{
		//�ړ��ꏊ�̊m�F
		VECTOR TempMoveVector;

		TempMoveVector.x = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.x * Sin + c_MoveVector.z * Cos;

		//�����蔻��̊m�F
		if (Collision_Sphere(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[0], 55) == false &&
			Collision_Cube(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[1], 55) == false &&
			Collision_Cube(VAdd(c_Position, TempMoveVector), c_enemyCol->c_ObjPos[2], 55) == false) {
			c_Position = VAdd(c_Position, TempMoveVector);		//�ړ�
		}
	}

	if (Collision_Player) {
		Collision_Draw();//�f�o�b�N�p
	}
}

void PLAYER::Collision_Draw() {

	VECTOR Copy_Vect1;//�I�u�W�F�N�g�̃R�s�[
	VECTOR Copy_Vect2;//�I�u�W�F�N�g�̃R�s�[
	VECTOR Copy_Vect3;//�I�u�W�F�N�g�̃R�s�[

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
	for (int i = 1; i < 3; i++) {
		Copy_Vect1 = c_enemyCol->c_ObjPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = c_enemyCol->c_ObjPos[i]; Copy_Vect2.x += CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = c_enemyCol->c_ObjPos[i]; Copy_Vect1.x -= CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = c_enemyCol->c_ObjPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = c_enemyCol->c_ObjPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z -= CHAR_SIZE_Z;
		Copy_Vect2 = c_enemyCol->c_ObjPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z -= CHAR_SIZE_Z;
		DrawLine3D(Copy_Vect1, Copy_Vect2, 0x00ffff);
		Copy_Vect1 = c_enemyCol->c_ObjPos[i]; Copy_Vect1.x += CHAR_SIZE_X; Copy_Vect1.z += CHAR_SIZE_Z;
		Copy_Vect2 = c_enemyCol->c_ObjPos[i]; Copy_Vect2.x -= CHAR_SIZE_X; Copy_Vect2.z += CHAR_SIZE_Z;
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
	DrawSphere3D(c_enemyCol->c_ObjPos[0], 55.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

}