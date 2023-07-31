#pragma once
#include <DxLib.h>
#include "../vector/vector.h"

namespace aqua
{
	class CMatrix
		:public MATRIX
	{
	public:
		CMatrix(void);
		CMatrix(const MATRIX& m);
		~CMatrix() = default;

		static CMatrix GetIdent(void);

		CMatrix& Scale(const aqua::CVector3& scale);

		CMatrix& Translate(const aqua::CVector3& trans);

		CMatrix& RotationX(float axis_rotat_x);

		CMatrix& RotationY(float axis_rotat_y);

		CMatrix& RotationZ(float axis_rotat_z);

		CMatrix& RotationAxis(const aqua::CVector3& rotat_axis, float rotat);

		CMatrix& RotVec2(const aqua::CVector3& vect1, const aqua::CVector3& vect2);

		CMatrix operator + (const CMatrix& matrix)
		{
			return CMatrix(MAdd(*this, matrix));
		}

		CMatrix operator * (CMatrix& matrix)
		{
			return CMatrix(MMult(*this, matrix));
		}

		CMatrix& operator *= (const CMatrix& matrix)
		{
			*this = MMult(*this, matrix);
			return *this;
		}

		CMatrix& operator = (const CMatrix& matrix)
		{
			memcpy(this->m, &matrix.m, sizeof(MATRIX));
			return *this;
		}

		CMatrix& operator * (float scale)
		{
			*this = MScale(*this, scale);

			return *this;
		}

		CMatrix Transpose(void);

		CMatrix Inverse(void);
	};
}