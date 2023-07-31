#include "axis_line.h"

CAxisLine::CAxisLine(IGameObject* parent)
	:IGameObject(parent, "AxisLine")
{
}

void CAxisLine::Initialize(void)
{
	m_Position_Start = aqua::CVector3(0.0f, 60.0f, 0.0f);

	m_Position_Goal_X = aqua::CVector3(1000.0f, 60.0f, 0.0f);
	m_Position_Goal_Y = aqua::CVector3(0.0f, 1000.0f, 0.0f);
	m_Position_Goal_Z = aqua::CVector3(0.0f, 60.0f, 1000.0f);

	m_Color = aqua::CColor::RED;

	IGameObject::Initialize();
}

void CAxisLine::Draw(void)
{
	DrawLine3D(m_Position_Start, m_Position_Goal_X, 0xffff0000);	// X
	DrawLine3D(m_Position_Start, m_Position_Goal_Y, 0xff00ff00);	// Y
	DrawLine3D(m_Position_Start, m_Position_Goal_Z, 0xff0000ff);	// Z

	IGameObject::Draw();
}