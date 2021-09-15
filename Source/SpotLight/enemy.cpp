#define _USE_MATH_DEFINES

#include <DxLib.h>
#include <math.h>

#include "enemy.h"
#include "Light.h"
#include "Player.h"
#include "Camera.h"
#include "debug.h"
#include "GameSound.h"


int ENEMY_WIN;//�ǂ̓G�������������ׂ�ϐ�
int ENEMY_WIN_COUNT1;//�G�P�̏�����
int ENEMY_WIN_COUNT2;//�G�Q�̏�����
int ENEMY_WIN_COUNT3;//�G�R�̏�����


ENEMY::ENEMY()
{
	////�I�u�W�F�N�g�̍��W������
	//c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	//c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	//c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// �R�c���f���̓ǂݍ���
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == 0) {//��
			c_EnemyModel[i] = MV1LoadModel("Model/EnMe3.mv1");
			c_WinEnemyModel[i] = MV1LoadModel("Model/EnMe4.mv1");
		}
		else if (i == 1) {//��
			//			c_EnemyModel[i] = MV1LoadModel("Model/obj.mv1");
			c_EnemyModel[i] = MV1LoadModel("Model/EnMe5.mv1");
			c_WinEnemyModel[i] = MV1LoadModel("Model/EnMe6.mv1");
		}
		else {//�I�����W
			//			c_EnemyModel[i] = MV1LoadModel("Model/obj.mv1");
			c_EnemyModel[i] = MV1LoadModel("Model/EnMe7.mv1");
			c_WinEnemyModel[i] = MV1LoadModel("Model/EnMe8.mv1");
		}
		
		//c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		//c_MoveKey[i] = true;
		//c_StmCount[i] = 300;	//�G�l�~�[�̗̑͂̍ő�
		//c_Rotation[i] = VGet(0.0f, 0.0f /*(c_PlayerAng * (M_PI / 180))*/, 0.0f);//�G�l�~�[�̉�]
		//c_Enemy_MoveAng[i] = 0;//�G�l�~�[�̊p�x
		//c_EnemySpeed[i] = 0.0f;//�G�l�~�[�̃X�s�[�h
		//c_EnemyState[i] = ENEMY_IDLE;//�G�l�~�[�̏������
		//MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//�G�l�~�[�̃X�P�[��������Ă���

		//c_EnemyAddVect[i] = VGet(0.0f, 0.0f, 0.0f);//�ǂ��z�������̂Ƃ��ɉ��Z����x�N�g����ۑ�
		//c_EnemyFrameCount[i] = 0;//�ǂ��z�������̂Ƃ��Ƀt���𐔂���
	}

	//c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//�X�|�b�g���C�g�̍��W
	//Coefficient = 1.0f;
	//c_MoveFlag = FALSE;
	//c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
}

ENEMY::~ENEMY()
{
}

void ENEMY::init() {
	//�I�u�W�F�N�g�̍��W������
	c_ObjPos[0] = VGet(-150.0f, 100.0f, 0.0f);
	c_ObjPos[1] = VGet(150.0f, 100.0f, 0.0f);
	c_ObjPos[2] = VGet(450.0f, 100.0f, 0.0f);

	// �R�c���f���̓ǂݍ���
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		c_StmCount[i] = c_StmMax;	//�G�l�~�[�̗̑͂̍ő�
		c_Rotation[i] = VGet(0.0f, (180.0f * (M_PI / 180)), 0.0f);//�G�l�~�[�̉�]
		c_Enemy_MoveAng[i] = 180;//�G�l�~�[�̊p�x
		c_EnemySpeed[i] = 0.0f;//�G�l�~�[�̃X�s�[�h
		c_EnemyState[i] = ENEMY_IDLE;//�G�l�~�[�̏������
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//�G�l�~�[�̃X�P�[��������Ă���
		MV1SetScale(c_WinEnemyModel[i], c_AddPosEnemy[i]);//�G�l�~�[�̃X�P�[��������Ă���

		c_EnemyAddVect[i] = VGet(0.0f, 0.0f, 0.0f);//�ǂ��z�������̂Ƃ��ɉ��Z����x�N�g����ۑ�
		c_EnemyFrameCount[i] = 0;//�ǂ��z�������̂Ƃ��Ƀt���𐔂���
		Damage[i].s_paralyzeKey = false;//���тꂽ���̕ϐ�������
		c_AliveEnemy[i] = true;
		Damage[i].s_ParaTime = 0;
		c_EnemyWin[i] = false;
		//�U�����Ă���t���O��������
		Att[i].s_AttackStartKey = false;
		Att[i].s_GetOneRot = false;
		Att[i].s_Rang = 0.0f;
	}

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//�X�|�b�g���C�g�̍��W
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
	Character_Init();
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_TempMoveVector[i] = VGet(0.0f, 0.0f, 0.0f);
	}
}

void ENEMY::Sadon_init() {
	

	// �R�c���f���̓ǂݍ���
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (c_AliveEnemy[i] == true) {
			c_ObjPos[i] = VGet(-150.0f + (300.0f * i), 100.0f, 0.0f);
		}
		else {//�G�l�~�[�����݂��Ȃ��B�̂ŉ����ɔ�΂�
			c_ObjPos[i] = VGet(-5000.0f, 100.0f, 0.0f);
		}
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		c_StmCount[i] = c_StmMax;	//�G�l�~�[�̗̑͂̍ő�
		c_Rotation[i] = VGet(0.0f, 0.0f /*(c_PlayerAng * (M_PI / 180))*/, 0.0f);//�G�l�~�[�̉�]
		c_Enemy_MoveAng[i] = 0;//�G�l�~�[�̊p�x
		c_EnemySpeed[i] = 0.0f;//�G�l�~�[�̃X�s�[�h
		c_EnemyState[i] = ENEMY_IDLE;//�G�l�~�[�̏������
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//�G�l�~�[�̃X�P�[��������Ă���
		MV1SetScale(c_WinEnemyModel[i], c_AddPosEnemy[i]);//�G�l�~�[�̃X�P�[��������Ă���

		c_EnemyAddVect[i] = VGet(0.0f, 0.0f, 0.0f);//�ǂ��z�������̂Ƃ��ɉ��Z����x�N�g����ۑ�
		c_EnemyFrameCount[i] = 0;//�ǂ��z�������̂Ƃ��Ƀt���𐔂���
		Damage[i].s_paralyzeKey = false;//���тꂽ���̕ϐ�������
		//c_AliveEnemy[i] = true;
		Damage[i].s_ParaTime = 0;
		c_EnemyWin[i] = false;
		//�U�����Ă���t���O��������
		Att[i].s_AttackStartKey = false;
		Att[i].s_GetOneRot = false;
		Att[i].s_Rang = 0.0f;
	}

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//�X�|�b�g���C�g�̍��W
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
	Character_Init();
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_TempMoveVector[i] = VGet(0.0f, 0.0f, 0.0f);
	}
}

