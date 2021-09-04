#pragma once

class PLAYER;
class STAGE;
class MAIN;

class CAMERA
{
private:
	//const float c_CameraPosHeight = 100000.0f;			//�J�����̏�������
	float c_CameraPosDist = 2000.0f;					//�v���C���[�ƃJ�����̏�������
	const float c_CameraSpeed = 3.0f;				//�J�����̈ړ�����

	float  c_SinParam;
	float  c_CosParam;
	

public:
	CAMERA();
	~CAMERA();

	float  c_CameraHAngle;		//�p�x
	float  c_CameraVAngle;		//�p�x
	float cko = -170;

	float x = 0;
	float y = 569;
	float z = -530;
	float x1 = -0.41;
	float y2 = 3.15;
	float z1 = 0;

	float GetCameraAngle() { return c_CameraHAngle; }

	void init();	//������
	void Camera_Control(STAGE* stage);
	void Camera_Result(MAIN* main);

};