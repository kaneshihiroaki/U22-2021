#include "DxLib.h"
#include <math.h>

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

VECTOR dis;
VECTOR dis1;
VECTOR dis2;
VECTOR dis3;
VECTOR dis4;
VECTOR dis5;
VECTOR dis6;
VECTOR dis7;
VECTOR dis8;
VECTOR LightPos;

void Light_init() {

	// ���_�V�F�[�_�[��ǂݍ���
	VertexShaderHandle = LoadVertexShader("Shader/NormalMesh_SpotPointLightVS.vso");

	// �s�N�Z���V�F�[�_�[��ǂݍ���
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
	SetLightAmbColorHandle(PointLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	// �|�C���g���C�g�̃f�B�t���[�Y�J���[�������F�ɂ���
	SetLightDifColorHandle(PointLightHandle, GetColorF(5.0f, 5.0f, 10.0f, 0.0f));

	//�|�C���g���C�g�̏����l��ݒ�
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 1000.0f, 0.0f));
	
	//// �f�B���N�V���i�����C�g���쐬����
	//DirLightHandle = CreateDirLightHandle(VGet(-1.0f, 0.0f, 0.0f));

	//// �f�B���N�V���i�����C�g�̃A���r�G���g�J���[��}����
	//SetLightAmbColorHandle(DirLightHandle, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	//// �f�B���N�V���i�����C�g�̃f�B�t���[�Y�J���[��΂ɂ���
	//SetLightDifColorHandle(DirLightHandle, GetColorF(5.0f, 5.0f, 10.0f, 0.0f));
	
	// �O���[�o���A���r�G���g���C�g( ������ )���Q�O���̖��邳�ɂ���
	SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));

	count = GetRand(8);
	cntFlg = count;

	dis = VGet(-distance, 0.0f, distance);
	dis1 = VGet(0.0f, 0.0f, distance);
	dis2 = VGet(distance, 0.0f, distance);
	dis3 = VGet(-distance, 0.0f, 0.0f);
	dis4 = VGet(0.0f, 0.0f, 0.0f);
	dis5 = VGet(distance, 0.0f, 0.0f);
	dis6 = VGet(-distance, 0.0f, -distance);
	dis7 = VGet(0.0f, 0.0f, -distance);
	dis8 = VGet(distance, 0.0f, -distance);
}
void Light()
{
	//10�b�o�߂���������]��
	if (time < 600) {
		time++;
	}
	else if (time >= 600) {
		while (cntFlg == count) {
				count = GetRand(8);
			}
		cntFlg = count;
		time = 0;
		//10�b�ԏ������~�߂�
		WaitTimer(10000);
	}
	if (count == 0) {
		if (LightPos.x > dis.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z > dis.z) {
			LightRotateAngle2 += 0.01f;
		}
	}
	else if (count == 1) {
		if (LightPos.x < dis1.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.x > dis1.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z < dis1.z) {
			LightRotateAngle2 += 0.01f;
		}
	}
	else if (count == 2) {
		if (LightPos.x < dis2.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z < dis2.z) {
			LightRotateAngle2 += 0.01f;
		}
	}
	else if (count == 3) {
		if (LightPos.x > dis3.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z > dis3.z) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z < dis3.z) {
			LightRotateAngle += 0.01f;
		}
	}
	else if (count == 4) {
		if (LightPos.x > dis4.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.x < dis4.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z > dis4.z) {
			LightRotateAngle2 -= 0.01f;
		}
		if (LightPos.z < dis4.z) {
			LightRotateAngle2 += 0.01f;
		}
	}
	else if (count == 5) {
		if (LightPos.x < dis5.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z < dis5.z) {
			LightRotateAngle2 += 0.01f;
		}
		if (LightPos.z > dis5.z) {
			LightRotateAngle2 -= 0.01f;
		}
	}
	else if (count == 6) {
		if (LightPos.x > dis6.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z > dis6.z) {
			LightRotateAngle2 -= 0.01f;
		}
	}
	else if (count == 7) {
		if (LightPos.x < dis7.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.x > dis7.x) {
			LightRotateAngle -= 0.01f;
		}
		if (LightPos.z > dis7.z) {
			LightRotateAngle -= 0.01f;
		}
	}
	else if (count == 8) {
		if (LightPos.x < dis8.x) {
			LightRotateAngle += 0.01f;
		}
		if (LightPos.z > dis8.z) {
			LightRotateAngle2 -= 0.01f;
		}
	}
	// ���C�g�̈ʒu�̉�]�l�����Z
	LightPos = VGet(LightRotateAngle * 200.0f, 800.0f, LightRotateAngle2 * 200.0f);

	//10�J�E���g�\��
	SetFontSize(100);
	DrawFormatString(500, 10, 0x25525000, "%d�b",time/60);
	
	// �X�|�b�g���C�g�̈ʒu�̍X�V
	SetLightPositionHandle(SpotLightHandle, LightPos);
}