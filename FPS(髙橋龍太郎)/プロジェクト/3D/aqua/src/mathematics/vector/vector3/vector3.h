
/*!
 *  @file       vector2.h
 *  @brief      �񎟌��x�N�g��
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once
#include <Dxlib.h>
#include "..\..\..\debug\debug.h"
#include <cmath>

 /*!
  *  @brief  aqua���O���
  */
namespace aqua
{
    class CMatrix;

    class CVector3
        :public VECTOR
    {
    public:

        /*!
         *  @brief  �R���X�g���N�^
         */
        CVector3(void);

        /*!
         *  @brief  �R���X�g���N�^
         *
         *  @param[in]  x   X����
         *  @param[in]  y   Y����
         */
        CVector3(float x, float y, float z);

        /*!
         *  @brief  �R���X�g���N�^
         *
         *  @param[in]  v  �x�N�g��
         */
        CVector3(const CVector3& v);

        CVector3(const VECTOR& vec);

        /*!
         *  @brief  �f�X�g���N�^
         */
        ~CVector3(void) = default;

        /*!
         *  @brief      �x�N�g���̐��K��<br>
         *              ���g�̃x�N�g�������K�������
         *
         *  @return     ���K�����ꂽ�x�N�g��
         */
        CVector3            Normalize(void);

        /*!
         *  @brief      �x�N�g���̐��K��
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ���K�����ꂽ�x�N�g��
         */
        static CVector3     Normalize(const CVector3& v);

        /*!
         *  @brief      �x�N�g���̑傫���擾
         *
         *  @return     �x�N�g���̑傫��
         */
        float               Length(void);

        /*!
         *  @brief      �x�N�g���̑傫���擾
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���̑傫��
         */
        static float        Length(const CVector3& v);

        /*!
         *  @brief      2�̃x�N�g���̓���<br>
         *              dot = vA�EvB
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     ����
         */
        static float        Dot(const CVector3& vA, const CVector3& vB);

        /*!
         *  @brief      2�̃x�N�g���̊O��<br>
         *              cross = vA�~vB
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �O��
         */
        static VECTOR        Cross(const CVector3& vA, const CVector3& vB);

        static CVector3     Transform(const CVector3& v, const CMatrix& m);

        CVector3            Transform(const CMatrix& m);

        /*!
         *  @brief      ������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector3& operator=(const CVector3& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;

            return *this;
        }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector3& operator+=(const CVector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;

            return *this;
        }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        CVector3& operator-=(const CVector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;

            return *this;
        }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        CVector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        /*!
         *  @brief      �������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ��̃x�N�g����������
         *  @retval     true    ������
         *  @retval     false   �������Ȃ�
         */
        bool                operator==(const CVector3& v) const { return (x == v.x && y == v.y && z == v.z); }

        /*!
         *  @brief      �s�����Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     ��̃x�N�g�����������Ȃ�
         *  @retval     true    �������Ȃ�
         *  @retval     false   ������
         */
        bool                operator!=(const CVector3& v) const { return (x != v.x || y != v.y || z != v.z); }

        /*!
         *  @brief      ���������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator+(const CVector3& v) { return v; }

        /*!
         *  @brief      ���������Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v   �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator-(const CVector3& v) { return CVector3(-v.x, -v.y, -v.z); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator+(const CVector3& vA, const CVector3& vB) { return aqua::CVector3(vA.x + vB.x, vA.y + vB.y, vA.z + vB.z); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator-(const CVector3& vA, const CVector3& vB) { return CVector3(vA.x - vB.x, vA.y - vB.y, vA.z - vB.z); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator*(const CVector3& vA, const CVector3& vB) { return CVector3(vA.x * vB.x, vA.y * vB.y, vA.z * vB.z); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v       �x�N�g���N���X
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator*(const CVector3& v, float scalar) { return CVector3(v.x * scalar, v.y * scalar, v.z * scalar); }

        /*!
         *  @brief      ��Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *  @param[in]  v       �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator*(float scalar, const CVector3& v) { return CVector3(v.x * scalar, v.y * scalar, v.z * scalar); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  vA  �x�N�g���N���X
         *  @param[in]  vB  �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator/(const CVector3& vA, const CVector3& vB) { return CVector3(vA.x / vB.x, vA.y / vB.y, vA.z / vB.z); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  v       �x�N�g���N���X
         *  @param[in]  scalar  �X�J���[�l
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator/(const CVector3& v, float scalar) { return CVector3(v.x / scalar, v.y / scalar, v.z / scalar); }

        /*!
         *  @brief      ���Z���Z�q�̃I�[�o�[���[�h
         *
         *  @param[in]  scalar  �X�J���[�l
         *  @param[in]  v       �x�N�g���N���X
         *
         *  @return     �x�N�g���N���X
         */
        friend CVector3     operator/(float scalar, const CVector3& v) { return CVector3(scalar / v.x, scalar / v.y, scalar / v.z); }

        /*!
         *  @brief      �f�o�b�O���O�ɒl��\������
         */
        void                DebugLog(void);

        //! ���������ׂ�0�̃x�N�g��
        static const CVector3   ZERO;
        //! ���������ׂ�1�̃x�N�g��
        static const CVector3   ONE;
    };
}
