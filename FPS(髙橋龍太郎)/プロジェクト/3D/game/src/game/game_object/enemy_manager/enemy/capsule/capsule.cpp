#include "capsule.h"

CCapsule::CCapsule(aqua::IGameObject* parent)
	:IEnemy(parent, "Capsule")
{
}

void CCapsule::Initialize(void)
{
	m_pStage = (CStage*)aqua::FindGameObject("Stage");
	m_pGameMain = (CGameMainScene*)aqua::FindGameObject("GameMainScene");

	m_Enemy.Load("data\\character\\enemy.mv1");

	m_Position = aqua::CVector3((float)aqua::Rand(4800, -4800), 150.0f, (float)aqua::Rand(4800, -4800));
	m_Scale = aqua::CVector3::ONE;
	m_Rotation = aqua::CVector3(0.0f, (float)aqua::Rand(10, 0), 0.0f);

	m_EnemyHp = 150;

	m_EnemyColl.SetUpColl(m_Enemy.GetResourceHandle(), -1, 1, 1, 1);

	IEnemy::Initialize();
}

void CCapsule::Update(void)
{
	m_EnemyColl.UpdateColl();

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::MAIN ||
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::FREETIME)
	{
		//¶‰E‚É“®‚­ˆ—
		if (m_TurnFlag == false)
		{
			m_Vec.x += 1.0f;

			m_Position.x += 8.0f;

			if (m_Vec.x >= 200.0f)
			{
				m_TurnFlag = true;
				m_Vec = aqua::CVector3::ZERO;
			}
		}
		else if (m_TurnFlag == true)
		{
			m_Vec.x -= 1.0f;

			m_Position.x -= 8.0f;

			if (m_Vec.x <= -200.0f)
			{
				m_TurnFlag = false;
				m_Vec = aqua::CVector3::ZERO;
			}
		}
	}

	IEnemy::Update();
}
