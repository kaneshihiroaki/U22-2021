#pragma once
//#include <DxLib.h>
//#include<math.h>
class CAMERA
{
public:
	CAMERA();
	~CAMERA();

	float  c_SinParam;
	float  c_CosParam;

	float  c_CameraHAngle;		//角度
	float  c_CameraVAngle;		//角度

	void Camera_Control(VECTOR PlayerPos);

protected:

private:
	const float c_CameraPosHeight = 0.0f;			//カメラの初期高さ
	float c_CameraPosDist = 350.0f;					//プレイヤーとカメラの初期距離
	const float c_CameraSpeed = 3.0f;				//カメラの移動速さ
};