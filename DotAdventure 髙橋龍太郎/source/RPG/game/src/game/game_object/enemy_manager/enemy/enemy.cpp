#include "enemy.h"
#include "catcoin/catcoin.h"
#include "reddemon/reddemon.h"
#include "chesthands/chesthands.h"

IEnemy::
IEnemy(aqua::IGameObject* parent, const std::string& name)
	:aqua::IGameObject(parent, name, "EnemyUnit")
{
}

void IEnemy::Initialize(void)
{
	IGameObject::Initialize();
}

void IEnemy::Update(void)
{
	 m_EnemySprite.position = 
		 aqua::CVector2((aqua::GetWindowWidth() / 2.0f - m_EnemySprite.GetTextureWidth() / 2.0f), 30);

	 IGameObject::Update();
}

void IEnemy::Draw(void)
{
	m_EnemySprite.Draw();

	IGameObject::Draw();
}

void IEnemy::Finalize(void)
{
	m_EnemySprite.Delete();

	IGameObject::Finalize();
}