void ENEMY::Enemy_Creat() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (c_AliveEnemy[i] == false)continue;//���݂��Ȃ��Ƃ�
		if (Damage[i].s_ParaTime%20<10 || Key_Look) {//0~9�܂ł͕`��10~19�܂ł͕`�悵�Ȃ��B�����������̂͂��������̂ŕ\������
			if (c_EnemyWin[i]) {//�������肵�Ă���Ƃ�
				MV1SetPosition(c_WinEnemyModel[i], c_ObjPos[i]);//�G�l�~�[�̈ړ���ʒu������Ă�
				MV1SetRotationXYZ(c_WinEnemyModel[i], c_Rotation[i]);//�G�l�~�[�̊p�x������Ă���
				MV1DrawModel(c_WinEnemyModel[i]);				 //�G�l�~�[�̃��f���`��
			}
			else {
				MV1SetPosition(c_EnemyModel[i], c_ObjPos[i]);//�G�l�~�[�̈ړ���ʒu������Ă�
				MV1SetRotationXYZ(c_EnemyModel[i], c_Rotation[i]);//�G�l�~�[�̊p�x������Ă���
				MV1DrawModel(c_EnemyModel[i]);				 //�G�l�~�[�̃��f���`��
			}
		}
	}
	//�I�u�W�F�N�g�`��
	//DrawSphere3D(c_ObjPos[0], 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[1], VAdd(c_ObjPos[1], VECTOR{ 50,50,50 }), GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[2], VAdd(c_ObjPos[2], VECTOR{ 50,50,50 }), GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

void ENEMY::debug() {
	//printfDx("%d\n", GetEnemyMoveKey(2));
}

void ENEMY::Enemy_State(int num, PLAYER* player, ENEMY* enemy) {
	if (Key_Look)return;//���s���������Ƃ��Ȃǂɓ���Ȃ��悤�ɂ���t���O
	if (c_AliveEnemy[num] == false)return;//�G�l�~�[�����݂��Ă��Ȃ��Ƃ�
	if (num == 0) {//�^�C�v�������[
		Ga_Move(num, player);
		Ga_Attack(num, player);
	}
	else if (num == 1) {//�^�C�v�T���O���X
		San_Move(num);
		San_Attack(num, player);
	}
	else if (num == 2) {//�^�C�v�A�X�J
		A_Move(num);
		A_Attack(num, player);
	}
	else {//����ȊO
		Bot_Normal(num, player);
	}
	
	
	if (Damage[num].s_paralyzeKey == true) {
		if (CheckSoundMem(damage_sound) == 0) {
			PlaySoundMem(damage_sound, DX_PLAYTYPE_BACK);
		}
		Enemy_Paralyze(num);//���т�Ă���Ȃ�J�E���g���Ȃ��Ƃ����Ȃ�
	}
	
	SetFontSize(20);
	switch (c_EnemyState[num])
	{
	case ENEMY_IDLE:
		c_StmCount[num] = StaminaCount(false, num);		//�X�^�~�i��
		if (Debug_Enemy) {
			DrawFormatString(1100, 420 + 20 * num, 0xFFFFFF, "%d IDLE\n", num);
		}
		break;
	case ENEMY_MOVE:
		Enemy_Move(num, player, enemy);
		if (Debug_Enemy) {
			DrawFormatString(1100, 420 + 20 * num, 0xFFFFFF, "%d MOVE\n", num);
		}
		break;
	case ENEMY_ATTACK:
		break;
	}

	if (Debug_Enemy) {
		DrawFormatString(1100, 620 + 20 * num, 0xFFFFFF, "%d %d\n", num, c_StmCount[num]);
		if (Damage[num].s_paralyzeKey) {
			DrawFormatString(1100, 520 + 20 * num, 0xFFFFFF, "%d True\n", num);
		}
		else {
			DrawFormatString(1100, 520 + 20 * num, 0xFFFFFF, "%d False\n", num);
		}
		DrawFormatString(500, 520 + 20 * num, 0xFFFFFF, "x:%lf y:%lf z:%lf\n", c_ObjPos[num].x, c_ObjPos[num].y, c_ObjPos[num].z);
		if (c_EnemyWin[num]) {
			DrawFormatString(100, 520 + 20 * num, 0xFFFFFF, "true\n");
		}
		else {
			DrawFormatString(100, 520 + 20 * num, 0xFFFFFF, "false\n");
		}
		
	}
	
}

