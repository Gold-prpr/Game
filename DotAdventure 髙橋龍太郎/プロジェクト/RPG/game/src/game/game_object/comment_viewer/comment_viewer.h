#pragma once
#include "aqua.h"
#include "../sound_manager/sound_manager.h"

class CSoundManager;

class CComment
	: public aqua::IGameObject
{
public:

	CComment(aqua::IGameObject* parent);
	~CComment() = default;

	void        Initialize(void) override;

	void        Update(void) override;

	void        Draw(void) override;

	void        Finalize(void) override;

	void		ShowText(std::string com);

	void		WaitInput(void);

	void		StepScript(void);

	enum class STATE
	{
		SHOE_TEXT,
		WAIT_INPUT,
	};

	STATE m_State;

	aqua::CLabel m_TextLabel; //��ʂɕ\������e�L�X�g
	std::string  m_NextText; //�e�L�X�g�̎��̕���

private:

	bool m_SoundFlag; //�T�E���h������Ă��邩���f����t���b�O

	std::string m_Byte; //���݂̕���

	aqua::CTimer m_Timer; //�����̗���鑬��

	int m_Start; //�ŏ��̕���

	int m_Next; //�Q�Ƃ��Ă��镶���̍Ō�

	CSoundManager* m_pSound;
};