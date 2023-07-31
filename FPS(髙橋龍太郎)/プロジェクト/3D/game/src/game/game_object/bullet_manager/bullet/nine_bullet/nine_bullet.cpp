#include "nine_bullet.h"

CNineBullet::CNineBullet(aqua::IGameObject* parent)
	:IBullet(parent, "NineBullet")
{
}

void CNineBullet::Initialize(void)
{
	IBullet::Initialize();

	m_Bullet.Load("data\\ammo\\ammo1.mv1");

	m_Bullet.scale = aqua::CVector3(1.0f, 0.5f, 0.5f);

	//�e�e1��15�_���[�W
	m_DamegeNum = 15;

	//�t���[����T���ʒu���Z�b�g
	m_FlameIndex = m_pGun->m_DummyGun.SearchFrame("Barrel_end_001");
	m_Posotion = m_pGun->m_DummyGun.GetFramePosition(m_FlameIndex);
}