#include "DxLib.h"
#include <math.h>
#include "Debug.h"
#include "Light.h"
#include "GameSound.h"
#include <cmath>

#define DRAW_NUM	(3)
#define SPACE		(512.0f)
#define PI 3.141592654f

int PixelShaderHandle;
int VertexShaderHandle;
float LightRotateAngle;
float LightRotateAngle2;
int SpotLightHandle;
int PointLightHandle;
int DirLightHandle;
float DrawX = 0.0f;
float DrawZ = 0.0f;
float DrawX2 = 0.0f;
float DrawZ2 = 0.0f;

int time;
int time2;

int count;       //�ړ����郉�C�g�̗\��ʒu
int cntFlg = 4;  //���݂̃��C�g�̈ʒu
int rc = 4;      //�ߋ��̃��C�g�̈ʒu
float distance = 600.0f;
float distance2 = 450.0f;

int WaitTime = 0;

bool LightFlg;

bool g_DispTime;	//�X�|�b�g���C�g�������Ă���Ƃ��������Ԃ�\���@true�F�\���@false:��\��

VECTOR dis[6];
VECTOR LightPos;
VECTOR LightPos2;

//�T�h���f�X���s�����ǂ���true�Ȃ�s���Ă���B
bool Sadondes_flg = false;

typedef struct {
	float x, z;    //���W
	float T;       //����
	float Range;   //���a
}Point_t;

void Light_SetUp() {

	//���_�V�F�[�_�[��ǂݍ���
	VertexShaderHandle = LoadVertexShader("Shader/NormalMesh_SpotPointLightVS.vso");

	//�s�N�Z���V�F�[�_�[��ǂݍ���
	PixelShaderHandle = LoadPixelShader("Shader/NormalMesh_SpotPointLightPS.pso");

	// �g�p���钸�_�V�F�[�_�[���Z�b�g
	SetUseVertexShader(VertexShaderHandle);

	// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
	SetUsePixelShader(PixelShaderHandle);

	// �W�����C�g�𖳌��ɂ���
	SetLightEnable(FALSE);

	//���C�g�̏�����1�s�N�Z�����Ƃɍs���i�������d���Ȃ�j
	SetUsePixelLighting(TRUE);

	// �X�|�b�g���C�g���쐬����
	SpotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.375f, 0.75f, 2000.0f, 0.0f, 0.007f, 0.0f);

	// �X�|�b�g���C�g�̃A���r�G���g�J���[�����F�ɂ���
	SetLightAmbColorHandle(SpotLightHandle, GetColorF(15.0f, 15.0f, 0.0f, 0.0f));

	// �X�|�b�g���C�g�̃f�B�t���[�Y�J���[�����F�ɂ���
	SetLightDifColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	// �|�C���g���C�g���쐬����
	PointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 7000.0f, 1.016523f, 0.0f, 0.000015f);

	// �|�C���g���C�g�̃A���r�G���g�J���[�𖳌��ɂ���
	SetLightAmbColorHandle(PointLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	// �|�C���g���C�g�̃f�B�t���[�Y�J���[�������F�ɂ���
	SetLightDifColorHandle(PointLightHandle, GetColorF(10.0f, 10.0f, 10.0f, 0.0f));
}

