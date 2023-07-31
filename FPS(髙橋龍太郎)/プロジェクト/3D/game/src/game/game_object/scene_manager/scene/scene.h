
#pragma once

#include "aqua.h"
#include "scene_id.h"

class IScene
    : public aqua::IGameObject
{
public:
    IScene(aqua::IGameObject* parent, const std::string& object_name);

    virtual ~IScene(void) = default;

    void    Change(SCENE_ID id);

    void    Push(SCENE_ID id);

    void    Pop(void);

    void    Reset(void);

private:
    static const std::string    m_scene_category;//シーンのカテゴリー
};
