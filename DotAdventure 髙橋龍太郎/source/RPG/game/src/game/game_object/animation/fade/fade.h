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
	aqua::CSprite* m_pSprite;	//スプライト
	unsigned char  m_Startfade;	//初期のアルファ値
	unsigned char  m_Endfade;	//最終のアルファ値
	aqua::CTimer m_Timer;		//イージングタイマー

	static const float m_defaulttimer; //スプライト
};