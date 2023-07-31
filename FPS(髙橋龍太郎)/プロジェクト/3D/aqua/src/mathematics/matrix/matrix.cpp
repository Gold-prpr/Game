#include "matrix.h"
using namespace aqua;

CMatrix::CMatrix(void)
	:CMatrix(MGetIdent())
{
}

aqua::CMatrix::CMatrix(const MATRIX& m)
{
	std::memcpy(this->m, &m, sizeof(MATRIX));
}

CMatrix CMatrix::GetIdent(void)
{
	return MGetIdent();
}

CMatrix& CMatrix::Scale(const aqua::CVector3& scale)
{
	*this *= MGetScale(scale);
	return *this;
}

CMatrix& CMatrix::Translate(const aqua::CVector3& trans)
{
	*this *= MGetTranslate(trans);
	return *this;
}

CMatrix& CMatrix::RotationX(float axis_rotat_x)
{
	*this *= MGetRotX(axis_rotat_x);
	return *this;
}

CMatrix& CMatrix::RotationY(float axis_rotat_y)
{
	*this *= MGetRotY(axis_rotat_y);
	return *this;
}

CMatrix& CMatrix::RotationZ(float axis_rotat_z)
{
	*this *= MGetRotZ(axis_rotat_z);
	return *this;
}

CMatrix& CMatrix::RotationAxis(const aqua::CVector3& rotat_axis, float rotat)
{
	*this *= MGetRotAxis(rotat_axis, rotat);
	return *this;
}

CMatrix& CMatrix::RotVec2(const aqua::CVector3& vect1, const aqua::CVector3& vect2)
{
	*this *= MGetRotVec2(vect1, vect2);
	return *this;
}

CMatrix CMatrix::Transpose(void)
{
	return MTranspose(*this);
}

CMatrix CMatrix::Inverse(void)
{
	return MInverse(*this);
}