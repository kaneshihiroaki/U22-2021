#include "DxLib.h"
#include <math.h>
#include "Debug.h"
#include "Light.h"

#define DRAW_NUM	(3)
#define SPACE		(512.0f)


int PixelShaderHandle;
int VertexShaderHandle;
float LightRotateAngle;
float LightRotateAngle2;
int SpotLightHandle;
int PointLightHandle;
int DirLightHandle;
int i, j;
float DrawX, DrawZ;

int time = 600;
int count;
int cntFlg;
float distance = 1200.0f;
int WaitTime = 0;

bool LightFlg;

VECTOR dis[9];
VECTOR LightPos;
VECTOR LightPos2;

void Light_init() {

	//���_�V�F�[�_�[��ǂݍ���
	VertexShaderHandle = LoadVertexShader("Shader/NormalMesh_SpotPointLightVS.vso");

	//�s�N�Z���V�F�[�_�[��ǂݍ���
	PixelShaderHandle = LoadPixelShader("Shader/NormalMesh_SpotPointLightPS.pso");

	// �g�p���钸�_�V�F�[�_�[���Z�b�g
	SetUseVertexShader(VertexShaderHandle);

	// �g�p����s�N�Z���V�F�[�_�[���Z�b�g
	SetUsePixelShader(PixelShaderHandle);

	// ���C�g�̈ʒu����]����l��������
	LightRotateAngle = 0.0f;

	// �W�����C�g�𖳌��ɂ���
	SetLightEnable(FALSE);

	//���C�g�̏�����1�s�N�Z�����Ƃɍs���i�������d���Ȃ�j
	SetUsePixelLighting(TRUE);

	// �X�|�b�g���C�g���쐬����
	SpotLightHandle = CreateSpotLightHandle(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, -1.0f, 0.0f), 0.18f, 0.15f, 1000.0f, 0.4f, 0.001662f, 0.000001f);

	// �X�|�b�g���C�g�̃A���r�G���g�J���[�����F�ɂ���
	SetLightAmbColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	// �X�|�b�g���C�g�̃f�B�t���[�Y�J���[�����F�ɂ���
	SetLightDifColorHandle(SpotLightHandle, GetColorF(10.0f, 10.0f, 0.0f, 0.0f));

	// �|�C���g���C�g���쐬����
	PointLightHandle = CreatePointLightHandle(VGet(0.0f, 0.0f, 0.0f), 7000.0f, 1.016523f, 0.000100f, 0.000010f);

	// �|�C���g���C�g�̃A���r�G���g�J���[�𖳌��ɂ���
	SetLightAmbColorHandle(PointLightHandle, GetColorF(10.0f, 10.0f, 10.0f, 0.0f));

	// �|�C���g���C�g�̃f�B�t���[�Y�J���[�������F�ɂ���
	SetLightDifColorHandle(PointLightHandle, GetColorF(9.0f, 9.0f, 9.0f, 0.0f));

	//�|�C���g���C�g�̏����l��ݒ�
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 1500.0f, 0.0f));

	LightFlg = true;

	count = 1;

	dis[0] = VGet(-distance, 0.0f, distance);
	dis[1] = VGet(0.0f, 0.0f, distance);
	dis[2] = VGet(distance, 0.0f, distance);
	dis[3] = VGet(-distance, 0.0f, 0.0f);
	dis[4] = VGet(0.0f, 0.0f, 0.0f);
	dis[5] = VGet(distance, 0.0f, 0.0f);
	dis[6] = VGet(-distance, 0.0f, -distance);
	dis[7] = VGet(0.0f, 0.0f, -distance);
	dis[8] = VGet(distance, 0.0f, -distance);
}
void Light()
{
	//10�b�o�߂���������]��
	if (time < 600) {
		time++;
	}
	else if (time >= 600 && WaitTime == 0) {
		while (cntFlg == count || cntFlg + 2 == count || cntFlg - 2 == count || cntFlg + 4 == count || cntFlg - 4 == count || cntFlg + 5 == count || cntFlg - 5 == count|| cntFlg + 6 == count || cntFlg - 6 == count 
			|| cntFlg + 7 == count || cntFlg - 7 == count || cntFlg + 8 == count || cntFlg - 8 == count || (cntFlg == 2) && (count == 3) || (cntFlg == 3) && (count == 2) || (cntFlg == 5) && (count == 6) || (cntFlg == 6) && (count == 5))
		{
			count = GetRand(8);
		}
		cntFlg = count;
		time = 0;
		WaitTime = 1;
		Key_Look = false;
		LightFlg = true;
	}
	else if (WaitTime == 1) {
		WaitTime = 0;
		time = 0;
		LightFlg = false;
	}
	if (WaitTime == 1 && count < 9) {
		if (LightPos.x > dis[count].x) {
			LightRotateAngle -= 0.01f;
		}
		else if (LightPos.x < dis[count].x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z > dis[count].z) {
			LightRotateAngle2 -= 0.01f;
		}
		else if (LightPos.z < dis[count].z) {
			LightRotateAngle2 += 0.01f;
		}
	}

	// ���C�g�̈ʒu�̉�]�l�����Z
	LightPos = VGet(LightRotateAngle * 200.0f, 800.0f, LightRotateAngle2 * 200.0f);
	LightPos2 = VGet(LightRotateAngle * 200.0f, 1100.0f, LightRotateAngle2 * 200.0f);

	//10�J�E���g�\��
	SetFontSize(100);
	DrawFormatString(500, 10, 0x25525000, "%d�b", time / 60);

	//�|�C���g���C�g�̏����l��ݒ�
	SetLightPositionHandle(PointLightHandle,LightPos2);

	// �X�|�b�g���C�g�̈ʒu�̍X�V
	SetLightPositionHandle(SpotLightHandle, LightPos);
}