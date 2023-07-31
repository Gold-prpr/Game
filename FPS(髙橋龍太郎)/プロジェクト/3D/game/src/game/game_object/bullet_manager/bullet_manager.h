#pragma once
#include "aqua.h"
#include "bullet\\bullet_id.h"

class CBulletManager
    : public aqua::IGameObject
{
public:
    CBulletManager(aqua::IGameObject* parent);

    ~CBulletManager(void) = default;

    void        Initialize(void) override;

    void        Update(void) override;

    void        Draw(void) override;

    void        Finalize(void) override;

    void        Create(BULLET_ID id);
private:


};
