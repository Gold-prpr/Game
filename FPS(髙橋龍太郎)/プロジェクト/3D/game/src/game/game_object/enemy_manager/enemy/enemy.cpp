#include "enemy.h"

IEnemy::IEnemy(aqua::IGameObject* parent, const std::string& name)
	:aqua::IGameObject(parent, "Enemy")
{
}

void IEnemy::Initialize(void)
{
	m_Vec = aqua::CVector3::ZERO;

	m_TurnFlag = false;

	IGameObject::Initialize();
}

void IEnemy::Update(void)
{
	m_Enemy.position = m_Position;
	m_Enemy.scale = m_Scale;
	m_Enemy.rotation = m_Rotation;

	IGameObject::Update();
}

void IEnemy::Draw(void)
{
	m_Enemy.Draw();

	IGameObject::Draw();
}

void IEnemy::Finalize(void)
{
	m_Enemy.Unload();

	m_EnemyColl.TerminateColl();

	IGameObject::Finalize();
}

bool IEnemy::CheckCollEnemy(const aqua::CVector3& start_pos, const aqua::CVector3& end_pos)
{
	m_HitPolygon = m_EnemyColl.CollCheckLine(start_pos, end_pos);

	return m_HitPolygon.HitFlag;
}

aqua::CVector3 IEnemy::GetHitPos(void)
{
	return m_HitPolygon.HitPosition;
}

bool IEnemy::CheckLife(void)
{
	if (m_EnemyHp <= 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
