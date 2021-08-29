#pragma once

class PLAYER;
class STAGE;

class CAMERA
{
private:
	//const float c_CameraPosHeight = 100000.0f;			//カメラの初期高さ
	float c_CameraPosDist = 2000.0f;					//プレイヤーとカメラの初期距離
	const float c_CameraSpeed = 3.0f;				//カメラの移動速さ

	float  c_SinParam;
	float  c_CosParam;
	float  c_CameraHAngle;		//角度
	float  c_CameraVAngle;		//角度
	float cko = -170;
	

public:
	CAMERA();
	~CAMERA();

	float GetCameraAngle() { return c_CameraHAngle; }

	void init();	//初期化
	void Camera_Control(STAGE* stage);

};