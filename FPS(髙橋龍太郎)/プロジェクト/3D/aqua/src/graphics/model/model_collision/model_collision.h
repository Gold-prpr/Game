#pragma once
#include <DxLib.h>
#include "../model.h"
#include "../../../mathematics/vector/vector.h"

namespace aqua
{
	class CModelColl
	{
	public:
		CModelColl(void);
		~CModelColl() = default;

		int SetUpColl(int model_handle, int frame_index, int div_num_x, int div_num_y, int div_num_z);

		int TerminateColl(void);

		int UpdateColl(void);

		MV1_COLL_RESULT_POLY CollCheckLine(aqua::CVector3 start_pos, aqua::CVector3 end_pos);

		MV1_COLL_RESULT_POLY_DIM CollCheckCapsule(aqua::CVector3 capsule_posA, float height, float radius);

		MV1_COLL_RESULT_POLY_DIM CollCheckSphere(aqua::CVector3 center_pos, float radius);

		MV1_COLL_RESULT_POLY CollCheckGetResultPoly(MV1_COLL_RESULT_POLY_DIM result_poly_dim, int poly_num);

		int CollResultPolyDimTerminate(MV1_COLL_RESULT_POLY_DIM result_poly_dim);
		
		int m_ModelHandle;//モデルハンドル
		int m_FrameIndex;//フレーム番号
		
	private:
		
	};
}