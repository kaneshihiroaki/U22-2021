#pragma once

class PLAYER;
class STAGE;
class MAIN;

class CAMERA
{
private:
	//const float c_CameraPosHeight = 100000.0f;			//�J�����̏�������
	float c_CameraPosDist = 1100.0f;					//�v���C���[�ƃJ�����̏�������
	const float c_CameraSpeed = 3.0f;				//�J�����̈ړ�����

	float  c_SinParam;
	float  c_CosParam;
	

public:
	CAMERA();
	~CAMERA();

	float  c_CameraHAngle;		//�p�x
	float  c_CameraVAngle;		//�p�x
	float cko = 100;

	float c_RPosX;
	float c_RPosY;
	float c_RPosZ;
	float c_RAngX;
	float c_RAngY;
	float c_RAngZ;

	float GetCameraAngle() { return c_CameraHAngle; }

	void init();	//������
	void Camera_Control(STAGE* stage);
	void Camera_Result(MAIN* main);

};