void ENEMY::Enemy_Move(int num, PLAYER* player, ENEMY* enemy)
{
	int p_Enemy_MoveAng = 0;//�G�l�~�[�̌������p�x
	//�ړ����Ă邩�ǂ���
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);


	Coefficient = 1.0f;

	c_SpotPos = LightPos;

	// �X�|�b�g���C�g��ǐ՗p
	if (c_SpotPos.x - c_SpotRadius > c_ObjPos[num].x) {
		c_MoveFlag = true;
		if (c_StmCount[num] > 0)c_MoveVector.x = c_movespeed;
		p_Enemy_MoveAng = 90;//�E

	}

	if (c_SpotPos.x + c_SpotRadius < c_ObjPos[num].x) {
		c_MoveFlag = true;
		if (c_StmCount[num] > 0)c_MoveVector.x = -c_movespeed;
		p_Enemy_MoveAng = 270;//��

	}

	if (c_SpotPos.z - c_SpotRadius > c_ObjPos[num].z) {
		c_MoveFlag = true;
		if (c_StmCount[num] > 0)c_MoveVector.z = c_movespeed;
		p_Enemy_MoveAng = 0;//��

	}

	if (c_SpotPos.z + c_SpotRadius < c_ObjPos[num].z) {
		c_MoveFlag = true;
		if (c_StmCount[num] > 0)c_MoveVector.z = -c_movespeed;
		p_Enemy_MoveAng = 180;//��
	}

	/****************
	��������
	*****************/
	//�G���ǂ��z������(�G)
	for (int i = 0; i < ENEMY_MAX; i++) {
		//if (num != 0)continue;//�O�̂݌���
		if (i == num)continue;
		VECTOR Check_Future_Pos = c_ObjPos[num];//�ύX���Ă������悤�Ƀ��[�J��VEC�ϐ�
		Check_Future_Pos.x += (c_MoveVector.x * 15);//�P�`�R�O�t���[����̃|�W�V�����i���j speed�~30�t���[��
		Check_Future_Pos.z += (c_MoveVector.z * 15);//�P�`�R�O�t���[����̃|�W�V�����i���j
		//if (i == 1)DrawSphere3D(Check_Future_Pos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		if (c_EnemyFrameCount[num] == 0) {



			
			//if(Collision_Cube())�@//�p�x���Q�Ƃ��Ă��Ȃ��̂ŕύX������
			if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], c_ObjPos[i], 30, 150, 105, 55) == true) {

				float rad = c_Rotation[num].y + (M_PI / 2);
				c_EnemyAddVect[num].x = 5.0f * sinf(rad)/* - c_MoveVector.z * sin(rad)*/;
				c_EnemyAddVect[num].z = 5.0f * cosf(rad) /*+ c_MoveVector.z * cos(rad)*/;

				c_MoveVector.x += c_EnemyAddVect[num].x;
				c_MoveVector.z += c_EnemyAddVect[num].z;

				c_EnemyFrameCount[num] = 1;

				//c_MoveVector.x += 5.0f;

				SetFontSize(20);
				//DrawFormatString(1100, 600, 0xFFFFFF, "���邺\n");

			}
			//1�񂾂��ʂ�
			if (i == 0 || (num == 0 && i == 1)) {
				if (Collision_Cube2(Check_Future_Pos, c_Rotation[num],player->c_Position, 30, 150, 105, 55) == true) {

					float rad = c_Rotation[num].y + (M_PI / 2);
					c_EnemyAddVect[num].x = 5.0f * sinf(rad)/* - c_MoveVector.z * sin(rad)*/;
					c_EnemyAddVect[num].z = 5.0f * cosf(rad) /*+ c_MoveVector.z * cos(rad)*/;

					c_MoveVector.x += c_EnemyAddVect[num].x;
					c_MoveVector.z += c_EnemyAddVect[num].z;

					c_EnemyFrameCount[num] = 1;

					//c_MoveVector.x += 5.0f;

					SetFontSize(20);
					//DrawFormatString(1100, 600, 0xFFFFFF, "���邺\n");

				}
			}
		}
		else if (c_EnemyFrameCount[num] < 30*(ENEMY_MAX-1)) {
			c_MoveVector.x += c_EnemyAddVect[num].x;
			c_MoveVector.z += c_EnemyAddVect[num].z;
			c_EnemyFrameCount[num]++;
		}
		else {
			c_EnemyFrameCount[num] = 0;
		}
	}
	//�G���ǂ��z�������i�v���C���[�j
	/****************
	�����܂�
	*****************/

	if ((c_MoveVector.x != 0.0f) && (c_MoveVector.z != 0.0f)) {
		Coefficient = 0.7f;
		if ((c_MoveVector.x > 0.0f) && (c_MoveVector.z > 0.0f))p_Enemy_MoveAng = 45;//�E��
		if ((c_MoveVector.x > 0.0f) && (c_MoveVector.z < 0.0f))p_Enemy_MoveAng = 135;//�E��
		if ((c_MoveVector.x < 0.0f) && (c_MoveVector.z < 0.0f))p_Enemy_MoveAng = 225;//����
		if ((c_MoveVector.x < 0.0f) && (c_MoveVector.z > 0.0f))p_Enemy_MoveAng = 315;//����
	}

	//�G�l�~�[�̊p�x������
	if (c_Enemy_MoveAng[num] >= 180) {//���݂̊p�x��180~359
		if (c_Enemy_MoveAng[num] < p_Enemy_MoveAng || c_Enemy_MoveAng[num] - 180 > p_Enemy_MoveAng) {//185�ȏ��5����
			if ((c_Enemy_MoveAng[num] < p_Enemy_MoveAng && c_Enemy_MoveAng[num] + 6 > p_Enemy_MoveAng) || (c_Enemy_MoveAng[num] + 6 - 360 > p_Enemy_MoveAng)) {
				c_Enemy_MoveAng[num] = p_Enemy_MoveAng;
			}
			else {
				c_Enemy_MoveAng[num] += 6;
				if (c_Enemy_MoveAng[num] >= 360) {
					c_Enemy_MoveAng[num] -= 360;
				}
			}
		}
		else {//���݂̊p�x��185�Ƃ��āA�ڎw���p�x��185�ȉ���5�ȏ�Ȃ�
			if (c_Enemy_MoveAng[num] - 6 < p_Enemy_MoveAng) {
				c_Enemy_MoveAng[num] = p_Enemy_MoveAng;
			}
			else {
				c_Enemy_MoveAng[num] -= 6;
			}
		}
	}
	else {//���݂̊p�x��0~179
		if (c_Enemy_MoveAng[num] > p_Enemy_MoveAng || c_Enemy_MoveAng[num] + 180 < p_Enemy_MoveAng) {//
			if ((c_Enemy_MoveAng[num] > p_Enemy_MoveAng && c_Enemy_MoveAng[num] - 6 < p_Enemy_MoveAng) || c_Enemy_MoveAng[num] - 6 + 360 < p_Enemy_MoveAng) {
				c_Enemy_MoveAng[num] = p_Enemy_MoveAng;
			}
			else {
				c_Enemy_MoveAng[num] -= 6;
				if (c_Enemy_MoveAng[num] < 0) {
					c_Enemy_MoveAng[num] += 360;
				}
			}
		}
		else {//���݂̊p�x��5�Ƃ��āA�ڎw���p�x��185�ȉ���5�ȏ�Ȃ�
			if (c_Enemy_MoveAng[num] + 6 > p_Enemy_MoveAng) {
				c_Enemy_MoveAng[num] = p_Enemy_MoveAng;
			}
			else {
				c_Enemy_MoveAng[num] += 6;
			}
		}
	}
	c_Rotation[num].y = c_Enemy_MoveAng[num] * (M_PI / 180);

	if (Damage[num].s_paralyzeKey == true) c_MoveFlag = false; //���т�Ă���Ȃ�ړ��t���O��off�ɂ���
	
	if (Att[num].s_AttackStartKey == true) Enemy_Attack(player, num);
	
	//�ړ��t���O�������Ă���ړ�
	if (c_MoveFlag == true)
	{
		if (c_EnemySpeed[num] == 0.0f) {//����
			c_EnemySpeed[num] = 0.9f;
		}
		else if (c_EnemySpeed[num] == 1.0f) {
		}
		else if (c_EnemySpeed[num] > 1.0f) {
			c_EnemySpeed[num] = 1.0f;
		}
		else {//�����x
			c_EnemySpeed[num] += 0.01f;
		}

		//�ړ��ꏊ�̊m�F
		//VECTOR TempMoveVector;

		c_TempMoveVector[num].x = c_MoveVector.x * Coefficient * c_EnemySpeed[num];
		c_TempMoveVector[num].y = 0.0f;
		c_TempMoveVector[num].z = c_MoveVector.z * Coefficient * c_EnemySpeed[num];


		//������l����̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], c_TempMoveVector[num]), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT ) == true) {
				if (Enemy_Push(i, player,enemy, c_TempMoveVector[num], 0) == false) {//false�Ȃ瓮�����Ȃ�����
					VECTOR Reserve_Vect = c_TempMoveVector[num];//X���W��0�ɂ��Ă݂�

					float Reserve = Reserve_Vect.x;//X���W��0�ɂ��Ă݂�
					Reserve_Vect.x = 0.0f;//
					
					if (Coefficient!=1.0f) {
						if ((Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) && (Enemy_Push(i, player, enemy,  Reserve_Vect,0) == false)) {
							Reserve_Vect.x = Reserve;//
							Reserve = Reserve_Vect.z;//
							Reserve_Vect.z = 0.0f;//
							if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
								if (Enemy_Push(i, player,enemy, Reserve_Vect, 0) == false) {//false�Ȃ瓮�����Ȃ�����
									c_MoveFlag = false;
								}
							}
						}
					}
					else {
						c_MoveFlag = false;
					}
					
					

					if (c_MoveFlag) {//TRUE�Ȃ�ړ����ύX
						c_TempMoveVector[num] = Reserve_Vect;
					}
					
				}
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], c_TempMoveVector[num]), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
			if (player->Player_Push(player,enemy,c_TempMoveVector[num], 0) == false) {//false�Ȃ瓮�����Ȃ�����
				VECTOR Reserve_Vect = c_TempMoveVector[num];//X���W��0�ɂ��Ă݂�

				float Reserve = Reserve_Vect.x;//X���W��0�ɂ��Ă݂�
				Reserve_Vect.x = 0.0f;//
				if (Coefficient != 1.0) {
					if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true && player->Player_Push(player, enemy,  Reserve_Vect, 0) == false) {//false�Ȃ瓮�����Ȃ�����

						Reserve_Vect.x = Reserve;//
						Reserve = Reserve_Vect.z;//
						Reserve_Vect.z = 0.0f;//
						if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
							if (player->Player_Push(player, enemy, Reserve_Vect, 0) == false) {//false�Ȃ瓮�����Ȃ�����
								c_MoveFlag = false;
							}
						}
					}
				}
				else {
					c_MoveFlag = false;
				}

				if (c_MoveFlag) {//TRUE�Ȃ�ړ����ύX
					c_TempMoveVector[num] = Reserve_Vect;
				}
			}
		}
		//c_MoveKey��true��������X�e�[�W�Ȃ��ɂ��遁����
		if (c_MoveFlag == true && c_MoveKey[num] == true)
		{
			c_ObjPos[num] = VAdd(c_ObjPos[num], c_TempMoveVector[num]);
		}
		
	}

	if(c_MoveFlag == false) {//�ړ����s
		c_EnemySpeed[num] = 0.0f;
	}
	c_StmCount[num] = StaminaCount(c_MoveFlag,num);		//�X�^�~�i�Ǘ�


	
	//DrawSphere3D(c_SpotPos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	
	//if (Collision_Player) {
	//	Collision_Draw();//�f�o�b�N�p
	//}
}


