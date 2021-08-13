#define _USE_MATH_DEFINES

#include <DxLib.h>
#include <math.h>

#include "enemy.h"
#include "Light.h"
#include "Player.h"
#include "Camera.h"
#include "debug.h"

ENEMY::ENEMY()
{
	//�I�u�W�F�N�g�̍��W������
	c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// �R�c���f���̓ǂݍ���
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_EnemyModel[i] = MV1LoadModel("Model/EnMe.mv1");
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		c_StmCount[i] = 300;	//�G�l�~�[�̗̑͂̍ő�
		c_Rotation[i] = VGet(0.0f, 0.0f /*(c_PlayerAng * (M_PI / 180))*/, 0.0f);//�G�l�~�[�̉�]
		c_EnemyAng[i] = 0;//�G�l�~�[�̊p�x
		c_Enemy_MoveAng[i] = 0;//�G�l�~�[�̊p�x
		c_EnemySpeed[i] = 0.0f;//�G�l�~�[�̃X�s�[�h
		c_EnemyState[i] = ENEMY_IDLE;//�G�l�~�[�̏������
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//�G�l�~�[�̃X�P�[��������Ă���
	}

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//�X�|�b�g���C�g�̍��W
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
}

ENEMY::~ENEMY()
{
}

void ENEMY::Enemy_Creat() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		MV1SetPosition(c_EnemyModel[i], c_ObjPos[i]);//�G�l�~�[�̈ړ���ʒu������Ă�
		MV1SetRotationXYZ(c_EnemyModel[i], c_Rotation[i]);//�G�l�~�[�̊p�x������Ă���
		MV1DrawModel(c_EnemyModel[i]);				 //�G�l�~�[�̃��f���`��
	}
	//�I�u�W�F�N�g�`��
	//DrawSphere3D(c_ObjPos[0], 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[1], VAdd(c_ObjPos[1], VECTOR{ 50,50,50 }), GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
	//DrawCube3D(c_ObjPos[2], VAdd(c_ObjPos[2], VECTOR{ 50,50,50 }), GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

void ENEMY::debug() {
	printfDx("%d\n", GetEnemyMoveKey(2));
}

void ENEMY::Enemy_State(int num, PLAYER* player, CAMERA* camera) {
	
	

	
	switch (c_EnemyState[num])
	{
	case ENEMY_IDLE:
		c_StmCount[num] = StaminaCount(false,num);		//�X�^�~�i��
		if (c_StmCount[num] >= 300) {//�X�^�~�i���}�b�N�X�ɂȂ�����ړ�����B
			c_EnemyState[num] = ENEMY_MOVE;
		}
		break;
	case ENEMY_MOVE:
		Enemy_Move(num, player, camera);
		if (c_StmCount[num] == 0) {//�X�^�~�i�O�ɂȂ�����A�C�h���ɂȂ��ĉ񕜂���B
			c_EnemyState[num] = ENEMY_IDLE;
		}
		break;
	case ENEMY_ATTACK:
		break;
	}

	SetFontSize(20);
	DrawFormatString(1100, 620 + 20 * num, 0xFFFFFF, "%d�̓G�̗� %d\n", num, c_StmCount[num]);

}

