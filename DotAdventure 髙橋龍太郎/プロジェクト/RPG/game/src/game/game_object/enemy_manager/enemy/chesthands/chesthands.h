#pragma once

#include "../enemy.h"
#include "../../../data/data.h"

class CData;

class CChestHands final
	: public IEnemy
{
public:
	CChestHands(aqua::IGameObject* parent);

	~CChestHands(void) = default;

	void    Initialize(void) override;

private:
	int	m_max_life; ////エネミーのHP

	CData* m_pData;
};