//num�͉�����鑤
bool ENEMY::Enemy_Push(int num, PLAYER* player, ENEMY* enemy, VECTOR PushVec, int count)
{
	//���т�Ă��邩�ǂ����B���т�Ă��Ȃ��Ȃ�false�ŋA��܂��̓J�E���g��3��ڈȏ�Ȃ�false�ł�����I�[�o�[�t���[�΍�
	if (Damage[num].s_paralyzeKey == false || count > 2) {
		return false;
	}
	//�����ŐV�������[�J���ϐ����쐬
	//�ړ����Ă邩�ǂ���
	bool r_MoveFlag = true;
	VECTOR r_MoveVector = PushVec;

	float r_Coefficient = 1.0f;







	//�ړ��t���O�������Ă���ړ�
	if (r_MoveFlag == true)
	{
		//�ړ��ꏊ�̊m�F
		c_TempMoveVector[num].x = r_MoveVector.x * r_Coefficient;
		c_TempMoveVector[num].y = 0.0f;
		c_TempMoveVector[num].z = r_MoveVector.z * r_Coefficient;


		//������l����̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], c_TempMoveVector[num]), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
				if (Enemy_Push(i, player, enemy, c_TempMoveVector[num], count + 1) == false) {//false�Ȃ瓮�����Ȃ�����
					r_MoveFlag = false;
				}
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], c_TempMoveVector[num]), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_WIDTH, ENEMY_HEIGHT) == true) {
			if (player->Player_Push(player, enemy, c_TempMoveVector[num], count + 1) == false) {//false�Ȃ瓮�����Ȃ�����
				r_MoveFlag = false;
			}
		}
		if (c_MoveKey[num] == false) {
			r_MoveFlag = false;
		}

		if (r_MoveFlag == true)
		{
			c_ObjPos[num] = VAdd(c_ObjPos[num], c_TempMoveVector[num]);
		}
	}
	//if (Collision_Player) {
	//	Collision_Draw();//�f�o�b�N�p
	//}

	return r_MoveFlag;
}


