#include "enemy_manager.h"
#include "enemy/catcoin/catcoin.h"
#include "enemy/reddemon/reddemon.h"
#include "enemy/chesthands/chesthands.h"
#include "enemy/boss/boss.h"
#include "game/game_object/enemy_manager/enemy/bossbattle/bossbattle.h"


CEnemyManager::
CEnemyManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "EnemyManager")
{
}

void
CEnemyManager::
Initialize(void)
{
	IGameObject::Initialize();
}

void
CEnemyManager::
Update(void)
{
	IGameObject::Update();
}

void
CEnemyManager::
Draw(void)
{
	IGameObject::Draw();
}

void
CEnemyManager::
Finalize(void)
{
	IGameObject::Finalize();
}

void
CEnemyManager::
Create(ENEMY_ID id)
{
	//エネミーの生成
	IGameObject* enemy = nullptr;

	switch (id)
	{
	case ENEMY_ID::REDDEMON:	enemy = aqua::CreateGameObject<CRedDemon>(this);		break;
	case ENEMY_ID::CATCOIN:		enemy = aqua::CreateGameObject<CCatCoin>(this);			break;
	case ENEMY_ID::CHESTHANDS:	enemy = aqua::CreateGameObject<CChestHands>(this);		break;
	case ENEMY_ID::BOSS:		enemy = aqua::CreateGameObject<CBossBattle>(this);		break;
	}

	if (!enemy) return;

	enemy->Initialize();
}