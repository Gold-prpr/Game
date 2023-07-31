
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
	IGameObject::Initialize();
}

void
CTitleScene::
Update(void)
{
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::NUMPADENTER) && 
		aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT))
	{
		Change(SCENE_ID::GAMEMAIN);
	}

	IGameObject::Update();
}

void
CTitleScene::
Draw(void)
{
	IGameObject::Draw();
}

void
CTitleScene::
Finalize(void)
{
	IGameObject::Finalize();
}