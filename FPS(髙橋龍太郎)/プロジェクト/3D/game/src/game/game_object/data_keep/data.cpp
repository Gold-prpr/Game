#include "data.h"

CData::CData(aqua::IGameObject* parent)
	:IGameObject(parent, "Data")
{
}

void CData::Initialize(void)
{
	m_Pos = aqua::CVector3::ZERO;
}

void CData::SetPos(const aqua::CVector3& pos)
{
	m_Pos = pos;
}

aqua::CVector3 CData::GetPos()
{
	return m_Pos;
}
