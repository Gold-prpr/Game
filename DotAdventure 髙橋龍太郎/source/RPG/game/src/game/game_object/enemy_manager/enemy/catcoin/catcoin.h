
#pragma once

#include "../enemy.h"
#include "../../../data/data.h"

class CData;

 class CCatCoin final
	: public IEnemy
{
public:
	CCatCoin(aqua::IGameObject* parent);

	~CCatCoin(void) = default;

	void    Initialize(void) override;

private:
	int m_max_life; ////エネミーのHP

	CData* m_pData;
};
