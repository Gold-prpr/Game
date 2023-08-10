#pragma once
#include "../enemy.h"
#include "../../../data/data.h"

class CData;

class CBossBattle final
	: public IEnemy
{
public:
	CBossBattle(aqua::IGameObject* parent);

	~CBossBattle(void) = default;

	void    Initialize(void) override;

private:
	int m_max_life; //エネミーのHP

	CData* m_pData;
};
