#pragma once
#include "../enemy.h"

class CCapsule
    :public IEnemy
{
public:
    CCapsule(aqua::IGameObject* parent);

    ~CCapsule(void) = default;

    void    Initialize(void) override;

    void    Update(void) override;

private:

    int m_FlameIndex;//ƒtƒŒ[ƒ€”Ô†
};