void ENEMY::Enemy_Move(int num, PLAYER* player, CAMERA* camera)
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
		if (c_MoveKey[num] == true && c_StmCount[num] > 0)c_MoveVector.x = c_movespeed;
		p_Enemy_MoveAng = 90;//�E

	}

	if (c_SpotPos.x + c_SpotRadius < c_ObjPos[num].x) {
		c_MoveFlag = true;
		if (c_MoveKey[num] == true && c_StmCount[num] > 0)c_MoveVector.x = -c_movespeed;
		p_Enemy_MoveAng = 270;//��

	}

	if (c_SpotPos.z - c_SpotRadius > c_ObjPos[num].z) {
		c_MoveFlag = true;
		if (c_MoveKey[num] == true && c_StmCount[num] > 0)c_MoveVector.z = c_movespeed;
		p_Enemy_MoveAng = 0;//��

	}

	if (c_SpotPos.z + c_SpotRadius < c_ObjPos[num].z) {
		c_MoveFlag = true;
		if (c_MoveKey[num] == true && c_StmCount[num] > 0)c_MoveVector.z = -c_movespeed;
		p_Enemy_MoveAng = 180;//��
	}

	//�G���ǂ��z������
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == num)continue;
	}

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
		VECTOR TempMoveVector;

		TempMoveVector.x = c_MoveVector.x * Coefficient * c_EnemySpeed[num];
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z * Coefficient * c_EnemySpeed[num];


		//������l����̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_ObjPos[i], 55, 55) == true) {
				if (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false) {//false�Ȃ瓮�����Ȃ�����
					VECTOR Reserve_Vect = TempMoveVector;//X���W��0�ɂ��Ă݂�

					float Reserve = Reserve_Vect.x;//X���W��0�ɂ��Ă݂�
					Reserve_Vect.x = 0.0f;//
					
					if (Coefficient!=1.0f) {
						if ((Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_ObjPos[i], 55, 55) == true) && (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false)) {
							Reserve_Vect.x = Reserve;//
							Reserve = Reserve_Vect.z;//
							Reserve_Vect.z = 0.0f;//
							if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_ObjPos[i], 55, 55) == true) {
								if (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false) {//false�Ȃ瓮�����Ȃ�����
									c_MoveFlag = false;
								}
							}
						}
					}
					else {
						c_MoveFlag = false;
					}
					
					

					if (c_MoveFlag) {//TRUE�Ȃ�ړ����ύX
						TempMoveVector = Reserve_Vect;
					}
					
				}
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), player->c_Position, 55, 55) == true) {
			if (player->Player_Push(camera, c_ObjPos, TempMoveVector) == false) {//false�Ȃ瓮�����Ȃ�����
				VECTOR Reserve_Vect = TempMoveVector;//X���W��0�ɂ��Ă݂�

				float Reserve = Reserve_Vect.x;//X���W��0�ɂ��Ă݂�
				Reserve_Vect.x = 0.0f;//
				if (Coefficient != 1.0) {
					if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), player->c_Position, 55, 55) == true && player->Player_Push(camera, c_ObjPos, Reserve_Vect) == false) {//false�Ȃ瓮�����Ȃ�����

						Reserve_Vect.x = Reserve;//
						Reserve = Reserve_Vect.z;//
						Reserve_Vect.z = 0.0f;//
						if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), player->c_Position, 55, 55) == true) {
							if (player->Player_Push(camera, c_ObjPos, Reserve_Vect) == false) {//false�Ȃ瓮�����Ȃ�����
								c_MoveFlag = false;
							}
						}
					}
				}
				else {
					c_MoveFlag = false;
				}

				if (c_MoveFlag) {//TRUE�Ȃ�ړ����ύX
					TempMoveVector = Reserve_Vect;
				}
			}
		}

		if (c_MoveFlag == true)
		{
			c_ObjPos[num] = VAdd(c_ObjPos[num], TempMoveVector);
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

bool ENEMY::Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec)
{
	//���т�Ă��邩�ǂ���
	/*if()*/

	//�ړ����Ă邩�ǂ���
	c_MoveFlag = FALSE;
	c_MoveVector = PushVec;

	Coefficient = 1.0f;

	c_SpotPos = LightPos;

	c_MoveFlag = true;




	//�ړ��t���O�������Ă���ړ�
	if (c_MoveFlag == true)
	{
		//�ړ��ꏊ�̊m�F
		VECTOR TempMoveVector;

		TempMoveVector.x = c_MoveVector.x * Coefficient;
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z * Coefficient;


		//������l����̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_ObjPos[i], 55, 55) == true) {
				c_MoveFlag = false;
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), PlayerCol, 55, 55) == true) {
			c_MoveFlag = false;
		}

		if (c_MoveFlag == true)
		{
			c_ObjPos[num] = VAdd(c_ObjPos[num], TempMoveVector);
		}
	}
	//if (Collision_Player) {
	//	Collision_Draw();//�f�o�b�N�p
	//}
	return c_MoveFlag;
}


// �v���C���[�ƃI�u�W�F�N�g�̂����蔻��
bool Collision_Cube(VECTOR MyCol, VECTOR YouCol, float MyScale, float YouScale) {
	// �e���W���擾����
	VECTOR pos = MyCol;
	VECTOR posYou = YouCol;

	//����������true
	if ((pos.x + MyScale > posYou.x - YouScale &&
		pos.z + MyScale > posYou.z - YouScale) &&
		(pos.x - MyScale < posYou.x + YouScale &&
			pos.z - MyScale < posYou.z + YouScale)) {
		return true;
	}

	return false;
}

bool ENEMY::EnemyCheckHit(VECTOR c_ObjPos[ENEMY_MAX], VECTOR LightPos) {
	VECTOR Light = LightPos;
	LightPos.y = 0.0f;
	for (int i = 0; i < ENEMY_MAX; i++) {

		float ex = Light.x - c_ObjPos[i].x;
		float ez = Light.z - c_ObjPos[i].z;

		float er = (ex * ex) + (ez * ez);
		float elr = (80.0f+70.0f);
		float elr2 = (elr * elr);

		// enemy��light�̓����蔻��( TRUE:�������Ă��� FALSE:�������Ă��Ȃ� )
		if (er <= elr2&&LightFlg==false) {
			
			return true;
		}

	}
	return false;

	/*SetFontSize(20);
	DrawFormatString(10, 100, 0x888888, "x:%f", Player.x);
	DrawFormatString(10, 130, 0x888888, "y:%f", Player.y);
	DrawFormatString(10, 160, 0x888888, "z:%f", Player.z);
	DrawFormatString(10, 190, 0x888888, "x:%f", Enemy.x);
	DrawFormatString(10, 220, 0x888888, "y:%f", Enemy.y);
	DrawFormatString(10, 250, 0x888888, "z:%f", Enemy.z);*/

}