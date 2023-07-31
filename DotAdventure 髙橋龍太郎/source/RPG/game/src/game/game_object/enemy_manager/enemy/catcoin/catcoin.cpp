#include "catcoin.h"

CCatCoin::
CCatCoin(aqua::IGameObject* parent)
	: IEnemy(parent, "CatCoin")
{
}

void
CCatCoin::
Initialize(void)
{
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_EnemySprite.Create("data\\ƒ†ƒjƒbƒg\\1538020401.png");

	m_EnemyStatus = { aqua::Rand(45,30),121,134,95,aqua::Rand(105,70) };

	m_pData->SetEnemyHp(m_EnemyStatus.hp);
	m_pData->SetEnemyLv(m_EnemyStatus.level);
	m_pData->SetEnemySpeed(m_EnemyStatus.speed);
	m_pData->SetEnemyStren(m_EnemyStatus.strength);
	m_pData->SetEnemyDefen(m_EnemyStatus.defense);

	IGameObject::Initialize();
}