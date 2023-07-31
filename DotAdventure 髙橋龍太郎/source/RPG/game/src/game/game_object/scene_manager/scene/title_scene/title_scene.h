
/*!
 *  @file       title_scene.h
 *  @brief      �^�C�g���V�[��
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
    aqua::CSprite m_BackgourndSprite; //�w�i�̃X�v���C�g
	
	aqua::CSprite m_Title; //�^�C�g���̃X�v���C�g
	bool m_CheckTitle; //�^�C�g���̓����𔻒f����t���b�O

	aqua::CSprite m_TitleShadow; //�^�C�g���̉e�̃X�v���C�g
	bool m_CheckTitleShadow; //�^�C�g���̉e�̓����𔻒f����t���b�O

	aqua::CSprite m_Sword; //���̃X�v���C�g
	bool m_CheckSword; //���̓����𔻒f����t���b�O
	
	aqua::CSprite m_Staff; //��̃X�v���C�g
	bool m_CheckStaff; //��̓����𔻒f����t���b�O

	aqua::CLabel m_Start; //�͂��߂�̃��x��

	aqua::CSprite m_Serect; //���̃X�v���C�g
	float Flame = 0; //���̉�]�Ɏg���C�[�W���O�̃t���[��

	bool m_ShadowAlpha; //�e�̃A���t�@�l

    aqua::CTimer m_Timer; //�w�i����������

    CSoundManager* m_pSound;
	CFade* m_pFade;
    CCharacter* m_pChara;
    CStage* m_pStage;
    CItem* m_pItem;
    CData* m_pData;
    CInventory* m_pInve;
};
