
/*!
 *  @file       scene.cpp
 *  @brief      シーン
 *  @author     Kazuya Maruyama
 *  @date       2021/05/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "scene.h"
#include "..\scene_manager.h"

const std::string   IScene::m_scene_category = "Scene";

/*
 *  コンストラクタ
 */
IScene::
IScene(aqua::IGameObject* parent, const std::string& object_name)
    : aqua::IGameObject(parent, object_name, m_scene_category)
{
}

/*
 *  シーンの変更
 */
void
IScene::
Change(SCENE_ID id)
{
    CSceneManager* sm = (CSceneManager*)GetParent();

    sm->Change(id);
}

/*
 *  シーンをスタックする
 */
void
IScene::
Push(SCENE_ID id)
{
    CSceneManager* sm = (CSceneManager*)GetParent();

    sm->Push(id);
}

/*
 *  スタックされたシーンを取り出す
 */
void
IScene::
Pop(void)
{
    CSceneManager* sm = (CSceneManager*)GetParent();

    sm->Pop();
}

/*
 *  シーンをリセットする
 */
void
IScene::
Reset(void)
{
    CSceneManager* sm = (CSceneManager*)GetParent();

    sm->Reset();
}
