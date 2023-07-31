#include "model_collision.h"

aqua::CModelColl::
CModelColl(void)
{
	
}

int
aqua::CModelColl::
SetUpColl(int model_handle, int frame_index, int div_num_x, int div_num_y, int div_num_z)
{
	m_ModelHandle = model_handle;
	m_FrameIndex = frame_index;

	return MV1SetupCollInfo(m_ModelHandle, m_FrameIndex, div_num_x, div_num_y, div_num_z);
}

int
aqua::CModelColl::
TerminateColl(void)
{
	return MV1TerminateCollInfo(m_ModelHandle, m_FrameIndex);
}

int
aqua::CModelColl::
UpdateColl(void)
{
	return MV1RefreshCollInfo(m_ModelHandle, m_FrameIndex);
}

MV1_COLL_RESULT_POLY
aqua::CModelColl::
CollCheckLine(aqua::CVector3 start_pos, aqua::CVector3 end_pos)
{
	return MV1_COLL_RESULT_POLY(MV1CollCheck_Line(m_ModelHandle, m_FrameIndex, start_pos, end_pos));
}

MV1_COLL_RESULT_POLY_DIM 
aqua::CModelColl::
CollCheckCapsule(aqua::CVector3 capsule_posA, float height, float radius)
{
	return MV1_COLL_RESULT_POLY_DIM(MV1CollCheck_Capsule(m_ModelHandle, m_FrameIndex,
		capsule_posA, aqua::CVector3(capsule_posA.x, capsule_posA.y + height, capsule_posA.z), radius));
}

MV1_COLL_RESULT_POLY_DIM 
aqua::CModelColl::
CollCheckSphere(aqua::CVector3 center_pos, float radius)
{
	return MV1_COLL_RESULT_POLY_DIM(MV1CollCheck_Sphere(m_ModelHandle, m_FrameIndex, center_pos, radius));
}

MV1_COLL_RESULT_POLY
aqua::CModelColl::
CollCheckGetResultPoly(MV1_COLL_RESULT_POLY_DIM result_poly_dim, int poly_num)
{
	return MV1_COLL_RESULT_POLY(MV1CollCheck_GetResultPoly(result_poly_dim, poly_num));
}

int
aqua::CModelColl::
CollResultPolyDimTerminate(MV1_COLL_RESULT_POLY_DIM result_poly_dim)
{
	return MV1CollResultPolyDimTerminate(result_poly_dim);
}