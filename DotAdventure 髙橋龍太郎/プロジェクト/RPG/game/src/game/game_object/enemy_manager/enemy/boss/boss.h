#pragma once
#include "aqua.h"
#include "../../../character/character.h"
#include "../../../scroll/scroll.h"
#include "../../../Inventory/Inventory.h"

class CInventory;
class CData;
class CCharacter;
class CScroll;

class CBoss
	: public aqua::IGameObject
{
public:

	CBoss(aqua::IGameObject* parent);
	~CBoss() = default;

	void Initialize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

	aqua::CAnimationSprite m_Boss; //ボスのスプライト

private:
	static const int m_boss_width; //ボスの幅
	static const int m_boss_height; //ボスの高さ

	aqua::CVector2 m_ScrollCamera; //スクロールの移動量

	aqua::CVector2 m_BossPos; //ボースの位置

	CInventory* m_pInve;
	CCharacter* m_pChara;
	CScroll* m_pScroll;
	CData* m_pData;
};