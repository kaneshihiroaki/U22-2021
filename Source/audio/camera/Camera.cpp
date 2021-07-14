#include "Dxlib.h"
VECTOR JikuPos = VGet(100.0f, 150.0f, 0.0f);
void Camera(){
// ÉJÉÅÉâ Set
    {
    VECTOR CameraEyePos, CameraAtPos;
    CameraAtPos = JikuPos;
    CameraEyePos.x = CameraAtPos.x;
    CameraEyePos.y = CameraAtPos.y + 600.0f;
    CameraEyePos.z = CameraAtPos.z - 400.0f;
    //
    SetCameraPositionAndTarget_UpVecY(CameraEyePos, CameraAtPos);
    }
 }