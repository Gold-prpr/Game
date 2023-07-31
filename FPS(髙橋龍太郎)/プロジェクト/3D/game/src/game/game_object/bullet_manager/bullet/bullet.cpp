#include "bullet.h"

IBullet::IBullet(aqua::IGameObject* parent, const std::string& name)
{
}

void IBullet::Initialize(void)
{
	m_pGun = (CGun*)aqua::FindGameObject("Gun");
	m_pEnemy = (IEnemy*)aqua::FindGameObject("Enemy");

	m_DamegeNum = 0;

	m_FireCheck = false;

	m_BulletColl.SetUpColl(m_Bullet.GetResourceHandle(), -1, 1, 1, 1);

	IGameObject::Initialize();
}

void IBullet::Update(void)
{
	m_BulletColl.UpdateColl();

	m_Posotion += m_pGun->m_BulletVec;
	m_Rotation = m_pGun->m_BulletRot;

	m_Bullet.position = m_Posotion;
	m_Bullet.rotation = m_Rotation;

	//�e�e�����݂��Ă���Ƃ��ɓ����蔻��
	if (m_Bullet.IsEnable() == true)
		EnemyColl();
	
	IGameObject::Update();
}

void IBullet::Draw(void)
{
	m_Bullet.Draw();

	IGameObject::Draw();
}

void IBullet::Finalize(void)
{
	m_Bullet.Unload();

	m_BulletColl.TerminateColl();

	IGameObject::Finalize();
}

void IBullet::EnemyColl(void)
{
	aqua::CVector3 bulletStart(m_Bullet.position.x, m_Bullet.position.y + 5.0f, m_Bullet.position.z);
	aqua::CVector3 bulletEnd = bulletStart + m_pGun->m_BulletVec;

	//���C�����΂��m�F
	if (m_pEnemy->CheckCollEnemy(bulletStart, bulletEnd) == true)
	{
		//���������ꏊ�ɌŒ�
		m_Posotion = m_pEnemy->GetHitPos();

		//1�������ł�
		if (m_FireCheck == false)
		{
			m_pEnemy->m_EnemyHp -= m_DamegeNum;

			m_FireCheck = true;
		}

		//���f���폜
		m_Bullet.Unload();
	}
}