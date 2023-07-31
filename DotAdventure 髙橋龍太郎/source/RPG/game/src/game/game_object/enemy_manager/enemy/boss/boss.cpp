#include "boss.h"

const int CBoss::m_boss_width = 80;
const int CBoss::m_boss_height = 80;

CBoss::CBoss(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Boss")
	, m_ScrollCamera(0,0)
{
}

void CBoss::Initialize(void)
{
	m_pInve = (CInventory*)aqua::FindGameObject("Inventory");
	m_pScroll = (CScroll*)aqua::FindGameObject("Scroll");
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_Boss.Create("data\\���j�b�g\\�{�X.ass", "down");

	m_BossPos = aqua::CVector2(3360.0f, 1520.0f);

	IGameObject::Initialize();
}

void CBoss::Update(void)
{
	m_Boss.position = m_BossPos;

	//�C���x���g���[��ʂ��o�Ă���Ɠ����Ȃ�����
	if (m_pInve->m_BsFlag == false)
		m_Boss.Update();

	IGameObject::Update();
}

void CBoss::Draw(void)
{
	//�X�N���[�����������l���{�X�̈ʒu�ɂ���
	m_ScrollCamera = m_BossPos - m_pScroll->GetScroll();
	m_Boss.position = m_ScrollCamera;

	m_Boss.Draw();

	IGameObject::Draw();
}

void CBoss::Finalize(void)
{
	m_Boss.Delete();

	IGameObject::Finalize();
}