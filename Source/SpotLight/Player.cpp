#define _USE_MATH_DEFINES
#include <DxLib.h>
#include "Player.h"
#include "enemy.h"
#include "Camera.h"
#include <math.h>
//#include "Main.h"
#include "Debug.h"


PLAYER::PLAYER()
{
	// �v���C���[���W������
	c_Position = VGet(100.0f, 100.0f, 0.0f);
	c_PlayerAng = 0;	//�v���C���[�̊p�x
	//�v���C���[��]�i���W�A���ϊ��j
	c_Rotation = VGet(0.0f, (c_PlayerAng *(M_PI/180)), 0.0f);
	//�v���C���[�̑傫��������
	c_AddPosPlay = { 0.5f,0.5f,0.5f };

	c_MoveFlag = FALSE;	//�v���C���[���ړ����Ă���̂�����

	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	c_StmCount = 300;		//�v���C���[�̗̑�

	// �R�c���f���̓ǂݍ���
	//c_PlayerModel = MV1LoadModel("Model/MyPlayer.mv1");
	c_PlayerModel = MV1LoadModel("Model/obj.mv1");

	c_enemyCol = new ENEMY();
}

PLAYER::~PLAYER()
{
}

void PLAYER::Player_Controller() {
	//�v���C���[
	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(c_PlayerModel, c_Position);
	MV1SetRotationXYZ(c_PlayerModel, c_Rotation);
	MV1SetScale(c_PlayerModel, c_AddPosPlay);
	SetFontSize(18);
	DrawFormatString(10, 670, 0xFFFFFF, "�X�^�~�i�F%d / %d", c_StmCount, c_StmMax);

	//Player_Move(Sin, Cos);
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

void PLAYER::Player_Attack(ENEMY* ene, VECTOR Player_rot) {
	//�ړ��ꏊ�̊m�F
	float Sin = sin(Player_rot.y) * Att.s_Rang;
	float Cos = cos(Player_rot.y) * Att.s_Rang;

	float x = c_Position.x + Sin;
	float z = c_Position.z + Cos;

	Att.s_Rang += Att.s_AttackSpeed;
	//DrawSphere3D(c_Position, Att.s_Rang, 16, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

	DrawCube3D(VGet(x-100, c_Position.y, z),
		VGet(x+100.0f, c_Position.y+100.0f,z+200.0f),
		GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	
	if (Att.s_Rang >= Att.s_RangMax) {
		Att.s_AttackStartKey = false;
		Att.s_Rang = 0.0f;
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (HitCheck_Sphere_Sphere(c_Position, Att.s_Rang, c_enemyCol->c_ObjPos[i], 55)) {
			ene->SetEnemyMoveKey(i);
			Att.s_ParaKey[i] = true;
		}
	}
}

void PLAYER::Player_Move(CAMERA* camera, ENEMY* ene)
{
	//�ړ��ꏊ�̊m�F
	//VECTOR TempMoveVector;
	//VECTOR TempRotVector;
	//float PlayerSin = sin(c_Rotation.y) * 200;
	//float PlayerCos = cos(c_Rotation.y) * 200;
	//float Angx = c_Position.x + PlayerSin;
	//float Angz = c_Position.z + PlayerCos;
	//float Sin = sin(camera->GetCameraAngle() / 180.0f * M_PI);
	//float Cos = cos(camera->GetCameraAngle() / 180.0f * M_PI);



	//TempMoveVector.x = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
	//TempMoveVector.y = 0.0f;
	//TempMoveVector.z = c_MoveVector.x * Sin + c_MoveVector.z * Cos;

	//TempRotVector.x = 0.0f;
	////TempRotVector.y = (PlayerSin + PlayerCos * (M_PI / 180));
	//TempRotVector.y = 0.0f;
	//TempRotVector.z = 0.0f;

	//DrawFormatString(10, 100, 0x888888, "y:%f", 90 * (M_PI / 180.0f));
	//DrawFormatString(10, 130, 0x888888, "y:%f", Angx + Angz);
	//DrawSphere3D(VGet(Angx, c_Position.y, Angz),25, 32, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);

	//�ړ����Ă邩�ǂ���
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);

	if (Key_Look == false) {
		// �v���C���[�ړ�
		if (((g_NowKey & PAD_INPUT_LEFT) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.x = -c_movespeed;
				//TempRotVector.y = -c_movespeed;

			}

			//TempRotVector.x = 0.0f;
			//TempRotVector.y = 0.1f;
			//TempRotVector.z = 0.0f;
		}

		if (((g_NowKey & PAD_INPUT_RIGHT) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.x = c_movespeed;
				//TempRotVector.y = c_movespeed;
			}

			//TempRotVector.x = 0.0f;
			//TempRotVector.y = 0.1f;
			//TempRotVector.z = 0.0f;
		}

		if (((g_NowKey & PAD_INPUT_DOWN) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.z = -c_movespeed;
				//TempRotVector.y = -c_movespeed;
			}

			//TempRotVector.x = 0.0f;
			//TempRotVector.y = 0.1f;
			//TempRotVector.z = 0.0f;
		}

		if (((g_NowKey & PAD_INPUT_UP) != 0))
		{
			c_MoveFlag = true;
			if (c_StmCount > 0) {
				c_MoveVector.z = c_movespeed;
				//TempRotVector.y = c_movespeed;
			}

			//TempRotVector.x = 0.0f;
			//TempRotVector.y = 0.1f;
			//TempRotVector.z = 0.0f;
		}
	}

	//G�L�[����������v���C���[����莞�Ԏ~�܂�
	if (CheckHitKey(KEY_INPUT_G)) Damage.s_paralyzeKey = true;
	if (Damage.s_paralyzeKey == true) Player_Paralyze();

	c_StmCount = StaminaCount(c_MoveFlag);		//�X�^�~�i�Ǘ�

	//�U��
	if (((g_NowKey & PAD_INPUT_2) != 0) && ((g_NowKey & g_OldKey) == 0) && Att.s_AttackStartKey == false)Att.s_AttackStartKey = true;
	if (Att.s_AttackStartKey == true) Player_Attack(ene, c_Rotation);
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (Att.s_ParaKey[i] == true) {
			if (Att.s_TimePara++ >= Att.s_TimeMaxPara) {
				Att.s_TimePara = 0;
				ene->SetEnemyMoveKey(i);
			}
		}
	}

	//c_Rotation = VAdd(c_Rotation, TempRotVector);

	//float Sin1 = sin(c_Rotation.y);
	//float Cos1 = cos(c_Rotation.y);
	//float Sin1 = sin(c_Rotation.y) * 300;
	//float Cos1 = cos(c_Rotation.y) * 300;

	//float one = c_Position.x + Sin1;
	//float two = c_Position.z + Cos1;

	//DrawFormatString(10, 100, 0x888888, "y:%f", c_Rotation.y);

	//DrawCube3D(VGet(one, c_Position.y, two),
	//	VGet((one + 100.0f) * Sin1, c_Position.y + 100.0f, (two + 200.0f)),
	//	GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	//DrawSphere3D(VGet(one, c_Position.y,two),25, 32, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
	//DrawSphere3D(VGet(c_Position.x, c_Position.y+100.0f, c_Position.z),25, 32, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
	//printfDx("%f\n", c_Rotation.y);


	//VECTOR c_plus;

	//DrawCube3D(VGet(c_Position.x + c_Rotation.y - 100.0f, c_Position.y, c_Position.z + c_Rotation.y),
	//	VGet(c_Position.x + c_Rotation.y + 100.0f, c_Position.y + 100.0f, c_Position.z + c_Rotation.y + 200.0f),
	//	GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

	//�ړ��t���O�������Ă���ړ�
	if (c_MoveFlag == true)
	{
		//�ړ��ꏊ�̊m�F
		VECTOR TempMoveVector;
		
		float Sin = sin(camera->GetCameraAngle() / 180.0f * M_PI);
		float Cos = cos(camera->GetCameraAngle() / 180.0f * M_PI);

		TempMoveVector.x = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.x * Sin + c_MoveVector.z * Cos;

		//�����蔻��̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (Collision_Sphere(VAdd(c_Position, TempMoveVector), ene->c_ObjPos[i], 55) == true) {
				if (Att.s_ParaKey[i] == false) {
					c_MoveFlag = false;
				}
				else if ((ene->Enemy_Push(i, c_Position, TempMoveVector)) == false) {//false�Ȃ瓮�����Ȃ������B
					c_MoveFlag = false;
				}
			}
		}
		if (c_MoveFlag) {//�ړ��ł���Ƃ��ɂ݂̂Ƃ���
			c_Position = VAdd(c_Position, TempMoveVector);		//�ړ�
			//c_Rotation = VAdd(c_Rotation, TempRotVector);
		}
	}

	if (Collision_Player) {
		Collision_Draw(ene->c_ObjPos);//�f�o�b�N�p
	}
}

