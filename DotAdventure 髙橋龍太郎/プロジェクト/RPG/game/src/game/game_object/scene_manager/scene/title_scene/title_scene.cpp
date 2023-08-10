
/*!
 *  @file       title_scene.cpp
 *  @brief      タイトルシーン
 *  @author     Kazuya Maruyama
 *  @date       2021/05/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "title_scene.h"
#include "..\..\scene_manager.h"
#include "../../../map/item/item.h"
#include "../../../map/map.h"

/*
 *  コンストラクタ
 */
CTitleScene::
CTitleScene(aqua::IGameObject* parent)
	: IScene(parent, "TitleScene")
{
}

void
CTitleScene::
Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_pFade = (CFade*)aqua::CreateGameObject<CFade>(this);
	//CCharacterManager* cm = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	//m_pChara = (CCharacter*)aqua::FindGameObject("Character");
	//m_pInve = (CInventory*)aqua::FindGameObject("Inventory");

	m_pSound->Play(SOUND_ID::MAINOP);

	//２週目用にキャラの位置とアイテムの所持をリセット
	//cm->Initialize();
	//m_pChara->Initialize();
	//m_pInve->ResetNum();

	m_Timer.Setup(5.0f);

	m_BackgourndSprite.Create("data\\タイトル\\無題.png");
	m_BackgourndSprite.position = aqua::CVector2::ZERO;

	m_Title.Create("data\\タイトル\\タイトル本体.png");
	m_Title.position = aqua::CVector2(200, -500);
	  
	m_TitleShadow.Create("data\\タイトル\\タイトル影.png");
	m_TitleShadow.position = aqua::CVector2(200, 200);
	m_TitleShadow.color.alpha = 0x00;

	m_Sword.Create("data\\タイトル\\剣.png");
	m_Sword.position = aqua::CVector2(300, 200);
	m_Sword.anchor = aqua::CVector2(m_Sword.GetTextureWidth() / 2.0f, (float)m_Sword.GetTextureHeight());
	m_Sword.rotation = -0.4f;
	  
	m_Staff.Create("data\\タイトル\\杖.png");
	m_Staff.position = aqua::CVector2(aqua::GetWindowWidth() - (float)m_Staff.GetTextureWidth() - 300, 200);
	m_Staff.anchor = aqua::CVector2((float)m_Staff.GetTextureWidth() / 2.0f, (float)m_Staff.GetTextureHeight());
	m_Staff.rotation = 0.4f;

	m_Start.Create(60);
	m_Start.text = "はじめる";
	m_Start.position = aqua::CVector2(((float)(aqua::GetWindowWidth() - m_Start.GetTextWidth()) / 2), (float)700);

	m_Serect.Create("data\\arrow-145781__480.png");
	m_Serect.position = aqua::CVector2(m_Start.position.x - m_Serect.GetTextureWidth(), m_Start.position.y);
	m_Serect.anchor = aqua::CVector2(m_Serect.GetTextureWidth() / 2.0f, m_Serect.GetTextureHeight() / 2.0f);
	m_Serect.scale.y = 1;

	m_CheckTitle = false;

	IGameObject::Initialize();
}

void
CTitleScene::
Update(void)
{
	m_Timer.Update();

	if (m_Timer.GetTime() >= 0.0f && m_CheckTitle == false)
	{
		if (m_Title.position.y <= 195.0f)
		{
			m_Title.position.y += 5.0f;
		}
		else
		{
			m_CheckTitle = true;
		}
	}
	if (m_Timer.GetTime() >= 3.0f && m_CheckTitle == true)
	{
		if (m_Title.position.x >= 200.0f - 20.0f)
		{
			m_Title.position.x -= 0.95f;
			m_Title.position.y -= 0.95f;

			m_pFade->Initialize(&m_TitleShadow, 0x00, 0xff);
		}
	}
	if (m_Timer.GetTime() >= 4.5f)
	{
		Flame += 2.0f;
		m_Serect.scale.y = sin(Flame * DX_PI_F / 90.0f);

		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER))
		{
			m_pSound->Play(SOUND_ID::ENTER);
			m_Timer.Reset();
			m_pSound->Stop(SOUND_ID::MAINOP);
			Change(SCENE_ID::GAMEMAIN);
		}
	}

	IGameObject::Update();
}

void
CTitleScene::
Draw(void)
{
	m_BackgourndSprite.Draw();

	m_Start.Draw();
	m_Serect.Draw();
	m_Staff.Draw();
	m_TitleShadow.Draw();
	m_Sword.Draw();
	m_Title.Draw();

	IGameObject::Draw();
}

void
CTitleScene::
Finalize(void)
{
	m_BackgourndSprite.Delete();

	m_Title.Delete();
	m_TitleShadow.Delete();
	m_Start.Delete();
	m_Serect.Delete();
	m_Sword.Delete();
	m_Staff.Delete();

	IGameObject::Finalize();
}