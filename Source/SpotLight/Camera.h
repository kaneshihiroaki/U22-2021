#pragma once
//#include <DxLib.h>
//#include<math.h>
class CAMERA
{
private:
	const float c_CameraPosHeight = 0.0f;			//�J�����̏�������
	float c_CameraPosDist = 350.0f;					//�v���C���[�ƃJ�����̏�������
	const float c_CameraSpeed = 3.0f;				//�J�����̈ړ�����

protected:
	//float getCameraAngle() { return c_CameraHAngle; };


public:
	CAMERA();
	~CAMERA();

	float  c_SinParam;
	float  c_CosParam;
	float  c_CameraHAngle;		//�p�x
	float  c_CameraVAngle;		//�p�x

	void Camera_Control(VECTOR PlayerPos);

};