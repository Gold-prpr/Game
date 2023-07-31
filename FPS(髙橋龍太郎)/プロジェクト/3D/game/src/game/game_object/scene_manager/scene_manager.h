#pragma once

#include "aqua.h"
#include "scene\scene_id.h"

class CSceneManager
    : public aqua::IGameObject
{
public:
    CSceneManager(aqua::IGameObject* parent);

    ~CSceneManager(void) = default;

    void        Initialize(void) override;

    void        Update(void) override;

    void        Draw(void) override;

    void        Finalize(void) override;

    void        Change(SCENE_ID id);

    void        Push(SCENE_ID id);

    void        Pop(void);

    void        Reset(void);

private:
    enum class STATE
    {
        SCENE_IN,
        SCENE_UPDATA,
        SCENE_OUT,
        SCENE_CHANGE,
    };

    void        Create(SCENE_ID id);

    void        Delete(void);

    void        SceneIn(void);

    void        SceneUpdate(void);

    void        SceneOut(void);

    void        SceneChange(void);

    static const float      m_fade_speed;
    SCENE_ID                m_CurrentSceneID;
    SCENE_ID                m_NextSceneID;
    SCENE_ID                m_PushSceneID;
    STATE                   m_State;
    bool                    m_PushFlag;
    aqua::CBoxPrimitive     m_FadePlane;
};
