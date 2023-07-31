#include "camera.h"

aqua::CCamera::CCamera(void)
{
}

int aqua::CCamera::SetCameraDepth(float Near, float Far)
{
	return SetCameraNearFar(Near, Far);
}

int aqua::CCamera::SetCamera(CVector3 Position, CVector3 Target, CVector3 UpDir)
{
	return SetCameraPositionAndTargetAndUpVec(Position, Target, UpDir);
}