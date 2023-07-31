#pragma once

#include "aqua.h"
#include "..\scene.h"
#include "../../../character/character.h"
#include "../../../data/data.h"
#include "../../../map/map.h"
#include "../../../enemy_manager/enemy/boss/boss.h"
#include "../../../map/item/item.h"
#include "../../../scroll/scroll.h"
#include "../../../Inventory/Inventory.h"
#include "../../../sound_manager/sound_manager.h"

class CSoundManager;
class CCharacter;
class CData;
class CStage;
class CBoss;
class CItem;
class CScroll;
class CInventory;

class CGameMainScene
	: public IScene
{
public:
	
	CGameMainScene(aqua::IGameObject* parent);

	~CGameMainScene(void) = default;

	void Initialize(void) override;

	void Update(void) override;
		 
	void Draw(void) override;
		 
	void Finalize(void) override;

private:
	
	enum class STATE
	{
		START,
		PLAY,
	};

	STATE   m_State;

	CSoundManager* m_pSound;
	CCharacter* m_pChara;
	CData* m_pData;
	CStage* m_pStage;
	CBoss* m_pBoss;
	CItem* m_pItem;
	CScroll* m_pScroll;
	CInventory* m_pInve;
}; 