// �v���C���[�ƃI�u�W�F�N�g�̂����蔻��//�p�x���Q�Ƃł���悤�ɂ���i�������j
//MyCol�������̒��S���W�AYouCol������̒��S���W�AMyScale�������̑傫�����������A�c�Ɖ����ǉ�����
bool Collision_Cube(VECTOR MyCol,VECTOR MyRot, VECTOR YouCol, float MyScale_X,float MyScale_Z, float YouScale_X, float YouScale_Z) {
	// �e���W���擾����
	VECTOR pos = MyCol;
	VECTOR rot = MyRot;
	VECTOR posYou = YouCol;

	/*********************************************************************************
	

	// ��`�̒��S�����_�Ƃ������΍��W���쐬����
	VECTOR relative_position = VGet(posYou.x - pos.x,0.0f, posYou.z - pos.z);

	// ���΍��W�ɑ΂��ċ�`�̉�]��ł������t�s����|����
	VECTOR transform_pos = VGet(
		cosf(rot.y) * relative_position.x + sinf(rot.y) * relative_position.z,
		0.0f,
		-sinf(rot.y) * relative_position.x + cosf(rot.y) * relative_position.z
	);

	// ��`�Ɠ_�̓����蔻����s��
	if (-MyScale_X / 2.0f <= transform_pos.x && MyScale_X / 2.0f >= transform_pos.x &&
		-MyScale_Z / 2.0f <= transform_pos.z && MyScale_Z / 2.0f >= transform_pos.z)
	{
		return true;
	}
	***********************************************************************/

	//����������true
	if ((pos.x + MyScale_X > posYou.x - YouScale_X &&
	 	 pos.z + MyScale_Z > posYou.z - YouScale_Z) &&
		(pos.x - MyScale_X < posYou.x + YouScale_X &&
		 pos.z - MyScale_Z < posYou.z + YouScale_Z)) {
		return true;
	}

	return false;
}

//��`�Ɠ_�̓����蔻��i�p�x���l���ɓ���Ă���j
//����͂܂��ҏW�ł������i�_�̂ق��̑傫���Ȃǂ��l���ɂ���邱�Ƃ��ł������j
bool ENEMY::Collision_Cube2(VECTOR MyCol, VECTOR MyRot, VECTOR YouCol, float MyScale_X, float MyScale_Z, float YouScale_X, float YouScale_Z) {
	// �e���W���擾����
	VECTOR pos = MyCol;
	VECTOR rot = MyRot;
	VECTOR posYou = YouCol;


	// ��`�̒��S�����_�Ƃ������΍��W���쐬����
	VECTOR relative_position = VGet(posYou.x - pos.x, 0.0f, posYou.z - pos.z);

	// ���΍��W�ɑ΂��ċ�`�̉�]��ł������t�s����|����
	VECTOR transform_pos = VGet(
		cosf(rot.y) * relative_position.x + sinf(rot.y) * relative_position.z,
		0.0f,
		-sinf(rot.y) * relative_position.x + cosf(rot.y) * relative_position.z
	);

	// ��`�Ɠ_�̓����蔻����s��
	if (-MyScale_X / 2.0f <= transform_pos.x && MyScale_X / 2.0f >= transform_pos.x &&
		-MyScale_Z / 2.0f <= transform_pos.z && MyScale_Z / 2.0f >= transform_pos.z)
	{
		return true;
	}

	return false;
}


void ENEMY::Enemy_Attack(PLAYER* player, int num) {

	//��x�����擾
	if (Att[num].s_GetOneRot == false) {
		//�ړ��ꏊ�̊m�F
		Att[num].s_RotSin = sin(c_Rotation[num].y);
		Att[num].s_RotCos = cos(c_Rotation[num].y);
		Att[num].s_Posx = c_ObjPos[num].x;
		Att[num].s_Posz = c_ObjPos[num].z;
		Att[num].s_GetOneRot = true;
	}

	//�G�l�~�[�̑O�������擾
	float x = Att[num].s_Posx + (Att[num].s_RotSin * Att[num].s_Rang);
	float z = Att[num].s_Posz + (Att[num].s_RotCos * Att[num].s_Rang);

	//�U�����O���ɐi��
	Att[num].s_Rang += Att[num].s_AttackSpeed;

	//����
	DrawLine3D(VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)), 0x880000);

	//�E�c
	DrawLine3D(VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)), 0x880000);

	//���c
	DrawLine3D(VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)), 0x880000);

	//�㉡
	DrawLine3D(VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)), 0x880000);

	//�E��� x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_Position.y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)
	//����� x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_Position.y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)
	//�E���� x + (Att[num].s_RotCos * Att[num].s_width), c_Position.y, z - (Att[num].s_RotSin * Att[num].s_width)
	//������ x - (Att[num].s_RotCos * Att[num].s_width), c_Position.y, z + (Att[num].s_RotSin * Att[num].s_width)

	//�U������
	if (Att[num].s_Rang >= Att[num].s_RangMax) {
		Att[num].s_AttackStartKey = false;
		Att[num].s_GetOneRot = false;
		Att[num].s_Rang = 0.0f;
	}

	//�G�l�~�[�̓����蔻��
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;
		if (Enemy_AttackCol(VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
			VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
			VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)),
			VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)),
			c_ObjPos[i],num, c_Rotation[num].y) == true) {
			/*SetEnemyMoveFalseKey(i);*/SetEnemyParaKey(i);		//SetEnemyMoveFalseKey�̓X�e�[�W�̔���Ɏg���̂ŕς��܂����i���̈ȊO�͑O�̂��̂Ɠ����ł��j
		}
	}

	//�v���C���[�̓����蔻��
	if (Enemy_AttackCol(VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)),
		player->c_Position, num, c_Rotation[num].y) == true) {
		player->SetPlayerParalyze();
		
	}
}

bool ENEMY::Enemy_AttackCol(VECTOR AttPosRU, VECTOR AttPosLU, VECTOR AttPosRD, VECTOR AttPosLD,VECTOR YouPos, int num, float ang) {
	//���S�_����o��
	float halfx = (AttPosRU.x + AttPosRD.x + AttPosLU.x + AttPosLD.x) / 4;
	float halfz = (AttPosRU.z + AttPosRD.z + AttPosLU.z + AttPosLD.z) / 4;

	//���S�_�ƓG�̍��W�̋���
	float distx = YouPos.x - halfx;
	float distz = YouPos.z - halfz;

	//�����蔻��̌v�Z
	float posz = cos(ang) * distz + sin(ang) * distx;
	float posx = -sin(ang) * distz + cos(ang) * distx;


	//��`�Ɠ_�̓����蔻����s��
	if (-Att[num].s_width /*/ 2.0f*/ <= posx && Att[num].s_width /*/ 2.0f*/ >= posx &&
		-Att[num].s_heigt / 2.0f <= posz && Att[num].s_heigt / 2.0f >= posz) {
		return true;
	}

	return false;
}

