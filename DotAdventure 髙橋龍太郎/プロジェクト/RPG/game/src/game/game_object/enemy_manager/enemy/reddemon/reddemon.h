#pragma once

#include "../enemy.h"
#include "../../../data/data.h"

class CData;

class CRedDemon final
	: public IEnemy
{
public:
	CRedDemon(aqua::IGameObject* parent);

	~CRedDemon(void) = default;

	void    Initialize(void) override;

private:
	int	m_max_life; ////エネミーのHP

	CData* m_pData;
};
