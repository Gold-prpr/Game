#pragma once

#include "aqua.h"
#include "../../scene.h"
#include "../../../../animation/animation.h"
#include "../../../scene_manager.h"
#include "../../../../data/data.h"
#include "../../../../sound_manager/sound_manager.h"
#include "../../../../map/item/item.h"

class CSoundManager;
class CData;
class CItem;

class CGameOverScene
	: public IScene
{
public:
	CGameOverScene(aqua::IGameObject* parent);

	~CGameOverScene(void) = default;

	void        Initialize(void) override;

	void        Update(void) override;

	void        Draw(void) override;

	void        Finalize(void) override;

private:
	aqua::CSprite m_BackGroundSprite; //背景のスプライト
	aqua::CSprite m_GameOverSprite; //ゲームオーバーのスプライト

	CSoundManager* m_pSound;
	CData* m_pData;
	CItem* m_pItem;
};