bool PLAYER::Player_Push(CAMERA* camera, VECTOR EnemyCol[ENEMY_MAX], VECTOR PushVec)
{
	//���т�Ă��邩�ǂ����B���т�Ă��Ȃ��Ȃ�false�ŋA��
	if (Damage.s_paralyzeKey == false) {
		return false;
	}

	//�ړ��ꏊ�̊m�F
	VECTOR TempMoveVector;
	//VECTOR TempRotVector;




	//�ړ����Ă邩�ǂ���
	c_MoveFlag = true;
	c_MoveVector = PushVec;

	//float Sin = sin(camera->GetCameraAngle() / 180.0f * DX_PI_F);
	//float Cos = cos(camera->GetCameraAngle() / 180.0f * DX_PI_F);

	//TempMoveVector.x = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
	//TempMoveVector.y = 0.0f;
	//TempMoveVector.z = c_MoveVector.x * Sin + c_MoveVector.z * Cos;

	//TempRotVector.x = 0.0f;
	//TempRotVector.y = c_MoveVector.x * Cos - c_MoveVector.z * Sin;
	//TempRotVector.z = 0.0f;

	//�ړ��t���O�������Ă���ړ�
	if (c_MoveFlag == true)
	{

		TempMoveVector.x = c_MoveVector.x;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z;


		//�����蔻��̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (Collision_Sphere(VAdd(c_Position, TempMoveVector), EnemyCol[i], 55) == true) {
				c_MoveFlag = false;
			}
		}
		if (c_MoveFlag) {//�ړ��ł���Ƃ��ɂ݂̂Ƃ���
			c_Position = VAdd(c_Position, TempMoveVector);		//�ړ�
			//c_Rotation = VAdd(c_Rotation, TempRotVector);
		}
	}

	return c_MoveFlag;
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
	for (int i = 1; i < 3; i++) {
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
	DrawSphere3D(EnemyPos[0], 55.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

}