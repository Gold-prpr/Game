
/*!
 *  @file       vector2.h
 *  @brief      二次元ベクトル
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
  *  @brief  aqua名前空間
  */
namespace aqua
{
    class CMatrix;

    class CVector3
        :public VECTOR
    {
    public:

        /*!
         *  @brief  コンストラクタ
         */
        CVector3(void);

        /*!
         *  @brief  コンストラクタ
         *
         *  @param[in]  x   X成分
         *  @param[in]  y   Y成分
         */
        CVector3(float x, float y, float z);

        /*!
         *  @brief  コンストラクタ
         *
         *  @param[in]  v  ベクトル
         */
        CVector3(const CVector3& v);

        CVector3(const VECTOR& vec);

        /*!
         *  @brief  デストラクタ
         */
        ~CVector3(void) = default;

        /*!
         *  @brief      ベクトルの正規化<br>
         *              自身のベクトルも正規化される
         *
         *  @return     正規化されたベクトル
         */
        CVector3            Normalize(void);

        /*!
         *  @brief      ベクトルの正規化
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     正規化されたベクトル
         */
        static CVector3     Normalize(const CVector3& v);

        /*!
         *  @brief      ベクトルの大きさ取得
         *
         *  @return     ベクトルの大きさ
         */
        float               Length(void);

        /*!
         *  @brief      ベクトルの大きさ取得
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルの大きさ
         */
        static float        Length(const CVector3& v);

        /*!
         *  @brief      2つのベクトルの内積<br>
         *              dot = vA・vB
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     内積
         */
        static float        Dot(const CVector3& vA, const CVector3& vB);

        /*!
         *  @brief      2つのベクトルの外積<br>
         *              cross = vA×vB
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     外積
         */
        static VECTOR        Cross(const CVector3& vA, const CVector3& vB);

        static CVector3     Transform(const CVector3& v, const CMatrix& m);

        CVector3            Transform(const CMatrix& m);

        /*!
         *  @brief      代入演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector3& operator=(const CVector3& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;

            return *this;
        }

        /*!
         *  @brief      加算演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector3& operator+=(const CVector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;

            return *this;
        }

        /*!
         *  @brief      減算演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        CVector3& operator-=(const CVector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;

            return *this;
        }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        CVector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        /*!
         *  @brief      等価演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     二つのベクトルが等しい
         *  @retval     true    等しい
         *  @retval     false   等しくない
         */
        bool                operator==(const CVector3& v) const { return (x == v.x && y == v.y && z == v.z); }

        /*!
         *  @brief      不等演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     二つのベクトルが等しくない
         *  @retval     true    等しくない
         *  @retval     false   等しい
         */
        bool                operator!=(const CVector3& v) const { return (x != v.x || y != v.y || z != v.z); }

        /*!
         *  @brief      正符号演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator+(const CVector3& v) { return v; }

        /*!
         *  @brief      負符号演算子のオーバーロード
         *
         *  @param[in]  v   ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator-(const CVector3& v) { return CVector3(-v.x, -v.y, -v.z); }

        /*!
         *  @brief      加算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator+(const CVector3& vA, const CVector3& vB) { return aqua::CVector3(vA.x + vB.x, vA.y + vB.y, vA.z + vB.z); }

        /*!
         *  @brief      減算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator-(const CVector3& vA, const CVector3& vB) { return CVector3(vA.x - vB.x, vA.y - vB.y, vA.z - vB.z); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator*(const CVector3& vA, const CVector3& vB) { return CVector3(vA.x * vB.x, vA.y * vB.y, vA.z * vB.z); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  v       ベクトルクラス
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator*(const CVector3& v, float scalar) { return CVector3(v.x * scalar, v.y * scalar, v.z * scalar); }

        /*!
         *  @brief      乗算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *  @param[in]  v       ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator*(float scalar, const CVector3& v) { return CVector3(v.x * scalar, v.y * scalar, v.z * scalar); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  vA  ベクトルクラス
         *  @param[in]  vB  ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator/(const CVector3& vA, const CVector3& vB) { return CVector3(vA.x / vB.x, vA.y / vB.y, vA.z / vB.z); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  v       ベクトルクラス
         *  @param[in]  scalar  スカラー値
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator/(const CVector3& v, float scalar) { return CVector3(v.x / scalar, v.y / scalar, v.z / scalar); }

        /*!
         *  @brief      除算演算子のオーバーロード
         *
         *  @param[in]  scalar  スカラー値
         *  @param[in]  v       ベクトルクラス
         *
         *  @return     ベクトルクラス
         */
        friend CVector3     operator/(float scalar, const CVector3& v) { return CVector3(scalar / v.x, scalar / v.y, scalar / v.z); }

        /*!
         *  @brief      デバッグログに値を表示する
         */
        void                DebugLog(void);

        //! 成分がすべて0のベクトル
        static const CVector3   ZERO;
        //! 成分がすべて1のベクトル
        static const CVector3   ONE;
    };
}
