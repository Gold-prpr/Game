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

	aqua::CLabel m_TextLabel; //画面に表示するテキスト
	std::string  m_NextText; //テキストの次の文字

private:

	bool m_SoundFlag; //サウンドが流れているか判断するフラッグ

	std::string m_Byte; //現在の文字

	aqua::CTimer m_Timer; //文字の流れる速さ

	int m_Start; //最初の文字

	int m_Next; //参照している文字の最後

	CSoundManager* m_pSound;
};