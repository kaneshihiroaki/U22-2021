#include"DxLib.h"

using namespace std;


extern int DebugNum; //�f�o�b�N�̐���
extern bool DebugMode;//�f�o�b�N���[�h�̃I���I�t

extern bool Collision_Player;//�����蔻�������悤
extern bool GamePadIn_bool;//�Q�[���p�b�h������悤
extern bool CameraUp_bool;//�J�����ړ��㉺�𔽓]
extern bool CameraLR_bool;//�J�����ړ����E�𔽓]

extern bool Build_bool;//�r���h��\�������悤

extern bool GameJudge;//���s����
extern bool Win;
extern bool Lose;

extern int g_KeyFlg;
extern int g_NowKey;
extern int g_OldKey;

extern bool Key_Look;//�v���C���[�̓��͂𐧌䂷��ϐ�

extern bool Debug_Enemy;//�f�o�b�N�p�t���Otrue�Ŋm�F�\�ɂ���
extern bool Debug_Camera;	//�J�����p�f�o�b�N�p�t���Otrue�Ŋm�F�\�ɂ���


extern int DebugCom();
extern void DebugDrawing();;
extern void CameraState();
extern void CameraReverse();
extern void Collision_player();
extern void GamePadIn();
extern void Build_In();
extern void Game_Judge_In();
extern void Enemy_State();
extern void FreeCamera();


extern void Build_Time();//�r���h�X�^���v�֐�
extern void Game_Judge();//���s�֐�

extern void Player_Enemy(VECTOR player, VECTOR Ene[3]);
