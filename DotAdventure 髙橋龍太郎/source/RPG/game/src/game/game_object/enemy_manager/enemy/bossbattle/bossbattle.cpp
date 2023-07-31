#include "bossbattle.h"

CBossBattle::CBossBattle(aqua::IGameObject* parent)
	: IEnemy(parent, "BossBattle")
{
}

void CBossBattle::Initialize(void)
{
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_EnemySprite.Create("data\\ƒ†ƒjƒbƒg\\1429010402.png");

	m_EnemyStatus = { aqua::Rand(60,50),280,104,130,aqua::Rand(105,90) };

	m_pData->SetEnemyHp(m_EnemyStatus.hp);
	m_pData->SetEnemyLv(m_EnemyStatus.level);
	m_pData->SetEnemySpeed(m_EnemyStatus.speed);
	m_pData->SetEnemyStren(m_EnemyStatus.strength);
	m_pData->SetEnemyDefen(m_EnemyStatus.defense);

	IGameObject::Initialize();
}