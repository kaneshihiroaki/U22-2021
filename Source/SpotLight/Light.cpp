#include "DxLib.h"
#include <math.h>

#define DRAW_NUM	(3)
#define SPACE		(512.0f)

int PixelShaderHandle;
int VertexShaderHandle;
float LightRotateAngle;
int SpotLightHandle;
int PointLightHandle;
int i, j;
float DrawX, DrawZ;
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

	// �O���[�o���A���r�G���g���C�g( ������ )���Q�O���̖��邳�ɂ���
	SetGlobalAmbientLight(GetColorF(0.2f, 0.2f, 0.2f, 0.0f));
	
	//�|�C���g���C�g�̈ʒu�̍X�V
	SetLightPositionHandle(PointLightHandle, VGet(0.0f, 1000.0f, 0.0f));
}
void Light() 
{
	// ���C�g�̈ʒu�̉�]�l�����Z
	LightRotateAngle += 0.01f;

	LightPos = VGet(sin(-LightRotateAngle) * 200.0f, 800.0f, sin(-LightRotateAngle * 2) * 150.0f);

	// �X�|�b�g���C�g�̈ʒu�̍X�V
	SetLightPositionHandle(SpotLightHandle, LightPos);
}