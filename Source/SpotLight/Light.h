#pragma once

extern int PixelShaderHandle;
extern int VertexShaderHandle;
extern float LightRotateAngle;
extern float LightRotateAngle2;
extern int SpotLightHandle;
extern int PointLightHandle;
extern int DirLightHandle;
extern int i, j;
extern float DrawX, DrawZ;
extern int count;
extern int cntFlg;
extern bool finish;		//�Q�[�����I�����������itrue:�Q�[���ĊJ false:�^�C�g���֖߂�)
extern bool judge_win;//���������J�E���g����Ƃ��Ɏg��flg
extern int round_count;//���E���h��
extern int WaitTime;

extern VECTOR LightPos;
extern bool LightFlg;//�~�܂��Ă��邩���ׂ�( TRUE:���� FALSE:�~�܂��Ă��� )

extern int time;//�G�l�~�[�̕��ō����b�Ȃ̂����m����悤
extern int WaitTime;//��ɓ���

/*�T�h���f�X�p�ϐ�*/
extern bool Sadondes_flg;//�T�h���f�X���s�����ǂ���true�Ȃ�s���Ă���B
/*�T�h���f�X�p�ϐ�*/

void Light();
void Light_init();
void Light_SetUp();