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
	////�I�u�W�F�N�g�̍��W������
	//c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	//c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	//c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// �R�c���f���̓ǂݍ���
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (i == 0) {
			c_EnemyModel[i] = MV1LoadModel("Model/EnMe.mv1");
		}
		else {
			c_EnemyModel[i] = MV1LoadModel("Model/obj.mv1");
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
	c_ObjPos[0] = VGet(500.0f, 80.0f, 500.0f);
	c_ObjPos[1] = VGet(300.0f, 100.0f, 50.0f);
	c_ObjPos[2] = VGet(50.0f, 100.0f, 170.0f);

	// �R�c���f���̓ǂݍ���
	for (int i = 0; i < ENEMY_MAX; i++) {
		c_AddPosEnemy[i] = { 0.5f,0.5f,0.5f };
		c_MoveKey[i] = true;
		c_StmCount[i] = 300;	//�G�l�~�[�̗̑͂̍ő�
		c_Rotation[i] = VGet(0.0f, 0.0f /*(c_PlayerAng * (M_PI / 180))*/, 0.0f);//�G�l�~�[�̉�]
		c_Enemy_MoveAng[i] = 0;//�G�l�~�[�̊p�x
		c_EnemySpeed[i] = 0.0f;//�G�l�~�[�̃X�s�[�h
		c_EnemyState[i] = ENEMY_IDLE;//�G�l�~�[�̏������
		MV1SetScale(c_EnemyModel[i], c_AddPosEnemy[i]);//�G�l�~�[�̃X�P�[��������Ă���

		c_EnemyAddVect[i] = VGet(0.0f, 0.0f, 0.0f);//�ǂ��z�������̂Ƃ��ɉ��Z����x�N�g����ۑ�
		c_EnemyFrameCount[i] = 0;//�ǂ��z�������̂Ƃ��Ƀt���𐔂���
	}

	c_SpotPos = VGet(100.0f, 0.0f, 800.0f);//�X�|�b�g���C�g�̍��W
	Coefficient = 1.0f;
	c_MoveFlag = FALSE;
	c_MoveVector = VGet(0.0f, 0.0f, 0.0f);
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
		if (i == 1)DrawSphere3D(Check_Future_Pos, 50.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		if (c_EnemyFrameCount[num] == 0) {



			
			//if(Collision_Cube())�@//�p�x���Q�Ƃ��Ă��Ȃ��̂ŕύX������
			if (Collision_Cube2(Check_Future_Pos, c_Rotation[num], c_ObjPos[i], 30, 150, 105, 55) == true) {

				float rad = c_Rotation[num].y + (M_PI / 2);
				c_EnemyAddVect[num].x = c_MoveVector.x * cos(rad) - c_MoveVector.z * sin(rad);
				c_EnemyAddVect[num].z = c_MoveVector.x * sin(rad) + c_MoveVector.z * cos(rad);

				c_MoveVector.x += c_EnemyAddVect[num].x;
				c_MoveVector.z += c_EnemyAddVect[num].z;

				c_EnemyFrameCount[num] = 1;

				//c_MoveVector.x += 5.0f;

				SetFontSize(20);
				DrawFormatString(1100, 600, 0xFFFFFF, "���邺\n");

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

	if (Damage[num].s_paralyzeKey == true) Enemy_Paralyze(num);//���т�Ă���Ȃ�J�E���g�ƈړ��t���O��off�ɂ���
	if (((g_KeyFlg & PAD_INPUT_5) != 0) && Att[num].s_AttackStartKey == false)Att[num].s_AttackStartKey = true;//���̂Ƃ���R1�������ƓG���U��
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
		VECTOR TempMoveVector;

		TempMoveVector.x = c_MoveVector.x * Coefficient * c_EnemySpeed[num];
		TempMoveVector.y = 0.0f;
		TempMoveVector.z = c_MoveVector.z * Coefficient * c_EnemySpeed[num];


		//������l����̊m�F
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (i == num)continue;
			if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
				if (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false) {//false�Ȃ瓮�����Ȃ�����
					VECTOR Reserve_Vect = TempMoveVector;//X���W��0�ɂ��Ă݂�

					float Reserve = Reserve_Vect.x;//X���W��0�ɂ��Ă݂�
					Reserve_Vect.x = 0.0f;//
					
					if (Coefficient!=1.0f) {
						if ((Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) && (Enemy_Push(i, c_ObjPos[i], TempMoveVector) == false)) {
							Reserve_Vect.x = Reserve;//
							Reserve = Reserve_Vect.z;//
							Reserve_Vect.z = 0.0f;//
							if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
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
		if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
			if (player->Player_Push(camera, c_ObjPos, TempMoveVector) == false) {//false�Ȃ瓮�����Ȃ�����
				VECTOR Reserve_Vect = TempMoveVector;//X���W��0�ɂ��Ă݂�

				float Reserve = Reserve_Vect.x;//X���W��0�ɂ��Ă݂�
				Reserve_Vect.x = 0.0f;//
				if (Coefficient != 1.0) {
					if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true && player->Player_Push(camera, c_ObjPos, Reserve_Vect) == false) {//false�Ȃ瓮�����Ȃ�����

						Reserve_Vect.x = Reserve;//
						Reserve = Reserve_Vect.z;//
						Reserve_Vect.z = 0.0f;//
						if (Collision_Cube(VAdd(c_ObjPos[num], Reserve_Vect), c_Rotation[num], player->c_Position, ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
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


//num�͉�����鑤
bool ENEMY::Enemy_Push(int num, VECTOR PlayerCol, VECTOR PushVec)
{
	//���т�Ă��邩�ǂ����B���т�Ă��Ȃ��Ȃ�false�ŋA��
	if (Damage[num].s_paralyzeKey == false) {
		return false;
	}

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
			if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector),c_Rotation[num], c_ObjPos[i], ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
				c_MoveFlag = false;
			}
		}
		if (Collision_Cube(VAdd(c_ObjPos[num], TempMoveVector), c_Rotation[num], PlayerCol, ENEMY_WIDTH, ENEMY_HEIGHT, 55, 55) == true) {
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
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)), 0x888888);

	//�E�c
	DrawLine3D(VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width)), 0x888888);

	//���c
	DrawLine3D(VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x - (Att[num].s_RotCos * Att[num].s_width), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width)), 0x888888);

	//�㉡
	DrawLine3D(VGet(x - (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z + (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)),
		VGet(x + (Att[num].s_RotCos * Att[num].s_width) + (Att[num].s_RotSin * Att[num].s_heigt), c_ObjPos[num].y, z - (Att[num].s_RotSin * Att[num].s_width) + (Att[num].s_RotCos * Att[num].s_heigt)), 0x888888);

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
			SetEnemyMoveFalseKey(i);
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
	float posx = cos(ang) * distx + sin(ang) * distz;
	float posz = -sin(ang) * distx + cos(ang) * distz;

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
	c_MoveFlag = false;

	if (Damage[num].s_ParaTime++ == Damage[num].s_MaxTimeParalyze) {
		Damage[num].s_paralyzeKey = false;
		Damage[num].s_ParaTime = 0;
	}
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