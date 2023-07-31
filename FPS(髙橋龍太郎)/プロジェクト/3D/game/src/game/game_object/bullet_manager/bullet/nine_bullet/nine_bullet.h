#pragma once
#include "../bullet.h"

class CNineBullet
    :public IBullet
{
public:
    CNineBullet(aqua::IGameObject* parent);

    ~CNineBullet(void) = default;

    void    Initialize(void) override;

private:

    int m_FlameIndex;//ƒtƒŒ[ƒ€”Ô†
};