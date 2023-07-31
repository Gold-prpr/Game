#pragma once
#include "aqua.h"
#include "../character/character.h"
#include "../map/map.h"
#include "../map/item/item.h"
#include "../data/data.h"

class CCharacter;
class CStage;
class CItem;
class CData;

class CScroll
	:public aqua::IGameObject
{
public:
	CScroll(aqua::IGameObject* parent);
	~CScroll() = default;
		
	void Initialize(void);

	void Update(void);

	aqua::CVector2 GetScroll();

private:
	aqua::CVector2 m_CharaPos; //キャラのポジション
	aqua::CVector2 m_Scroll; //スクロールの移動量

	CCharacter* m_pChara;
	CStage* m_pStage;
	CItem* m_pItem;
	CData* m_pData;
};