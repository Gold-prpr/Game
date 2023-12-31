#pragma once
#include "aqua.h"
#include "../../gun/gun.h"
#include "../../enemy_manager/enemy/enemy.h"

class CGun;
class IEnemy;

class IBullet
    : public aqua::IGameObject
{
public:
    IBullet(aqua::IGameObject* parent, const std::string& name);

    virtual ~IBullet(void) = default;

    virtual void Initialize(void);

    void    Update(void);

    void    Draw(void);

    void    Finalize(void);

    void    EnemyColl(void);

protected:
    aqua::CModel m_Bullet;//銃弾のモデル

    aqua::CVector3 m_Posotion;//銃弾の

    aqua::CVector3 m_Rotation;//銃弾の回転

    aqua::CVector3 m_BulletStart;//当たり判定ラインの最初
    aqua::CVector3 m_BulletEnd;//当たり判定ラインの最後

    int m_DamegeNum;//銃弾のダメージ数

    bool m_FireCheck;//銃弾の発射チェック

    MV1_COLL_RESULT_POLY m_HitPolygon;//当たり判定ポリゴン構造体

    aqua::CModelColl m_BulletColl;//銃弾のコリジョン

    CGun* m_pGun;
    IEnemy* m_pEnemy;
};
