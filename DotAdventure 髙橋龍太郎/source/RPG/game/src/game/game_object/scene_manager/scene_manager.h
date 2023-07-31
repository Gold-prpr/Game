
/*!
 *  @file       scene_manager.h
 *  @brief      シーン管理
 *  @author     Kazuya Maruyama
 *  @date       2021/05/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"
#include "scene\scene_id.h"

 /*!
  *  @class      CSceneManager
  *
  *  @brief      シーン管理クラス
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2021/05/20
  *
  *  @version    1.0
  */
class CSceneManager
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親オブジェクト
     */
    CSceneManager(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CSceneManager(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(void) override;

    /*!
     *  @brief      更新
     */
    void        Update(void) override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*!
     *  @brief      シーンの変更
     *
     *  @param[in]  id  シーンID
     */
    void        Change(SCENE_ID id);

    /*!
     *  @brief      シーンをスタックする
     *
     *  @param[in]  id  シーンID
     */
    void        Push(SCENE_ID id);

    /*!
     *  @brief      スタックしたシーンを取り出す
     */
    void        Pop(void);

    /*!
     *  @brief      現在のシーンをリセットする
     */
    void        Reset(void);

private:
    /*!
     *  @brief      状態ID
     */
    enum class STATE
    {
        SCENE_IN,
        SCENE_UPDATA,
        SCENE_OUT,
        SCENE_CHANGE,
    };

    /*!
     *  @brief      シーンの生成
     *
     *  @param[in]  id  シーンID
     */
    void        Create(SCENE_ID id);

    /*!
     *  @brief      現在のシーンを削除
     */
    void        Delete(void);

    /*!
     *  @brief      シーン開始演出
     */
    void        SceneIn(void);

    /*!
     *  @brief      シーン更新
     */
    void        SceneUpdate(void);

    /*!
     *  @brief      シーン終了演出
     */
    void        SceneOut(void);

    /*!
     *  @brief      シーン変更
     */
    void        SceneChange(void);

    static const float      m_fade_speed;
    SCENE_ID                m_CurrentSceneID;
    SCENE_ID                m_NextSceneID;
    SCENE_ID                m_PushSceneID;
    STATE                   m_State;
    bool                    m_PushFlag;
    aqua::CBoxPrimitive     m_FadePlane;
};
