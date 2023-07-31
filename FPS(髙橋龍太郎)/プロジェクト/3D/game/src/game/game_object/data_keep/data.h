#pragma once
#include "aqua.h"

class CData
	:public aqua::IGameObject
{
public:
	CData(aqua::IGameObject* parent);
	~CData(void) = default;

	void Initialize(void) override;

	void SetPos(const aqua::CVector3& pos);

	aqua::CVector3 GetPos();

private:

	aqua::CVector3 m_Pos;//ˆÊ’u
};
