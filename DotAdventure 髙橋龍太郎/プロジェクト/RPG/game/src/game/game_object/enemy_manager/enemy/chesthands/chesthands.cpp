#include "chesthands.h"

CChestHands::
CChestHands(aqua::IGameObject* parent)
	: IEnemy(parent, "ChestHands")
{
}

void
CChestHands::
Initialize(void)
{
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_EnemySprite.Create("data\\ƒ†ƒjƒbƒg\\1475010402.png");

	m_EnemyStatus = { aqua::Rand(50,45),151,134,95,aqua::Rand(105,70) };

	m_pData->SetEnemyHp(m_EnemyStatus.hp);
	m_pData->SetEnemyLv(m_EnemyStatus.level);
	m_pData->SetEnemySpeed(m_EnemyStatus.speed);
	m_pData->SetEnemyStren(m_EnemyStatus.strength);
	m_pData->SetEnemyDefen(m_EnemyStatus.defense);

	IGameObject::Initialize();
}