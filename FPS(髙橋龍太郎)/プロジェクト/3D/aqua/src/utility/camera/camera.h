#pragma once
#include <DxLib.h>
#include "../../mathematics/vector/vector.h"

namespace aqua
{
	class CCamera
	{
	public:
		CCamera(void);
		~CCamera(void) = default;

		int SetCameraDepth(float Near, float Far);

		int SetCamera(CVector3 Position, CVector3 Target, CVector3 UpDir);
	};
}