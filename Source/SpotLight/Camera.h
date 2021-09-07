#pragma once

class PLAYER;
class STAGE;
class MAIN;

class CAMERA
{
private:
	//const float c_CameraPosHeight = 100000.0f;			//カメラの初期高さ
	float c_CameraPosDist = 1100.0f;					//プレイヤーとカメラの初期距離
	const float c_CameraSpeed = 3.0f;				//カメラの移動速さ

	float  c_SinParam;
	float  c_CosParam;
	

public:
	CAMERA();
	~CAMERA();

	float  c_CameraHAngle;		//角度
	float  c_CameraVAngle;		//角度
	float cko = 100;

	float c_RPosX;
	float c_RPosY;
	float c_RPosZ;
	float c_RAngX;
	float c_RAngY;
	float c_RAngZ;

	float GetCameraAngle() { return c_CameraHAngle; }

	void init();	//初期化
	void Camera_Control(STAGE* stage);
	void Camera_Result(MAIN* main);

};