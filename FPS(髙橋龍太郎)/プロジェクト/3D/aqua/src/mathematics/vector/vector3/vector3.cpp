#include "vector3.h"
#include "../../matrix/matrix.h"

const aqua::CVector3 aqua::CVector3::ZERO = aqua::CVector3(0.0f, 0.0f, 0.0f);
const aqua::CVector3 aqua::CVector3::ONE = aqua::CVector3(1.0f, 1.0f, 1.0f);

aqua::CVector3::
CVector3(void)
	: CVector3(0.0f, 0.0f, 0.0f)
{
}

aqua::CVector3::
CVector3(float x, float y, float z)
	: VECTOR({ x, y, z })
{
}

aqua::CVector3::
CVector3(const CVector3& v)
	: VECTOR(v)
{
}

aqua::CVector3::
CVector3(const VECTOR& vec)
	: CVector3(vec.x, vec.y, vec.z)
{
}

aqua::CVector3
aqua::CVector3::
Normalize(void)
{
	return Normalize(*this);
}

aqua::CVector3
aqua::CVector3::
Normalize(const CVector3& v)
{
	aqua::CVector3 t = v;

	float inv = 1.0f / t.Length();

	t.x *= inv;
	t.y *= inv;
	t.z *= inv;

	return t;
}

float
aqua::CVector3::
Length(void)
{
	return Length(*this);
}

float
aqua::CVector3::
Length(const CVector3& v)
{
	return VSize(v);
}

float
aqua::CVector3::
Dot(const CVector3& vA, const CVector3& vB)
{
	return VDot(vA, vB);
}

VECTOR
aqua::CVector3::
Cross(const CVector3& vA, const CVector3& vB)
{
	return VCross(vA, vB);
}

aqua::CVector3 aqua::CVector3::Transform(const CVector3& v, const CMatrix& m)
{
	return VTransform(v, m);
}

aqua::CVector3 aqua::CVector3::Transform(const CMatrix& m)
{
	return Transform(*this, m);
}

void
aqua::CVector3::
DebugLog(void)
{
	AQUA_DEBUG_LOG("CVector3(x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z) + ")");
}
