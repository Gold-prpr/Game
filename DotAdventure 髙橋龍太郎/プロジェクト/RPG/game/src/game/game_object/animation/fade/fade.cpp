#include"fade.h"

const float CFade::m_defaulttimer = 2.0f;

CFade::CFade(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Fade")
	, m_pSprite(nullptr)
	, m_Startfade(0x00)
	, m_Endfade(0xff)
{
}

void CFade::Initialize(aqua::CSprite* sprite, unsigned char start, unsigned char end)
{
	if (sprite == nullptr)
	{
		DeleteObject();
		return;
	}
	m_pSprite = sprite;
	m_Startfade = start;
	m_Endfade = end;

	m_Timer.Setup(m_defaulttimer);
}

void CFade::Update(void)
{
	if (m_pSprite == nullptr)return;

	m_Timer.Update();

	//イージングを使用したアルファ値の変化
	unsigned char direction = m_Endfade - m_Startfade;
	m_pSprite->color.alpha = (unsigned char)(m_Startfade + direction * aqua::easing::OutQuart(m_Timer.GetTime(), m_Timer.GetLimit()));

	//タイマーが終了したら消す
	if (m_Timer.Finished())
	{
		DeleteObject();
	}
}
