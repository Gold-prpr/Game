#include "reddemon.h"

CRedDemon::
CRedDemon(aqua::IGameObject* parent)
	: IEnemy(parent, "RedDemon")
{
}

void
CRedDemon::
Initialize(void)
{
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_EnemySprite.Create("data\\ƒ†ƒjƒbƒg\\1517010402.png");

	m_EnemyStatus = { aqua::Rand(30,25),120,70,110,aqua::Rand(105,80) };

	m_pData->SetEnemyHp(m_EnemyStatus.hp);
	m_pData->SetEnemyLv(m_EnemyStatus.level);
	m_pData->SetEnemySpeed(m_EnemyStatus.speed);
	m_pData->SetEnemyStren(m_EnemyStatus.strength);
	m_pData->SetEnemyDefen(m_EnemyStatus.defense);
	
	IGameObject::Initialize();
}