#pragma once

class PLAYER;
class STAGE;

class CAMERA
{
private:
	//const float c_CameraPosHeight = 100000.0f;			//�J�����̏�������
	float c_CameraPosDist = 1500.0f;					//�v���C���[�ƃJ�����̏�������
	const float c_CameraSpeed = 3.0f;				//�J�����̈ړ�����

	float  c_SinParam;
	float  c_CosParam;
	float  c_CameraHAngle;		//�p�x
	float  c_CameraVAngle;		//�p�x

protected:
	//float getCameraAngle() { return c_CameraHAngle; };


public:
	CAMERA();
	~CAMERA();

	float GetCameraAngle() { return c_CameraHAngle; }



	void Camera_Control(STAGE* stage);

};