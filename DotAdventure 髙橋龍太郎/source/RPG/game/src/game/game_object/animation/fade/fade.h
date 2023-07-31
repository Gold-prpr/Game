#pragma once
#include"aqua.h"

class CFade : public aqua::IGameObject
{
public:
	CFade(aqua::IGameObject* parent);
	~CFade() = default;

	void Initialize(aqua::CSprite* sprite, unsigned char  start, unsigned char  end);

	void Update(void);

private:
	aqua::CSprite* m_pSprite;	//�X�v���C�g
	unsigned char  m_Startfade;	//�����̃A���t�@�l
	unsigned char  m_Endfade;	//�ŏI�̃A���t�@�l
	aqua::CTimer m_Timer;		//�C�[�W���O�^�C�}�[

	static const float m_defaulttimer; //�X�v���C�g
};