void Light_init() {
	// Direct3D9Ex ���g�p����
	SetUseDirect3DVersion(DX_DIRECT3D_9EX);

	// ���C�g�̈ʒu����]����l��������
	//LightRotateAngle = 0.0f;

	//// �W�����C�g�𖳌��ɂ���
	//SetLightEnable(FALSE);

	////���C�g�̏�����1�s�N�Z�����Ƃɍs���i�������d���Ȃ�j
	//SetUsePixelLighting(TRUE);

	//// �X�|�b�g���C�g���쐬����
	//SpotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.18f, 0.15f, 1000.0f, 0.4f, 0.001662f, 0.000001f);

	//// �X�|�b�g���C�g�̃A���r�G���g�J���[�����F�ɂ���
	//SetLightAmbColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	//// �X�|�b�g���C�g�̃f�B�t���[�Y�J���[�����F�ɂ���
	//SetLightDifColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	//// �|�C���g���C�g���쐬����
	//PointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 7000.0f, 1.016523f, 0.000100f, 0.000010f);

	//// �|�C���g���C�g�̃A���r�G���g�J���[�𖳌��ɂ���
	//SetLightAmbColorHandle(PointLightHandle, GetColorF(10.0f, 10.0f, 10.0f, 0.0f));

	//// �|�C���g���C�g�̃f�B�t���[�Y�J���[�������F�ɂ���
	//SetLightDifColorHandle(PointLightHandle, GetColorF(9.0f, 9.0f, 9.0f, 0.0f));

	//�|�C���g���C�g�̏����l��ݒ�
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 0.0f, 0.0f));

	LightFlg = true;

	// ���C�g�̈ʒu�̉�]�l�����Z
	LightPos = VGet(0.0f, 600.0f, -250.0f);
	LightPos2 = VGet(0.0f, 1000.0f, 0.0f);

	dis[0] = VGet(-distance, 0.0f, distance2 - 200);
	dis[1] = VGet(0.0f, 0.0f, distance2 - 200);
	dis[2] = VGet(distance, 0.0f, distance2 - 200);
	dis[3] = VGet(-distance, 0.0f, -250.0f);
	dis[4] = VGet(0.0f, 0.0f, -250.0f);
	dis[5] = VGet(distance, 0.0f, -250.0f);

	//�p�x��������
	LightRotateAngle = 0;
	LightRotateAngle2 = 0;

	//�|�C���g���C�g�̏����l
	SetLightPositionHandle(PointLightHandle, LightPos2);

	// �X�|�b�g���C�g�̏����l
	SetLightPositionHandle(SpotLightHandle, LightPos);

	//���ԏ�����
	time2 = 120;
	time = 600;
	WaitTime = 1;
	cntFlg = 4;
	rc = 4;
	while (count == 0 || count == 2 || count == 4)
	{
		count = GetRand(5);
	}
}
void Light()
{
	//10�J�E���g�\��
	SetFontSize(100);
	if (g_DispTime == true)DrawFormatString(600, 100, 0xffff00, "%d", time / 60);

	Point_t
		cp1 = { dis[rc].x,dis[rc].z, -180, distance2 - 200 },
		cp2 = { dis[rc].x,dis[rc].z, -180, distance2 - 200 },
		cp3 = { dis[rc].x,dis[rc].z, -180, distance / 2 },
		cp4 = { dis[rc].x,dis[rc].z, -180, distance / 2 };


	//10�b�o�߂Ń��E���h���̃��E���h��
	if (time < 600 && WaitTime == 1) {//�ŏ���10�b
		time++;	
		
		//2�b�o�߂���������]��
		if (time2 < 120) {
			time2++;
		}
		else if (time2 >= 120) {

			while (cntFlg == count || cntFlg + 2 == count || cntFlg - 2 == count || cntFlg + 4 == count || cntFlg - 4 == count ||
				cntFlg + 5 == count || cntFlg - 5 == count || (cntFlg == 2) && (count == 3) || (cntFlg == 3) && (count == 2))
			{
				count = GetRand(5);
				rc = cntFlg;
			}
			PlaySoundMem(drum, DX_PLAYTYPE_LOOP);

			cntFlg = count;
			time2 = 1;

			LightRotateAngle = 0.0f;
			LightRotateAngle2 = 0.0f;
		}
	}
	else if (time < 600 && WaitTime == 0) {//���s����
		time++;
	}
	else if (time >= 600 && WaitTime == 1) {//���C�g���~�܂�
		time = 0;
		WaitTime = 0;
		LightFlg = false;
		g_DispTime = false;
		judge_win = false;
	}
	else if (time >= 600 && WaitTime == 0) {//���̃��E���h�ɍs��
		time = 0;
		LightFlg = true;
		g_DispTime = true;
		WaitTime = 1;
		Key_Look = false;
		round_count++;
		if (round_count > 6 && Sadondes_flg == false) finish = false;		//6���E���h�������I���
		if (Sadondes_flg == true) finish = false;		//6���E���h�������I���
	}


	if (WaitTime == 1 && count < 6) {

		//��Ɉړ�
		if (count == rc - 3) {
			LightRotateAngle += 1.5f;
			LightRotateAngle2 += 1.5f;
			if (count == 0) {
				DrawX = cp1.x + -sin(PI / cp1.T * LightRotateAngle) * cp1.Range;
				DrawZ = cp1.z + -cos(PI / cp1.T * LightRotateAngle2) * cp1.Range + cp1.Range;
			}
			else {
				DrawX = cp1.x + sin(PI / cp1.T * LightRotateAngle) * cp1.Range;
				DrawZ = cp1.z + -cos(PI / cp1.T * LightRotateAngle2) * cp1.Range + cp1.Range;
			}
		}

		//���Ɉړ�
		else if (count == rc + 3) {
			LightRotateAngle += 1.5f;
			LightRotateAngle2 += 1.5f;
			if (count == 3) {
				DrawX = cp2.x + -sin(PI / cp2.T * LightRotateAngle) * cp2.Range;
				DrawZ = cp2.z + cos(PI / cp2.T * LightRotateAngle2) * cp2.Range - cp2.Range;
			}
			else {
				DrawX = cp2.x + sin(PI / cp2.T * LightRotateAngle) * cp2.Range;
				DrawZ = cp2.z + cos(PI / cp2.T * LightRotateAngle2) * cp2.Range - cp2.Range;
			}
		}

		//�E�Ɉړ�
		if (count == rc + 1) {
			LightRotateAngle += 1.5f;
			LightRotateAngle2 += 1.5f;
			if (count >= 3) {
				DrawX = cp3.x + -cos(PI / cp3.T * LightRotateAngle) * cp3.Range + cp3.Range;
				DrawZ = cp3.z + -sin(PI / cp3.T * LightRotateAngle2) * cp3.Range;
			}
			else {
				DrawX = cp3.x + -cos(PI / cp3.T * LightRotateAngle) * cp3.Range + cp3.Range;
				DrawZ = cp3.z + sin(PI / cp3.T * LightRotateAngle2) * cp3.Range;
			}
		}

		//���Ɉړ�
		else if (count == rc - 1) {
			LightRotateAngle += 1.5f;
			LightRotateAngle2 += 1.5f;
			if (count >= 3) {
				DrawX = cp4.x + cos(PI / cp4.T * LightRotateAngle) * cp4.Range - cp4.Range;
				DrawZ = cp4.z + -sin(PI / cp4.T * LightRotateAngle2) * cp4.Range;
			}
			else {
				DrawX = cp4.x + cos(PI / cp4.T * LightRotateAngle) * cp4.Range - cp4.Range;
				DrawZ = cp4.z + sin(PI / cp4.T * LightRotateAngle2) * cp4.Range;
			}
		}
	}

	//���C�g�̈ʒu�̉�]�l�����Z
	LightPos = VGet(DrawX, 600.0f, DrawZ);

	// �X�|�b�g���C�g�̈ʒu�̍X�V
	SetLightPositionHandle(SpotLightHandle, LightPos);

	//�|�C���g���C�g�̏����l��ݒ�
	SetLightPositionHandle(PointLightHandle, LightPos2);

	// ���C�g�̎~�܂�ʒu�����ŕ`�悷��
//DrawSphere3D(VGet(-distance, 40.0f, distance2 - 200), 40.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

//DrawSphere3D(VGet(0.0f, 40.0f, distance2 - 200), 40.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

//DrawSphere3D(VGet(distance, 40.0f, distance2 - 200), 40.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

//DrawSphere3D(VGet(-distance, 40.0f, -250.0f), 40.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

//DrawSphere3D(VGet(0.0f, 40.0f, -250.0f), 40.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

//DrawSphere3D(VGet(distance, 40.0f, -250.0f), 40.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

}