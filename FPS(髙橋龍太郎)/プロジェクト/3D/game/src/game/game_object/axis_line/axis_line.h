#pragma once
#include "aqua.h"
#include <DxLib.h>

class CAxisLine
    :public aqua::IGameObject
{
public:
    CAxisLine(IGameObject* parent);
    ~CAxisLine(void) = default;

    void        Initialize(void) override;

    void        Draw(void) override;
private:

    aqua::CVector3  m_Position_Start;

    aqua::CVector3  m_Position_Goal_X;

    aqua::CVector3  m_Position_Goal_Y;

    aqua::CVector3  m_Position_Goal_Z;

    aqua::CColor    m_Color;

    VECTOR c;
};