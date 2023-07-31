#include "scroll.h"

CScroll::CScroll(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Scroll")
{
}

void CScroll::Initialize(void)
{
	m_pData = (CData*)aqua::FindGameObject("Data");
	m_pChara = (CCharacter*)aqua::FindGameObject("Character");
	m_pStage = (CStage*)aqua::FindGameObject("Map");
	m_pItem = (CItem*)aqua::FindGameObject("Item");

	m_CharaPos = aqua::CVector2::ZERO;
	m_Scroll = aqua::CVector2::ZERO;
}

void CScroll::Update(void)
{
	m_CharaPos = aqua::CVector2(m_pData->GetCharaPos().x, m_pData->GetCharaPos().y);

	int lx = aqua::GetWindowWidth() / 2;
	int ly = aqua::GetWindowHeight() / 2;
	int rx = m_pStage->GetChipCountX() * m_pStage->GetChipSize() - lx;
	int ry = m_pStage->GetChipCountY() * m_pStage->GetChipSize() - ly;

	// 左右スクロール
	if (m_CharaPos.x > lx && m_CharaPos.x < rx)
		m_Scroll.x = m_CharaPos.x - lx;
	else if (m_CharaPos.x < lx)
		m_Scroll.x = 0.0f;
	else if (m_CharaPos.x > rx)
		m_Scroll.x = (float)(m_pStage->GetChipCountX() * m_pStage->GetChipSize() - aqua::GetWindowWidth());

	// 上下スクロール
	if (m_CharaPos.y > ly && m_CharaPos.y < ry)
		m_Scroll.y = m_CharaPos.y - ly;
	else if (m_CharaPos.y < ly)
		m_Scroll.y = 0.0f;
	else if (m_CharaPos.y > ry)
		m_Scroll.y = (float)(m_pStage->GetChipCountY() * m_pStage->GetChipSize() - aqua::GetWindowHeight());
}

aqua::CVector2 CScroll::GetScroll()
{
	return aqua::CVector2(m_Scroll.x, m_Scroll.y);
}