bool ENEMY::CheckPara(int num) {
	return Damage[num].s_paralyzeKey;
}//���ׂ����G�l�~�[�����т�Ă��邩�ǂ����̔���


void ENEMY::Enemy_Paralyze(int num) {
	
	if (Damage[num].s_ParaTime++ == Damage[num].s_MaxTimeParalyze) {
		Damage[num].s_paralyzeKey = false;
		Damage[num].s_ParaTime = 0;
	}
}


int ENEMY::EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos) {
	int Win_Count = 0;

	for (int i = 0; i < ENEMY_MAX; i++) {
		c_EnemyWin[i] = false;
		float ex = LightPos.x - c_ObjPos[i].x;
		float ez = LightPos.z - c_ObjPos[i].z;
		if (c_AliveEnemy[i] == false)continue;//���݂��Ă��Ȃ�
		float er = (ex * ex) + (ez * ez);
		float elr = ( 70.0f);
		float elr2 = (elr * elr);
		//DrawSphere3D(c_ObjPos[i], 10.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
		// enemy��light�̓����蔻��
		if (er <= elr2) {
			c_EnemyWin[i] = true;
			Win_Count++;
			if (LightFlg == false) {
				if (i == 0) {
					ENEMY_WIN = 1;
				}
				else if (i == 1) {
					ENEMY_WIN = 2;
				}
				else if (i == 2) {
					ENEMY_WIN = 3;
				}
			}
		}

	}

	return Win_Count;
	

	/*SetFontSize(20);
	DrawFormatString(10, 100, 0x888888, "x:%f", Player.x);
	DrawFormatString(10, 130, 0x888888, "y:%f", Player.y);
	DrawFormatString(10, 160, 0x888888, "z:%f", Player.z);
	DrawFormatString(10, 190, 0x888888, "x:%f", Enemy.x);
	DrawFormatString(10, 220, 0x888888, "y:%f", Enemy.y);
	DrawFormatString(10, 250, 0x888888, "z:%f", Enemy.z);*/

}



