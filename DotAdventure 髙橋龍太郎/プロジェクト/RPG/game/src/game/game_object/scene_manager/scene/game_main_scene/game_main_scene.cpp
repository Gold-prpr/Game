
/*!
*  @file       game_main_scene.cpp
*  @brief      ゲームメインシーン
*  @author     Kazuya Maruyama
*  @date       2021/05/20
*  @version    1.0
*
*  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
*/

#include "game_main_scene.h"
#include "..\..\..\game_object.h"
#include "../../../character_manager/character_manager.h"

/*
 *  コンストラクタ
 */
CGameMainScene::
CGameMainScene(aqua::IGameObject* parent)
	: IScene(parent, "GameMainScene")
{
}

/*
 *  初期化
 */
void
CGameMainScene::
Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	CCharacterManager* cm = (CCharacterManager*)aqua::FindGameObject("CharacterManager");
	m_pData = (CData*)aqua::FindGameObject("Data");
	m_pBoss = (CBoss*)aqua::CreateGameObject<CBoss>(this);
	
	m_pSound->Play(SOUND_ID::FIELDBGM);

	m_pData->GetBossFlag();

	//保存したキャラクターの位置を取得
	m_pChara = cm->GetCharacter();

	//キャラクターのエンカウント値をリセット
	m_pChara->EncountReset();

	IGameObject::Initialize();
}

/*
 *  更新
 */
void
CGameMainScene::
Update(void)
{
	m_pBoss->Update();
	
	if (m_pChara)
	{
		m_pChara->Update();

		/*
		* エンカウント値の変化と
		* ボスフラッグがtrueになったらエンカウント
		* ※ボスフラッグはcharacter.cppの最後で判断
		*/
		if (m_pChara->IsEncount() || m_pData->GetBossFlag() == true)
		{
			m_pSound->Stop(SOUND_ID::FIELDBGM);
			m_pChara->StopWalkSound();

			Change(SCENE_ID::BATTLE);
		}
	}

	IGameObject::Update();
}

void CGameMainScene::Draw(void)
{
	m_pBoss->Draw();
	m_pChara->Draw();

	IGameObject::Draw();
}

void CGameMainScene::Finalize(void)
{
	IGameObject::Finalize();
}
