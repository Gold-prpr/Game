#include "enemy_manager.h"
#include "enemy/capsule/capsule.h"

CEnemyManager::CEnemyManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "EnemyManager")
{
}

void CEnemyManager::Initialize(void)
{
	IGameObject::Initialize();
}

void CEnemyManager::Update(void)
{
	IGameObject::Update();
}

void CEnemyManager::Draw(void)
{
	IGameObject::Draw();
}

void CEnemyManager::Finalize(void)
{
	IGameObject::Finalize();
}

void CEnemyManager::Create(ENEMY_ID id)
{
	m_pEnemy = nullptr;

	//セットしたIDのクラスを作成
	switch (id)
	{
	case ENEMY_ID::CAPSULE: m_pEnemy = aqua::CreateGameObject<CCapsule>(this); break;
	}

	if (!m_pEnemy) return;

	m_pEnemy->Initialize();
}