
/*!
 *  @file       title_scene.h
 *  @brief      タイトルシーン
 *  @author     Kazuya Maruyama
 *  @date       2021/05/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "..\scene.h"
#include "../../../animation/animation.h"
#include "../../../character/character.h"
#include "../../../map/map.h"
#include "../../../map/item/item.h"
#include "../../../data/data.h"
#include "../../../character_manager/character_manager.h"
#include "../../../Inventory/Inventory.h"
#include "../../../sound_manager/sound_manager.h"

class CSoundManager;
class CFade;
class CCharacter;
class CStage;
class CItem;
class CData;
class CInventory;

class CTitleScene
    : public IScene
{
public:
    CTitleScene(aqua::IGameObject* parent);

    ~CTitleScene(void) = default;

    void        Initialize(void) override;

    void        Update(void) override;

    void        Draw(void) override;

    void        Finalize(void) override;

private:
    aqua::CSprite m_BackgourndSprite; //背景のスプライト
	
	aqua::CSprite m_Title; //タイトルのスプライト
	bool m_CheckTitle; //タイトルの動きを判断するフラッグ

	aqua::CSprite m_TitleShadow; //タイトルの影のスプライト
	bool m_CheckTitleShadow; //タイトルの影の動きを判断するフラッグ

	aqua::CSprite m_Sword; //剣のスプライト
	bool m_CheckSword; //剣の動きを判断するフラッグ
	
	aqua::CSprite m_Staff; //杖のスプライト
	bool m_CheckStaff; //杖の動きを判断するフラッグ

	aqua::CLabel m_Start; //はじめるのラベル

	aqua::CSprite m_Serect; //矢印のスプライト
	float Flame = 0; //矢印の回転に使うイージングのフレーム

	bool m_ShadowAlpha; //影のアルファ値

    aqua::CTimer m_Timer; //背景が動く時間

    CSoundManager* m_pSound;
	CFade* m_pFade;
    CCharacter* m_pChara;
    CStage* m_pStage;
    CItem* m_pItem;
    CData* m_pData;
    CInventory* m_pInve;
};
