
/*!
 *  @file       game.cpp
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"
#include "game_object/game_object.h"
#include "game_object/sound_manager/sound_manager.h"
#include "game_object/enemy_manager/enemy/enemy.h"

const unsigned int CGame::m_clear_color = 0xff000000;

/*
 *  コンストラクタ
 */
CGame::
CGame(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Game")
{
}

/*
 *  初期化
 */
void
CGame::
Initialize(void)
{
	aqua::CreateGameObject<CSoundManager>(this);

	aqua::CreateGameObject<CData>(this);

	aqua::CreateGameObject<CStage>(this);

	aqua::CreateGameObject<CItem>(this);

	aqua::CreateGameObject<CInventory>(this);

	aqua::CreateGameObject<CScroll>(this);

	aqua::CreateGameObject<CSceneManager>(this);

	aqua::CreateGameObject<CCharacterManager>(this);

	IGameObject::Initialize();
}

/*
 *  描画
 */
void
CGame::
Draw(void)
{
	// 画面のクリア
	aqua::Clear(m_clear_color);

	// 描画したいオブジェクト群
	IGameObject::Draw();
}