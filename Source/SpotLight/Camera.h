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

	void Camera_Control(VECTOR PlayerPos);

protected:

private:
	float  c_CameraHAngle;
	float  c_CameraVAngle;

	const float c_CameraPosHeight = 0.0f;
	float c_CameraPosDist = 350.0f;
	const float c_CameraSpeed = 3.0f;
};