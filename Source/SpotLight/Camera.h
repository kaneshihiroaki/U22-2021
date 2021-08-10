#pragma once

class PLAYER;
class STAGE;

class CAMERA
{
private:
	//const float c_CameraPosHeight = 100000.0f;			//カメラの初期高さ
	float c_CameraPosDist = 1500.0f;					//プレイヤーとカメラの初期距離
	const float c_CameraSpeed = 3.0f;				//カメラの移動速さ

	float  c_SinParam;
	float  c_CosParam;
	float  c_CameraHAngle;		//角度
	float  c_CameraVAngle;		//角度

protected:
	//float getCameraAngle() { return c_CameraHAngle; };


public:
	CAMERA();
	~CAMERA();

	float GetCameraAngle() { return c_CameraHAngle; }



	void Camera_Control(STAGE* stage);

};