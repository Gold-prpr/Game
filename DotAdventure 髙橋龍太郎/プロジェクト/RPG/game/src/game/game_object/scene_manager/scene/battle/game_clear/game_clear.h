#pragma once

#include "aqua.h"
#include "../../scene.h"
#include "../../../../animation/animation.h"
#include "../../../scene_manager.h"
#include "../../../../sound_manager/sound_manager.h"
#include "../../../../map/item/item.h"

class CSoundManager;
class CFade;
class CItem;

class CGameClearScene
	: public IScene
{
public:
	CGameClearScene(aqua::IGameObject* parent);

	~CGameClearScene(void) = default;

	void        Initialize(void) override;

	void        Update(void) override;

	void        Draw(void) override;

	void        Finalize(void) override;

private:
	aqua::CSprite m_BackGroundSprite; //背景のスプライト
	aqua::CSprite m_GameClearSprite; //クリアのスプライト
	
	CSoundManager* m_pSound;
	CFade* m_pFade;
	CItem* m_pItem;
};
