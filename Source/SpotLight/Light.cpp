#include "DxLib.h"
#include <math.h>
#include "Debug.h"
#include "Light.h"
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

int time = 600;
int count;
int cntFlg = 4;
int rc = 4;
float distance = 1200.0f;
int WaitTime = 1;

bool LightFlg;

VECTOR dis[9];
VECTOR LightPos;
VECTOR LightPos2;

typedef struct {
	float x, z;    //���W
	float ox, oz;//��]�̒��S
	float T;    //����
	float Range;//���a
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
	SpotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.28f, 0.0f, 2000.0f, 0.0f, 0.006f, 0.0f);

	// �X�|�b�g���C�g�̃A���r�G���g�J���[�����F�ɂ���
	SetLightAmbColorHandle(SpotLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	// �X�|�b�g���C�g�̃f�B�t���[�Y�J���[�����F�ɂ���
	SetLightDifColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	// �|�C���g���C�g���쐬����
	PointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 7000.0f, 1.016523f, 0.0001f, 0.00001f);

	// �|�C���g���C�g�̃A���r�G���g�J���[�𖳌��ɂ���
	SetLightAmbColorHandle(PointLightHandle, GetColorF(10.0f, 10.0f, 10.0f, 0.0f));

	// �|�C���g���C�g�̃f�B�t���[�Y�J���[�������F�ɂ���
	SetLightDifColorHandle(PointLightHandle, GetColorF(9.0f, 9.0f, 9.0f, 0.0f));
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
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 1200.0f, 0.0f));

	LightFlg = true;

	// ���C�g�̈ʒu�̉�]�l�����Z
	LightPos = VGet(0.0f, 800.0f, 0.0f);
	LightPos2 = VGet(0.0f, 1100.0f, 0.0f);

	dis[0] = VGet(-distance, 0.0f, distance);
	dis[1] = VGet(0.0f, 0.0f, distance);
	dis[2] = VGet(distance, 0.0f, distance);
	dis[3] = VGet(-distance, 0.0f, 0.0f);
	dis[4] = VGet(0.0f, 0.0f, 0.0f);
	dis[5] = VGet(distance, 0.0f, 0.0f);
	dis[6] = VGet(-distance, 0.0f, -distance);
	dis[7] = VGet(0.0f, 0.0f, -distance);
	dis[8] = VGet(distance, 0.0f, -distance);

	//�p�x��������
	LightRotateAngle = 0;
	LightRotateAngle2 = 0;

	//�|�C���g���C�g�̏����l
	SetLightPositionHandle(PointLightHandle, LightPos2);

	// �X�|�b�g���C�g�̏����l
	SetLightPositionHandle(SpotLightHandle, LightPos);

	//���ԏ�����
	time = 600;

	WaitTime = 0;
	cntFlg = 4;
	rc = 4;
	while (count == 0 || count == 2 || count == 4 || count == 6 || count == 8)
	{
		count = GetRand(8);
	}
}
void Light()
{
	Point_t
		cp1 = { 0, 0, 0, distance / 2, -180, distance / 2 },
		cp2 = { 0, 0, 0, -distance / 2, -180, distance / 2 },
		cp3 = { 0, 0, distance / 2, 0, -180, distance / 2 },
		cp4 = { 0, 0, -distance / 2, 0, -180, distance / 2 };

	//10�b�o�߂���������]��
	if (time < 600) {
		time++;
	}
	else if (WaitTime == 1) {
		WaitTime = 0;
		time = 0;
		LightFlg = false;
		//finish = false;
		round_count++;
	}
	else if (time >= 600 && WaitTime == 0) {
		while (cntFlg == count || cntFlg + 2 == count || cntFlg - 2 == count || cntFlg + 4 == count || cntFlg - 4 == count || cntFlg + 5 == count || cntFlg - 5 == count || cntFlg + 6 == count || cntFlg - 6 == count
			|| cntFlg + 7 == count || cntFlg - 7 == count || cntFlg + 8 == count || cntFlg - 8 == count || (cntFlg == 2) && (count == 3) || (cntFlg == 3) && (count == 2) || (cntFlg == 5) && (count == 6) || (cntFlg == 6) && (count == 5))
		{
			count = GetRand(8);
			rc = cntFlg;
		}
		cntFlg = count;
		time = 0;
		WaitTime = 1;
		Key_Look = false;
		LightFlg = true;
		judge_win = false;
		if (round_count >= 6) finish = false;		//6���E���h�������I���
	}

	if (WaitTime == 1 && count < 9) {
		if (count == rc - 3 && LightPos.z < dis[count].z) {
			cp1.x += cp1.ox + sin(PI / cp1.T * LightRotateAngle) * cp1.Range;
			cp1.z += cp1.oz + -cos(PI / cp1.T * LightRotateAngle2) * cp1.Range;
			LightRotateAngle += 0.6f;
			LightRotateAngle2 += 0.3f;
			DrawX = cp1.x;
			DrawZ = cp1.z;
		}
		else if (count == rc + 3 && LightPos.z > dis[count].z) {
			cp2.x += cp2.ox + sin(PI / cp2.T * LightRotateAngle) * cp2.Range;
			cp2.z += cp2.oz + cos(PI / cp2.T * LightRotateAngle2) * cp2.Range;
			LightRotateAngle += 0.6f;
			LightRotateAngle2 += 0.3f;
			DrawX = cp2.x;
			DrawZ = cp2.z;
		}
		if (count == rc + 1 && LightPos.x < dis[count].x) {
			cp3.x += cp3.ox + -cos(PI / cp1.T * LightRotateAngle) * cp3.Range;
			cp3.z += cp3.oz + sin(PI / cp1.T * LightRotateAngle2) * cp3.Range;
			LightRotateAngle += 0.3f;
			LightRotateAngle2 += 0.6f;
			DrawX = cp3.x;
			DrawZ = cp3.z;
		}
		else if (count == rc - 1 && LightPos.x > dis[count].x) {
			cp4.x += cp4.ox + cos(PI / cp4.T * LightRotateAngle) * cp4.Range;
			cp4.z += cp4.oz + sin(PI / cp4.T * LightRotateAngle2) * cp4.Range;
			LightRotateAngle += 0.3f;
			LightRotateAngle2 += 0.6f;
			DrawX = cp4.x;
			DrawZ = cp4.z;
		}
	}

	//���C�g�̈ʒu�̉�]�l�����Z
	LightPos = VGet(DrawX, 600.0f, DrawZ);
	LightPos2 = VGet(DrawX, 1200.0f, DrawZ);

	// �X�|�b�g���C�g�̈ʒu�̍X�V
	SetLightPositionHandle(SpotLightHandle, LightPos);

	//�|�C���g���C�g�̏����l��ݒ�
	SetLightPositionHandle(PointLightHandle, LightPos2);

	//10�J�E���g�\��
	SetFontSize(100);
	DrawFormatString(500, 10, 0x25525000, "%d�b", time / 60);
}