#include "comment_viewer.h"

CComment::CComment(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Comment")
{
}

void CComment::Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");

	m_TextLabel.Create(55);

	m_TextLabel.position.x = 750.0f;
	m_TextLabel.position.y = 750.0f;

	m_Start = 0;

	m_Next = 1;

	m_SoundFlag = false;

	m_Timer.Setup(0.1f);
}

void CComment::Update(void)
{
	switch (m_State)
	{
	case STATE::SHOE_TEXT: ShowText(""); break;
	case STATE::WAIT_INPUT: WaitInput(); break;
	default: break;
	}
}

void CComment::Draw(void)
{
	m_TextLabel.Draw();
}

void CComment::Finalize(void)
{
	m_TextLabel.Delete();
}

void CComment::ShowText(std::string com)
{
	/*
	* １文字目が最後の文字より小さいとき
	* 半角かどうかを判断し
	* テキストに代入する
	* １文字目が最後の文字より大きいとき
	* 引数とフラッグをリセットする
	*/

	m_NextText = com;

	m_Timer.Update();

	if (m_Timer.Finished())
	{
		if (m_Start < m_NextText.size())
		{
			if (IsDBCSLeadByte(m_NextText[m_Start]) == 0)
			{
				if (m_SoundFlag == false)
				{
					m_pSound->Play(SOUND_ID::TALK);
					m_SoundFlag = true;
				}

				m_Next = 1;
				m_Byte = m_NextText.substr(m_Start, m_Next);
				m_TextLabel.text += m_Byte;
			}
			else
			{
				if (m_SoundFlag == false)
				{
					m_pSound->Play(SOUND_ID::TALK);
					m_SoundFlag = true;
				}

				m_Next = 2;
				m_Byte = m_NextText.substr(m_Start, m_Next);
				m_TextLabel.text += m_Byte;
			}

			m_Start += (int)m_Byte.size();
		}
		else
		{
			m_pSound->Stop(SOUND_ID::TALK);

			m_SoundFlag = false;
			com.clear();
			
			m_State = STATE::WAIT_INPUT;
		}

		m_Timer.Reset();
	}
}

void CComment::WaitInput(void)
{
}

void CComment::StepScript(void)
{
	//テキストのリセット
	m_Start = 0;
	m_TextLabel.text.clear();
	m_NextText.clear();
}