void ENEMY::Ga_Attack(int num, PLAYER* player) {
	if (Att[num].s_AttackStartKey == true) {
		
		return; //�U�������ƋA��
	}
	if (Ga_Interval[num] > 0) {//�U���̃C���^�[�o��
		Ga_Interval[num]--;
		return;
	}
	if (c_StmCount[num] < c_AttackStm + 1 || Damage[num].s_paralyzeKey == true) {
		
		return;
	}//�X�^�~�i��15�ȉ��܂��́A���т�Ă�����U���ł��Ȃ��̂ŋA��

	VECTOR Check_Future_Pos = c_ObjPos[num];//�O���ɍ��W���������߁B�����X�U
	Check_Future_Pos.x += 96.0f * sinf(c_Rotation[num].y)/* - c_MoveVector.z * sin(rad)*/;
	Check_Future_Pos.z += 96.0f * cosf(c_Rotation[num].y) /*+ c_MoveVector.z * cos(rad)*/;
	//DrawSphere3D(Check_Future_Pos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	if (((g_KeyFlg & PAD_INPUT_5) != 0)) {
		Att[num].s_AttackStartKey = true;//���̂Ƃ���R1�������ƓG���U��
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}

	//���̃G�l�~�[�������̎���ɂ��邩�ǂ�������
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;

		//�����̑O�����݂�
		if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], c_Rotation[i], 30, 96, 105, 55) == true) {

			Ga_Interval[num] = Ga_Debug_Interval;//�U���̃C���^�[�o��60�t���[��
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy1_attack_sound) == 0) {
					PlaySoundMem(enemy1_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
		//�����̌��������݂�
		if (Collision_Cube(c_ObjPos[num], c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH * 2, ENEMY_HEIGHT * 2, 55, 55) == true) {
			float PosX = c_ObjPos[i].x - c_ObjPos[num].x;
			float PosZ = c_ObjPos[i].z - c_ObjPos[num].z;
			float rad = atan2f(c_ObjPos[i].z - c_ObjPos[num].z, c_ObjPos[i].x - c_ObjPos[num].x) * 180 / M_PI;
			//�����Ă���p�x�̒���
			if ((rad >= -180 && rad < -135) || (rad >= 135)) {//��
				c_Rotation[num].y = 270.0f;
			}
			else if (rad >= -135 && rad < -45) {//��
				c_Rotation[num].y = 180.0f;
			}
			else if (rad >= -45 && rad < 45) {//�E
				c_Rotation[num].y = 90.0f;
			}
			else if (rad >= 45 && rad < 135) {//��
				c_Rotation[num].y = 0.0f;
			}

			Ga_Interval[num] = Ga_Debug_Interval;//�U���̃C���^�[�o��60�t���[��
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy1_attack_sound) == 0) {
					PlaySoundMem(enemy1_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
	}
	//�v���C���[�������̎���ɂ��邩�ǂ�������
	//�����̑O�����݂�
	if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], player->c_Position, 30, 150, 105, 55) == true) {
		Ga_Interval[num] = Ga_Debug_Interval;//�U���̃C���^�[�o��60�t���[
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy1_attack_sound) == 0) {
				PlaySoundMem(enemy1_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
	//�����̌��������݂�
	if (Collision_Cube(c_ObjPos[num], c_Rotation[num], player->c_Position, ENEMY_WIDTH * 2, ENEMY_HEIGHT * 2, 55, 55) == true) {
		float PosX = player->c_Position.x - c_ObjPos[num].x;
		float PosZ = player->c_Position.z - c_ObjPos[num].z;
		float rad = atan2f(player->c_Position.z - c_ObjPos[num].z, player->c_Position.x - c_ObjPos[num].x) * 180 / M_PI;
		//�����Ă���p�x�̒���
		if ((rad >= -180 && rad < -135) || (rad >= 135)) {//��
			c_Rotation[num].y = 270.0f;
		}
		else if (rad >= -135 && rad < -45) {//��
			c_Rotation[num].y = 180.0f;
		}
		else if (rad >= -45 && rad < 45) {//�E
			c_Rotation[num].y = 90.0f;
		}
		else if (rad >= 45 && rad < 135) {//��
			c_Rotation[num].y = 0.0f;
		}

		Ga_Interval[num] = Ga_Debug_Interval;//�U���̃C���^�[�o��60�t���[
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy1_attack_sound) == 0) {
				PlaySoundMem(enemy1_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
}

void ENEMY::Ga_Move(int num, PLAYER* player) {
	if (WaitTime == 0 || time_All >= 480) {//�X�|�b�g���C�g�̓������~�܂��Ă���܂��́A8�b�ȏ�ɂȂ��Ă���
		if (c_StmCount[num] >= (int)(c_StmMax * 0.5)) {//�X�^�~�i��50%�ȏ�Ȃ珟�������ɍs�����Ɠ���
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < 10) {//�X�^�~�i��10�ȉ��Ȃ�񕜂ɐ�O
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}
	else {//�X�^�[�g����0~8�b�܂ł̊Ԃ͕��ʂɓ���
		if (c_StmCount[num] >= c_StmMax-10) {//�X�^�~�i���ő�|10�ȏ�Ȃ�قڑS�񕜂Ɣ��f���Ĉړ��Ɉڂ�
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < (int)(c_StmMax * 0.3)) {//�X�^�~�i��30%�ȉ��Ȃ�񕜂ɐ�O
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}
	
}
void ENEMY::A_Move(int num) {
	if (WaitTime == 0 || time_All >= 480) {//�X�|�b�g���C�g�̓������~�܂��Ă���܂��́A8�b�ȏ�ɂȂ��Ă���
		if (c_StmCount[num] >= (int)(c_StmMax * 0.4)) {//�X�^�~�i��40%�ȏ�Ȃ珟�������ɍs�����Ɠ���
			//if (check_1 == 0 && check_2 == 0) {//�G�Ɩ��������Ƃ��͈͂ɂ��Ȃ��ꍇ�s���Ɉڂ�
				c_EnemyState[num] = ENEMY_MOVE;
			//}
		}
		else if (c_StmCount[num] < 10) {//�X�^�~�i��10�ȉ��Ȃ�񕜂ɐ�O
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}
	else {//�X�^�[�g����0~8�b�܂ł̊Ԃ͕��ʂɓ���
		if (c_StmCount[num] >= (int)(c_StmMax * 0.8)) {//�X�^�~�i��80%�ȏ�Ȃ�قڑS�񕜂Ɣ��f���Ĉړ��Ɉڂ�
			//if (check_1 == 0 && check_2 == 0) {//�G�Ɩ��������Ƃ��͈͂ɂ��Ȃ��ꍇ�s���Ɉڂ�
			//	
			//}
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < (int)(c_StmMax * 0.3)) {//�X�^�~�i��30%�ȉ��Ȃ�񕜂ɐ�O
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}

}
void ENEMY::A_Attack(int num, PLAYER* player) {
	if (Att[num].s_AttackStartKey == true) {
		
		return; //�U�������ƋA��
	}
	if (Ga_Interval[num] > 0) {//�U���̃C���^�[�o��
		Ga_Interval[num]--;
		return;
	}
	if (c_StmCount[num] < c_AttackStm + 1 || Damage[num].s_paralyzeKey == true) {
		
		return; 
	}//�X�^�~�i��15�ȉ����ƋA��

	
	if (((g_KeyFlg & PAD_INPUT_5) != 0)) {
		Att[num].s_AttackStartKey = true;//���̂Ƃ���R1�������ƓG���U��
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}

	//���̃G�l�~�[�������̎���ɂ��邩�ǂ�������
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;

		
		//�����̌��������݂�
		if (Collision_Cube(c_ObjPos[num], c_Rotation[num], c_ObjPos[i], 200,200, 55, 55) == true) {
			float PosX = c_ObjPos[i].x - c_ObjPos[num].x;
			float PosZ = c_ObjPos[i].z - c_ObjPos[num].z;
			float rad = atan2f(c_ObjPos[i].z - c_ObjPos[num].z, c_ObjPos[i].x - c_ObjPos[num].x) * 180 / M_PI;
			//�����Ă���p�x�̒���
			if ((rad >= -180 && rad < -135) || (rad >= 135)) {//��
				c_Rotation[num].y = 270.0f;
			}
			else if (rad >= -135 && rad < -45) {//��
				c_Rotation[num].y = 180.0f;
			}
			else if (rad >= -45 && rad < 45) {//�E
				c_Rotation[num].y = 90.0f;
			}
			else if (rad >= 45 && rad < 135) {//��
				c_Rotation[num].y = 0.0f;
			}

			Ga_Interval[num] = A_Debug_Interval;//�U���̃C���^�[�o��60�t���[��
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy3_attack_sound) == 0) {
					PlaySoundMem(enemy3_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
	}
	//�v���C���[�������̎���ɂ��邩�ǂ�������
	//�����̌��������݂�
	if (Collision_Cube(c_ObjPos[num], c_Rotation[num], player->c_Position, 200,200, 55, 55) == true) {
		float PosX = player->c_Position.x - c_ObjPos[num].x;
		float PosZ = player->c_Position.z - c_ObjPos[num].z;
		float rad = atan2f(player->c_Position.z - c_ObjPos[num].z, player->c_Position.x - c_ObjPos[num].x) * 180 / M_PI;
		//�����Ă���p�x�̒���
		if ((rad >= -180 && rad < -135) || (rad >= 135)) {//��
			c_Rotation[num].y = 270.0f;
		}
		else if (rad >= -135 && rad < -45) {//��
			c_Rotation[num].y = 180.0f;
		}
		else if (rad >= -45 && rad < 45) {//�E
			c_Rotation[num].y = 90.0f;
		}
		else if (rad >= 45 && rad < 135) {//��
			c_Rotation[num].y = 0.0f;
		}

		Ga_Interval[num] = A_Debug_Interval;//�U���̃C���^�[�o��60�t���[
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy3_attack_sound) == 0) {
				PlaySoundMem(enemy3_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
}

void ENEMY::San_Attack(int num, PLAYER* player) {
	if (Att[num].s_AttackStartKey == true) {
		

		return; //�U�������ƋA��
	}
	if (Ga_Interval[num] > 0) {//�U���̃C���^�[�o��
		Ga_Interval[num]--;
		return;
	}
	if (c_StmCount[num] < c_AttackStm + 1 || Damage[num].s_paralyzeKey == true) {
		
		return;//�X�^�~�i��15�ȉ����ƋA��
	}
	VECTOR Check_Future_Pos = c_ObjPos[num];//�O���ɍ��W���������߁B����123
	Check_Future_Pos.x += 123.0f * sinf(c_Rotation[num].y)/* - c_MoveVector.z * sin(rad)*/;
	Check_Future_Pos.z += 123.0f * cosf(c_Rotation[num].y) /*+ c_MoveVector.z * cos(rad)*/;
	//DrawSphere3D(Check_Future_Pos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	if (((g_KeyFlg & PAD_INPUT_5) != 0)) {
		Att[num].s_AttackStartKey = true;//���̂Ƃ���R1�������ƓG���U��
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}

	//���̃G�l�~�[�������̎���ɂ��邩�ǂ�������
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;

		//�����̑O�����݂�
		if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], c_Rotation[i], 30, 96, 105, 55) == true) {

			Ga_Interval[num] = San_Debug_Interval;//�U���̃C���^�[�o��10�t���[��
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy2_attack_sound) == 0) {
					PlaySoundMem(enemy2_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
		//�����̌��������݂�
		if (Collision_Cube(c_ObjPos[num], c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH * 2, ENEMY_HEIGHT * 2, 55, 55) == true) {
			float PosX = c_ObjPos[i].x - c_ObjPos[num].x;
			float PosZ = c_ObjPos[i].z - c_ObjPos[num].z;
			float rad = atan2f(c_ObjPos[i].z - c_ObjPos[num].z, c_ObjPos[i].x - c_ObjPos[num].x) * 180 / M_PI;
			//�����Ă���p�x�̒���
			if ((rad >= -180 && rad < -135) || (rad >= 135)) {//��
				c_Rotation[num].y = 270.0f;
			}
			else if (rad >= -135 && rad < -45) {//��
				c_Rotation[num].y = 180.0f;
			}
			else if (rad >= -45 && rad < 45) {//�E
				c_Rotation[num].y = 90.0f;
			}
			else if (rad >= 45 && rad < 135) {//��
				c_Rotation[num].y = 0.0f;
			}

			Ga_Interval[num] = San_Debug_Interval;//�U���̃C���^�[�o��10�t���[��
			if (Enemy_Sound_flg == false) {
				if (CheckSoundMem(enemy2_attack_sound) == 0) {
					PlaySoundMem(enemy2_attack_sound, DX_PLAYTYPE_BACK);
				}
			}
			Att[num].s_AttackStartKey = true;//
			c_StmCount[num] = AttackStaminaCount(num);
			return;

		}
	}
	//�v���C���[�������̎���ɂ��邩�ǂ�������
	//�����̑O�����݂�
	if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], player->c_Position, 30, 150, 105, 55) == true) {
		Ga_Interval[num] = San_Debug_Interval;//�U���̃C���^�[�o��10�t���[
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy2_attack_sound) == 0) {
				PlaySoundMem(enemy2_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
	//�����̌��������݂�
	if (Collision_Cube(c_ObjPos[num], c_Rotation[num], player->c_Position, ENEMY_WIDTH * 2, ENEMY_HEIGHT * 2, 55, 55) == true) {
		float PosX = player->c_Position.x - c_ObjPos[num].x;
		float PosZ = player->c_Position.z - c_ObjPos[num].z;
		float rad = atan2f(player->c_Position.z - c_ObjPos[num].z, player->c_Position.x - c_ObjPos[num].x) * 180 / M_PI;
		//�����Ă���p�x�̒���
		if ((rad >= -180 && rad < -135) || (rad >= 135)) {//��
			c_Rotation[num].y = 270.0f;
		}
		else if (rad >= -135 && rad < -45) {//��
			c_Rotation[num].y = 180.0f;
		}
		else if (rad >= -45 && rad < 45) {//�E
			c_Rotation[num].y = 90.0f;
		}
		else if (rad >= 45 && rad < 135) {//��
			c_Rotation[num].y = 0.0f;
		}

		Ga_Interval[num] = San_Debug_Interval;//�U���̃C���^�[�o��10�t���[
		if (Enemy_Sound_flg == false) {
			if (CheckSoundMem(enemy2_attack_sound) == 0) {
				PlaySoundMem(enemy2_attack_sound, DX_PLAYTYPE_BACK);
			}
		}
		Att[num].s_AttackStartKey = true;//
		c_StmCount[num] = AttackStaminaCount(num);
		return;
	}
}

void ENEMY::San_Move(int num) {
	
	if (WaitTime == 0 || time_All >= 540) {//�X�|�b�g���C�g�̓������~�܂��Ă���܂��́A9�b�ȏ�ɂȂ��Ă���
		if (c_StmCount[num] >= (int)(c_StmMax*0.15)) {//�X�^�~�i��15%�ȏ�Ȃ珟�������ɍs�����Ɠ���
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < 10) {//�X�^�~�i��10�ȉ��Ȃ�񕜂ɐ�O
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}
	else {//�X�^�[�g����0~8�b�܂ł̊Ԃ͕��ʂɓ���
		if (c_StmCount[num] >= c_StmMax-10) {//�X�^�~�i���ő�|10�ȏ�Ȃ�قڑS�񕜂Ɣ��f���Ĉړ��Ɉڂ�
			c_EnemyState[num] = ENEMY_MOVE;
		}
		else if (c_StmCount[num] < 10) {//�X�^�~�i��10�ȉ��Ȃ�񕜂ɐ�O
			c_EnemyState[num] = ENEMY_IDLE;
		}
	}

}

void ENEMY::Bot_Normal(int num, PLAYER* player) {

	if (c_StmCount[num] >= c_StmMax - 10) {//�X�^�~�i���}�b�N�X�ɂȂ�����ړ�����B
		c_EnemyState[num] = ENEMY_MOVE;
	}
	if (c_StmCount[num] == 10) {//�X�^�~�i�O�ɂȂ�����A�C�h���ɂȂ��ĉ񕜂���B
		c_EnemyState[num] = ENEMY_IDLE;
	}
}

