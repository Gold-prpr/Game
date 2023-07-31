#pragma once
#include "aqua.h"
#include "enemy/enemy_id.h"
#include "enemy/enemy.h"

class IEnemy;

class CEnemyManager
    : public aqua::IGameObject
{
public:
    CEnemyManager(aqua::IGameObject* parent);

    ~CEnemyManager(void) = default;

    void        Initialize(void) override;

    void        Update(void) override;

    void        Draw(void) override;

    void        Finalize(void) override;

    void        Create(ENEMY_ID id);

    IEnemy* m_pEnemy;
private:
    aqua::CTimer m_GameTimer;

};
